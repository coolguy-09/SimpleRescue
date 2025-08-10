#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

void run_uname_arg(const char *arg, char *buf, size_t size) {
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(1);
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(1);
    } else if (pid == 0) {
        // Child
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        execl("/bin/uname", "uname", arg, NULL);
        perror("execl");
        exit(1);
    } else {
        // Parent
        close(pipefd[1]);
        ssize_t count = read(pipefd[0], buf, size - 1);
        if (count > 0) {
            buf[count] = '\0';
            // Remove newline
            for (int i = 0; i < count; i++) {
                if (buf[i] == '\n') {
                    buf[i] = '\0';
                    break;
                }
            }
        } else {
            buf[0] = '\0';
        }
        close(pipefd[0]);
        wait(NULL);
    }
}

int main() {
    char sysname[128], release[128], machine[128];

    run_uname_arg("-s", sysname, sizeof(sysname));
    run_uname_arg("-r", release, sizeof(release));
    run_uname_arg("-m", machine, sizeof(machine));

    printf("Version: SimpleRescue v0.2\n");
    printf("Kernel Version: %s %s\n", sysname, release);
    printf("Kernel Arch: %s\n", machine);

    return 0;
}

