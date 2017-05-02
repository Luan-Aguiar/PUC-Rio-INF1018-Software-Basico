.data
Sf:	.string "%d\n"		# string de formato para printf

.text
.globl	main
main:
/****** mantenha este trecho aqui e nao mexa - prologo !!!! */
        push    %ebp
        movl    %esp, %ebp
	pushl	%ebx		/* salva ebx */
/*******/

	movl $1, %ecx
L0:	cmpl $11, %ecx
	je L1
	movl %ecx, %eax
	imull %eax, %eax
	
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

	addl $1, %ecx
	jmp L0

/****** mantenha este trecho aqui e nao mexa - finalizacao!!!! */
L1:	popl	%ebx		
        movl    %ebp, %esp
        popl    %ebp
	ret			
/*******/


