/*void foo (int a[], int n) {
  int i;
  int s = 0;
  for (i=0; i<n; i++) {
    s += a[i];
    if (a[i] == 0) {
      a[i] = s;
      s = 0;
    }
  }
}*/

/*
int add (int a, int b, int c) {
  return a+b+c;
}
*/

.globl foo
foo:
	push %ebp
	movl %esp, %ebp
	
	
	movl $0, %eax		/* valor de soma = 0 */
	movl $0, %edx		/* i = 0; */
L0:	cmpl 12(%ebp), %edx	/* i < n ? */
	je L1
	movl $4, %ecx
	imull %edx, %ecx
	addl 8(%ebp), %ecx	/* soma o valor do endereço de a */
	addl (%ecx), %eax
	cmpl $0, (%ecx)
	jne A1
	movl %eax, (%ecx)
	movl $0, %eax		/* valor de soma = 0 */
A1:	addl $4, %ecx
	addl $1, %edx
	jmp L0

L1:	movl %ebp, %esp
	popl %ebp
	ret
