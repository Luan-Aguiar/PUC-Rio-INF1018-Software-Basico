/*double foo3 (double *a, int n) {
  int i;
  double r = 0.0;
  for (i=0; i<n; i++) {
    r += sin(*a);
    a++;
  }
  return r;
}
*/
.text
.globl foo3
foo3:
	pushl %ebp
	movl %esp, %ebp
	
	movl 8(%ebp), %eax /* eax -> a */
	
	subl $8, %esp /* double r */
	movl %esp, %edx /* edx -> r */
	fildl $0
	fstpl (%edx) // r = 0.0
	movl $0, %ecx /* i = 0 */
	
l0:	cmpl 12(%ebp), %ecx
	je l1
	
		

	addl $1, %eax // a++
	jmp l0	

l1:	movl %ebp, %esp
	popl %ebp
	ret
