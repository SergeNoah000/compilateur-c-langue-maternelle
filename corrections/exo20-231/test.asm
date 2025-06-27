extern printf, scanf
section .data
    b: dd 0
    i: dd 0
    fmt: db "%d", 10, 0 
    fmtlec: db "%d", 0

section .text
global _start

_start:
    ; Lecture de b
    push b
    push dword fmtlec
    call scanf
    add esp, 8

    ; Initialisation de i à 1
    mov dword [i], 1

    ; Boucle for
debutFor:
    ; Condition de sortie de la boucle (i < b)
    mov eax, [b]
    cmp dword [i], eax
    jge finFor

    ; Instructions à exécuter dans la boucle for

    ; Affichage de la valeur de i
    mov eax, [i]
    push eax
    push dword fmt
    call printf
    add esp, 8

    ; Incrémentation de i
    mov eax, [i]
    add eax, 1
    mov [i], eax

    ; Retour au début de la boucle
    jmp debutFor

finFor:
    ; Sortie du programme
    mov eax, 1   ; sys_exit
    xor ebx, ebx ; Exit with return code of 0 (no error)
    int 80h
