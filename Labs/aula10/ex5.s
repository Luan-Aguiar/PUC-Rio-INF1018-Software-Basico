.text
.globl map2
	map2:

	pushl %ebp
	movl %esp, %ebp
	pushl %ebx

	movl $1, %ecx /*i=0*/
J0:	cmpl 16(%ebp), %ecx /*i<n*/
	je L2
	movl 8(%ebp), %edx /*um*/
	addl %ecx, %edx  /*um+i*/
	pushl %ecx
	pushl %edx
	pushl (%edx)
	call f
	addl $4, %esp
	popl %edx
	popl %ecx
	
	movl 12(%ebp), %ebx  
	addl %ecx, %ebx  /*outro+i*/
	movl %eax, (%ebx)

	addl $1, %ecx

        jmp J0

L2:	popl %ebx
	movl %ebp, %esp
	popl %ebp
	ret

.globl f
f:
    pushl %ebp
    movl %esp, %ebp

    movl 8(%ebp), %eax
    addl $2, %eax

    movl %ebp, %esp
    popl %ebp
    ret
