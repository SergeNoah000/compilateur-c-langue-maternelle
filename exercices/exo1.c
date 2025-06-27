#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

int countOccurrences(FILE *file, const char *word) {
    char buffer[BUFFER_SIZE];
    int count = 0;
    size_t word_len = strlen(word);

    while (fgets(buffer, BUFFER_SIZE, file) != NULL) {
        char *pos = buffer;
        while ((pos = strstr(pos, word)) != NULL) {
            count++;
            pos += word_len;
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
