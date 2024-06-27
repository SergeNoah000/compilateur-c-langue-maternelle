#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int countOccurrences(FILE *file, const char *word) {
    int count = 0;
    int state = 0;
    char c;
    const char *p = word;

    while ((c = fgetc(file)) != EOF) {
        if (c == *p) {
            p++;
            state++;
            if (state == 3) { // longueur de "mur" est 3
                count++;
                state = 0;
                p = word;
            }
        } else {
            state = 0;
            p = word;
        }
    }

    return count;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    const char *word = "mur";
    int occurrences = countOccurrences(file, word);
    fclose(file);

    printf("The word '%s' occurs %d times in the file '%s'.\n", word, occurrences, argv[1]);

    return EXIT_SUCCESS;
}
