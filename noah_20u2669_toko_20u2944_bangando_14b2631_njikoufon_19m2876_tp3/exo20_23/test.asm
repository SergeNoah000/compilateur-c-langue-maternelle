Enter commands:
mov eax, 3
mov ebx, 0
lea ecx, [vars + 0]
mov edx, 1
int 0x80
mov eax, 4
mov [vars + 4], eax
mov eax, 0
mov ebx, 1
mov ecx, eax
mov edx, 1
int 0x80
mov eax, 0
mov [vars + 8], eax
mov eax, 1
mov [vars + 12], eax
mov eax, 1
mov [vars + 0], eax
mov eax, 0
mov [vars + 4], eax
mov eax, 0
mov ebx, 1
mov ecx, eax
mov edx, 1
int 0x80
mov eax, 0
mov ebx, 1
mov ecx, eax
mov edx, 1
int 0x80
mov eax, 0
mov ebx, 1
mov ecx, eax
mov edx, 1
int 0x80
mov eax, 0
mov ebx, 1
mov ecx, eax
mov edx, 1
int 0x80
mov eax, 3
mov ebx, 0
lea ecx, [vars + 0]
mov edx, 1
int 0x80
mov eax, 0
mov ebx, 1
mov ecx, eax
mov edx, 1
int 0x80
cmp eax, 0
je .if_end_0
.if_start_0:
