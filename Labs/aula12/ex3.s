.text
.globl foo2
foo2:
	pushl %ebp
	movl %esp, %ebp
	
	flds 8(%ebp)
	subl $8, %esp
	fstpl -8(%ebp)
	call sin
	fstpl -8(%ebp)

	flds 12(%ebp)
	subl $8, %esp
	fstpl -16(%ebp)
	call cos
	fstpl -16(%ebp)
	
	fldl -8(%ebp)
	fldl -16(%ebp)
	faddp
	addl $16, %esp
	
	movl %ebp, %esp
	popl %ebp
	ret
