.data
nums:	.int	10, -21, -30, 45, 0
Sf:	.string "%d\n"		# string de formato para printf

.text
.globl	main
main:
/****** mantenha este trecho aqui e nao mexa - prologo !!!! */
        push    %ebp
        movl    %esp, %ebp
/*******/

	movl	$nums, %ecx	/* ecx = &nums; */
L1:	cmpl	$0, (%ecx)	/* if (ecx == 0) ? */
	je	L2		/* goto L2 */
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

	addl	$4, %ecx	/* ecx += 4; */
	jmp	L1		/* goto L1; */
L2:	movl	$0, %eax	/* eax = 0;  (valor de retorno) */

/****** mantenha este trecho aqui e nao mexa - finalizacao!!!! */
        movl    %ebp, %esp
        popl    %ebp
	ret			
/*******/



