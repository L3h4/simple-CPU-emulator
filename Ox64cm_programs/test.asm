jmp start

start:
  call print
  call exit
  hlt

; bx, cx - in
; ax - out
;multiply:
;  push dx
;  mov dx, 0
;  mov ax, 0
;  .loop:
;    cmp dx, cx
;    je .finish
;    add ax, bx
;    add dx, 1
;    jmp .loop
;  .finish:
;  pop dx
;  mov status, 0
;  ret

print:
  mov ax, 1
  mov bx, 0x41
  mov cx, 0
  .loop:
    cmp cx, 26
    je .finish
    syscall
    add cx, 1
    add bx, 1
    jmp .loop
   .finish:

  mov bx, 0xA
  syscall
  mov ax, 3 ; print
  syscall
  mov ax, 2
  syscall
  ret

exit:
  mov ax, 0
  mov bx, 0
  syscall