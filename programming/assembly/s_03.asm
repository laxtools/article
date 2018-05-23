.386
;; 386 instruction set 

.model flat, stdcall
;; memory model
;; flat : far, near�� ������� �ʴ� ��  
;; stdcall : �Ķ���� ���� ���. �����ʿ��� ���� ������ ���ÿ� ����

option casemap :none
;; lable���� ��ҹ��� ����


include \masm32\include\windows.inc 
include \masm32\include\kernel32.inc 
include \masm32\include\masm32.inc 
;; include files

includelib \masm32\lib\kernel32.lib
includelib \masm32\lib\masm32.lib

.data 
	ProgramText 	db 	"Hello World!", 0
	BadText 		db 	"Error: Sum is incorrect value", 0
	GoodText 		db 	"Excellent. Sum is 6", 0
	Sum 			sdword 0


.code

start: 

	mov ecx, 6 	 		; ecx = 6	
	xor eax, eax 		; eax = 0

_label: add eax, ecx 	; eax += ecx  
	dec ecx  			; ecx--
	jnz _label  		; if ( ecx > 0 ) goto _label
	; eax = 6 + 5 + 4 + 3 + 2 + 1

	mov edx, 7  		; edx = 7
	mul edx  			; eax = edx * eax => ( 6 * 7 / 2 ) * 7 = 147
	push eax  			;  
	pop Sum  			; 
	cmp Sum, 147 		; cmp --> Sum - 147 �׸��� EFLAGS ����
	jz _good  				

_bad: invoke StdOut, addr BadText
	jmp _quit
	
_good: invoke StdOut, addr GoodText
	
_quit: invoke ExitProcess, 0

end start

;; console program

;; for loop�� if�� jz, jnz, jmp ������ �����Ѵ�
