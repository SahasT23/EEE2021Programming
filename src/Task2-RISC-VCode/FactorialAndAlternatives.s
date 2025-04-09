	.file	"FactorialAndAlternatives.c"
	.text
	.globl	measure_time
	.def	measure_time;	.scl	2;	.type	32;	.endef
	.seh_proc	measure_time
measure_time:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$48, %rsp
	.seh_stackalloc	48
	.seh_endprologue
	movq	%rcx, 16(%rbp)
	movl	%edx, 24(%rbp)
	movl	%r8d, 32(%rbp)
	call	clock
	movl	%eax, -8(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L2
.L3:
	movl	24(%rbp), %eax
	movq	16(%rbp), %rdx
	movl	%eax, %ecx
	call	*%rdx
	movl	%eax, -16(%rbp)
	addl	$1, -4(%rbp)
.L2:
	movl	-4(%rbp), %eax
	cmpl	32(%rbp), %eax
	jl	.L3
	call	clock
	movl	%eax, -12(%rbp)
	movl	-12(%rbp), %eax
	subl	-8(%rbp), %eax
	pxor	%xmm0, %xmm0
	cvtsi2sdl	%eax, %xmm0
	movsd	.LC0(%rip), %xmm1
	divsd	%xmm1, %xmm0
	pxor	%xmm1, %xmm1
	cvtsi2sdl	32(%rbp), %xmm1
	divsd	%xmm1, %xmm0
	movq	%xmm0, %rax
	movq	%rax, %xmm0
	addq	$48, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.globl	iterative_array
	.def	iterative_array;	.scl	2;	.type	32;	.endef
	.seh_proc	iterative_array
iterative_array:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$16, %rsp
	.seh_stackalloc	16
	.seh_endprologue
	movl	%ecx, 16(%rbp)
	movl	$1, -4(%rbp)
	movl	$1, -8(%rbp)
	jmp	.L6
.L7:
	movl	-4(%rbp), %eax
	imull	-8(%rbp), %eax
	movl	%eax, -4(%rbp)
	addl	$1, -8(%rbp)
.L6:
	movl	-8(%rbp), %eax
	cmpl	16(%rbp), %eax
	jle	.L7
	movl	-4(%rbp), %eax
	addq	$16, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.globl	recursive
	.def	recursive;	.scl	2;	.type	32;	.endef
	.seh_proc	recursive
recursive:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$32, %rsp
	.seh_stackalloc	32
	.seh_endprologue
	movl	%ecx, 16(%rbp)
	cmpl	$1, 16(%rbp)
	jg	.L10
	movl	$1, %eax
	jmp	.L11
.L10:
	movl	16(%rbp), %eax
	subl	$1, %eax
	movl	%eax, %ecx
	call	recursive
	imull	16(%rbp), %eax
.L11:
	addq	$32, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.globl	add_multiply
	.def	add_multiply;	.scl	2;	.type	32;	.endef
	.seh_proc	add_multiply
add_multiply:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$16, %rsp
	.seh_stackalloc	16
	.seh_endprologue
	movl	%ecx, 16(%rbp)
	movl	%edx, 24(%rbp)
	movl	$0, -4(%rbp)
	movl	$0, -8(%rbp)
	jmp	.L13
.L14:
	movl	16(%rbp), %eax
	addl	%eax, -4(%rbp)
	addl	$1, -8(%rbp)
.L13:
	movl	-8(%rbp), %eax
	cmpl	24(%rbp), %eax
	jl	.L14
	movl	-4(%rbp), %eax
	addq	$16, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.globl	iterativeRISCV
	.def	iterativeRISCV;	.scl	2;	.type	32;	.endef
	.seh_proc	iterativeRISCV
iterativeRISCV:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$16, %rsp
	.seh_stackalloc	16
	.seh_endprologue
	movl	%ecx, 16(%rbp)
	movl	$1, -4(%rbp)
	movl	$1, -8(%rbp)
	jmp	.L17
.L20:
	movl	$0, -12(%rbp)
	movl	$0, -16(%rbp)
	jmp	.L18
.L19:
	movl	-4(%rbp), %eax
	addl	%eax, -12(%rbp)
	addl	$1, -16(%rbp)
.L18:
	movl	-16(%rbp), %eax
	cmpl	-8(%rbp), %eax
	jl	.L19
	movl	-12(%rbp), %eax
	movl	%eax, -4(%rbp)
	addl	$1, -8(%rbp)
.L17:
	movl	-8(%rbp), %eax
	cmpl	16(%rbp), %eax
	jle	.L20
	movl	-4(%rbp), %eax
	addq	$16, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.globl	recursiveRISCV
	.def	recursiveRISCV;	.scl	2;	.type	32;	.endef
	.seh_proc	recursiveRISCV
recursiveRISCV:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$48, %rsp
	.seh_stackalloc	48
	.seh_endprologue
	movl	%ecx, 16(%rbp)
	cmpl	$1, 16(%rbp)
	jg	.L23
	movl	$1, %eax
	jmp	.L24
.L23:
	movl	16(%rbp), %eax
	subl	$1, %eax
	movl	%eax, %ecx
	call	recursiveRISCV
	movl	%eax, -12(%rbp)
	movl	$0, -4(%rbp)
	movl	$0, -8(%rbp)
	jmp	.L25
.L26:
	movl	-12(%rbp), %eax
	addl	%eax, -4(%rbp)
	addl	$1, -8(%rbp)
.L25:
	movl	-8(%rbp), %eax
	cmpl	16(%rbp), %eax
	jl	.L26
	movl	-4(%rbp), %eax
.L24:
	addq	$48, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.def	__main;	.scl	2;	.type	32;	.endef
	.section .rdata,"dr"
.LC1:
	.ascii "w\0"
.LC2:
	.ascii "factorial_results.csv\0"
.LC3:
	.ascii "Error creating CSV file\0"
	.align 8
.LC4:
	.ascii "Method,Input,Result,ExecutionTime(s)\12\0"
.LC5:
	.ascii "Iterative\0"
.LC6:
	.ascii "Recursive\0"
.LC7:
	.ascii "IterativeRISCV\0"
.LC8:
	.ascii "RecursiveRISCV\0"
.LC9:
	.ascii "%s,%d,%d,%.10f\12\0"
	.align 8
.LC10:
	.ascii "%s for n=%d: result=%d, time=%.10f seconds\12\0"
	.align 8
.LC11:
	.ascii "CSV report generated: factorial_results.csv\0"
	.text
	.globl	main
	.def	main;	.scl	2;	.type	32;	.endef
	.seh_proc	main
main:
	pushq	%rbp
	.seh_pushreg	%rbp
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
	subq	$176, %rsp
	.seh_stackalloc	176
	.seh_endprologue
	call	__main
	leaq	.LC1(%rip), %rax
	movq	%rax, %rdx
	leaq	.LC2(%rip), %rax
	movq	%rax, %rcx
	call	fopen
	movq	%rax, -16(%rbp)
	cmpq	$0, -16(%rbp)
	jne	.L28
	leaq	.LC3(%rip), %rax
	movq	%rax, %rcx
	call	perror
	movl	$1, %eax
	jmp	.L34
.L28:
	movq	-16(%rbp), %rax
	movq	%rax, %r9
	movl	$37, %r8d
	movl	$1, %edx
	leaq	.LC4(%rip), %rax
	movq	%rax, %rcx
	call	fwrite
	movl	$3, -64(%rbp)
	movl	$6, -60(%rbp)
	movl	$7, -56(%rbp)
	movl	$8, -52(%rbp)
	movl	$4, -20(%rbp)
	movl	$100000, -24(%rbp)
	leaq	.LC5(%rip), %rax
	movq	%rax, -128(%rbp)
	leaq	iterative_array(%rip), %rax
	movq	%rax, -120(%rbp)
	leaq	.LC6(%rip), %rax
	movq	%rax, -112(%rbp)
	leaq	recursive(%rip), %rax
	movq	%rax, -104(%rbp)
	leaq	.LC7(%rip), %rax
	movq	%rax, -96(%rbp)
	leaq	iterativeRISCV(%rip), %rax
	movq	%rax, -88(%rbp)
	leaq	.LC8(%rip), %rax
	movq	%rax, -80(%rbp)
	leaq	recursiveRISCV(%rip), %rax
	movq	%rax, -72(%rbp)
	movl	$4, -28(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L30
.L33:
	movl	$0, -8(%rbp)
	jmp	.L31
.L32:
	movl	-8(%rbp), %eax
	cltq
	movl	-64(%rbp,%rax,4), %eax
	movl	%eax, -32(%rbp)
	movl	-4(%rbp), %eax
	cltq
	salq	$4, %rax
	addq	%rbp, %rax
	subq	$120, %rax
	movq	(%rax), %rdx
	movl	-32(%rbp), %eax
	movl	%eax, %ecx
	call	*%rdx
	movl	%eax, -36(%rbp)
	movl	-4(%rbp), %eax
	cltq
	salq	$4, %rax
	addq	%rbp, %rax
	subq	$120, %rax
	movq	(%rax), %rax
	movl	-24(%rbp), %ecx
	movl	-32(%rbp), %edx
	movl	%ecx, %r8d
	movq	%rax, %rcx
	call	measure_time
	movq	%xmm0, %rax
	movq	%rax, -48(%rbp)
	movl	-4(%rbp), %eax
	cltq
	salq	$4, %rax
	addq	%rbp, %rax
	addq	$-128, %rax
	movq	(%rax), %rcx
	movl	-32(%rbp), %r8d
	movq	-16(%rbp), %rax
	movsd	-48(%rbp), %xmm0
	movsd	%xmm0, 40(%rsp)
	movl	-36(%rbp), %edx
	movl	%edx, 32(%rsp)
	movl	%r8d, %r9d
	movq	%rcx, %r8
	leaq	.LC9(%rip), %rdx
	movq	%rax, %rcx
	call	fprintf
	movl	-4(%rbp), %eax
	cltq
	salq	$4, %rax
	addq	%rbp, %rax
	addq	$-128, %rax
	movq	(%rax), %rax
	movl	-36(%rbp), %ecx
	movl	-32(%rbp), %edx
	movsd	-48(%rbp), %xmm0
	movsd	%xmm0, 32(%rsp)
	movl	%ecx, %r9d
	movl	%edx, %r8d
	movq	%rax, %rdx
	leaq	.LC10(%rip), %rax
	movq	%rax, %rcx
	call	printf
	addl	$1, -8(%rbp)
.L31:
	movl	-8(%rbp), %eax
	cmpl	-20(%rbp), %eax
	jl	.L32
	addl	$1, -4(%rbp)
.L30:
	movl	-4(%rbp), %eax
	cmpl	-28(%rbp), %eax
	jl	.L33
	movq	-16(%rbp), %rax
	movq	%rax, %rcx
	call	fclose
	leaq	.LC11(%rip), %rax
	movq	%rax, %rcx
	call	puts
	movl	$0, %eax
.L34:
	addq	$176, %rsp
	popq	%rbp
	ret
	.seh_endproc
	.section .rdata,"dr"
	.align 8
.LC0:
	.long	0
	.long	1083129856
	.ident	"GCC: (Rev3, Built by MSYS2 project) 13.2.0"
	.def	clock;	.scl	2;	.type	32;	.endef
	.def	fopen;	.scl	2;	.type	32;	.endef
	.def	perror;	.scl	2;	.type	32;	.endef
	.def	fwrite;	.scl	2;	.type	32;	.endef
	.def	fprintf;	.scl	2;	.type	32;	.endef
	.def	printf;	.scl	2;	.type	32;	.endef
	.def	fclose;	.scl	2;	.type	32;	.endef
	.def	puts;	.scl	2;	.type	32;	.endef
