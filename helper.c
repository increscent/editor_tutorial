#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

/*
 * Error and exit
 */
void die(const char *s) {
    write(STDOUT_FILENO, "\x1b[2J", 4);
    write(STDOUT_FILENO, "\x1b[H", 3);

    perror(s);
    exit(EXIT_FAILURE);
}

int safe(int val, const char *s) {
    if (val == -1)
        die(s);

    return val;
}

void* safe_malloc(size_t size) {
    void *ptr;

    if ((ptr = malloc(size)) == NULL)
        die("malloc");

    return ptr;
}

void* safe_realloc(void *ptr, size_t size) {
    if ((ptr = realloc(ptr, size)) == NULL)
        die("realloc");

    return ptr;
}
