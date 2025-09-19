#define _GNU_SOURCE

#ifndef FD_BACKUP_H
#define FD_BACKUP_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <unistd.h>
#include <stdlib.h>

/**
 * Structure used to store copies of the standard
 * file descriptors (stdin, stdout, stderr).
 */
typedef struct {
    int stdin_fd;
    int stdout_fd;
    int stderr_fd;
} FDBackup;

/**
 * @brief Saves the current standard file descriptors.
 * 
 * Saves the current standard file descriptors (stdin, stdout, stderr).
 *
 * @return FDBackup struct containing copies of the original file descriptors.
 */
FDBackup save_original_fds();

/**
 * @brief Restores the standard file descriptors from a backup.
 * 
 * Restores the standard file descriptors (stdin, stdout, stderr)
 * from a previously saved backup.
 *
 * @param backup The FDBackup struct containing saved file descriptors.
 */
void restore_original_fds(FDBackup backup);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* FD_BACKUP_H */
