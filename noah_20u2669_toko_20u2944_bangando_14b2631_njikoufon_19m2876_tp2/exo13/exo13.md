### Exercice 13: Analyse du mot "x + y * z"

En utilisant la table de l'exercice 12, analysons le mot "x + y * z".

1. **Initialisation**:
   \[
   \text{Pile} = [0]
   \]
   \[
   \text{Entrée} = x + y * z\$
   \]

2. **Étapes d'analyse (shift puis reduce)**:
   - État 0, `x` : action = `s4`
     \[
     \text{Pile} = [0, 4]
     \]
     \[
     \text{Entrée} = + y * z\$
     \]

   - État 4, `+` : action = `r3` (E -> int)
     \[
     \text{Pile} = [0, 1]
     \]
     \[
     \text{Entrée} = + y * z\$
     \]

   - État 1, `+` : action = `s2`
     \[
     \text{Pile} = [0, 1, 2]
     \]
     \[
     \text{Entrée} = y * z\$
     \]

   - État 2, `y` : action = `s4`
     \[
     \text{Pile} = [0, 1, 2, 4]
     \]
     \[
     \text{Entrée} = * z\$
     \]

   - État 4, `*` : action = `r3` (E -> int)
     \[
     \text{Pile} = [0, 1, 2, 5]
     \]
     \[
     \text{Entrée} = * z\$
     \]

   - État 5, `*` : action = `s3`
     \[
     \text{Pile} = [0, 1, 2, 5, 3]
     \]
     \[
     \text{Entrée} = z\$
     \]

   - État 3, `z` : action = `s4`
     \[
     \text{Pile} = [0, 1, 2, 5, 3, 4]
     \]
     \[
     \text{Entrée} = \$ \]
     
   - État 4, `$` : action = `r3` (E -> int)
     \[
     \text{Pile} = [0, 1, 2, 5, 3, 6]
     \]
     \[
     \text{Entrée} = \$ \]

   - État 6, `$` : action = `r1` (E -> E * E)
     \[
     \text{Pile} = [0, 1, 2, 5, 7]
     \]
     \[
     \text{Entrée} = \$ \]

   - État 7, `$` : action = `r2` (E -> E + E)
     \[
     \text{Pile} = [0, 1]
     \]
     \[
     \text{Entrée} = \$ \]

   - État 1, `$` : action = `accept`
     \[
     \text{Reconnaissance terminée}
     \]
