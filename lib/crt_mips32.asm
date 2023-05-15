# CRT MIPS32 
.global	__start
.extern	main
.text
__start:

	lw 	$a0,0($sp)
	move	$a1,$sp
	addi	$a1,$a1,4
	
	jal 	main
	
_exit:	
	move 	$a0,$v0		# Return code
	li 	$v0,4001	# _exit()
	syscall
	

	
	
	

