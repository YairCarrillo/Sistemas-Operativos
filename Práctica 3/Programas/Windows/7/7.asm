segment .bss 
	handleConsola resd 1			;Primer argumento para la llamada al sistema _ReadConsoleA()
	cadLeer resd 30					;Segundo argumento para la llamada al sistema _ReadConsoleA()
	longitudCadena resd 1 			;Tercer argumento para la llamada al sistema _ReadConsoleA()
	caractLeidos resd 1				;Cuarto argumento para la llamada al sistema _ReadConsoleA()
	ultimoArgumento resd 1 			;Quinto argumento para la llamada al sistema _ReadConsoleA()
segment .text
global _main
extern _GetStdHandle@4				;Acceso externo a la llamado al sistema _GetStdHandle()
extern _WriteConsoleA@20				;Acceso externo a la llamado al sistema _WriteConsoleA()
extern _ReadConsoleA@20				;Acceso externo a la llamado al sistema _ReadConsoleA()
extern _ExitProcess@4				;Acceso externo a la llamado al sistema _ExitProcess()
_main:
	push dword-10					;Argumento pasado por la pila y usado en _GetStdHandle() para la entrada estandar
	call _GetStdHandle@4			;Invocación de _GetStdHanle()
	mov [handleConsola],eax			;Devolucion del manejador de consola para la lectura en el registro

	xor eax,eax						;Limpieza del registro eax (eax=0)
	mov eax,30d						;eax=30 caracteres de longitud de la cadena a leer 
	mov [longitudCadena],eax		;Se guarda la longitud en memoria 
	xor eax,eax						;Limpieza del registro eax (eax=0)
	mov eax,0d						;eax=0 valor del ultimo argumento de _ReadConsoleA()
	mov [ultimoArgumento],eax		;Se guarda el valor del ultimo argumento en memoria

	push dword [ultimoArgumento]	;Quinto argumento de _ReadConsoleA() pasado por la pila 
	push dword caractLeidos 		;Cuarto argumento de _ReadConsoleA() pasado por la pila
	push dword [longitudCadena]		;Tercer argumento de _ReadConsoleA() pasado por la pila
	push dword cadLeer 				;Segundo argumento de _ReadConsoleA() pasado por la pila
	push dword [handleConsola]		;Primer argumento de _ReadConsoleA() pasado por la pila
	call _ReadConsoleA@20

	xor eax,eax						;Limpieza del registro eax (eax=0)
	push dword-11					;Argumento pasado por la pila y usado en _GetStdHandle() para la salida estandar
	call _GetStdHandle@4			;Invocacion de _GetStdHandle()
	mov [handleConsola],eax			;Devolucion del manejador de consola para escritura en el registro eax

	xor eax,eax						;Limpieza del registro eax(eax=0)
	mov eax,30d						;eax=30 caracteres del longitud de la cadena a imprimir
	mov [longitudCadena],eax		;Se guarda la longitud en memoria
	xor eax,eax						;Limpieza del registro eax(eax=0)
	mov eax,0d						;eax=0 valor del ultimo argumento de _WriteConsoleA()
	mov [ultimoArgumento],eax		;Se guarda el valor del ultimo argumento en memoria

	push dword [ultimoArgumento]	;Quinto argumento de WriteConsoleA() pasado por la pila 
	push dword caractLeidos 		;Cuarto argumento de WriteConsoleA() pasado por la pila
	push dword [longitudCadena]		;Tercer argumento de WriteConsoleA() pasado por la pila
	push dword cadLeer 				;Segundo argumento de WriteConsoleA() pasado por la pila
	push dword [handleConsola]		;Primer argumento de WriteConsoleA() pasado por la pila
	call _WriteConsoleA@20			;Invocacion de WriteConsoleA()

	xor eax,eax									;Limpieza del registro eax(eax=0)
	mov eax,0d									;eax=0 valor del argumento de _ExitProcess()
	mov [ultimoArgumento],eax					;Se guarda el valor del argumento en memoria
	push dword [ultimoArgumento]				;Argumento del ExitProcess() pasado por la pila
	call _ExitProcess@4							;Invocacion de ExitProcess()