
/* Reconnaissance de la regex `[abc]*`

Construction de l'automate
1. **[abc]*** : Reconnaît zéro ou plusieurs occurrences des caractères 'a', 'b', ou 'c'.

L'automate correspondant aura un seul état qui accepte les caractères 'a', 'b', ou 'c' et reste dans le même état.

*/



#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Fonction qui vérifie si la chaîne donnée correspond à la regex [abc]*
int match_abc_star(const char *str) {
    int state = 0; // État initial
    while (*str) {
        switch (state) {
            case 0: 
                if (*str == 'a' || *str == 'b' || *str == 'c' || *str == '\n') {
                    state = 0; // Reste dans l'état 0 si les caractères sont 'a', 'b' ou 'c'
                } else {
                    printf(" `%c` ", *str);
                    return false; // Rejette la chaîne pour tout autre caractère
                }
                break;
        }
        str++;
    }
    return true; // Accepte si tous les caractères sont 'a', 'b' ou 'c'
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <path>\n", argv[0]);
        return 1;
    }

    const char *path = argv[1];
    FILE *file = fopen(path, "r");
    if (!file) {
        printf("Error opening file: %s\n", path);
        return 1;
    }
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file)) {
        bool matched = match_abc_star(buffer);
        printf("%s%s", matched? "Matched: " : "Not matched: ", buffer);
    }
    fclose(file);
    return 0;
}

