Sean Clayton
Multi-threaded Consumer Produce Pipeline

To compile:
"gcc main.c buffer.c handlers.c utils.c -o line_processor -pthread"

To run (three options):
1) "./line_processor"
2) "./line_processor > filename"
3) "./line_processor < filename1 > filename2"