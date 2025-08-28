#include "../include/command.h"

Command *command_list[MAX_COMMANDS] = { NULL };

Command *create_command(void) {
    Command *command = malloc(sizeof(Command));
    if (!command)
        fatal_error("Failed to allocate memory for Command!");

    command->name = NULL;
    for (int i = 0; i < MAX_ARGS; i++)
        command->args[i] = NULL;

    command->args_count = 0;
    command->input_file = NULL;
    command->output_file = NULL;
    command->background = false;
    command->type = UNDEFINED;
    command->builtin_type = NONE;

    return command;
}

static void free_command(Command *command) {
    if (!command) return;

    free(command->name);
    command->name = NULL;

    for (int i = 0; i < MAX_ARGS; i++) {
        free(command->args[i]);
        command->args[i] = NULL;
    }

    free(command->input_file);
    command->input_file = NULL;

    free(command->output_file);
    command->output_file = NULL;

    free(command);
}

void free_command_list(void) {
    for (int i = 0; i < MAX_COMMANDS; i++) {
        if (command_list[i]) {
            free_command(command_list[i]);
            command_list[i] = NULL;
        }
    }
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
