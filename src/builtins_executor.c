#include "../include/builtins_executor.h"

void execute_builtin_command(Command *command) {
    if (!command || !command->name) return;

    if (strcmp(command->name, "cd") == 0) {
        execute_cd_command(command);
    } else if (strcmp(command->name, "exit") == 0) {
        execute_exit_command(command);
    } else if (strcmp(command->name, "pwd") == 0) {
        execute_pwd_command(command);
    } else if (strcmp(command->name, "echo") == 0) {
        execute_echo_command(command);
    } else if (strcmp(command->name, "export") == 0) {
        execute_export_command(command);
    } else if (strcmp(command->name, "unset") == 0) {
        execute_unset_command(command);
    } else if (strcmp(command->name, "env") == 0) {
        execute_env_command(command);
    } else if (strcmp(command->name, "help") == 0) {
        execute_help_command(command);
    } else {
        print_error_message("Unknown built-in command\n");
    }
}


void execute_cd_command(Command *command) {
    if (!command) return;

    if (command->args_count > 2) {
        print_error_message("cd: too many arguments!");
        return;
    }

    const char *path = command->args_count > 1 ? command->args[1] : getenv("HOME");
    if (chdir(path) != 0) {
        print_error_message("cd: couldn't change dir!");
    }
}

void execute_exit_command(Command *command) {
    if (!command) return;

    int status = 0;
    if (command->args_count > 1 && command->args[1]) {
        status = atoi(command->args[1]);
    }
    exit(status);
}

void execute_pwd_command(Command *command) {
    if (!command) return;

    char cwd[MAX_PATH_LENGTH];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        print_message(stdout, "%s\n", cwd);
    }
}

void execute_echo_command(Command *command) {
    if (!command) return;

    for (int i = 0; i < command->args_count; i++) {
        if (command->args[i][0] == '$') {
            char *env_ret = wish_getenv(command->args[i] + 1);
            if (env_ret)
                print_message(stdout, "%s ", env_ret);
        } else {
            print_message(stdout, "%s ", command->args[i]);
        }
    }
    print_message(stdout, "\n");
}

void execute_export_command(Command *command) {
    if (!command) return;

    for (size_t i = 1; i < command->args_count; i++) {
        char *arg = command->args[i];
        char *equal_sign = strchr(arg, '=');
        if (!equal_sign) {
            print_error_message("export: invalid format, expected NAME=VALUE\n");
            continue;
        }

        // split into name-value
        *equal_sign = '\0';
        char *name = arg;
        char *value = equal_sign + 1;
        if (strcmp(name, "PATH") == 0) {
            if (strncmp(value, "$PATH:", 6) == 0) {
                char *paths_to_add = value + 6; // skip "$PATH:"
                char *token = strtok(paths_to_add, ":");
                while (token) {
                    add_path(token);
                    token = strtok(NULL, ":");
                }
            } else {
                // overwrite existing PATH
                free_path_list();
                char *token = strtok(value, ":");
                while (token) {
                    add_path(token);
                    token = strtok(NULL, ":");
                }
            }
        } else {
            wish_setenv(name, value, 1);
        }
    }
}

void execute_unset_command(Command *command) {
    if (!command || command->args_count < 2) return;

    char *name = command->args[1];
    if (!wish_unsetenv(name)) {
        print_error_message("wish_unsetenv: failed to unset variable\n");
    }
}

void execute_env_command(Command *command) {
    if (!command) return;

    for (char **env = wish_environ; *env != NULL; env++) {
        print_message(stdout, "%s\n", *env);
    }
}

void execute_help_command(Command *command) {
    print_message(stdout, "Supported built-in commands:\n");
    print_message(stdout, "cd [dir]         change directory\n");
    print_message(stdout, "exit             exit the shell\n");
    print_message(stdout, "pwd              print the current directory\n");
    print_message(stdout, "echo [args]      echo arguments\n");
    print_message(stdout, "export NAME=VAL  set environment variable\n");
    print_message(stdout, "unset NAME       unset environment variable\n");
    print_message(stdout, "env              print environment variables\n");
    print_message(stdout, "help             print the help message\n");
}
