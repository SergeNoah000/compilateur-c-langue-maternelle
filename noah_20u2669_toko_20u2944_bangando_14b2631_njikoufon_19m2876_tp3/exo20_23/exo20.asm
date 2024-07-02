section .data
    result db 0          ; Variable pour stocker le résultat

section .text
    global _start

_start:
    ; Calculer 4 * 5
    mov eax, 4
    mov ebx, 5
    mul ebx             ; eax = eax * ebx (4 * 5 = 20)

    ; Ajouter 1 à 20
    add eax, 1          ; eax = eax + 1 (20 + 1 = 21)

    ; Stocker le résultat dans result
    mov [result], eax   ; Sauvegarde du résultat dans la variable result

    ; Terminer le programme
    mov eax, 1          ; sys_exit
    xor ebx, ebx        ; retourne 0
    int 0x80            ; appel système
