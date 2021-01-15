#ifndef TERMINAL_H
#define TERMINAL_H

struct terminal_details {
    int rows;
    int cols;
};

char editor_read_key();
void disable_raw_mode();
void enable_raw_mode();
struct terminal_details get_terminal_details();

#endif
