#include "../header/error.h"

void print_error_message(const char* error_message) {
    fprintf(stderr, "wish: ");
    perror(error_message);
}

void fatal_error(const char* error_message) {
    print_error_message(error_message);
    exit(1);
}
