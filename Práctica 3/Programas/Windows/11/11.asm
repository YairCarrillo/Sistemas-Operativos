STDIN     equ dword -10
STDOUT    equ dword -11

segment .data
    mensaje1 db 'Ingrese la cadena:'
    len1 equ $- mensaje1
    mensaje2 db 'Longtud de la cadena:'
    len2 equ $- mensaje2
    longitud dw 0
    leido db 0
    handleConsola resd 0
segment .bss 
	cad resd 1515
	longitudCad resd 2
	

segment .text
    global _main
    extern    _GetStdHandle@4
    extern    _WriteConsoleA@20
    extern    _ReadConsoleA@20
    extern    _ExitProcess@4
_main:
	PedirCadena:
	push dword STDOUT
    call _GetStdHandle@4
    mov [handleConsola], eax
    push dword 0
    push dword leido
    push dword len1
    push dword mensaje1
    push dword [handleConsola]
    call _WriteConsoleA@20

    push dword STDIN
    call _GetStdHandle@4
    mov [handleConsola], EAX
    push dword 0
    push dword longitud
    push dword 1515
    push dword cad
    push dword [handleConsola]
    call _ReadConsoleA@20

    push dword STDOUT
    call _GetStdHandle@4
    mov [handleConsola], EAX
    push dword 0
    push dword leido
    push dword len2
    push dword mensaje2
    push dword [handleConsola]
    call _WriteConsoleA@20

    dec word[longitud]      ;Borramos el CR
    dec word[longitud]      ;Borramos el LF
    mov ax, word[longitud]  ;Aqui guardaremos la longitud de la cadena
    mov bx, 0               ;Contador de digitos de la longitud
    mov cx, 10              ;Nos servira para extraer los digitos de la longitud
    mov dx, 0               ;Residuo de las divisiones

enteroACadena:              ;Obtenemos digito por digito
    mov cx, 10              ;Divisor
    div cx                  ;Hacemos la division DX:AX / BX
    add dx, '0'             ;El residuo se almacena en DX y el cociente en AX, lo convertimos a caracter
    push dx                 ;Lo ponemos en el tope de la pila
    inc bx                  ;Incrementamos el numero de digitos
    mov dx, 0               ;Regresamos DX a 0 para que la division se haga correctamente
    cmp ax, 0               ;Preguntamos si ya terminamos de procesar el numero
    jne enteroACadena       ;No hemos terminado, repetimos

imprimirDigitos:            ;Imprimimos digito por digito desde la pila
    pop dx
    mov [longitudCad], dx
    
    push dword STDOUT
    call _GetStdHandle@4
    mov [handleConsola], eax
    push dword 0
    push dword leido
    push dword 1
    push dword longitudCad
    push dword [handleConsola]
    call _WriteConsoleA@20

    dec bx                  ;Ya tenemos un digito menos que procesar
    cmp bx, 0               ;Si ya no tenemos digitos pendientes,
    jne imprimirDigitos     ;nos salimos del bucle

salida:
    push dword 0
    call _ExitProcess@4

    



