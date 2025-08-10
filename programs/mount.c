#include <stdio.h>
#include <stdlib.h>
#include <sys/mount.h>

int main(int argc, char **argv) {
    if (argc < 4) {
        fprintf(stderr, "Usage: %s <source> <target> <fstype> [flags] [data]\n", argv[0]);
        return 1;
    }

    unsigned long flags = 0;
    if (argc > 4)
        flags = strtoul(argv[4], NULL, 0);

    const char *data = NULL;
    if (argc > 5)
        data = argv[5];

    mount(argv[1], argv[2], argv[3], flags, data);
    return 0;
}

