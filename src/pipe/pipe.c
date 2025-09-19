#include "pipe.h"
#include "../command/command.h"

Pipe *create_pipe(void) {
    Pipe *p = malloc(sizeof(Pipe));
    if (!p)
        fatal_error("Failed to allocate memory for Pipe!");

    p->fd[0] = p->fd[1] = -1;

    if (pipe(p->fd) == -1)
        fatal_error("Failed to create pipe!");

    return p;
}

void close_pipe(Pipe *pipe) {
    if (!pipe) return;

    if (pipe->fd[0] != -1) {
        close(pipe->fd[0]);
        pipe->fd[0] = -1;
    }
    if (pipe->fd[1] != -1) {
        close(pipe->fd[1]);
        pipe->fd[1] = -1;
    }
}

void free_pipe(Pipe *pipe) {
    if (!pipe) return;
    close_pipe(pipe);
    free(pipe);
}

void apply_pipe(Pipe *prev, Pipe *cur) {
    if (prev && prev->fd[0] != -1) {
        if (dup2(prev->fd[0], STDIN_FILENO) == -1)
            fatal_error("dup2 failed for stdin");
        close(prev->fd[0]);
        close(prev->fd[1]);
    }

    if (cur && cur->fd[1] != -1) {
        if (dup2(cur->fd[1], STDOUT_FILENO) == -1)
            fatal_error("dup2 failed for stdout");
        close(cur->fd[0]);
        close(cur->fd[1]);
    }
}

void close_all_pipes(CommandGroup *command_group) {
    if (!command_group) return;

    for (size_t i = 0; i < command_group->count; i++) {
        if (command_group->command_list[i] && command_group->command_list[i]->cur_pipe) {
            close_pipe(command_group->command_list[i]->cur_pipe);
        }
    }
}
