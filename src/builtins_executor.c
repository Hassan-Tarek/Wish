#include "../include/builtins_executor.h"

void execute_cd_command(Command *command) {
    if (!command) return;

    if (command->args_count > 2) {
        perror("cd: too many arguments!");
        return;
    }

    const char *path = command->args_count > 1 ? command->args[1] : getenv("HOME");
    if (chdir(path) != 0) {
        perror("cd: couldn't change dir!");
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
            char *env_ret = getenv(command->args[i] + 1);
            if (env_ret)
                print_message(stdout, "%s ", env_ret);
        } else {
            print_message(stdout, "%s ", command->args[i]);
        }
    }
    print_message(stdout, "\n");
}

void execute_export_command(Command *command) {

}

void execute_unset_command(Command *command) {

}

void execute_env_command(Command *command) {
    if (!command) return;

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
