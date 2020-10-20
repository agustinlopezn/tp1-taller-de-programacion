#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

typedef struct file_reader_t {
    FILE *file;
}file_reader_t;

// Initializes the file reader 
void file_reader_init(struct file_reader_t *self, FILE *file);

// Clears the buffer, reads from the file and returns the bytes readed
size_t file_reader_read(struct file_reader_t *self,
                        unsigned char *buffer, size_t size);

// Returns true if the end of file is reached
bool file_reader_finished(struct file_reader_t *self);

// Puts the file pointer to NULL
void file_reader_uninit(struct file_reader_t *self);
