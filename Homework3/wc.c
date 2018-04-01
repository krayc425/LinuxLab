#include <stdio.h>
#include <stdlib.h>

void countChar(char ch);

int char_count = 0;
int word_count = 0;
int line_count = 0;

int main(int argc, char **argv) {

    if (argc != 1) {
        FILE *file = fopen(argv[1], "r");
        if (file == NULL) {
            printf("Open error\n");
            exit(0);
        } else {
            while (1) {
                char ch = fgetc(file);
                if (ch == EOF) {
                    break;
                } else {
                    countChar(ch);
                }
            }
            fclose(file);
        }

        printf("%d\t%d\t%d\t%s\n", line_count, word_count, char_count, argv[1]);
    } else {
        char ch;
        while ((ch = getchar()) != EOF) {
            countChar(ch);
        }

        printf("%d\t%d\t%d\t\n", line_count, word_count, char_count);
    }

    return 0;
}

void countChar(char ch) {
    char_count++;
    if (ch == ' ' || ch == '\n' || ch == '\r' || ch == '\f'
        || ch == '\t' || ch == '\v') {
        word_count++;
    }
    if (ch == '\n') {
        line_count++;
    }
}