#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

typedef struct file_reader_t{
    FILE *file;
}file_reader_t;

void file_reader_init(struct file_reader_t *self, FILE *file);
size_t file_reader_read(struct file_reader_t *self, unsigned char *buffer, size_t size);
bool file_reader_finished(struct file_reader_t *self);
void file_reader_uninit(struct file_reader_t *self);