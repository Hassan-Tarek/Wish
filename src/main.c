#include "wish/wish.h"

int main(int argc, char* argv[], char* envp[]) {
    init_shell();
    run_shell();
    cleanup_shell();

    printf("%s\n", getenv("PATH"));

    fprintf(stdout, "Supported built-in commands:\n");
    fprintf(stdout, "cd [dir]         change directory\n");
    fprintf(stdout, "exit             exit the shell\n");
    fprintf(stdout, "pwd              print the current directory\n");
    fprintf(stdout, "echo [args]      echo arguments\n");
    fprintf(stdout, "export NAME=VAL  set environment variable\n");
    fprintf(stdout, "unset NAME       unset environment variable\n");
    fprintf(stdout, "env              print environment variables\n");
    fprintf(stdout, "help             print the help message\n");

    char *env = getenv("env");
    printf("%s\n", env);
    return 0;
}
