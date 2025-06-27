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

 ;recuperation en memoire
mov eax, [a] 
push eax
push 2
;Teste de différence
pop ebx
pop eax
cmp eax, ebx

jne test1
push 0
jmp fintest1 
test1:
push 1
fintest1:


;Réduction du alors1
pop eax
cmp eax,1
jne sinon1
;affiher
mov eax, [a] 
push eax
push dword fmt
call printf

sinon1:
;Réduction du fsi1
push 0
 ;affectation
pop eax
mov [a], eax

;lire
push  b 
push dword fmtlec
call scanf

;lire
push  c 
push dword fmtlec
call scanf

;********Lieu de l'étiquete
debutWhile1:
 ;recuperation en memoire
mov eax, [a] 
push eax
 ;recuperation en memoire
mov eax, [c] 
push eax
;Teste d'infériorité
pop ebx
pop eax
cmp eax, ebx

jge test2
push 1
jmp fintest2 
test2:
push 0
fintest2:


;*************** ***** ****Réduction de la condition
pop eax
cmp eax,1
jne finWhile1
;*************** ***** ****Réduction du do
 ;recuperation en memoire
mov eax, [a] 
push eax
 ;recuperation en memoire
mov eax, [b] 
push eax
 ; addition
pop eax
pop ebx
add eax,ebx
push eax

  ;affectation
pop eax
mov [a], eax

 ;recuperation en memoire
mov eax, [a] 
push eax
push 2
;Teste de différence
pop ebx
pop eax
cmp eax, ebx

jne test3
push 0
jmp fintest3 
test3:
push 1
fintest3:


;Réduction du alors2
pop eax
cmp eax,1
jne sinon2
;affiher
mov eax, [a] 
push eax
push dword fmt
call printf

sinon2:
;Réduction du fsi2
;*************** ***** ****Réduction du done
jmp debutWhile1
finWhile1:
;*************** ***** ****Réduction du bloc while
mov eax,1 ; sys_exit 
mov ebx,0; Exit with return code of 0 (no error)
int 80h