#ifndef OUTPUT_H
#define OUTPUT_H

#include "file.h"
#include "terminal.h"

#define KILO_VERSION "0.0.1"

struct cursor_pos {
    int x;
    int y;
};

void init_output(struct terminal_details td);
void editor_refresh_screen(struct file *f);
void move_cursor(int x_offset, int y_offset);
void move_page(int up);
void move_line(int begin);

#endif
