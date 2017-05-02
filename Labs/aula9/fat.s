/*
int fat (int n) {
  if (n==0) return 1;
  else return n*fat(n-1);
}
*/

.globl fat
fat:
	push %ebp
	movl %esp, %ebp
	
	movl 8(%ebp), %eax	/* guarda o valor de n no eax */
	
F0:	cmpl $0, %eax	/* n == 0 */
	je F1		/* retorna 1 */
	movl %eax, %ecx /* guardar valor de n em ecx */
	subl $1, %ecx   /* calcular n - 1, em ecx */
	pushl %eax	/* salvar eax (n) */
	pushl %ecx	/* passa ecx (n-1) para a função */
	call fat	
	addl $4, %esp
	popl %edx	/* recupera n em edx */
	imull %edx, %eax /* multiplica o valor retornado por n */
	jmp F2		/* retorna valor da multiplicação */
	
F1:	movl $1, %eax	/* valor de retorno = 1 */

F2:	movl %ebp, %esp
	popl %ebp
	ret
