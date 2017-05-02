.data
s1: .string "ls -ls"

.text
.globl main
main:
/* prologo */
pushl %ebp
movl  %esp, %ebp

/* coloque seu codigo aqui */
pushl $s1
call system
addl $4, %esp

/* finalizacao */
movl %ebp, %esp
popl %ebp
ret
