#include "wish.h"

static void signal_child_handler(int signal) {
    (void) signal;

    while (waitpid(-1, NULL, WNOHANG) > 0) 
        ;
}

void init_shell(void) {
    init_wish_environ();
    init_path_list();

    // Reap zombies automatically
    signal(SIGCHLD, signal_child_handler);
}

void run_iterative(void) {
    while (1) {
        print_prompt();
        char *input = read_command();
        Command **command_list = malloc(MAX_COMMANDS * sizeof(Command *));
        size_t commands_count = parse_input(input, command_list, MAX_COMMANDS);
        for (size_t i = 0; i < commands_count; i++) {
            execute_command(command_list[i]);
            free_command(command_list[i]);
        }
        free(input);
        free(command_list);
    }
}

void run_batch(const char *filename) {
    char **buffer = read_commands_from_file(filename);
    for (size_t i = 0; buffer[i] != NULL; i++) {
        Command **command_list = malloc(MAX_COMMANDS * sizeof(Command *));
        size_t commands_count = parse_input(buffer[i], command_list, MAX_COMMANDS);
        for (size_t j = 0; j < commands_count; j++) {
            execute_command(command_list[i]);
            free_command(command_list[i]);
        }
        free(command_list);
    }

    // free batch buffer
    for (size_t line = 0; buffer[line] != NULL; line++) {
        free(buffer[line]);
    }
    free(buffer);
}

void cleanup_shell(void) {

}
