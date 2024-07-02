1)
Par defaut avec flex , il a ses propres expressions regulieres qui sont comme le '| , () ,*,+ "et autres . Donc si on veut utiliser cela dans un programme comme chaine , il faudrait les echapés . Ici on utilise '\' pour echapper. 

2) + : un ou plusieurs fois (l’ ́etoile positive).

3)Le fichier simple.h inclu dans parser.lex permet d’échanger des lexèmes entre flex et bison.
Il est généré automatiquement par bison.

4)Dans la section regex, yylval permet à bison de retourner la valeur du lexème lue.
{entier} { yylval=atoi(yytext);return INTEGER;}
{operateur} {return *yytext;}

5) On a les affectation composee de la forme a += b; a -= b; a /= b; a *= b; a %= b;

Pour executer le programme , il faut taper la commande "make" et pour executer vous taper ./sortie