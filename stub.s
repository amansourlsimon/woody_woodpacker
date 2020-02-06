global stub
global stub_len

section .text
stub:

stub_start:
	jmp woody_string

stub_len: dq stub_end - stub

stub_core:
	mov rax, 1
	mov rdi, 1
	pop rsi				; pop message of the stack
	mov rdx, 9
	syscall				; write(1, "Woody...\n", 9)
	ret

woody_string:
	call stub_core
	db "Woody...", 10	; put message on the stack

stub_end:
