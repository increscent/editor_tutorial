#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

#include "abuf.h"
#include "file.h"
#include "helper.h"
#include "output.h"

static struct terminal_details td;
static struct cursor_pos cp;

void init_output(struct terminal_details terminal_details) {
    td = terminal_details;

    cp.x = 0;
    cp.y = 0;
}

int max(int a, int b) { return a > b ? a : b; }
int min(int a, int b) { return a < b ? a : b; }

void move_line(int begin) {
    if (begin)
        move_cursor(-1 * td.cols, 0);
    else
        move_cursor(td.cols, 0);
}

void move_page(int up) {
    if (up)
        move_cursor(0, td.rows);
    else
        move_cursor(0, -1 * td.rows);
}

void move_cursor(int x_offset, int y_offset) {
    cp.x = max(0, min(cp.x + x_offset, td.cols-1));
    cp.y = max(0, min(cp.y - y_offset, td.rows-1));
}

void editor_draw_rows(struct abuf *ab, struct file *f) {
    int y;
    for (y = 0; y < td.rows; y++) {

        struct abuf *row;
        if ((row = file_get_row(f, y)) != NULL) {
            abuf_append(ab, row->buf, min(row->len, td.cols));
        } else if (f->num_rows == 0 && y == td.rows / 3) {
            char welcome[80];
            int welcomelen = snprintf(welcome, sizeof(welcome),
                        "Kilo editor -- version %s", KILO_VERSION);

            if (welcomelen > td.cols)
                welcomelen = td.cols;

            int padding = (td.cols - welcomelen) / 2;

            if (padding) {
                abuf_append(ab, "~", 1);
                padding--;
            }

            while (padding--)
                abuf_append(ab, " ", 1);

            abuf_append(ab, welcome, welcomelen);
        } else {
            abuf_append(ab, "~", 1);
        }

        // clear rest of line
        abuf_append(ab, "\x1b[K", 3);

        if (y < td.rows - 1)
            abuf_append(ab, "\r\n", 2);
    }
}

void editor_refresh_screen(struct file *f) {
    struct abuf ab = abuf_init();

    // hide cursor
    abuf_append(&ab, "\x1b[?25l", 6);
    // position cursor at (1, 1)
    abuf_append(&ab, "\x1b[H", 3);

    editor_draw_rows(&ab, f);

    // move cursor
    char buf[32];
    int len = snprintf(buf, sizeof(buf), "\x1b[%d;%dH", cp.y + 1, cp.x + 1);
    abuf_append(&ab, buf, len);

    // show cursor
    abuf_append(&ab, "\x1b[?25h", 6);

    safe(write(STDOUT_FILENO, ab.buf, ab.len), "write");
    abuf_free(&ab);
}
