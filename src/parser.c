#include "../header/parser.h"

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

    int new_len = end - start;
    for (int i = 0; i < new_len; i++) {
        command[i] = command[start + i];
    }
    command[new_len] = '\0';
}

static void parse_command_name(Command *command, const char *input) {
    if (!command || !input)
        return NULL;
    
    char *copy = strdup(input);
    char *token = strtok(copy, " \t");
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
        if (strcmp(token, "<") == 0 || strcmp(token, ">") == 0 ||
            strcmp(token, "<<") == 0 || strcmp(token, ">>") == 0 ||
            strcmp(token, "&") == 0 || strcmp(token, ";") == 0) {
            break;
        }
        
        command->args[index++] = strdup(token);
        token = strtok(NULL, " \t");
    }

    command->args[index] = NULL;
    command->args_count = index;
    free(copy);
}

static int detect_redirection(const char *input) {
    if (strstr(input, "<<") != NULL) return 3;
    if (strstr(input, ">>") != NULL) return 4;
    if (strchr(input, '<') != NULL) return 1;
    if (strchr(input, '>') != NULL) return 2;
    return 0;
}

static void parse_input_file(Command *command, const char *input) {
    if (!command || !input)
        return;
    
    int type = detect_redirection(input);
    if (type != 1 && type != 3) 
        return;

    char copy = strdup(input);
    char *token = strtok(copy, " \t");
    while (token && strcmp(token, "<") != 0 && strcmp(token, "<<") != 0) {
        token = strtok(NULL, " \t");
    }

    if (token) 
        token = strtok(NULL, " \t");
    command->input_file = strdup(token);
    free(copy);
}

static void parse_output_file(Command *command, const char *input) {
    if (!command || !input)
        return;
    
    int type = detect_redirection(input);
    if (type != 2 && type != 4) 
        return;

    char *copy = strdup(input);
    char *token = strtok(copy, " \t");
    while (token && strcmp(token, ">") != 0 && strcmp(token, ">>") != 0) {
        token = strtok(NULL, " \t");
    }
    if (token) 
        token = strtok(NULL, " \t");
    command->output_file = strdup(token);
    free(copy);
}

static Command *parse_command(const char *token) {
    if (!token) 
        return NULL;
    
    trim(token);

    Command *command = create_command();
    parse_command_name(command, token);
    parse_command_args(command, token);
    parse_input_file(command, token);
    parse_output_file(command, token);
    command->type = get_command_type(command->name);

    if (command->type == BUILTIN)
        command->builtin_type = get_builtin_type(command->name);
    else
        command->builtin_type = NONE;

    return command;
}

ParsedCommands *parse_input(const char *input) {
    if (!input)
        return NULL;
    
    trim(input);

    ParsedCommands *parsed_commands = malloc(sizeof(ParsedCommands));
    if (!parsed_commands)
        fatal_error("Failed to allocate ParsedCommands!");

    parsed_commands->commands = malloc(MAX_COMMANDS * sizeof(Command));
    if (!parsed_commands->commands) {
        free(parsed_commands);
        fatal_error("Failed to allocate commands array!");
    }
    parsed_commands->count = 0;

    char *saveptr;
    char *token = strtok_r(input, "&", &saveptr);
    while (token != NULL && parsed_commands->count < MAX_COMMANDS) {
        Command *command = parse_command(token);
        if (command) {
            command->background = true;
            parsed_commands->commands[parsed_commands->count++] = command;
        }
        token = strtok_r(NULL, "&", &saveptr);
    }

    return parsed_commands;
}


void free_parsed_commands(ParsedCommands *parsed_commands) {
    if (!parsed_commands)
        return;
    
    for (int i = 0; i < parsed_commands->count; i++) {
        free_command(parsed_commands->commands[i]);
    }

    free(parsed_commands->commands);
    free(parsed_commands);
}
