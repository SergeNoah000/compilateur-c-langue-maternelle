
	
sortie: sortie.o
	 ld -s -o sortie sortie.o -melf_i386 -I/lib/ld-linux.so.2 -lc 

sortie.o: code_assembleur.asm
	nasm -f elf -o sortie.o code_assembleur.asm 

code_assembleur.asm: commande

commande: parse
	cat programme.txt | ./parse

parse: lexical.yy.c syntaxiq.c 
	gcc lexical.yy.c syntaxiq.c -o parse -lfl

lexical.yy.c: parser.lex
	 flex -o lexical.yy.c parser.lex
	
syntaxiq.c: grammaire.y
	bison --defines=simple.h -v -o syntaxiq.c grammaire.y

