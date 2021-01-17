#define _DEFAULT_SOURCE
#define _BSD_SOURCE
#define _GNU_SOURCE

#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

#include "abuf.h"
#include "file.h"
#include "helper.h"

struct file file_init() {
    struct file f;

    f.rows = NULL;
    f.num_rows = 0;
    f.rows_size = 0;

    return f;
}

void file_open(struct file *f, char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) die("fopen");

    char *line = NULL;
    size_t n = 0;
    ssize_t len;
    while ((len = getline(&line, &n, fp)) > 0) {
        while (len > 0 && (line[len-1] == '\n' || line[len-1] == '\r'))
            len--;

        file_add_row(f, line, len);

        free(line);
        line = NULL;
        n = 0;
    }

    fclose(fp);
}

/*
 * Uses abuf under the hood, so row is copied
 */
void file_add_row(struct file *f, char *row, size_t len) {
    if (f->num_rows + 1 > f->rows_size) {
        size_t new_size = (f->num_rows + 1) * 2;
        f->rows = safe_realloc(f->rows, new_size * sizeof(struct abuf));
        f->rows_size = new_size;
    }

    f->rows[f->num_rows] = abuf_init();
    abuf_append(&f->rows[f->num_rows], row, len);
    f->num_rows++;
}

struct abuf *file_get_row(struct file *f, size_t index) {
    return (index < f->num_rows) ? &f->rows[index] : NULL;
}

void file_free(struct file *f) {
    for (size_t i = 0; i < f->num_rows; i++)
        abuf_free(&f->rows[i]);

    free(f->rows);
}
