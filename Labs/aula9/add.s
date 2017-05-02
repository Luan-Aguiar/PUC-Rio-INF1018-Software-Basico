/*
int add (int a, int b, int c) {
  return a+b+c;
}
*/

.globl add
add:
	push %ebp
	movl %esp, %ebp
	movl 8(%ebp), %eax
	addl 12(%ebp), %eax
	addl 16(%ebp), %eax
	movl %ebp, %esp
	popl %ebp
	ret
