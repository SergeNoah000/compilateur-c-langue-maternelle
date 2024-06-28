#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Fonction pour compter les occurrences d'un mot dans un fichier
int count_occurrences(const char *filename, const char *word) {
    // Ouvrir le fichier en mode lecture
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Unable to open file"); // Afficher un message d'erreur si le fichier ne peut pas être ouvert
        return -1;
    }

    int state = 0, count = 0; // Initialiser l'état et le compteur
    int word_len = strlen(word); // Longueur du mot à chercher
    char c; // Variable pour stocker le caractère lu

    // Lire le fichier caractère par caractère
    while ((c = fgetc(file)) != EOF) {
        if (c == word[state]) { // Si le caractère correspond à l'état actuel du mot
            state++; // Passer à l'état suivant
            if (state == word_len) { // Si tous les caractères du mot ont été trouvés
                count++; // Incrémenter le compteur
                state = 0; // Réinitialiser l'état pour chercher de nouvelles occurrences
            }
        } else {
            if (state > 0) {
                // Vérifier pour une correspondance partielle si le caractère actuel correspond au début du mot
                if (c == word[0]) {
                    state = 1; // Réinitialiser l'état pour le début du mot
                } else {
                    state = 0; // Réinitialiser l'état
                }
            }
        }
    }

    fclose(file); // Fermer le fichier
    return count; // Retourner le nombre d'occurrences trouvées
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <filename> <word>\n", argv[0]); // Afficher un message d'utilisation si les arguments sont incorrects
        return 1;
    }

    const char *filename = argv[1]; // Nom du fichier passé en argument
    const char *word = argv[2]; // Mot à chercher passé en argument
    int occurrences = count_occurrences(filename, word); // Compter les occurrences du mot dans le fichier
    if (occurrences != -1) {
        printf("The word '%s' occurs %d times in the file '%s'.\n", word, occurrences, filename); // Afficher le résultat
    }
    return 0;
}
