#include "path.h"

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
    char *env_path = wish_getenv("PATH");
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
    for (size_t i = 0; i < paths_count; i++)
        if (strcmp(path_list[i], path) == 0)
            return;
    path_list[paths_count] = strdup(path);
    paths_count++;
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

char *find_executable_in_path(const char *command_name) {
    if (!command_name || !*command_name) 
        return NULL;

    // If command contains '/'
    if (strchr(command_name, '/')) {
        if (access(command_name, X_OK) == 0) {
            return strdup(command_name);
        } else {
            return NULL;
        }
    }

    for (size_t i = 0; i < paths_count; i++) {
        char fullpath[MAX_PATH_LENGTH];
        snprintf(fullpath, sizeof(fullpath), "%s/%s", path_list[i], command_name);
        if (access(fullpath, X_OK) == 0) {
            return strdup(fullpath);
        }
    }
    return NULL;
}
