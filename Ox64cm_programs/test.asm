entry start


text: string "Hello world!"

start:
  call print
  hlt

print:
  mov ax, 1
  mov cx, text
  .loop:
    cmp [cx], 0
    je .finish
    mov byte b, [cx]
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
  ret
