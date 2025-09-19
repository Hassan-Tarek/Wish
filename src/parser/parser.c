#include "parser.h"

static void trim(char *command) {
    if (!command) return;

    int len = strlen(command);
    int start = 0;
    int end = len - 1;

    while (start < len && isspace(command[start])) 
        start++;
    while (end >= start && isspace(command[end])) 
        end--;

    int new_len = end - start + 1;
    if (new_len > 0) {
        memmove(command, command + start, new_len);
    }
    command[new_len] = '\0';
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
    if (strchr(token, '&'))
        command->background = true;
    return command;
}

CommandGroupList *parse_input(char *input) {
    if (!input) 
        return NULL;

    trim(input);

    CommandGroupList *list = create_command_group_list();

    char *segment_save_ptr = NULL;
    char *segment = strtok_r(input, ";", &segment_save_ptr);
    while (segment != NULL) {
        CommandGroup *group = create_command_group();

        char *token_save_ptr = NULL;
        char *token = strtok_r(segment, "|", &token_save_ptr);
        Pipe *prev_pipe = NULL;
        while (token) {
            Command *command = parse_command(token);
            if (!command)
                break;

            command->prev_pipe = prev_pipe;

            char *next = strtok_r(NULL, "|", &token_save_ptr);
            if (next) {
                command->cur_pipe = create_pipe();
                prev_pipe = command->cur_pipe;
                token = next;
            } else {
                command->cur_pipe = NULL;
                token = NULL;
            }
            add_command(group, command);
        }
        segment = strtok_r(NULL, ";", &segment_save_ptr);
        add_command_group(list, group);
    }

    return list;
}
