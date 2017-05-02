/*
int foo (int x) {
  return add(x);
}
*/
.text
.globl foo
foo:
	push %ebp
	movl %esp, %ebp
	
	push 8(%ebp)
	call add

	movl %ebp, %esp
	pop  %ebp
	ret
