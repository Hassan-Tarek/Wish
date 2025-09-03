#include "external.h"

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

    char *executable_path = find_executable_in_path(command->name);
    if (!executable_path) {
        print_error_message("Command not found!");
        return -1;
    }

    pid_t pid = fork();
    if (pid < 0) {
        print_error_message("Failed to fork");
        free(executable_path);
        return -1;
    } else if (pid == 0) {
        // Child process
        if (!setup_redirects(command->redirects, MAX_REDIRECTS)) {
            fatal_error("Failed to apply redirects");
        }

        execv(executable_path, command->args);
        fatal_error("execv failed");
    } else {
        // Parent process
        if (!command->background) {
            int status;
            waitpid(pid, &status, 0);
            free(executable_path);
            if (WIFEXITED(status)) {
                return WEXITSTATUS(status);
            } else {
                return -1;
            }
        } else {
            // Background: don't wait
            free(executable_path);
            return 0;
        }
    }

    free(executable_path);
    return -1;
}
