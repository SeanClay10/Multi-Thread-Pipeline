#include "line_processor.h"
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

void* input_handler(void* args) {
    char input[MAX_LENGTH] = {0};
    int line = 0;
    int pos = -1;
    bool running = true;
    bool stop_detected = false;

    while (running && line < MAX_LINES) {
        if (fgets(input, MAX_LENGTH, stdin) == NULL) {
            break;
        }
        pos = contains_stop(input);
        if (pos != -1) {
            input[pos] = END_CHAR;
            stop_detected = true;
        }
        write_to_buffer(buffers[0], line, input);
        if (stop_detected) {
            running = false;
        }
        line += 1;
    }
    return NULL;
}

void* line_separator_handler(void* args) {
    int line = 0;
    char input[MAX_LENGTH] = {0};
    bool running = true;
    bool stop_detected = false;

    while (running) {
        read_from_buffer(buffers[0], line, input);
        if (strstr(input, END_STR) != NULL) {
            stop_detected = true;
        }
        replace_substr(input, "\n", " ");
        write_to_buffer(buffers[1], line, input);
        if (stop_detected) {
            running = false;
        }
        line += 1;
    }
    return NULL;
}

void* plus_sign_handler(void* args) {
    bool running = true;
    bool stop_detected = false;
    int line = 0;
    char input[MAX_LENGTH] = {0};

    while (running) {
        read_from_buffer(buffers[1], line, input);
        if (strstr(input, END_STR) != NULL) {
            stop_detected = true;
        }
        replace_substr(input, "++", "^");
        write_to_buffer(buffers[2], line, input);
        if (stop_detected) {
            running = false;
        }
        line += 1;
    }
    return NULL;
}

void* output_handler(void* args) {
    char total_output[MAX_LINES * MAX_LENGTH] = {0};
    char output[81] = {0};
    int remaining_chars = 80;
    int i = 0;
    int j = 0;
    bool running = true;
    bool stop_detected = false;
    int line = 0;
    char input[MAX_LENGTH] = {0};

    while (running) {
        read_from_buffer(buffers[2], line, input);
        strcat(total_output, input);
        if (strstr(input, END_STR) != NULL) {
            stop_detected = true;
        }
        while (j < strlen(total_output) && total_output[j] != END_CHAR) {
            output[i] = total_output[j];
            i += 1;
            j += 1;
            remaining_chars -= 1;
            if (remaining_chars == 0) {
                printf("%s\n", output);
                fflush(stdout);
                memset(output, 0, 81);
                i = 0;
                remaining_chars = 80;
            }
        }
        if (stop_detected) {
            running = false;
        }
        line += 1;
    }
    return NULL;
}
