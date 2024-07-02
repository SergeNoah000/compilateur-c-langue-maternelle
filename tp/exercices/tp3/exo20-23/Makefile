all: test

exo20-23: exo20-23.y exo20-23.lex
	bison --defines=simple.h -v -o exo20-23.c exo20-23.y
	flex -o exo20-23.yy.c exo20-23.lex
	gcc exo20-23.yy.c exo20-23.c -o exo20-23 -lfl

test: test.o exo20-23
	ld -s -o test test.o -melf_i386 -I/lib/ld-linux.so.2 -lc

test.o: test.asm
	nasm -f elf -o test.o test.asm

