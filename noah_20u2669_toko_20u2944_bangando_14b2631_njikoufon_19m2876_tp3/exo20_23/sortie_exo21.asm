section .data
	result db 0

section .text
	global _start
_start:
	mov ebx, 1
	mov eax, 1
	mov ebx, 5
	add eax, 5
	; Store result in memory
	mov [result], eax
	; Print result
	mov eax, 4
	mov ebx, 1
	mov ecx, result
	mov edx, 1
	int 0x80
	; Exit program
	mov eax, 1
	xor ebx, ebx
	int 0x80
