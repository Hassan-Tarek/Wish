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
        CommandGroupList *list = parse_input(input);
        execute_command_group_list(list);
        free(input);
        free_command_group_list(list);
    }
}

void run_batch(const char *filename) {
    char **buffer = read_commands_from_file(filename);
    for (size_t i = 0; buffer[i] != NULL; i++) {
        CommandGroupList *list = parse_input(buffer[i]);
        execute_command_group_list(list);
        free_command_group_list(list);
    }

    // free batch buffer
    for (size_t line = 0; buffer[line] != NULL; line++) {
        free(buffer[line]);
    }
    free(buffer);
}

void cleanup_shell(void) {
    free_wish_environ();
    free_path_list();
}
