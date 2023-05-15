; SysCalls
global	_exit
global	fork
global	read
global	write
global	open
global	close
global	waitpid
global	execve
global	chdir
global	chmod
global	brk
global	stat
global	getcwd

global	sys_errno

section	.text

generic_syscall_1:
	push	ebp
	mov	ebp,esp
	push	ebx
	mov	ebx,[ebp+8]
	;mov	ecx,[ebp+12]
	;mov	edx,[ebp+16]
	int	0x80
	mov	edx,eax
	and	edx,0xfffff000
	cmp	edx,0xfffff000
	jnz	.okay
	mov	[sys_errno],eax
	mov	eax,-1
.okay:
	pop	ebx
	mov	esp,ebp
	pop	ebp
	ret
	
generic_syscall_2:
	push	ebp
	mov	ebp,esp
	push	ebx
	mov	ebx,[ebp+8]
	mov	ecx,[ebp+12]
	;mov	edx,[ebp+16]
	int	0x80
	mov	edx,eax
	and	edx,0xfffff000
	cmp	edx,0xfffff000
	jnz	.okay
	mov	[sys_errno],eax
	mov	eax,-1
.okay:
	pop	ebx
	mov	esp,ebp
	pop	ebp
	ret

generic_syscall_3:
	push	ebp
	mov	ebp,esp
	push	ebx
	mov	ebx,[ebp+8]
	mov	ecx,[ebp+12]
	mov	edx,[ebp+16]
	int	0x80
	mov	edx,eax
	and	edx,0xfffff000
	cmp	edx,0xfffff000
	jnz	.okay
	mov	[sys_errno],eax
	mov	eax,-1
.okay:
	pop	ebx
	mov	esp,ebp
	pop	ebp
	ret
	
_exit:
	mov	eax,1
	jmp	generic_syscall_1
fork:
	mov	eax,2
	jmp	generic_syscall_1
read:
	mov	eax,3
	jmp	generic_syscall_3
write:
	mov	eax,4
	jmp	generic_syscall_3
open:
	mov	eax,5
	jmp	generic_syscall_3
close:
	mov	eax,6
	jmp	generic_syscall_1
waitpid:
	mov	eax,7
	jmp	generic_syscall_3
execve:
	mov	eax,11
	jmp	generic_syscall_3
chdir:
	mov	eax,12
	jmp	generic_syscall_1
chmod:
	mov	eax,15
	jmp	generic_syscall_2
brk:
	mov	eax,45
	jmp	generic_syscall_1
stat:
	mov	eax,106
	jmp	generic_syscall_2
getcwd:
	mov	eax,183
	jmp	generic_syscall_2	

section	.bss
sys_errno	resd	1
