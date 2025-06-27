Je corrige les erreurs de copie-collage et ajoute le état manquant dans la table action/goto. Voici le texte sous format Markdown :

### Exercice 12: Construction de la table action/goto pour la grammaire

La grammaire donnée est :
1. \( E  -- > E + E \)
2. \( E  -- > E * E \)
3. \( E  -- > int \)

#### Étape 1: Grammaire augmentée

On ajoute une nouvelle production pour commencer:

S' → E

Cela donne les productions suivantes:



S' & -- > E
E & -- > E + E
E & -- > E * E
E & -- > int



#### Étape 2: Construction des ensembles d'éléments LR(0)

- **I0**: Initial state

````
S' & -- > .E
E & -- > .E + E
E & -- > .E * E
E & -- > .int


- **I1**: Après "S' -> E"



S' & -- > E.



- **I2**: Après "E -> E +"



E & -- > E + .E
E & -- > .E + E
E & -- > .E * E
E & -- > .int



- **I3**: Après "E -> E *"



E & -- > E * .E
E & -- > .E + E
E & -- > .E * E
E & -- > .int



- **I4**: Après "E -> int"



E & -- > int.



- **I5**: Après "E -> E + E"



E & -- > E + E.



- **I6**: Après "E -> E * E"



E & -- > E * E.



- **I7**: Après "int"

