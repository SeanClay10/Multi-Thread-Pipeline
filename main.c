#include "line_processor.h"
#include <stdlib.h>
#include <stdio.h>

int main(void) {
    initialize_buffers();
    
    pthread_t thread1, thread2, thread3, thread4;
    pthread_create(&thread1, NULL, input_handler, NULL); 
    pthread_create(&thread2, NULL, line_separator_handler, NULL);
    pthread_create(&thread3, NULL, plus_sign_handler, NULL);
    pthread_create(&thread4, NULL, output_handler, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
    pthread_join(thread4, NULL);

    free_buffers();

    return EXIT_SUCCESS;
}
