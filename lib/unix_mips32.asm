# SysCalls MIPS32
 
.global	_exit
.global	fork
.global	read
.global	write
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


	
_exit:
	li 	$v0,4001
	syscall
	jr	$ra
fork:
	li 	$v0,4002
	syscall
	jr	$ra
read:
	li 	$v0,4003
	syscall
	jr	$ra
write:
	li 	$v0,4004
	syscall
	jr	$ra
open:
	li 	$v0,4005
	syscall
	jr	$ra
close:
	li 	$v0,4006
	syscall
	jr	$ra
waitpid:
	li 	$v0,4007
	syscall
	jr	$ra
execve:
	li 	$v0,4011
	syscall
	jr	$ra
chdir:
	li 	$v0,4012
	syscall
	jr	$ra
chmod:
	li 	$v0,4015
	syscall
	jr	$ra
brk:
	li 	$v0,4045
	syscall
	jr	$ra
stat:
	li 	$v0,4106
	syscall
	jr	$ra
getcwd:
	li 	$v0,4203	#4183
	syscall
	jr	$ra
	

.data
sys_errno:	.word	0
