#include "../header/builtins.h"

char *path_list[MAX_PATHS] = {"/bin", "/usr/bin"};
const char *builtin_names[] = { "cd", "path", "pwd", "echo", "exit" };
const size_t builtin_count = sizeof(builtin_names) / sizeof(builtin_names[0]);



bool is_valid_builtin_command(const char *command_name) {
    for (int i = 0; i < builtin_count; i++) {
        if (strcmp(command_name, builtin_names[i]) == 0) {
            return true;
        }
    }
        
    return false;
}

BuiltinType get_builtin_type(const char *command_name) {
    if (!command_name || !is_valid_builtin_command(command_name))
        return NONE;

    for (int i = 0; i < builtin_count; i++) {
        if (strcmp(command_name, builtin_names[i]) == 0) {
            return (BuiltinType) i;
        }
    }

    return NONE;
}

void execute_cd_command(Command *command) {
    if (command) {
        if (command->args_count > 2) {
            perror("cd: too many arguments!");
            return;
        }

        const char *path = (command->args_count > 1 && command->args[1]) ? command->args[1] : getenv("HOME");
        if (chdir(path) != 0) {
            perror("cd: couldn't change dir!");
        }
    }
}

void execute_path_command(Command *command) {
    if (command) {
        if (command->args_count == 1) {
            for (int i = 0; i < path_list;);
        }
        for (int i = 0; i < command->args_count; i++) {

        }
    }
}

void execute_pwd_command(Command *command) {
    if (command) {
        char cwd[MAX_PATH_LENGTH];
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            print_message(stdout, "%s\n", cwd);
        }
    }
}

void execute_echo_command(Command *command) {
    if (command) {
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
}

void execute_exit_command(void) {
    exit(0);
}
