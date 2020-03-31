;jmp start

data:
  nop
  nop
  nop

; TODO fix size modifiers priorities

start:

  mov w A, B
  mov b AX, BX
  mov A, BX
  mov AX, B

  mov [A], [B]
  mov byte [AX], [BX]
  mov [A], [BX]
  mov [AX], [B]

  mov BX, 0x10
  mov w [0x0123], [0x0123]
  mov b [ax], [sp]
  mov b [0x44], 0xFFE

  mov b [0x0133], data
  mov b [start], data
  nop