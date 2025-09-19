#include "wish/wish.h"

int main(int argc, char* argv[], char* envp[]) {
    init_shell();
    if (argc == 1) {
        run_iterative();
    } else if (argc > 1) {
        char *file = argv[1];
        run_batch(file);
    }
    cleanup_shell();
    return 0;
}
