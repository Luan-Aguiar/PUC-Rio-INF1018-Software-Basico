/*
int add (int a, int b, int c) {
  return a+b+c;
}
*/

.globl add1
add1:
	push %ebp
	movl %esp, %ebp
	
	movl 8(%ebp), %ecx	/* guarda o valor de a */
	movl $0, %eax		/* valor de retorno = 0 */
	movl $0, %edx		/* i = 0; */
L0:	cmpl 12(%ebp), %edx	/* i < n ? */
	je L1
	addl (%ecx), %eax
	addl $4, %ecx
	addl $1, %edx
	jmp L0

L1:	movl %ebp, %esp
	popl %ebp
	ret
