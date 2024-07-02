section .data
    hello db 'Hello, World!', 0    ; Null-terminated string

section .text
    global _start

_start:
    ; Write the string to stdout
    mov eax, 4          ; sys_write
    mov ebx, 1          ; file descriptor 1 is stdout
    mov ecx, hello      ; pointer to string
    mov edx, 13         ; number of bytes
    int 0x80            ; call kernel

    ; Exit the program
    mov eax, 1          ; sys_exit
    xor ebx, ebx        ; return 0 status
    int 0x80            ; call kernel
