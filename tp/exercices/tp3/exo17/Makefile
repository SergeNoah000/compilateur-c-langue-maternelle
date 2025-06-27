exo17: exo17.y exo17.lex
	bison --defines=simple.h -v -o exo17.c exo17.y
	flex -o exo17.yy.c exo17.lex
	gcc utilitaire.c exo17.yy.c exo17.c -o exo17 -lfl

