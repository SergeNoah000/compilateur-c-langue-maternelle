extern printf,scanf 
section .data
; declaration des variables en memoire
a:  dd  0
b:  dd  0
c:  dd  0
d:  dd  0
e:  dd  0
f:  dd  0
g:  dd  0
h:  dd  0
i:  dd  0
j:  dd  0
k:  dd  0
l:  dd  0
m:  dd  0
n:  dd  0
o:  dd  0
p:  dd  0
q:  dd  0
r:  dd  0
s:  dd  0
t:  dd  0
u:  dd  0
v:  dd  0
w:  dd  0
x:  dd  0
y:  dd  0
z:  dd  0
A:  dd  0
B:  dd  0
C:  dd  0
D:  dd  0
E:  dd  0
F:  dd  0
G:  dd  0
H:  dd  0
I:  dd  0
J:  dd  0
K:  dd  0
L:  dd  0
M:  dd  0
N:  dd  0
O:  dd  0
P:  dd  0
Q:  dd  0
R:  dd  0
S:  dd  0
T:  dd  0
U:  dd  0
V:  dd  0
W:  dd  0
X:  dd  0
Y:  dd  0
Z:  dd  0
fmt:db "%d", 10, 0 
fmtlec:db "%d",0
section .text
global _start

_start:

push 12
 ;affectation
pop eax
mov [a], eax

push 12
push 12
 ;multiplication
pop eax
pop ebx
mul ebx
push eax

  ;affectation
pop eax
mov [a], eax

push 100
 ;affectation
pop eax
mov [c], eax

 ;recuperation en memoire
mov eax, [a] 
push eax
push 144
;Teste d'égalité
pop ebx
pop eax
cmp eax, ebx

jne test1
push 1
jmp fintest1 
test1:
push 0
fintest1:


;Réduction du alors1
pop eax
cmp eax,1
jne sinon1
;affiher
mov eax, [c] 
push eax
push dword fmt
call printf

jmp suite1
sinon1:
;Réduction du sinon1
;affiher
mov eax, [a] 
push eax
push dword fmt
call printf

suite1:
;Réduction du fsis1
;Condition detectée 2
mov eax,1 ; sys_exit 
mov ebx,0; Exit with return code of 0 (no error)
int 80h