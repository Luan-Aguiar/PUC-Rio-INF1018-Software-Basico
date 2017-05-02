/*
int add (struct X *x) {
  int a = 0;
  for (; x != NULL; x = x->next)
    a += x->val;
  return a;
}
*/

.text

.globl add
add:
     push %ebp
     movl %esp, %ebp
  
     movl 8(%ebp), %ecx
     movl $0, %eax
L0:  cmpl $0, %ecx
     je E0
     addl (%ecx), %eax
     movl 4(%ecx), %ecx
     jmp L0

E0:  movl %ebp, %esp
     popl %ebp
     ret
  
