#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

#include "helper.h"
#include "terminal.h"

static struct termios original_termios;

char editor_read_key() {
    int nread;
    char c;

    while ((nread = read(STDIN_FILENO, &c, 1)) != 1) {
        if (nread == -1 && errno != EAGAIN)
            die("read");
    }

    if (c == '\x1b') {
        char a = c;
        read(STDIN_FILENO, &a, 1);
        char b = c;
        read(STDIN_FILENO, &b, 1);

        if (a == '[') {
            if (b >= '0' && b <= '1') {
                read(STDIN_FILENO, &c, 1);
                if (c == '~')
                    return b | 0x80;
            } else {
                return b | 0x80;
            }
        }
    }

    return c;
}

void disable_raw_mode() {
    safe(tcsetattr(STDIN_FILENO, TCSAFLUSH, &original_termios), "tcsetattr");
}

void enable_raw_mode() {
    safe(tcgetattr(STDIN_FILENO, &original_termios), "tcgetattr");
    atexit(disable_raw_mode);

    struct termios raw = original_termios;

    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 1;
    raw.c_cflag |= (CS8);
    raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
    raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
    raw.c_oflag &= ~(OPOST);

    safe(tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw), "tcsetattr");
}

int get_cursor_position(int *rows, int *cols) {
    char buf[32];
    unsigned int i = 0;

    if (safe(write(STDOUT_FILENO, "\x1b[6n", 4), "write") != 4)
        return -1;

    while (i < sizeof(buf) - 1) {
        if (read(STDIN_FILENO, &buf[i], 1) != 1)
            break;
        if (buf[i] == 'R')
            break;
        i++;
    }
    buf[i] = '\0';

    if (buf[0] != '\x1b' || buf[1] != '[')
        return -1;
    if (sscanf(&buf[2], "%d;%d", rows, cols) != 2)
        return -1;

    return 0;
}

int get_window_size(int *rows, int *cols) {
    struct winsize ws;

    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0) {
        if (safe(write(STDOUT_FILENO, "\x1b[999C\x1b[999B", 12), "write") != 12)
            return -1;

        return get_cursor_position(rows, cols);
    } else {
        *cols = ws.ws_col;
        *rows = ws.ws_row;
        return 0;
    }
}

struct terminal_details get_terminal_details() {
    struct terminal_details td;

    safe(get_window_size(&td.rows, &td.cols), "get_window_size");

    return td;
}
