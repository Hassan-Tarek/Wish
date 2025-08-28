#include "../include/builtins.h"

const char *builtin_names[] = { 
    "cd",
    "exit", 
    "pwd", 
    "echo", 
    "export", 
    "unset", 
    "env", 
    "help"
};
const size_t builtin_count = sizeof(builtin_names) / sizeof(builtin_names[0]);

bool is_valid_builtin_command(const char *command_name) {
    for (int i = 0; i < builtin_count; i++) {
        if (strcmp(command_name, builtin_names[i]) == 0)
            return true;
    }   
    return false;
}

BuiltinType get_builtin_type(const char *command_name) {
    if (!command_name || !is_valid_builtin_command(command_name))
        return NONE;

    for (int i = 0; i < builtin_count; i++) {
        if (strcmp(command_name, builtin_names[i]) == 0)
            return (BuiltinType) i;
    }
    return NONE;
}
