#include "command.h"

Command *create_command(void) {
    Command *command = malloc(sizeof(Command));
    if (!command)
        fatal_error("Failed to allocate memory for Command!");

    command->name = NULL;
    for (size_t i = 0; i < MAX_ARGS; i++)
        command->args[i] = NULL;
    command->args_count = 0;
    command->background = false;
    command->command_type = UNDEFINED;
    command->builtin_type = NONE;
    for (size_t i = 0; i < MAX_REDIRECTS; i++)
        command->redirects[i] = create_redirect();

    return command;
}

void free_command(Command *command) {
    if (!command) return;

    free(command->name);
    command->name = NULL;
    for (int i = 0; i < MAX_ARGS; i++) {
        free(command->args[i]);
        command->args[i] = NULL;
    }
    for (size_t i = 0; i < MAX_REDIRECTS; i++) {
        free_redirect(command->redirects[i]);
    }
    free(command);
}

bool is_valid_command(const char *command_name) {
    if (!command_name) 
        return false;
    return is_valid_builtin_command(command_name) || is_valid_external_command(command_name);
}

CommandType get_command_type(const char *command_name) {
    if (!command_name || !is_valid_command(command_name))
        return UNDEFINED;

    return is_valid_builtin_command(command_name) ? BUILTIN : EXTERNAL;
}
