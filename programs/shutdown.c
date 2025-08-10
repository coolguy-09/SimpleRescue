#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    execl("/bin/shutdown_service", "shutdown_service", "-f", NULL);
    perror("execl failed");
    return 1;
}

