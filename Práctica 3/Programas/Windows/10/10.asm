STDIN     equ dword -10
STDOUT    equ dword -11

segment .data
    mensaje1 db 'Ingrese la primer cadena: '
    len1 equ $- mensaje1
    mensaje2 db 'Ingrese la segunda cadena: '
    len2 equ $- mensaje2
    mensaje3 db 'Ingrese la tercer cadena: '
    len3 equ $- mensaje3
    mensaje4 db 'La cadena final es: '
    len4 equ $- mensaje4

segment .bss
    cad1 resb 50
    cad2 resb 50
    cad3 resb 50
    cad4 resb 151
    handle resb 1
    leido resb 2
 
segment .text
    global _start
    extern    _GetStdHandle@4
    extern    _WriteConsoleA@20
    extern    _ReadConsoleA@20
    extern    _ExitProcess@4

_start:

obtenerCadena1:
    
  pedirCadena1:
    push dword STDOUT
    call _GetStdHandle@4
    mov [handle], EAX
    push dword 0
    push dword leido
    push dword len1
    push dword mensaje1
    push dword [handle]
    call _WriteConsoleA@20

  leerCadena1:
    push dword STDIN
    call _GetStdHandle@4
    mov [handle], EAX
    push dword 0
    push dword leido
    push dword 50
    push dword cad1
    push dword [handle]
    call _ReadConsoleA@20

obtenerCadena2:
    
  pedirCadena2:
    push dword STDOUT
    call _GetStdHandle@4
    mov [handle], EAX
    push dword 0
    push dword leido
    push dword len2
    push dword mensaje2
    push dword [handle]
    call _WriteConsoleA@20

  leerCadena2:
    push dword STDIN
    call _GetStdHandle@4
    mov [handle], EAX
    push dword 0
    push dword leido
    push dword 50
    push dword cad2
    push dword [handle]
    call _ReadConsoleA@20

obtenerCadena3:
    
  pedirCadena3:
    push dword STDOUT
    call _GetStdHandle@4
    mov [handle], EAX
    push dword 0
    push dword leido
    push dword len3
    push dword mensaje3
    push dword [handle]
    call _WriteConsoleA@20

  leerCadena3:
    push dword STDIN
    call _GetStdHandle@4
    mov [handle], EAX
    push dword 0
    push dword leido
    push dword 50
    push dword cad3
    push dword [handle]
    call _ReadConsoleA@20

intercalar:

  moverCadenas:
    mov EAX, cad1
    mov EBX, cad2
    mov EDI, cad3
    mov ESI, cad4

  moverCadena1:
    mov DL, byte[EAX]
    cmp DL, 0xD
    je moverCadena2

    mov byte[ESI], DL
    inc EAX
    inc ESI

  moverCadena2:
    mov DL, byte[EBX]
    cmp DL, 0xD
    je moverCadena3

    mov byte[ESI], DL
    inc EBX
    inc ESI

  moverCadena3:
    mov DL, byte[EDI]
    cmp DL, 0xD
    je mostrarCadenaFinal

    mov byte[ESI], DL
    inc EDI
    inc ESI
    jmp moverCadena1


mostrarCadenaFinal:
    push dword STDOUT
    call _GetStdHandle@4
    mov [handle], EAX
    push dword 0
    push dword leido
    push dword len4
    push dword mensaje4
    push dword [handle]
    call _WriteConsoleA@20

    push dword STDOUT
    call _GetStdHandle@4
    mov [handle], EAX
    push dword 0
    push dword leido
    push dword 151
    push dword cad4
    push dword [handle]
    call _WriteConsoleA@20

salida:
    push dword 0
    call _ExitProcess@4
