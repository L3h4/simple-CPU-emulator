jmp start

start:
  mov bx, 10
  mov cx, 10
  call multiply
  hlt

; bx, cx - in
; ax - out
multiply:
  push dx
  mov dx, 0
  mov ax, 0
  .loop:
    cmp dx, cx
    je .finish
    add ax, bx
    add dx, 1
    jmp .loop
  .finish:
  pop dx
  mov status, 0
  ret