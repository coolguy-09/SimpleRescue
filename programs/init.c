#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mount.h>
#include <errno.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/sysmacros.h>

void mountfs() {
    mount("proc", "/proc", "proc", 0, NULL);
    mount("sysfs", "/sys", "sysfs", 0, NULL);
    mount("devtmpfs", "/dev", "devtmpfs", 0, NULL);
}

int main(void) {
    printf("Init started!\n");
    
    mountfs();
    system("bootscreen");
    sleep(5);

    signal(SIGCHLD, SIG_IGN); // optional: ignore child exit signals

    while (1) {
        pid_t pid = fork();
        if (pid == 0) {
            // Child process
            system("clear");
            execl("/bin/sh", "sh", NULL);
            perror("execl failed");
            exit(1);
        } else if (pid > 0) {
            // Parent (PID 1)
            int status;
            waitpid(pid, &status, 0);
            printf("Shell exited with status %d\n", status);
            sleep(1);
        } else {
            perror("fork failed");
            sleep(1);
        }
    }
    
    return 0;
}

