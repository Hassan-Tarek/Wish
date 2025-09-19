#define _GNU_SOURCE

#ifndef BUILTIN_H
#define BUILTIN_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#include "../util/builtin_type.h"
#include "../error/error.h"
#include "../io/io.h"

// Forward declaration to avoid circular includes.
struct Command;

/**
 * @typedef BuiltinFunc
 * @brief Function pointer type for builtin executors.
 *
 * Each builtin function takes a pointer to a ::Command structure,
 * executes the builtin, and returns an integer exit status.
 *
 * Return codes:
 * - `0` : Success
 * - `1` : General error
 * - `2` : Misuse of builtin (invalid syntax/arguments)
 * - `3` : Command not found
 */
typedef int (*BuiltinFunc)(struct Command *);

/**
 * @struct Builtin
 * @brief Mapping of builtin type to its executor function.
 *
 * Associates a ::BuiltinType with the corresponding ::BuiltinFunc
 * that implements the command’s behavior.
 */
typedef struct {
    const BuiltinType builtin_type; /**< The builtin command type. */
    BuiltinFunc builtin_func;       /**< The function that executes the builtin. */
} Builtin;

/**
 * @brief Checks whether a given command name is a builtin.
 *
 * @param command_name The command name to check.
 * 
 * @return true if the command is a builtin, false otherwise.
 */
bool is_valid_builtin_command(const char *command_name);

/**
 * @brief Resolves the ::BuiltinType of a command name.
 *
 * @param command_name The command name to check.
 * 
 * @return The corresponding ::BuiltinType, or NONE if not recognized.
 */
BuiltinType get_builtin_type(const char *command_name);

/**
 * @brief Executes a builtin command.
 *
 * @param command Pointer to the ::Command representing the builtin invocation.
 * 
 * @return Exit status code (see ::BuiltinFunc return codes).
 */
int execute_builtin_command(struct Command *command);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* BUILTIN_H */
