#define _GNU_SOURCE

#ifndef PIPE_H
#define PIPE_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

// Forward declaration to avoid circular dependency
struct CommandGroup;

/**
 * @struct Pipe
 * @brief Represents a pipe with a read and write file descriptor.
 *
 * fd[0] = read end  
 * fd[1] = write end
 */
typedef struct {
    int fd[2];
} Pipe;

/**
 * @brief Creates a new pipe.
 *
 * Allocates a Pipe structure and initializes it using the system call `pipe()`.
 *
 * @return Pointer to the created Pipe, or NULL if allocation/pipe creation fails.
 */
Pipe *create_pipe(void);

/**
 * @brief Closes both ends of a pipe.
 *
 * Safely closes the read and write file descriptors stored in the pipe.
 *
 * @param pipe Pointer to the Pipe to close. No effect if NULL.
 */
void close_pipe(Pipe *pipe);

/**
 * @brief Frees a pipe structure and closes its descriptors.
 *
 * @param pipe Pointer to the Pipe to free. No effect if NULL.
 */
void free_pipe(Pipe *pipe);

/**
 * @brief Applies a pipe between two commands.
 *
 * Redirects the standard output of the previous command into the standard
 * input of the next command using `dup2()`. This is used for command pipelines.
 *
 * @param prev Pointer to the previous command's pipe (output).
 * @param next Pointer to the next command's pipe (input).
 */
void apply_pipe(Pipe *prev, Pipe *next);

/**
 * @brief Closes all pipes in a list of commands.
 *
 * Iterates over a list of commands and closes any pipes associated with them.
 *
 * @param command_group Pointer to the CommandGroup containing commands. 
 */
void close_all_pipes(struct CommandGroup *command_group);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* PIPE_H */
