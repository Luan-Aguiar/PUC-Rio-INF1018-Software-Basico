/*
int nums[] = {10, -21, -30, 45};
int main() {
  int i, *p;
  for (i = 0, p = nums; i != 4; i++, p++)
    if ((*p % 2) == 0)
      printf("%d\n", *p);
  return 0;
}
*/

.data
nums:	.int	10, -21, -30, 45
Sf:	.string "%d\n"		# string de formato para printf

.text
.globl	main
main:
/****** mantenha este trecho aqui e nao mexa - prologo !!!! */
        push    %ebp
        movl    %esp, %ebp
	pushl	%ebx		/* salva ebx */
/*******/

	movl	$0, %ebx	/* ebx = 0; */
	movl	$nums, %ecx	/* ecx = &nums; */
L1:	cmpl	$4, %ebx	/* if (ebx == 4) ? */
	je	L2		/* goto L2 */
	testl	$1, (%ecx)	/* if ((*p % 2)!= 0) */
	jne	L3		/* goto L3 */
	movl	(%ecx), %eax	/* eax = *ecx; */
	
/****** este trecho imprime o valor de %eax (nao mexa) !!!! */
/* pode estragar o valor de %eax           ******/
        pushl   %ecx
        pushl   %edx
        pushl   %eax
        pushl   $Sf
 	call	printf	
        addl    $8, %esp
        popl   %edx
        popl   %ecx
/*******/

L3:	addl	$1, %ebx	/* ebx += 1; */
	addl	$4, %ecx	/* ecx += 4; */
	jmp	L1		/* goto L1; */
L2:	movl	$0, %eax	/* eax = 0;  (valor de retorno) */

/****** mantenha este trecho aqui e nao mexa - finalizacao!!!! */
	popl	%ebx		
        movl    %ebp, %esp
        popl    %ebp
	ret			
/*******/



