	.file	"InitialStub.c"
	.text
	.globl	factorial
	.def	factorial;	.scl	2;	.type	32;	.endef
	.seh_proc	factorial
factorial:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$32, %rsp
	.seh_stackalloc	32
	.seh_endprologue
	movl	%ecx, 16(%rbp)
	cmpl	$0, 16(%rbp)
	je	.L2
	cmpl	$1, 16(%rbp)
	jne	.L3
.L2:
	movl	$1, %eax
	jmp	.L4
.L3:
	movl	16(%rbp), %eax
	subl	$1, %eax
	movl	%eax, %ecx
	call	factorial
	imull	16(%rbp), %eax
.L4:
	addq	$32, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.def	__main;	.scl	2;	.type	32;	.endef
	.section .rdata,"dr"
.LC0:
	.ascii "%d \0"
	.text
	.globl	main
	.def	main;	.scl	2;	.type	32;	.endef
	.seh_proc	main
main:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$64, %rsp
	.seh_stackalloc	64
	.seh_endprologue
	call	__main
	movl	$3, -32(%rbp)
	movl	$6, -28(%rbp)
	movl	$7, -24(%rbp)
	movl	$8, -20(%rbp)
	movl	$0, -4(%rbp)
	movl	$4, -8(%rbp)
	jmp	.L6
.L7:
	movl	-4(%rbp), %eax
	cltq
	movl	-32(%rbp,%rax,4), %eax
	movl	%eax, -12(%rbp)
	movl	-12(%rbp), %eax
	movl	%eax, %ecx
	call	factorial
	movl	%eax, -16(%rbp)
	movl	-16(%rbp), %eax
	movl	%eax, %edx
	leaq	.LC0(%rip), %rax
	movq	%rax, %rcx
	call	printf
	addl	$1, -4(%rbp)
.L6:
	movl	-4(%rbp), %eax
	cmpl	-8(%rbp), %eax
	jl	.L7
	movl	$10, %ecx
	call	putchar
	movl	$0, %eax
	addq	$64, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.ident	"GCC: (Rev3, Built by MSYS2 project) 13.2.0"
	.def	printf;	.scl	2;	.type	32;	.endef
	.def	putchar;	.scl	2;	.type	32;	.endef
