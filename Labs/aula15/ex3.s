.text

/*
int myopen (const char *pathname, int flags, int buffersize) {
  tamBufferAberto = buffersize;
  return open(pathname, flags);
}
*/
.globl myopen
myopen:	pushl %ebp
	movl %esp, %ebp
	pushl %ebx
	movl 16(%ebp), %edx
	movl $5, %eax
	movl 8(%ebp), %ebx
	movl 12(%ebp), %ecx
	int $0x80
	popl %ebx
	movl %ebp, %esp
	popl %ebp
	ret

/*
ssize_t myread(int fd, void *buf) {
  return read(fd, buf, tamBufferAberto);
}
*/
.globl myread
myread:	pushl %ebp
	movl %esp, %ebp
	push %ebx
	movl $3, %eax
	movl 8(%ebp), %ebx
	movl 12(%ebp), %ecx
	int $0x80
	popl %ebx
	movl %ebp, %esp
	popl %ebp
	ret

/*
ssize_t mywrite(int fd, const void *buf, size_t count) {
  return write(fd, buf, count);
}
*/
.globl mywrite
mywrite: pushl %ebp
	movl %esp, %ebp
	push %ebx
	movl $4, %eax
	movl 8(%ebp), %ebx
	movl 12(%ebp), %ecx
	movl 16(%ebp), %edx
	int $0x80
	popl %ebx
	movl %ebp, %esp
	popl %ebp
	ret

/*
int myclose(int fd) {
  return close(fd);
}
*/ 
.globl myclose
myclose: pushl %ebp
	movl %esp, %ebp
	push %ebx
	movl $6, %eax
	movl 8(%ebp), %ebx
	int $0x80
	popl %ebx
	movl %ebp, %esp
	popl %ebp
	ret


