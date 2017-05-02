/*
int add2 (struct X *x) {
  if (x == NULL) return 0;
  else return x->val + add2(x->next);
}
*/

.text
.globl add2
add2:
    push %ebp
    movl %esp, %ebp
    
    movl 8(%ebp), %ecx /* salva struct X *x */
    cmpl $0, %ecx       /* if(x == NULL) */
    je F0	       /* return 0; */
    
    pushl %ecx
    pushl 4(%ecx)
    call add2
    addl $4, %esp
    popl %ecx
    addl (%ecx), %eax

    jmp E0

F0: movl $0, %eax    
E0: movl %ebp, %esp
    popl %ebp
    ret
