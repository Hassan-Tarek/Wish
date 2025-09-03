#include "io.h"

void print_prompt(void) {
    printf("wish> ");
    fflush(stdout);
}

void print_message(FILE *out, const char *format, ...) {
    if (!out)
        out = stdout;

    va_list args;
    va_start(args, format);
    vfprintf(out, format, args);
    va_end(args);
    fflush(out);
}

char* read_command(void) {
    char* command = NULL;
    size_t len = 0;

    if (getline(&command, &len, stdin) == -1) {
        fatal_error("Failed to read command from stdin!");
    }
    return command;
}

char** read_commands_from_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fatal_error("Can't open file!");
    }

    size_t capacity = INITIAL_CAPACITY;
    char **buffer = malloc(capacity * sizeof(char*));
    if (!buffer) {
        fatal_error("Memory allocation failed!");
    }

    char *line = NULL;
    size_t line_number = 0;
    size_t len = 0;
    ssize_t read = 0;
    while((read = getline(&line, &len, file)) != -1) {
        // remove \n
        if (read > 0 && line[read - 1] == '\n') {
            line[read - 1] = '\0';
        }

        // allocate more memory if needed
        if (line_number >= capacity) {
            capacity *= 2;
            char **temp = realloc(buffer, capacity * sizeof(char*));
            if (!temp) {
                fatal_error("Memory allocation failed!");
            }
            buffer = temp;
        }
        buffer[line_number++] = strdup(line);
    }

    free(line);
    fclose(file);
    buffer[line_number] = NULL;
    return buffer;
}
