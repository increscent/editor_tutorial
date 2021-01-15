#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "abuf.h"

struct abuf abuf_init() {
    struct abuf ab;

    ab.buf = NULL;
    ab.len = 0;
    ab.buf_size = 0;

    return ab;
}

void abuf_append(struct abuf *ab, char *data, size_t len) {
    if (len + ab->len > ab->buf_size) {
        if ((ab->buf = realloc(ab->buf, (len + ab->len) * 2)) == NULL) {
            fprintf(stderr, "abuf: out of memory\n");
            exit(EXIT_FAILURE);
        }
    }

    memcpy(&ab->buf[ab->len], data, len);
    ab->len += len;

    return 0;
}

void abuf_free(struct abuf *ab) {
    free(ab->buf);
}
