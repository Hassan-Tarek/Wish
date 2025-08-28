#include "../include/env.h"

char **wish_environ = NULL;
size_t wish_environ_count = 0;

void init_wish_environ() {
    extern char **environ;

    size_t count = 0;
    while (environ[count] != NULL) {
        count++;
    }
    wish_environ_count = count;

    // Allocate space for pointers (+1 for NULL terminator)
    wish_environ = malloc((count + 1) * sizeof(char *));
    if (!wish_environ) {
        fatal_error("malloc: couldn't allocate memory for wish environ");
    }

    // Duplicate environment variables
    for (size_t i = 0; i < count; i++) {
        wish_environ[i] = strdup(environ[i]);
        if (!wish_environ[i]) {
            fatal_error("strdup: couldn't duplicate the environ variable");
        }
    }
    wish_environ[count] = NULL;
}

void free_wish_environ() {
    if (!wish_environ) return;

    for (size_t i = 0; i < wish_environ_count; i++) {
        if (wish_environ[i]) {
            free(wish_environ[i]);
            wish_environ[i] = NULL;
        }
    }
    free(wish_environ);
    wish_environ = NULL;
    wish_environ_count = 0;
}
