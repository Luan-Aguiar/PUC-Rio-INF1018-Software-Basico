/*
int add (struct X *x) {
  int a = 0;
  for (; x != NULL; x = x->next)
    a += x->val;
  return a;
}

int add2 (struct X *x) {
  if (x == NULL) return 0;
  else return x->val + add2(x->next);
}
*/

.globl add
add:
     push %ebp
     movl %esp, %ebp
  
     movl 8(%ebp), %ecx
     movl $0, %eax
L0:  cmpl $0, %ecx
     je E0
     movsbl (%ecx), %edx
     addl %edx, %eax
     movl 4(%ecx), %ecx	/* Move 4 bytes (1 - char / 3 - padding) */
     jmp L0

E0:  movl %ebp, %esp
     popl %ebp
     ret

.text
.globl add2
add2:
    push %ebp
    movl %esp, %ebp
    
    movl 8(%ebp), %ecx /* salva struct X *x */
    cmpl $0, %ecx       /* if(x == NULL) */
    je F1	       /* return 0; */
    
    pushl %ecx
    pushl 4(%ecx) 	/* Move 4 bytes (1 - char / 3 - padding) */
    call add2
    addl $4, %esp
    popl %ecx
    movsbl (%ecx), %edx
    addl %edx, %eax

    jmp E1

F1: movl $0, %eax    
E1: movl %ebp, %esp
    popl %ebp
    ret
