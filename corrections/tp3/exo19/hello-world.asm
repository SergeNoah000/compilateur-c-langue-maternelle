; registres utilisables : eax, ebx, ecx, edx
extern	printf

section .data
	hello:     	db 'Hello world!',10,0   	; 'Hello world!' suivi de \n\0
	helloLen:  	equ $-hello             	; longueur de hello world - equ : constante
	fmt:    	db "%d", 10, 0	           	; chaine a afficher ( %d\n\0) avec printf - db/dw : on déclare des variables initialisées

section .text
	global _start

_start:
	; on affiche HelloWorld directement avec l'interruption 80h
	mov eax,4            ; The system call for write (sys_write)
	mov ebx,1            ; File descriptor 1 - standard output
	mov ecx,hello        ; Put the offset of hello in ecx
	mov edx,helloLen     ; helloLen is a constant, so we don't need to say
	                     ;  mov edx,[helloLen] to get it's actual value
	int 80h              ; Call the kernel
	
	; on fait une addition, ici, 11 et 5
	mov ecx,11
	add ecx,5
	
	; ici ecx vaut 16, on l'affiche avec la fonction printf
	push    ecx 		; on met eax (à afficher) dans la pile)
	push    dword fmt 	; on met la fonction d'affichage dans la pile
	call    printf		; on appelle la fonction printf
	
	; on sort en renvoyant 0
	mov eax,1            ; sys_exit
	mov ebx,0            ; Exit with return code of 0 (no error)
	int 80h
