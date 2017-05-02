.data
S2:	.byte	65, 108, 111, 32, 123, 103, 97, 108, 101, 114, 97, 125, 33, 0
Sf:	.string "%c"		# string de formato para printf
Sf2:	.string "\n"		# string de formato para printf

.text
.globl	main
main:
/****** mantenha este trecho aqui e nao mexa - prologo !!!! */
        push    %ebp
        movl    %esp, %ebp
	pushl	%ebx		/* salva ebx */
/*******/

	movl $S2, %ecx
L0:     cmpb $0, (%ecx)
	je L1
	movl (%ecx), %eax
	
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

/****** este trecho imprime o \n !!!! */
L1:     pushl   $Sf2
 	call	printf	
        addl    $8, %esp
/*******/

/****** mantenha este trecho aqui e nao mexa - finalizacao!!!! */
	popl	%ebx		
        movl    %ebp, %esp
        popl    %ebp
	ret			
/*******/


