#include "external.h"
#include "../command/command.h"

bool is_valid_external_command(const char *command_name) {
    if (!command_name || !*command_name)
        return false;

    char *path = find_executable_in_path(command_name);
    if (path) {
        free(path);
        return true;
    }
    return false;
}

int execute_external_command(Command *command) {
    if (!command || !command->args || !command->args[0]) {
        print_error_message("Invalid command");
        return -1;
    }

    pid_t pid = fork();
    if (pid < 0) {
        print_error_message("Failed to fork");
        return -1;
    } else if (pid == 0) {
        // Child process
        execute_external_direct(command);
    } else {
        // Parent process
        if (!command->background) {
            int status;
            waitpid(pid, &status, 0);
            if (WIFEXITED(status)) {
                return WEXITSTATUS(status);
            } else {
                return -1;
            }
        }

        // Background: don't wait
        return 0;
    }
    return -1;
}

void execute_external_direct(Command *command) {
    if (!command || !command->args || !command->args[0]) {
        print_error_message("Invalid command");
    }

    char *executable_path = find_executable_in_path(command->name);
    if (!executable_path) {
        print_error_message("Command not found!");
    }

    execv(executable_path, command->args);

    // If execv fails
    free(executable_path);
    fatal_error("execv failed");
}
