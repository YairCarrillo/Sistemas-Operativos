SYS_EXIT  equ 1
SYS_READ  equ 3
SYS_WRITE equ 4
STDIN     equ 0
STDOUT    equ 1
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
 segment .text
global _start
_start:
obtenerCadena1:
  pedirCadena1:
    mov eax, SYS_WRITE
    mov ebx, STDOUT
    mov ecx, mensaje1
    mov edx, len1
    int 0x80
  leerCadena1:
    mov eax, SYS_READ
    mov ebx, STDIN
    mov ecx, cad1
    mov edx, 50d
    int 0x80
obtenerCadena2:
  pedirCadena2:
    mov eax, SYS_WRITE
    mov ebx, STDOUT
    mov ecx, mensaje2
    mov edx, len2
    int 0x80
  leerCadena2:
    mov eax, SYS_READ
    mov ebx, STDIN
    mov ecx, cad2
    mov edx, 50d
    int 0x80
obtenerCadena3:
  pedirCadena3:
    mov eax, SYS_WRITE
    mov ebx, STDOUT
    mov ecx, mensaje3
    mov edx, len3
    int 0x80
  leerCadena3:
    mov eax, SYS_READ
    mov ebx, STDIN
    mov ecx, cad3
    mov edx, 50d
    int 0x80
intercalar:
  moverCadenas:
    mov eax, cad1
    mov ebx, cad2
    mov edi, cad3
    mov esi, cad4
  moverCadena1:
    mov dl, byte[eax]
    cmp dl, 0xA
    je moverCadena2
    mov byte[esi], dl
    inc eax
    inc esi
  moverCadena2:
    mov dl, byte[ebx]
    cmp dl, 0xA
    je moverCadena3
    mov byte[esi], dl
    inc ebx
    inc esi
  moverCadena3:
    mov dl, byte[edi]
    cmp dl, 0xA
    je mostrarCadenaFinal
    mov byte[esi], dl
    inc edi
    inc esi
    jmp moverCadena1
mostrarCadenaFinal:
    inc esi
    mov byte[esi], 0xA
    mov eax, SYS_WRITE
    mov ebx, STDOUT
    mov ecx, mensaje4
    mov edx, len4
    int 0x80
    mov eax, SYS_WRITE
    mov ebx, STDOUT
    mov ecx, cad4
    mov edx, 151d
    int 0x80
salida:
    mov eax, SYS_EXIT
    mov ebx, 0
    int 0x80

