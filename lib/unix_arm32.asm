@ SysCalls ARM32
 
.global	_exit
.global	fork
.global	read
.global	write
.global	write2
.global	open
.global	close
.global	waitpid
.global	execve
.global	chdir
.global	chmod
.global	brk
.global	stat
.global	getcwd

.global	sys_errno

.text


	
@_exit:
@	li 	$v0,4001
@	syscall
@	jr	$ra
@fork:
@	li 	$v0,4002
@	syscall
@	jr	$ra
@read:
@	li 	$v0,4003
@	syscall
@	jr	$ra
write:
	stmfd sp!, {r7, lr}
	mov 	r7,#4	
	
	mov r0,#1
	mov r2,#19
	ldr r1,=string
		
	swi 	0
	bx 	lr

	
	
	mov	r1,r0
	@and	r1,r1,#0xfffff000
	cmp	r1,#0xfffff000
	bne	.okay
	ldr	r1,=sys_errno
	str	r0,[r1]
	mov	r0,#-1
.okay:
	ldmfd	sp!, {r7, pc}
	

write2:
	@stmfd sp!, {r7, lr}
	push	{r7, lr}
	
	
	mov 	r7,#4	
	
	mov 	r0,#1
	mov 	r2,#19
	ldr 	r1,=string
		
	swi 	0
	
	

	@add	r0,r0,#4
	pop 	{r7,pc}
	@bx 	lr

	
	
	@ldmfd	sp!, {r7, pc}
	


open:
@	li 	$v0,4005
@	syscall
@	jr	$ra
close:
@	li 	$v0,4006
@	syscall
@	jr	$ra
waitpid:
@	li 	$v0,4007
@	syscall
@	jr	$ra
execve:
@	li 	$v0,4011
@	syscall
@	jr	$ra
chdir:
@	li 	$v0,4012
@	syscall
@	jr	$ra
chmod:
@	li 	$v0,4015
@	syscall
@	jr	$ra
brk:
@	li 	$v0,4045
@	syscall
@	jr	$ra
stat:
@	li 	$v0,4106
@	syscall
@	jr	$ra
getcwd:
@	li 	$v0,4183
@	syscall
@	jr	$ra
	

.data
sys_errno:	.word	0


string:	.ascii 	"Hello World String\n"
