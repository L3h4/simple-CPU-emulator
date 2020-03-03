jmp start; комментарий


; комментарий 2
start:
  mov A, 10
  mov BX, 0x10
  mov word [0x0123], [0x0123]
  mov b [ax], [sp]
  nop