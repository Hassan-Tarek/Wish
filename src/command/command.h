#define _GNU_SOURCE

#ifndef COMMAND_H
#define COMMAND_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../external/external.h"
#include "../redirect/redirect.h"
#include "../pipe/pipe.h"
#include "../util/builtin_type.h"
#include "../error/error.h"

#define MAX_COMMANDS 128
#define MAX_COMMAND_GROUPS 64
#define MAX_ARGS 128
#define MAX_REDIRECTS 5

/**
 * @enum CommandType
 * @brief Defines the type of a command.
 * 
 * - UNDEFINED: Not yet classified
 * - BUILTIN: Built-in shell command
 * - EXTERNAL: External binary
 */
typedef enum {
    UNDEFINED,
    BUILTIN,
    EXTERNAL
} CommandType;

/**
 * @struct Command
 * @brief Represents a single shell command.
 */
typedef struct Command {
    char *name;
    char *args[MAX_ARGS];
    size_t args_count;
    bool background;
    CommandType command_type;
    BuiltinType builtin_type;
    RedirectInfo *redirects[MAX_REDIRECTS];
    Pipe *prev_pipe;
    Pipe *cur_pipe;
} Command;

/**
 * @struct CommandGroup
 * @brief Represents a group of commands connected via pipes.
 */
typedef struct CommandGroup {
    Command **command_list;
    size_t count;
} CommandGroup;

/**
 * @struct CommandGroupList
 * @brief Represents a list of command groups separated by `;`.
 */
typedef struct CommandGroupList {
    CommandGroup **groups;
    size_t count;
} CommandGroupList;


/**
 * @brief Allocate and initialize a new Command.
 * 
 * @return Pointer to the created ::Command, or NULL on failure.
 */
Command *create_command(void);

/**
 * @brief Free a Command and its resources.
 * 
 * @param command Pointer to the ::Command to free.
 */
void free_command(Command *command);

/**
 * @brief Allocate and initialize a new CommandGroup.
 * 
 * @return Pointer to the created ::CommandGroup, or NULL on failure.
 */
CommandGroup *create_command_group(void);

/**
 * @brief Free a CommandGroup and all contained commands.
 * 
 * @param group Pointer to the ::CommandGroup to free.
 */
void free_command_group(CommandGroup *group);

/**
 * @brief Add a Command to a CommandGroup.
 * 
 * @param group Pointer to the ::CommandGroup.
 * @param command Pointer to the ::Command to add.
 */
void add_command(CommandGroup *group, Command *command);

/**
 * @brief Allocate and initialize a new CommandGroupList.
 * 
 * @return Pointer to the created ::CommandGroupList, or NULL on failure.
 */
CommandGroupList *create_command_group_list(void);

/**
 * @brief Free a CommandGroupList and all contained groups/commands.
 * 
 * @param list Pointer to the ::CommandGroupList to free.
 */
void free_command_group_list(CommandGroupList *list);

/**
 * @brief Add a CommandGroup to a CommandGroupList.
 * 
 * @param list Pointer to the ::CommandGroupList.
 * 
 * @param group Pointer to the ::CommandGroup to add.
 */
void add_command_group(CommandGroupList *list, CommandGroup *group);

/**
 * @brief Check if a command name is valid.
 * 
 * @param command_name Command string.
 * 
 * @return true if the command name is valid, false otherwise.
 */
bool is_valid_command(const char *command_name);

/**
 * @brief Determine the type of a command (builtin or external).
 * 
 * @param command_name Command string.
 * 
 * @return The ::CommandType.
 */
CommandType get_command_type(const char *command_name);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* COMMAND_H */
