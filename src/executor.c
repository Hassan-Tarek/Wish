#include "../include/executor.h"

void execute_command(Command *command) {
    if (!command) return;

    if (command->type == BUILTIN) {
        execute_builtin_command(command);
    } else if (command->type = EXTERNAL) {
        execute_external_command(command);
    } else {
        print_error_message("Unknown command type\n");
    }
}
