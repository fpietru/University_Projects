section .text
global smax
global umax

smax:
	mov eax, esi
	cmp edi, esi
	cmovge eax, edi
	ret

umax:
	mov eax, esi
	cmp edi, esi
	cmovae eax, edi
	ret