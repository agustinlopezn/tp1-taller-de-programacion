#include "client_file_reader.h"

void file_reader_init(struct file_reader_t *self, FILE *file) {
    self->file = file;
}

size_t file_reader_read(struct file_reader_t *self,
                        unsigned char *buffer, size_t size) {
    memset(buffer, 0, size);
    return fread(buffer, sizeof(char), size, self->file);
}

bool file_reader_finished(struct file_reader_t *self) {
    return feof(self->file) != 0;
}

void file_reader_uninit(struct file_reader_t *self) {
    self->file = NULL;
}
