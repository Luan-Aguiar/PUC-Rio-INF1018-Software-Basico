	.data
	nums: .int 3, -5, 7, 8, -2
	s1:   .string "%d\n"

	.text
	.globl main
	main:
	/* prologo */
	pushl %ebp
	movl  %esp, %ebp

	/* coloque seu codigo aqui */
	movl $0, %eax /* int i = 0 */
	movl $nums, %ecx
L0:	cmp $5, %eax
	je L1	
	pushl %eax
	pushl %ecx
	pushl $1 /* LIM=1 */
	pushl (%ecx)
	call filtro
	addl $8, %esp
	pushl %eax
	pushl $s1
	call printf
	addl $8, %esp
	pop %ecx
	pop %eax
	addl $1, %eax
	addl $4, %ecx
	jmp L0

L1:	/* finalizacao */
	movl %ebp, %esp
	popl %ebp
	ret

