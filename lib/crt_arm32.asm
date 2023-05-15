@ CRT ARM32 
.global	_start
.extern	main
.text
_start:


	
	@bl	write
	

	
	
	
	ldr	r0,[sp]
	mov	r1,sp
	add	r1,r1,#4
	
	bl 	main
	
_exit:	
	@mov 	r0,#65		@ Return code
	mov 	r7,#1		@ _exit()
	swi 	0
	
write:
	stmfd sp!, {r7, lr}
	mov 	r7,#4	
	
	mov r0,#1
	mov r2,#19
	ldr r1,=string
		
	swi 	0
	@bx 	lr

	
	
	mov	r1,r0
	@and	r1,r1,#0xfffff000
	cmp	r1,#0xfffff000
	bne	.okay
	ldr	r1,=sys_errno
	str	r0,[r1]
	mov	r0,#-1
.okay:
	ldmfd	sp!, {r7, pc}

	
.data
string:
.ascii "Hello World String\n"

	
	
	

