#ifndef LINE_PROCESSOR_H
#define LINE_PROCESSOR_H

#include <pthread.h>

#define MAX_LINES 50
#define MAX_LENGTH 1000
#define NUM_BUFFERS 4
#define END_COMMAND "STOP\n"
#define END_CHAR '\3'
#define END_STR "\3"

struct buffer {
    char lines[MAX_LINES][MAX_LENGTH];
    pthread_mutex_t lock;
    pthread_cond_t full;
};

extern struct buffer *buffers[NUM_BUFFERS];

void initialize_buffers(void);
void free_buffers(void);
void write_to_buffer(struct buffer* buf, int line, const char input[]);
void read_from_buffer(struct buffer* buf, int line, char output[]);
void replace_substr(char* str, const char* old, const char* new);
int contains_stop(char* input);
void* input_handler(void* args);
void* line_separator_handler(void* args);
void* plus_sign_handler(void* args);
void* output_handler(void* args);

#endif // LINE_PROCESSOR_H
