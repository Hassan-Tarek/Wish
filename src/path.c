#include "../include/path.h"

char *path_list[MAX_PATHS] = { NULL };
size_t paths_count = 0;

static bool is_valid_dir(const char *path) {
    if (!path) 
        return false;
    
    struct stat st;
    if (stat(path, &st) != 0) {
        // path does not exist
        return false;
    }

    return S_ISDIR(st.st_mode);
}

void init_path_list() {
    char *env_path = getenv("PATH");
    if (!env_path) 
        return;

    char *copy = strdup(env_path);
    if (!copy) 
        return;

    char *token = strtok(copy, ":");
    while (token) {
        add_path(token);
        token = strtok(NULL, ":");
    }
    free(copy);
}

void add_path(const char *path) {
    if (!path || paths_count >= MAX_PATHS || !is_valid_dir(path)) 
        return;

    // skip if already exists
    for (size_t i = 0; i < paths_count; i++) {
        if (strcmp(path_list[i], path) == 0)
            return;
    }

    path_list[paths_count] = strdup(path);
    paths_count++;
}

void remove_path(const char *path) {
    if (!path) 
        return;

    for (size_t i = 0; i < paths_count; i++) {
        if (strcmp(path_list[i], path) == 0) {
            free(path_list[i]);
            path_list[i] = NULL;

            // shift remaining paths to left
            for (size_t j = i + 1; j < paths_count; j++) {
                path_list[j - 1] = path_list[j];
            }

             paths_count--;
            path_list[paths_count] = NULL;
            break;
        }
    }
}

void free_path_list() {
    for (size_t i = 0; i < paths_count; i++) {
        if (path_list[i]) {
            free(path_list[i]);
            path_list[i] = NULL;
        }
    }
    paths_count = 0;
}
