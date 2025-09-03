#include "executor.h"

void execute_command(Command *command) {
    if (!command) return;

    if (command->command_type == BUILTIN) {
        execute_builtin_command(command);
    } else if (command->command_type = EXTERNAL) {
        execute_external_command(command);
    } else {
        print_error_message("Unknown command type\n");
    }
}
