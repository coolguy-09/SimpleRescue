#include <stdio.h>
#include <unistd.h>

int main() {
    // ANSI escape codes for colors
    // Light gray background = 47 (white background is 47, light gray is close enough)
    // Black text = 30
    // Clear screen and home cursor = \033[2J\033[H

    // Clear screen + home cursor
    printf("\033[2J\033[H");

    // Set background light gray and text black
    printf("\033[47m\033[30m");

    // Get terminal size (optional, fallback to 80x24)
    int cols = 80, rows = 24;

    // Try to get terminal size with ioctl, fallback if fails
    #ifdef TIOCGWINSZ
    #include <sys/ioctl.h>
    #include <unistd.h>
    struct winsize ws;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == 0) {
        cols = ws.ws_col;
        rows = ws.ws_row;
    }
    #endif

    const char *msg = "Booting SystemRescue...";

    // Calculate position for roughly center text horizontally & vertically
    int xpos = (cols - (int)strlen(msg)) / 2;
    int ypos = rows / 2;

    // Move cursor to ypos; xpos
    printf("\033[%d;%dH", ypos, xpos);

    // Print message
    printf("%s", msg);

    // Reset colors
    printf("\033[0m\n");

    return 0;
}

