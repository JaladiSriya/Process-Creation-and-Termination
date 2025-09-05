/* -----------------------------------------------------------------------------
 * file: fork_exec_wait.c
 * brief: Demonstrates creating a child with fork(), executing a command with
 *        execvp(), and waiting in the parent with waitpid().
 *
 * build:   gcc -Wall -Wextra -Wpedantic -O2 fork_exec_wait.c -o fork_demo
 * usage:   ./fork_demo [command [arg1 arg2 ...]]
 * example: ./fork_demo ls -l
 *
 * Notes:
 *  - Uses execvp() so arguments are simple (argv-style). If no command is
 *    provided, defaults to: ls -l
 *  - Handles fork/exec/wait errors and EINTR during waitpid().
 *  - Uses _exit() in the child on failure paths (no stdio re-flush).
 * ---------------------------------------------------------------------------*/

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

static int wait_for_child(pid_t child_pid) {
    int status = 0;
    for (;;) {
        pid_t w = waitpid(child_pid, &status, 0);
        if (w == -1) {
            if (errno == EINTR) {
                // Interrupted by a signal; retry wait
                continue;
            }
            perror("waitpid");
            return -1;
        }
        // Successfully waited for our child
        break;
    }

    if (WIFEXITED(status)) {
        int code = WEXITSTATUS(status);
        if (code == 0) {
            printf("Child process has completed.\n");
        } else {
            printf("Child exited with non-zero code: %d\n", code);
        }
    } else if (WIFSIGNALED(status)) {
        printf("Child terminated by signal: %d\n", WTERMSIG(status));
    } else if (WIFSTOPPED(status)) {
        printf("Child was stopped by signal: %d\n", WSTOPSIG(status));
    } else {
        printf("Child ended in an unexpected state (status=%d).\n", status);
    }
    return 0;
}

int main(int argc, char *argv[]) {
    // Provide a sensible default command: ls -l
    char *default_cmd[] = {"ls", "-l", NULL};
    char **cmd_argv = (argc > 1) ? &argv[1] : default_cmd;

    // Print parent PID first; useful for grading logs
    printf("Parent Process ID: %d\n", getpid());

    pid_t pid = fork();
    if (pid < 0) {
        // Creation failed
        perror("fork");
        return EXIT_FAILURE;
    }

    if (pid == 0) {
        // --- Child branch ---
        printf("Child Process ID: %d\n", getpid());
        fflush(stdout); // ensure PID prints even if exec succeeds immediately

        // Replace child image with requested command
        execvp(cmd_argv[0], cmd_argv);

        // Only reached on error; preserve errno for perror
        perror("execvp");
        // Use _exit to avoid flushing stdio buffers twice in a forked child
        _exit(127); // 127 is conventional for "command not found"/exec failure
    }

    // --- Parent branch ---
    if (wait_for_child(pid) != 0) {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
