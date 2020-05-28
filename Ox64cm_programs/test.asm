entry start


text: string "Hello, world!"

start:
  mov bx, [text] 
  call print
  ;call exit
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
  mov cx, text
  .loop:
    cmp [cx], 0
    je .finish
    mov b b, [cx]
    syscall
    add cx, 1
    jmp .loop
   .finish:

  mov bx, 0xA
  syscall

  mov ax, 3
  syscall
  
  mov ax, 4 ; print
  syscall

  mov ax, 4 ; print
  syscall
  ret

exit:
  mov ax, 0
  mov bx, 0
  syscall