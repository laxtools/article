section .text
	global main 

main: 
	mov edx, len
	mov ecx, msg
	mov ebx, 1 		; file (stdout)
	mov eax, 4 		; sys_write
	int 0x80  		; call 
	mov eax, 1		; sys_exit
	int 0x80 		; call

section .data 
msg db 'Hello, world!', 0xa 	; string . db? 
len equ $ - msg 				; length of the string. $? 


;;
;; nasm -f win32 hello_world.asm  
;; link /subsystem:console /nodefaultlib /entry:main hello_world.obj 
;; 
