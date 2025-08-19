#include "../header/command.h"
#include "../header/error.h"

Command *create_command(void) {
    Command* command = malloc(sizeof(Command));
    if (!command) {
        fatal_error("Failed to allocate memory for Command!");
    }

    command->name = malloc(MAX_NAME_LENGTH * sizeof(char));
    if (!command->name) {
        fatal_error("Failed to allocate memory for command name!");
    }

    for (int i = 0; i < MAX_ARGS; i++) {
        command->args[i] = malloc(MAX_ARG_LENGTH * sizeof(char));
        if (!command->args[i]) {
            fatal_error("Failed to allocate memory for args!");
        }
    }
    command->args_count = 0;

    command->input_file = malloc(MAX_FILE_LENGTH * sizeof(char));
    command->output_file = malloc(MAX_FILE_LENGTH * sizeof(char));
    if (!command->input_file || !command->output_file) {
        fatal_error("Failed to allocate memory for input/output files!");
    }

    command->background = false;
    command->type = UNDEFINED;
    command->builtin_type = NONE;

    return command;
}


void free_command(Command *command) {
    if (command) {
        if (command->name)
            free(command->name);

        if (command->args) {
            for (int i = 0; i < MAX_ARGS; i++) {
                if (command->args[i]) {
                    free(command->args[i]);
                }
            }
        }

        if (command->input_file)
            free(command->input_file);
        if (command->output_file)
            free(command->output_file);

        free(command);
    }
}

bool is_valid_command(const char *command_name) {
    return is_valid_builtin_command(command_name) || is_valid_external_command(command_name);
}

CommandType get_command_type(const char *command_name) {
    if (!command_name || !is_valid_command(command_name))
        return UNDEFINED;

    return is_valid_builtin_command(command_name) ? BUILTIN : EXTERNAL;
}
