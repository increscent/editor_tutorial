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
    char c = editor_read_key();

    switch (c) {
        // ctrl-q
        case ('q' & 0x1f):
            exit(EXIT_SUCCESS);
            break;

        case 'h':
        case 'D' | (char)0x80: // left arrow
            move_cursor(-1, 0);
            break;
        case 'l':
        case 'C' | (char)0x80: // right arrow
            move_cursor(1, 0);
            break;
        case 'k':
        case 'A' | (char)0x80: // up arrow
            move_cursor(0, 1);
            break;
        case 'j':
        case 'B' | (char)0x80: // down arrow
            move_cursor(0, -1);
            break;
        case '5' | (char)0x80: // page up
            move_page(1);
            break;
        case '6' | (char)0x80: // page down
            move_page(0);
            break;
    }
}
