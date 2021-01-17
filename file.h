#ifndef FILE_H
#define FILE_H

#include "abuf.h"

struct file {
    struct abuf *rows;
    size_t num_rows;
    size_t rows_size;
};

struct file file_init();
void file_open(struct file *f, char *filename);
void file_add_row(struct file *f, char *row, size_t len);
struct abuf *file_get_row(struct file *f, size_t index);
void file_free(struct file *f);

#endif
