/*
#include <stdio.h>

int nums[4] = {65, -105, 111, 34};

int main (void) {
  int i;
  int s = 0;

  for (i=0;i<4;i++)
    s = s+nums[i];

  printf ("soma = %d\n", s);

  return 0;
}
*/

.data
Nums:	.int	65, -105, 111, 34
Sf:	.string "soma = %d\n"		# string de formato para printf

.text
.globl	main
main:
/****** mantenha este trecho aqui e nao mexa - prologo !!!! */
        push    %ebp
        movl    %esp, %ebp
	pushl	%ebx		/* salva ebx */
/*******/
	
	movl $0, %eax		/* soma = 0 */
	movl $0, %ecx
L0:	cmpl $4, %ecx
	je L1
	movl $4, %edx
	imull %ecx, %edx
	addl $Nums, %edx
	addl (%edx), %eax
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


