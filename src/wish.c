#include "wish.h"
#include "io.h"
#include "parser.h"
#include "executor.h"
#include "builtins.h"
#include "redirect.h"

int main(int argc, char* argv[], char* envp[]) {
    init_shell();
    run_shell();
    cleanup_shell();
    return 0;
}

void init_shell(void) {

}

void run_shell(void) {

}

void cleanup_shell(void) {

}
