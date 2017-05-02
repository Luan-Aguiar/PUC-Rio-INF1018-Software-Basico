.text
.globl foo1
foo1:
	pushl %ebp
	movl %esp, %ebp
	
	flds 8(%ebp)
	subl $8, %esp
	fstpl -8(%ebp)
	call sin
	addl $8, %esp
	flds 12(%ebp)
	faddp
	
	movl %ebp, %esp
	popl %ebp
	ret
