/*
#### Construction de l'automate
1. ^ : Le début de la ligne.
2. if : Reconnaît littéralement "if".
3. .* : Reconnaît zéro ou plusieurs caractères (n'importe quel caractère).
4. n$ : Reconnaît littéralement "n" en fin de ligne.

L'automate correspondant aura les états suivants:
- État 0: Début de la ligne.
- État 1: Après avoir lu `i`.
- État 2: Après avoir lu `f`.
- État 3: Après avoir lu `if`.
- État 4: Après avoir lu n'importe quel nombre de caractères (.*).
- État 5: Après avoir lu `n` en fin de ligne.

*/
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Fonction qui vérifie si la chaîne donnée correspond à la regex ^if.*n$
bool match_if_n(const char *str) {
    int state = 0;
    while (*str) {
        switch (state) {
            case 0: 
                if (*str == 'i') state = 1;
                else return false;
                break;
            case 1: 
                if (*str == 'f') state = 2;
                else return false;
                break;
            case 2: 
                state = 3; // transition vers état 3 (.*)
                break;
            case 3: 
                if (*str == 'n' && *(str + 1) == '\n') state = 4; // 'n' en fin de ligne
                break;
        }
        str++;
    }
    return state == 4;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <path> \n", argv[0]);
        return 1;
    }
    FILE *f = fopen(argv[1], "r");
    if (!f) {
        perror("fopen");
        return 1;
    }
    char line[1024];
    int count = 0;
    while (fgets(line, sizeof(line), f)) {
        if (match_if_n(line) ) {
            count++;
        }
    }
    fclose(f);
    if (ferror(f)) {
        perror("fgets");
        return 1;
    }
    printf("Total lines matching `^if.*n$`:\n");
    printf("-----------------\n");
    printf("%d\n", count);
    return 0;


}

