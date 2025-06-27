exo15: exo15.y exo15.lex
	bison --defines=simple.h -v -o exo15.c exo15.y
	flex -o exo15.yy.c exo15.lex
	gcc exo15.yy.c exo15.c -o exo15 -lfl

