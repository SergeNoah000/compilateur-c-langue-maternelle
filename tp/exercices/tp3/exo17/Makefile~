exo17_18: exo17_18.y exo17_18.lex
	bison --defines=simple.h -v -o exo17_18.c exo17_18.y
	flex -o exo17_18.yy.c exo17_18.lex
	gcc utilitaire.c exo17_18.yy.c exo17_18.c -o exo17_18 -lfl

