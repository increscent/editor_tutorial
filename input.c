#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

#include "helper.h"
#include "input.h"
#include "output.h"
#include "terminal.h"

void editor_process_keypress() {
    long c = editor_read_key();

    switch (c) {
        // ctrl-q
        case ('q' & 0x1f):
            exit(EXIT_SUCCESS);
            break;

        case ARROW_LEFT:
            move_cursor(-1, 0);
            break;
        case ARROW_RIGHT:
            move_cursor(1, 0);
            break;
        case ARROW_UP:
            move_cursor(0, 1);
            break;
        case ARROW_DOWN:
            move_cursor(0, -1);
            break;
        case HOME_KEY:
            move_line(1);
            break;
        case END_KEY:
            move_line(0);
            break;
        case PAGE_UP:
            move_page(1);
            break;
        case PAGE_DOWN:
            move_page(0);
            break;
    }
}
