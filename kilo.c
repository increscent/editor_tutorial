// DONATE WHEN I'M DONE
// https://viewsourcecode.org/snaptoken/kilo/04.aTextViewer.html

#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

#include "file.h"
#include "helper.h"
#include "input.h"
#include "output.h"
#include "terminal.h"

int main(int argc, char **argv) {
    enable_raw_mode();
    struct terminal_details td = get_terminal_details();
    init_output(td);

    struct file f = file_init();

    if (argc >= 2)
        file_open(&f, argv[1]);

    while (1) {
        editor_refresh_screen(&f);
        editor_process_keypress(&f);
    }

    return 0;
}
