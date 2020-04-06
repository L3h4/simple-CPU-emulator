jmp start

data:
  nop
  nop
  nop


start:
  mov ax, 10
  cmp ax, 9
  je equ
  jg grd
  jl lss
  .finish:
  hlt

equ:
  mov ax, 22
  jmp .finish

grd:
  mov bx, 22
  jmp .finish

lss:
  mov cx, 22
  jmp .finish
