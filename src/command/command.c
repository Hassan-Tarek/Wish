#include "command.h"
#include "../builtin/builtin.h"

Command *create_command(void) {
    Command *command = malloc(sizeof(Command));
    if (!command)
        fatal_error("Failed to allocate memory for Command!");

    command->name = NULL;
    for (size_t i = 0; i < MAX_ARGS; i++)
        command->args[i] = NULL;
    command->args_count = 0;
    command->background = false;
    command->command_type = UNDEFINED;
    command->builtin_type = NONE;
    for (size_t i = 0; i < MAX_REDIRECTS; i++)
        command->redirects[i] = create_redirect();
    command->prev_pipe = NULL;
    command->cur_pipe = NULL;

    return command;
}

void free_command(Command *command) {
    if (!command) return;

    if (command->name) {
        free(command->name);
        command->name = NULL;
    }
    for (int i = 0; i < MAX_ARGS; i++) {
        if (command->args[i]) {
            free(command->args[i]);
            command->args[i] = NULL;
        }
    }
    for (size_t i = 0; i < MAX_REDIRECTS; i++) {
        free_redirect(command->redirects[i]);
    }
    free_pipe(command->cur_pipe);
    free(command);
}

CommandGroup *create_command_group(void) {
    CommandGroup *group = malloc(sizeof(CommandGroup));
    group->command_list = malloc(sizeof(Command *) * MAX_COMMANDS);
    group->count = 0;
    return group;
}

void free_command_group(CommandGroup *group) {
    if (!group) return;

    for (size_t i = 0; i < group->count; i++) {
        free_command(group->command_list[i]);
    }
    free(group->command_list);
    free(group);
}

void add_command(CommandGroup *group, Command *command) {
    if (!group || !command || group->count >= MAX_COMMANDS) 
        return;

    group->command_list[group->count] = command;
    group->count++;
}

CommandGroupList *create_command_group_list(void) {
    CommandGroupList *list = malloc(sizeof(CommandGroupList));
    list->groups = malloc(sizeof(CommandGroup *) * MAX_COMMAND_GROUPS);
    list->count = 0;
    return list;
}

void free_command_group_list(CommandGroupList *list) {
    if (!list) return;

    for (size_t i = 0; i < list->count; i++) {
        free_command_group(list->groups[i]);
    }
    free(list->groups);
    free(list);
}

void add_command_group(CommandGroupList *list, CommandGroup *group) {
    if (!list || !group || list->count >= MAX_COMMAND_GROUPS)
        return;

    list->groups[list->count] = group;
    list->count++;
}

bool is_valid_command(const char *command_name) {
    if (!command_name) 
        return false;
    return is_valid_builtin_command(command_name) || is_valid_external_command(command_name);
}

CommandType get_command_type(const char *command_name) {
    if (!command_name || !is_valid_command(command_name))
        return UNDEFINED;

    return is_valid_builtin_command(command_name) ? BUILTIN : EXTERNAL;
}
