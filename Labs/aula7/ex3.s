.data
S2:	.byte	65, 108, 111, 32, 123, 103, 97, 108, 101, 114, 97, 125, 33, 0
Sf:	.string "%d\n"		# string de formato para printf

.text
.globl	main
main:
/****** mantenha este trecho aqui e nao mexa - prologo !!!! */
        push    %ebp
        movl    %esp, %ebp
	pushl	%ebx		/* salva ebx */
/*******/

	movl $S2, %ecx
	movl $0, %eax
L0:	cmpb $0, (%ecx)
	je L1
	addl $1, %eax
	addl $1, %ecx
	jmp L0

/****** este trecho imprime o valor de %eax (nao mexa) !!!! */
/* pode estragar o valor de %eax           ******/
L1:     pushl   %ecx
        pushl   %edx
        pushl   %eax
        pushl   $Sf
 	call	printf	
        addl    $8, %esp
        popl   %edx
        popl   %ecx
/*******/

/****** mantenha este trecho aqui e nao mexa - finalizacao!!!! */
	popl	%ebx		
        movl    %ebp, %esp
        popl    %ebp
	ret			
/*******/
