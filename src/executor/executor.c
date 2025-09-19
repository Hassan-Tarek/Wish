#include "executor.h"
#include "../command/command.h"

int execute_command(Command *command) {
    if (!command) return -1;

    int status = 0;

    FDBackup backup = save_original_fds();
    if (!setup_redirects(command->redirects, MAX_REDIRECTS)) {
        fatal_error("Failed to apply redirects");
    }

    if (command->command_type == BUILTIN) {
        status = execute_builtin_command(command);
    } else if (command->command_type == EXTERNAL) {
        status = execute_external_command(command);  // single command path
    } else {
        status = -1;
        print_error_message("Unknown command type\n");
    }

    restore_original_fds(backup);
    return status;
}

int execute_pipeline(CommandGroup *group) {
    if (!group || group->count == 0) return -1;

    size_t n = group->count;
    pid_t pids[MAX_COMMANDS];

    for (size_t i = 0; i < n; i++) {
        Command *command = group->command_list[i];
        pid_t pid = fork();

        if (pid < 0) {
            fatal_error("fork failed in pipeline");
        } else if (pid == 0) {
            // Child process
            apply_pipe(command->prev_pipe, command->cur_pipe);

            // Close all pipe fds in child
            for (size_t j = 0; j < n - 1; j++) {
                close_pipe(group->command_list[j]->cur_pipe);
            }

            // Redirect files if any
            if (!setup_redirects(command->redirects, MAX_REDIRECTS))
                fatal_error("Failed to apply redirects");

            if (command->command_type == BUILTIN) {
                execute_builtin_command(command);
            } else if (command->command_type == EXTERNAL) {
                execute_external_direct(command);
            } else {
                fatal_error("Unknown command in pipeline\n");
            }
        } else {
            // Parent
            pids[i] = pid;
        }
    }

    // Closes all pipes
    close_all_pipes(group);

    // Wait for all children
    int status = 0;
    for (size_t i = 0; i < n; i++) {
        int wstatus;
        waitpid(pids[i], &wstatus, 0);
        if (i == n - 1 && WIFEXITED(wstatus)) {
            status = WEXITSTATUS(wstatus);
        }
    }

    return status;
}

int execute_command_group_list(CommandGroupList *list) {
    if (!list) return -1;

    int status = 0;
    for (size_t i = 0; i < list->count; i++) {
        CommandGroup *group = list->groups[i];
        if (group->count == 1) {
            status = execute_command(group->command_list[0]);
        } else {
            status = execute_pipeline(group);
        }
    }
    return status;
}
