section .data
    result db 0

section .text
    global _start

_start:
    ; Calcul 5 * 6
    mov eax, 5       ; Met 5 dans eax
    mov ebx, 6       ; Met 6 dans ebx
    mul ebx          ; eax = eax * ebx (5 * 6)
    
    ; Ajout de 4 au résultat précédent
    add eax, 4       ; eax = eax + 4 (résultat de 5 * 6 + 4)

    ; Stocke le résultat dans la variable result
    mov [result], eax

    ; Affiche le résultat
    mov eax, 4       ; Numéro de l'appel système pour écrire
    mov ebx, 1       ; Descripteur de fichier (stdout)
    mov ecx, result  ; Adresse du message à afficher (ici le résultat)
    mov edx, 1       ; Longueur du message à afficher (1 byte)
    int 0x80         ; Appel système pour écrire sur stdout

    ; Sortie du programme
    mov eax, 1       ; Numéro de l'appel système pour exit
    xor ebx, ebx     ; Code de sortie 0
    int 0x80         ; Appel système pour exit
