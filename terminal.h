#ifndef TERMINAL_H
#define TERMINAL_H

struct terminal_details {
    int rows;
    int cols;
};

enum editor_key {
    ARROW_LEFT = 256,
    ARROW_RIGHT,
    ARROW_UP,
    ARROW_DOWN,
    DELETE_KEY,
    HOME_KEY,
    END_KEY,
    PAGE_UP,
    PAGE_DOWN
};

long editor_read_key();
void disable_raw_mode();
void enable_raw_mode();
struct terminal_details get_terminal_details();

#endif
