#include "builtin.h"
#include "../command/command.h"

static const char *builtin_names[] = {
    "cd", 
    "exit", 
    "pwd", 
    "echo", 
    "export", 
    "unset", 
    "env", 
    "help", 
    NULL
};

static int execute_cd_command(Command *command) {
    if (!command) return 1;

    if (command->args_count > 2) {
        print_error_message("cd: too many arguments\n");
        return 2;
    }

    const char *home = wish_getenv("HOME");
    const char *path = command->args_count > 1 ? command->args[1] : (home ? home : "/");
    if (chdir(path) != 0) {
        print_error_message_errno("cd: no such file or directory\n");
        return 1;
    }

    return 0;
}

static int execute_exit_command(Command *command) {
    if (!command) return 1;

    int status = 0;
    if (command->args_count > 1 && command->args[1])
        status = atoi(command->args[1]);
        
    exit(status);
}

static int execute_pwd_command(Command *command) {
    if (!command) return 1;
    
    char cwd[MAX_PATH_LENGTH];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        FILE *out = stdout;
        if ((command->redirects[3] && command->redirects[3]->file) ||
            (command->redirects[4] && command->redirects[4]->file)) {
            out = stderr;
        }

        print_message(out, "%s\n", cwd);
        return 0;
    } else {
        print_error_message_errno("pwd: failed to get current directory\n");
        return 1;
    }
}

static int execute_echo_command(Command *command) {
    if (!command) return 1;

    FILE *out = stdout;
    if ((command->redirects[3] && command->redirects[3]->file) ||
        (command->redirects[4] && command->redirects[4]->file)) {
        out = stderr;
    }
    for (size_t i = 1; i < command->args_count; i++) {
        if (command->args[i][0] == '$') {
            char *env_ret = wish_getenv(command->args[i] + 1);
            if (env_ret)
                print_message(out, "%s ", env_ret);
        } else {
            print_message(out, "%s ", command->args[i]);
        }
    }
    print_message(out, "\n");
    return 0;
}

static int execute_export_command(Command *command) {
    if (!command) return 1;

    for (size_t i = 1; i < command->args_count; i++) {
        char *arg_copy = strdup(command->args[i]);
        if (!arg_copy) continue;

        char *equal_sign = strchr(arg_copy, '=');
        if (!equal_sign) {
            print_error_message("export: invalid format, expected NAME=VALUE\n");
            free(arg_copy);
            return 2;
        }

        *equal_sign = '\0';
        char *name = arg_copy;
        char *value = equal_sign + 1;
        if (strcmp(name, "PATH") == 0) {
            if (strncmp(value, "$PATH:", 6) == 0) {
                char *paths_to_add = value + 6;
                char *token = strtok(paths_to_add, ":");
                while (token) {
                    add_path(token);
                    token = strtok(NULL, ":");
                }
            } else {
                free_path_list();
                char *token = strtok(value, ":");
                while (token) {
                    add_path(token);
                    token = strtok(NULL, ":");
                }
            }
        } else {
            if (wish_setenv(name, value, 1) != 0) {
                print_error_message("export: failed to set variable\n");
                free(arg_copy);
                return 1;
            }
        }

        free(arg_copy);
    }

    return 0;
}

static int execute_unset_command(Command *command) {
    if (!command || command->args_count < 2) return 2;

    char *name = command->args[1];
    if (!wish_unsetenv(name)) {
        print_error_message("unset: failed to unset variable\n");
        return 1;
    }

    return 0;
}

static int execute_env_command(Command *command) {
    (void) command;

    for (char **env = wish_environ; *env != NULL; env++)
        print_message(stdout, "%s\n", *env);

    return 0;
}

static int execute_help_command(Command *command) {
    (void) command;
    print_message(stdout, "Supported built-in commands:\n");
    print_message(stdout, "cd [dir]         change directory\n");
    print_message(stdout, "exit             exit the shell\n");
    print_message(stdout, "pwd              print the current directory\n");
    print_message(stdout, "echo [args]      echo arguments\n");
    print_message(stdout, "export NAME=VAL  set environment variable\n");
    print_message(stdout, "unset NAME       unset environment variable\n");
    print_message(stdout, "env              print environment variables\n");
    print_message(stdout, "help             print the help message\n");
    return 0;
}

static const Builtin builtins[] = {
    {CD, execute_cd_command},
    {EXIT, execute_exit_command},
    {PWD, execute_pwd_command},
    {ECHO, execute_echo_command},
    {EXPORT, execute_export_command},
    {UNSET, execute_unset_command},
    {ENV, execute_env_command},
    {HELP, execute_help_command},
    {NONE, NULL}
};

bool is_valid_builtin_command(const char *command_name) {
    if (!command_name) 
        return false;
    for (size_t i = 0; builtin_names[i] != NULL; i++)
        if (strcmp(command_name, builtin_names[i]) == 0) 
            return true;
    return false;
}

BuiltinType get_builtin_type(const char *command_name) {
    if (!command_name)
        return NONE;
    for (size_t i = 0; builtin_names[i] != NULL; i++)
        if (strcmp(command_name, builtin_names[i]) == 0)
            return (BuiltinType)(i + 1);  // +1 because NONE = 0
    return NONE;
}

int execute_builtin_command(Command *command) {
    if (!command || !command->name) 
        return 3;  // command not found

    for (size_t i = 0; builtins[i].builtin_type != NONE; i++) {
        if (builtins[i].builtin_type == command->builtin_type) {
            builtins[i].builtin_func(command);
            return 0;
        }
    }
    print_error_message("Unknown built-in command\n");
    return 3;
}
