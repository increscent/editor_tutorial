// DONATE WHEN I'M DONE
// https://viewsourcecode.org/snaptoken/kilo/03.rawInputAndOutput.html

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

int main() {
    enable_raw_mode();
    struct terminal_details td = get_terminal_details();
    init_output(td);

    while (1) {
        editor_refresh_screen();
        editor_process_keypress();
    }

    return 0;
}
