extern printf,scanf 
section .data
; declaration des variables en memoire
a:  dd  0
b:  dd  0
c:  dd  0
d:  dd  0
fmt:db "%d", 10, 0 
fmtlec:db "%d",0
section .text
global _start

_start:

push 0
 ;affectation
pop eax
mov [a], eax

push 1
 ;affectation
pop eax
mov [b], eax

push 10
 ;affectation
pop eax
mov [c], eax

;********Lieu de l'étiquete
debutFor1:
 ;recuperation en memoire
mov eax, [i] 
push eax
 ;recuperation en memoire
mov eax, [a] 
push eax
mov eax,1 ; sys_exit 
mov ebx,0; Exit with return code of 0 (no error)
int 80h