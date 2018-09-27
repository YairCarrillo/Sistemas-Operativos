segment .data
	cadImprimir db 'Ensamblado en Windows',0xA	;Segundo argumento para la llamada al sistema _WriteConsoleA()
segment .bss 
	handleConsola resd 1						;Primer argumento para la llamada al sistema _WriteConsoleA()
	longitudCadena resd 1						;Tercer argumento para la llamada al sistema _WriteConsoleA()
	caractEscritos resd 1						;Cuarto argumento para la llamada al sistema _WriteConsoleA()
	ultimoArgumento resd 1						;Quinto argumento para la llamada al sistema _WriteConsoleA()
segment .text
global _main
extern _GetStdHandle@4							;Acceso externo a la llamda al sistema _GetStdHandle()
extern _WriteConsoleA@20						;Acceso externo a la llamda al sistema _WriteConsoleA()
extern _ExitProcess@4							;Acceso externo a la llamda al sistema _ExitProcess()
_main:
	push dword-11								;Argumento pasado por la pila y usado en _GetStdHandle() para la salida estandar
	call _GetStdHandle@4						;Invocación de GetStdHandle()
	mov [handleConsola],eax						;Devolucion del manejador de consola para escribir en el registro eax

	xor eax,eax									;Limpieza del registro eax(eax=0)
	mov eax,23d									;eax=23 caracteres de longitud de la cadena a imprimir
	mov [longitudCadena],eax					;Seguarda la longitud en memoria 
	xor eax,eax									;Limpieza del registro eax(eax=0)
	mov eax,0d									;eax=0 valor del ultimo argumento de _WriteConsoleA()
	mov [ultimoArgumento],eax					;Se guarda el valor del ultimo arguento en memoria

	push dword [ultimoArgumento]				;Quito argumento de _WriteConsoleA() pasado a la pila
	push dword caractEscritos 					;Cuarto argumento de _WriteConsoleA() pasado a la pila
	push dword [longitudCadena]					;Tercer argumento de _WriteConsoleA() pasado a la pila
	push dword cadImprimir 						;Segundo argumento de _WriteConsoleA() pasado a la pila
	push dword [handleConsola]					;Primer argumento de _WriteConsoleA() pasado a la pila
	call _WriteConsoleA@20						;Invocación de _WriteConsoleA()

	xor eax,eax									;Limpieza del registro eax(eax=0)
	mov eax,0d									;eax=0 valor del argumento de _ExitProcess()
	mov [ultimoArgumento],eax					;Se guarda el valor del argumento en memoria
	push dword [ultimoArgumento]				;Argumento del ExitProcess() pasado por la pila
	call _ExitProcess@4							;Invocacion de ExitProcess()