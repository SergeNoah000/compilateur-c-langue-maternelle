exo18: exo18.y exo18.lex
	bison --defines=simple.h -v -o exo18.c exo18.y
	flex -o exo18.yy.c exo18.lex
	gcc utilitaire.c exo18.yy.c exo18.c -o exo18 -lfl

