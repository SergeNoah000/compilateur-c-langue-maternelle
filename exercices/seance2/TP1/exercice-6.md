Pour construire un automate fini déterministe (DFA) qui accepte les lignes qui commencent par "if" et se terminent par "n", nous devons suivre ces étapes :

1. **Définir les états de l'automate** :
   - `q0`: État initial.
   - `q1`: Après avoir lu "i".
   - `q2`: Après avoir lu "if".
   - `q3`: Après avoir lu "if" et zéro ou plusieurs caractères quelconques.
   - `q4`: État final, après avoir lu "n" à la fin de la ligne.

2. **Transitions entre les états** :
   - `q0` à `q1` sur 'i'.
   - `q1` à `q2` sur 'f'.
   - `q2` à `q3` sur n'importe quel caractère (sauf retour à la ligne).
   - `q3` reste en `q3` sur n'importe quel caractère (sauf retour à la ligne).
   - `q3` à `q4` sur 'n' et ensuite retour à la ligne.

3. **État final** :
   - `q4` est l'état final qui accepte les lignes.

### Construction de l'Automate

Voici un pseudocode pour la construction de cet automate :

1. Créer un DFA avec les états mentionnés ci-dessus.
2. Ajouter les transitions basées sur les caractères lus.
3. Déterminer si une ligne est acceptée en fonction de l'état final `q4`.

### Code en C

Le code en C suivant implémente ce DFA pour lire un fichier ligne par ligne et vérifier si une ligne correspond au motif requis :

```c
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define BUFFER_SIZE 1024

// Fonction pour vérifier si une ligne correspond au motif
bool match_pattern(const char *line) {
    int state = 0;
    for (int i = 0; line[i] != '\0'; ++i) {
        char c = line[i];
        switch (state) {
            case 0:
                if (c == 'i') state = 1;
                break;
            case 1:
                if (c == 'f') state = 2;
                else state = 0;  // Reset si le motif est rompu
                break;
            case 2:
                if (c == 'n' && line[i+1] == '\0') state = 4;
                else state = 3;
                break;
            case 3:
                if (c == 'n' && line[i+1] == '\0') state = 4;
                break;
            case 4:
                break;
        }
    }
    return state == 4;
}

int main() {
    FILE *file = fopen("/etc/bash.bashrc", "r");
    if (!file) {
        perror("Erreur lors de l'ouverture du fichier");
        return 1;
    }

    char line[BUFFER_SIZE];
    int count = 0;

    while (fgets(line, sizeof(line), file)) {
        // Supprimer le caractère de nouvelle ligne à la fin de la ligne
        line[strcspn(line, "\n")] = '\0';
        
        if (match_pattern(line)) {
            count++;
        }
    }

    fclose(file);

    printf("Nombre de lignes correspondant au motif: %d\n", count);

    return 0;
}
```

### Explication du Code

1. **match_pattern** : Cette fonction vérifie si une ligne donnée correspond au motif en utilisant l'automate DFA défini plus tôt.
2. **main** :
   - Ouvre le fichier `/etc/bash.bashrc`.
   - Lit le fichier ligne par ligne.
   - Supprime le caractère de nouvelle ligne `\n` pour chaque ligne lue.
   - Utilise `match_pattern` pour vérifier si la ligne correspond au motif.
   - Compte les lignes qui correspondent et affiche le résultat.

### Compilation et Exécution

Pour compiler et exécuter ce programme, utilisez les commandes suivantes :

```sh
gcc -o dfa_pattern_matcher dfa_pattern_matcher.c
./dfa_pattern_matcher
```

Notre programme lit le fichier `/etc/bash.bashrc`, applique l'automate pour chaque ligne et affiche le nombre de lignes qui commencent par "if" et se terminent par "n".