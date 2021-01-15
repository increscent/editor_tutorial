#ifndef ABUF_H
#define ABUF_H

struct abuf {
    char *buf;
    size_t len;
    size_t buf_size;
};

struct abuf abuf_init();
void abuf_append(struct abuf *ab, char *data, size_t len);
void abuf_free(struct abuf *ab);

#endif
