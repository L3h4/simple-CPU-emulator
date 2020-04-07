jmp start

data:
  nop
  nop
  nop


start:
  ;jmp 0x7F0
  mov ax, [0x07F0]
  mov [0x07FF], 1
  .finish:
  hlt

