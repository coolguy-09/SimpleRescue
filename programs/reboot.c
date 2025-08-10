#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    execl("/bin/reboot_service", "reboot_service", "-f", NULL);
    perror("execl failed");
    return 1;
}

