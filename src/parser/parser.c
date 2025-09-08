#include "parser.h"

static void trim(char *command) {
    if (!command)
        return;

    int len = strlen(command);
    int start = 0;
    int end = len - 1;
    while (start < len && isspace(command[start])) 
        start++;
    while (end > start && isspace(command[end]))
        end--;

    memmove(command, command + start, end - start + 1);
    command[end + start + 1] = '\0';
}

static bool is_redirect(const char *token) {
    return token && (!strcmp(token, "<") || !strcmp(token, ">") ||
                     !strcmp(token, ">>") || !strcmp(token, "2>") ||
                     !strcmp(token, "2>>"));
}

static void parse_command_name(Command *command, const char *input) {
    if (!command || !input)
        return;
    
    char *copy = strdup(input);
    char *token = strtok(copy, " \t");
    if (token)
        command->name = strdup(token);
    free(copy);
}

static void parse_command_args(Command *command, const char *input) {
    if (!command || !input)
        return;

    int index = 0;
    // command->args[index] = strdup(command->name);
    // index++;

    char *copy = strdup(input);
    char *token = strtok(copy, " \t");
    while (token && index < MAX_ARGS - 1) {
        if (is_redirect(token) || !strcmp(token, "&") || !strcmp(token, ";")) {
            break;
        }
        
        command->args[index] = strdup(token);
        index++;
        token = strtok(NULL, " \t");
    }

    command->args[index] = NULL;
    command->args_count = index;
    free(copy);
}

static void parse_redirects(Command *command, const char *input) {
    if (!command || !input)
        return;

    char *copy = strdup(input);
    char *save_ptr = NULL;
    char *token = strtok_r(copy, " \t", &save_ptr);
    while (token) {
        if (is_redirect(token)) {
            char *target = strtok_r(NULL, " \t", &save_ptr);
            if (strcmp(token, "<") == 0) {
                if (target) {
                    if (command->redirects[0]->file) {
                        free(command->redirects[0]->file);
                        command->redirects[0]->file = NULL;
                    }
                    command->redirects[0]->file = strdup(target);
                    command->redirects[0]->redirect_type = REDIR_INPUT;
                }
            } else if (strcmp(token, ">") == 0) {
                if (target) {
                    if (command->redirects[1]->file) {
                        free(command->redirects[1]->file);
                        command->redirects[1]->file = NULL;
                    }
                    command->redirects[1]->file = strdup(target);
                    command->redirects[1]->redirect_type = REDIR_OUTPUT;
                }
            } else if (strcmp(token, ">>") == 0) {
                if (target) {
                    if (command->redirects[2]->file) {
                        free(command->redirects[2]->file);
                        command->redirects[2]->file = NULL;
                    }
                    command->redirects[2]->file = strdup(target);
                    command->redirects[2]->redirect_type = REDIR_OUTPUT_APPEND;
                }
            } else if (strcmp(token, "2>") == 0) {
                if (target) {
                    if (command->redirects[3]->file) {
                        free(command->redirects[3]->file);
                        command->redirects[3]->file = NULL;
                    }
                    command->redirects[3]->file = strdup(target);
                    command->redirects[3]->redirect_type = REDIR_ERROR;
                }
            } else if (strcmp(token, "2>>") == 0) {
                if (target) {
                    if (command->redirects[4]->file) {
                        free(command->redirects[4]->file);
                        command->redirects[4]->file = NULL;
                    }
                    command->redirects[4]->file = strdup(target);
                    command->redirects[4]->redirect_type = REDIR_ERROR_APPEND;
                }
            }
        }
        token = strtok_r(NULL, " \t", &save_ptr);
    }

    free(copy);
}

static Command *parse_command(char *token) {
    if (!token) 
        return NULL;
    
    trim(token);

    Command *command = create_command();
    parse_command_name(command, token);
    parse_command_args(command, token);
    parse_redirects(command, token);
    command->command_type = get_command_type(command->name);
    if (command->command_type == BUILTIN)
        command->builtin_type = get_builtin_type(command->name);
    else
        command->builtin_type = NONE;
    return command;
}

int parse_input(char *input, const Command **command_list, const size_t max_commands) {
    if (!input || !command_list)
        return 0;
    
    trim(input);

    size_t index = 0;
    char *save_ptr;
    char *token = strtok_r(input, "&", &save_ptr);
    while (token != NULL && index < max_commands) {
        Command *command = parse_command(token);
        if (command) {
            command->background = true;
            command_list[index++] = command;
        }
        token = strtok_r(NULL, "&", &save_ptr);
    }

    return index;
}
