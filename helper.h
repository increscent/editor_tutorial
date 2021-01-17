#ifndef HELPER_H
#define HELPER_H

void die(const char *s);
int safe(int val, const char *s);
void* safe_malloc(size_t size);
void* safe_realloc(void *ptr, size_t size);

#endif
