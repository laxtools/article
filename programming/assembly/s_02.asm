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
include \masm32\include\user32.inc 
;; include files

includelib \masm32\lib\kernel32.lib
includelib \masm32\lib\user32.lib

.data 
;; all data 

	HelloWorld db "Hello World!", 0 
;; db : define byte
;; 0 : NUL


.code
;; all code

start: 
;; start label

	invoke MessageBox, NULL, addr HelloWorld, addr HelloWorld, MB_OK
;; call function

	invoke ExitProcess, 0
;; 0 is an argument 

end start


;; ml /c /Zd /coff s_01.asm 
;; link /SUBSYSTEM:WINDOWS s_01.obj 
;; s_01.exe ����. 



