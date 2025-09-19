#include "fd_backup.h"

FDBackup save_original_fds() {
    FDBackup original_fds = {
        .stdin_fd = dup(STDIN_FILENO),
        .stdout_fd = dup(STDOUT_FILENO),
        .stderr_fd = dup(STDERR_FILENO)
    };
    return original_fds;
}

void restore_original_fds(FDBackup backup) {
    if (backup.stdin_fd != -1) {
        dup2(backup.stdin_fd, STDIN_FILENO);
        close(backup.stdin_fd);
    }
    if (backup.stdout_fd != -1) {
        dup2(backup.stdout_fd, STDOUT_FILENO);
        close(backup.stdout_fd);
    }
    if (backup.stderr_fd != -1) {
        dup2(backup.stderr_fd, STDERR_FILENO);
        close(backup.stderr_fd);
    }
}
