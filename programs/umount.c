#include <stdio.h>
#include <stdlib.h>
#include <sys/mount.h>

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <target>\n", argv[0]);
        return 1;
    }

    umount(argv[1]);
    return 0;
}

