/*
int foo(int x) {
	return x + 1;
}
*/
.text
.globl foo
foo:
	push %ebp
	movl %esp, %ebp
	
	movl 8(%ebp), %eax
	addl $1, %eax

	movl %ebp, %esp
	pop  %ebp
	ret
