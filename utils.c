#include "line_processor.h"
#include <string.h>
#include <ctype.h>

void replace_substr(char* str, const char* old, const char* new) {
    char temp[MAX_LENGTH] = {0};
    char *pos = &temp[0];
    const char *curr = str;
    size_t len_old = strlen(old);
    size_t len_new = strlen(new);

    while (1) {
        const char *found = strstr(curr, old);
        if (!found) {
            strcpy(pos, curr);
            break;
        }
        memcpy(pos, curr, found - curr);
        pos += found - curr;
        memcpy(pos, new, len_new);
        pos += len_new;
        curr = found + len_old;
    }
    strcpy(str, temp);
}

int contains_stop(char* input) {
    char* pos = strstr(input, END_COMMAND);
    if (!pos) {
        return -1;
    }
    int idx = pos - input;
    if (idx == 0 && !isalnum(input[4]) && !ispunct(input[4])) {
        return idx;
    }
    if (!isalnum(input[idx-1]) && !ispunct(input[idx-1])) {
        return idx;
    }
    return -1;
}
