#include "line_processor.h"
#include <stdlib.h>
#include <string.h>

struct buffer *buffers[NUM_BUFFERS];

void initialize_buffers(void) {
    for (int i = 0; i < NUM_BUFFERS; i++) {
        buffers[i] = calloc(1, sizeof(struct buffer));
        memset(buffers[i]->lines, 0, sizeof(char) * MAX_LINES * MAX_LENGTH);
        buffers[i]->lock = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
        buffers[i]->full = (pthread_cond_t)PTHREAD_COND_INITIALIZER;
    }
}

void free_buffers(void) {
    for (int i = 0; i < NUM_BUFFERS; i++) {
        free(buffers[i]);
    }
}

void write_to_buffer(struct buffer* buf, int line, const char input[]) {
    pthread_mutex_lock(&buf->lock);
    strcpy(buf->lines[line], input);
    pthread_cond_signal(&buf->full);
    pthread_mutex_unlock(&buf->lock);
}

void read_from_buffer(struct buffer* buf, int line, char output[]) {
    pthread_mutex_lock(&buf->lock);
    while (strlen(buf->lines[line]) == 0) {
        pthread_cond_wait(&buf->full, &buf->lock);
    }
    strcpy(output, buf->lines[line]);
    pthread_mutex_unlock(&buf->lock);
}
