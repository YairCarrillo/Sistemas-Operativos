segment .data
	nuevaLinea db  "" ,0xA
segment .bss
	i resb 1
segment .text
global _start
_start:
	mov al, '0'
bucle:

  mostrarValor:
	mov [i], al

	mov eax, 4
	mov ebx, 1
	mov ecx, i
	mov edx, 1
	int 0x80
  mostrarLinea:
	mov eax, 4
	mov ebx, 1
	mov ecx, nuevaLinea
	mov edx, 1
	int 0x80

  incrementar:
	mov al, [i]
	inc al

  comprobarFin:
	cmp al, 58
	je  salida
	jmp bucle

salida:
	mov eax, 1
	mov ebx, 0
	int 0x80
