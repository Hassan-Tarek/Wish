#include "env.h"

char **wish_environ = NULL;
size_t wish_environ_count = 0;

void init_wish_environ() {
    extern char **environ;

    size_t count = 0;
    while (environ[count] != NULL) {
        count++;
    }
    wish_environ_count = count;

    wish_environ = malloc((count + 1) * sizeof(char *));
    if (!wish_environ) {
        fatal_error("malloc: couldn't allocate memory for wish environ");
    }

    for (size_t i = 0; i < count; i++) {
        wish_environ[i] = strdup(environ[i]);
        if (!wish_environ[i]) {
            fatal_error("strdup: couldn't duplicate the environ variable");
        }
    }
    wish_environ[count] = NULL;
}

int wish_setenv(const char *name, const char *value, int overwrite) {
    if (!name || !*name || !value) return -1;

    size_t name_len = strlen(name);
    size_t value_len = strlen(value);
    size_t len = name_len + value_len + 2;

    char *entry = malloc(len);
    if (!entry) return -1;
    snprintf(entry, len, "%s=%s", name, value);

    for (size_t i = 0; i < wish_environ_count; i++) {
        if (strncmp(name, wish_environ[i], name_len) == 0 &&
            wish_environ[i][name_len] == '=') {
            if (overwrite) {
                free(wish_environ[i]);
                wish_environ[i] = entry;
            } else {
                free(entry);
            }
            return 0;
        }
    }

    char **new_env = realloc(wish_environ, (wish_environ_count + 2) * sizeof(char *));
    if (!new_env) {
        print_error_message("realloc failed");
        free(entry);
        return -1;
    }

    wish_environ = new_env;
    wish_environ[wish_environ_count] = entry;
    wish_environ[wish_environ_count + 1] = NULL;
    wish_environ_count++;
    return 0;
}

int wish_unsetenv(const char *name) {
    if (!name || !*name) return -1;
    size_t name_len = strlen(name);

    for (size_t i = 0; i < wish_environ_count; i++) {
        if (strncmp(name, wish_environ[i], name_len) == 0 &&
            wish_environ[i][name_len] == '=') {
            free(wish_environ[i]);

            for (size_t j = i + 1; j < wish_environ_count; j++) {
                wish_environ[j - 1] = wish_environ[j];
            }

            wish_environ_count--;
            wish_environ[wish_environ_count] = NULL;
            return 1;
        }
    }
    return 0;
}

char *wish_getenv(const char *name) {
    if (!name || !*name) return NULL;
    size_t name_len = strlen(name);

    for (size_t i = 0; i < wish_environ_count; i++) {
        if (strncmp(name, wish_environ[i], name_len) == 0 &&
            wish_environ[i][name_len] == '=') {
            return wish_environ[i] + name_len + 1;
        }
    }
    return NULL;
}

void free_wish_environ() {
    if (!wish_environ) return;

    for (size_t i = 0; i < wish_environ_count; i++) {
        free(wish_environ[i]);
    }
    free(wish_environ);
    wish_environ = NULL;
    wish_environ_count = 0;
}
