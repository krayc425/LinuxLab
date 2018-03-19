#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    FILE *file = NULL;

    int char_count = 0;
    int word_count = 0;
    int line_count = 0;

//    int last_is_split = 0;

    if (argc != 1) {
        printf("Wrong file name\n");
    }

    file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Open error\n");
        exit(0);
    } else {
        while (1) {
            char ch;
            ch = fgetc(file);


            if (ch == EOF) {
                break;
            } else {
                char_count++;
                if (ch == ' ' || ch == '\n' || ch == '\r' || ch == '\f'
                    || ch == '\t' || ch == '\v') {
//                    if (last_is_split == 0) {
                    word_count++;
//                        last_is_split = 1;
//                    }
//                } else {
//                    last_is_split = 0;
                }
                if (ch == '\n') {
                    line_count++;
                }
            }
        }
        fclose(file);
    }

    printf("%d\t%d\t%d\t%s\n", line_count, word_count, char_count, argv[1]);

    return 0;
}