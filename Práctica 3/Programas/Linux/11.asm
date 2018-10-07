SYS_EXIT  equ 1
SYS_READ  equ 3
SYS_WRITE equ 4
STDIN     equ 0
STDOUT    equ 1
segment .data
    mensaje1 db 'Ingrese una cadena: '
    len1 equ $- mensaje1
    mensaje2 db 'La longitud de la cadena que ingresaste es: '
    len2 equ $- mensaje2
    cr db 0xA
segment .bss
    cad resb 1515
    digito resb 1
    temp resb 16
segment .text
global _start
_start:
pedirCadena:
    mov eax, SYS_WRITE
    mov ebx, STDOUT
    mov ecx, mensaje1
    mov edx, len1
    int 0x80

    mov eax, SYS_READ
    mov ebx, STDIN
    mov ecx, cad
    mov edx, 1515
    int 0x80

    mov esi, cad            ;Movemos la cadena leida a este registro

mostrarAvisoLongitud:
    mov eax, SYS_WRITE
    mov ebx, STDOUT
    mov ecx, mensaje2
    mov edx, len2
    int 0x80
    mov ax, 0               ;Aqui guardaremos la longitud de la cadena
    mov bx, 10              ;Nos servira para extraer los digitos de la longitud
    mov cx, 0               ;Contador de digitos de la longitud
    mov dx, 0               ;Residuo de las divisiones

calculoLongitud:
    mov BL, byte[esi]       ;Copiamos el byte actual de la cadena
    cmp BL, 0xA             ;Preguntamos si estamos en el fin
    je  enteroACadena       ;Si si estamos, ya terminamos de contar
    inc esi                 ;Si no, incrementamos el puntero de la cadena
    inc ax                  ;y el contador de la longitud
    jmp calculoLongitud     ;Bucle

enteroACadena:              ;Obtenemos digito por digito
    mov bx, 10              ;Divisor
    div bx                  ;Hacemos la division dx:ax / bx
    add dx, '0'             ;El residuo se almacena en dx y el cociente en ax, 
                            ;lo convertimos a caracter
    push dx                 ;Lo ponemos en el tope de la pila
    inc cx                  ;Incrementamos el numero de digitos
    mov dx, 0              
    cmp ax, 0               ;Preguntamos si ya terminamos de procesar el numero
    jne enteroACadena       ;No hemos terminado, repetimos

imprimirDigitos:            ;Imprimimos digito por digito desde la pila
    pop dx
    mov [digito], dx
    mov [temp], cx          ;Guardamos el valor de cx para que no se pierda
    mov eax, SYS_WRITE
    mov ebx, STDOUT
    mov ecx, digito
    mov edx, 1
    int 0x80
    mov cx, [temp]          ;Restauramos el valor de cx
    dec cx                  ;Ya tenemos un digito menos que procesar
    cmp cx, 0               ;Si ya no tenemos digitos pendientes,
    jne imprimirDigitos     ;nos salimos del bucle

salida:
    mov eax, SYS_WRITE
    mov ebx, STDOUT
    mov ecx, cr
    mov edx, 1
    int 0x80

    mov eax, SYS_EXIT
    mov ebx, 0
    int 0x80
