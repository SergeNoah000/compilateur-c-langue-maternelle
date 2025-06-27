	.file	"exo1.c"
	.section	.rodata
.LC0:
	.string	"r"
	.align 4
.LC1:
	.string	"Le nombre d'occurence est: %d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	andl	$-16, %esp
	subl	$32, %esp
	movl	$0, 16(%esp)
	movl	$-1, 20(%esp)
	movl	$.LC0, %edx
	movl	12(%ebp), %eax
	addl	$4, %eax
	movl	(%eax), %eax
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	fopen
	movl	%eax, 24(%esp)
	jmp	.L2
.L6:
	leal	31(%esp), %eax
	movl	24(%esp), %edx
	movl	%edx, 12(%esp)
	movl	$1, 8(%esp)
	movl	$1, 4(%esp)
	movl	%eax, (%esp)
	call	fread
	movzbl	31(%esp), %eax
	cmpb	$109, %al
	jne	.L3
	movl	$0, 20(%esp)
.L3:
	movzbl	31(%esp), %eax
	cmpb	$117, %al
	jne	.L4
	cmpl	$0, 20(%esp)
	jne	.L4
	movl	$1, 20(%esp)
.L4:
	movzbl	31(%esp), %eax
	cmpb	$114, %al
	jne	.L5
	cmpl	$1, 20(%esp)
	jne	.L5
	movl	$2, 20(%esp)
.L5:
	cmpl	$2, 20(%esp)
	jne	.L2
	addl	$1, 16(%esp)
	movl	$-1, 20(%esp)
.L2:
	movl	24(%esp), %eax
	movl	%eax, (%esp)
	call	feof
	testl	%eax, %eax
	je	.L6
	movl	24(%esp), %eax
	movl	%eax, (%esp)
	call	fclose
	movl	$.LC1, %eax
	movl	16(%esp), %edx
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	printf
	movl	$0, %eax
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu/Linaro 4.6.3-1ubuntu5) 4.6.3"
	.section	.note.GNU-stack,"",@progbits
