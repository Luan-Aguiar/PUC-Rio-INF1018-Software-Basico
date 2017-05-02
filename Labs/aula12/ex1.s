.text
.globl foo
foo:
	pushl %ebp
	movl %esp, %ebp

	flds 16(%ebp)
	fldl 8(%ebp)
	fsubp
	flds 16(%ebp)
	fldl 8(%ebp)
	faddp
	fmulp
	
	movl %ebp, %esp
	popl %ebp
	ret
