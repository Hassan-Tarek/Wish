#include "error.h"

void print_error_message(const char* error_message) {
    print_message(stderr, "wish: %s\n", error_message);
}

void print_error_message_errno(const char* error_message) {
    print_message(stderr, "wish: %s: %s\n", error_message, strerror(errno));
}

void fatal_error(const char* error_message) {
    print_error_message(error_message);
    _exit(EXIT_FAILURE);
}
