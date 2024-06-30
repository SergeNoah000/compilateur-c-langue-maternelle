<!-- ### Exercice 11 : Construction de la table de la grammaire

#### Grammaire :
1. \( E -- >  E + E \)
2. \( E -- >  E * E \)
3. \( E -- >  int \)

#### Étapes de construction de la table LR(0) :

1. **Déterminer les éléments canoniques (LR(0) items)** :
   - Ajouter l'élément initial : \( S' -- >  .E \)
   - Fermer chaque état en ajoutant les productions nécessaires.

2. **Construire l'automate LR(0)** :
   - Utiliser les éléments canoniques pour créer les états de l'automate.
   - Définir les transitions entre les états en fonction des symboles.

3. **Remplir les actions et les transitions dans la table (action/goto)** :
   - Utiliser les états et les transitions pour remplir la table d'analyse.

#### Exemples de construction des états :

- \( I_0 : S' -- >  .E \)
  - Fermeture de \( I_0 \) :
    - \( S' -- >  .E \)
    - \( E -- >  .E + E \)
    - \( E -- >  .E * E \)
    - \( E -- >  .int \)

- Transitions :
  - \( I_0 \xrightarrow{int} I_1 \) où \( I_1 : E -- >  int. \)
  - \( I_0 \xrightarrow{E} I_2 \) où \( I_2 : S' -- >  E. \)

4. **Table LR(0) d'analyse** :

| États | int | +  | *  | $  | E  |
|-------|-----|----|----|----|----|
| 0     | S3  |    |    |    | 1  |
| 1     |     | S2 | S4 | Acc|    |
| 2     |     |    |    | R1 |    |
| 3     |     | R3 | R3 | R3 |    |
| 4     |     | S2 |    | R2 |    |

- `S` : shift
- `R` : reduce
- `Acc` : accept

Pour analyser le mot "dcadcb", on suite les actions de la table ci-dessus en maintenant une pile des états.





### Exercice 14 : Construction d'un automate à pile

#### Grammaire :
1. \( E -- >  E + E \)
2. \( E -- >  E * E \)
3. \( E -- >  int \)

#### Automate à pile :

1. **Création du fichier lex (`lexer.l`)** :

c
%{
#include "y.tab.h"
%}

%%
"+"     { return PLUS; }
"*"     { return MUL; }
"("     { return LPAREN; }
")"     { return RPAREN; }
[0-9]+  { yylval = atoi(yytext); return NUMBER; }
\n      { return 0; }
[ \t]   { /* ignore whitespace */ }
.       { printf("Unexpected character: %s\n", yytext); return 0; }
%%

int yywrap() {
    return 1;
}


2. **Création du fichier yacc (`parser.y`)** :

c
%{
#include <stdio.h>
#include <stdlib.h>
%}

%token NUMBER PLUS MUL LPAREN RPAREN

%%

expression:
    expression PLUS expression
    | expression MUL expression
    | NUMBER
    ;

%%

int main() {
    yyparse();
    return 0;
}

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}


3. **Compilation et exécution** :

Pour compiler et exécuter le code :

sh
flex lexer.l
yacc -d parser.y
gcc lex.yy.c y.tab.c -o parser -ll -ly
echo "12 * 12 + 14" | ./parser


Ce programme utilisera les lexèmes générés par lex pour les tokens d'expression arithmétique et utilisera yacc pour construire l'analyseur syntaxique basé sur la grammaire donnée.

### Explications :

- **Lexer** : génère les tokens pour les nombres, les opérateurs et les parenthèses.
- **Parser** : utilise ces tokens pour construire un arbre syntaxique en respectant la grammaire.
- **Évaluation** : Les actions du parser peuvent être étendues pour effectuer des calculs ou générer une représentation postfixée pour une évaluation ultérieure.

Ce processus combine lex et yacc pour créer un analyseur syntaxique et évaluer des expressions arithmétiques en respectant les priorités des opérateurs. -->







### Exercice 11: Construction de la table pour la grammaire donnée

#### Grammaire
1. `E -> Ac`
2. `A -> AaAb`
3. `A -> d`

#### Table LR(0)

La première étape consiste à construire les éléments de la grammaire augmentée, les ensembles d'éléments LR(0), et ensuite la table d'analyse LR(0).

##### Grammaire augmentée
On ajoute une nouvelle production pour commencer :

S' -> E

Cela donne les productions suivantes :

S' → E
E → Ac
A → AaAb
A → d


##### Ensembles d'éléments LR(0)
- **I0**: Initial state

S' → .E
E → .Ac
A → .AaAb
A → .d


- **I1**: Après "S' -> E"

S' → E.


- **I2**: Après "E -> Ac"

E → A.c
A → .AaAb
A → .d


- **I3**: Après "E -> A"

E → Ac.


- **I4**: Après "A -> AaAb"

A → Aa.Ab
A → .AaAb
A → .d


- **I5**: Après "A -> d"

A → d.


- **I6**: Après "A -> Aa"

A → AaAb.


- **I7**: Après "A -> AaAb"

A → AaA.b
A → .AaAb
A → .d


- **I8**: Après "A -> b"

A → AaAb.


##### Table d'analyse LR(0)
La table d'analyse consiste en deux parties : Action et Goto.

**Action table**

|  | d | a | b | c | $ |
| --- | --- | --- | --- | --- | --- |
| 0 | s5 |  |  |  |  |
| 1 |  |  |  |  | accept |
| 2 | s5 | s3 |  |  |  |
| 3 |  | s7 | s8 |  |  |
| 4 |  |  |  | s6 |  |
| 5 |  & s3 |
| 6 & r1 |
| 7 & s3 & s8 |
| 8 & & s6 |


**Goto table**

|  | E | A |
| --- | --- | --- |
| 0 | 1 & 2 |
| 2 & & 4 |
| 4 & &   |
| 7 & &   |


#### Analyse du mot "dcadcb"

Pour analyser le mot `dcadcb` en utilisant cette table, suivez ces étapes de l'algorithme d'analyse LR(0):

1. **Initialisation**

Pile = [0]
Entrée = dcadcb$


2. **Étapes d'analyse**
- État 0, `d` : action = `s5`

Pile = [0, 5]
Entrée = cadcb$


- État 5, `c` : action = `r3` (A -> d)

Pile = [0, 2]
Entrée = cadcb$


- État 2, `c` : action = `s6`

Pile = [0, 2, 6]
Entrée = adcb$


- État 6, `a` : action = `r1` (E -> Ac)

Pile = [0, 1]
Entrée = adcb$


- État 1, `a` : action = `s3`

Pile = [0, 1, 3]
Entrée = dcb$


- État 3, `d` : action = `s5`

Pile = [0, 1, 3, 5]
Entrée = cb$


- État 5, `c` : action = `r3` (A -> d)

Pile = [0, 1, 3, 4]
Entrée = b$


- État 4, `b` : action = `s8`

Pile = [0, 1, 3, 4, 8]
Entrée = $


- État 8, `$` : action = `accept`

Reconnaissance terminée