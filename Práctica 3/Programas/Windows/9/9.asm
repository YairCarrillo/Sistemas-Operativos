segment .data
	nuevaLinea db "",0xA
segment .bss
	contador resd 1
	handleConsola resd 1			
	leido resd 1			
			
segment .text
global _main
extern _GetStdHandle@4				
extern _WriteConsoleA@20				
extern _ExitProcess@4		
_main:
	mov al,'0'
bucle:
	ImprimirValor:
		mov [contador],al
		push dword-11
		call _GetStdHandle@4			
		mov [handleConsola],eax			

		push dword 0	
		push dword leido 					
		push dword 1		
		push dword contador 				
		push dword [handleConsola]		
		call _WriteConsoleA@20

		push dword-11
    	call _GetStdHandle@4
   		mov [handleConsola], eax
   		push dword 0
    	push dword leido
    	push dword 1
    	push dword nuevaLinea
    	push dword [handleConsola]
    	call _WriteConsoleA@20


	Incrementar:
		 mov al,[contador]
		 inc al
	comprobar:
	cmp al,58
	je salida
	jmp bucle

	salida:
		push dword 0
		call _ExitProcess@4
