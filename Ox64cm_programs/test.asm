jmp start

start:
  .loop:
    cmp ax, 10
    je .finish
    add ax, 1
    jmp .loop
  .finish:
  hlt

