.data
list: .byte 10, 20, 30, 40, 50, 60, 70, 80, 90, 100
newList: .space 10
length: .byte 10
format: .asciz "%d "

.text
.global main

main:

    pushq %rbp
    movq %rsp, %rbp
    xorq %rcx, %rcx
    movb length, %cl
    xorq %rbx, %rbx


apilar:

    lea list, %rsi
    xorq %rdx, %rdx
    movb (%rsi, %rbx, 1), %dl
    pushq %rdx
    incq %rbx
    loop apilar

intermedio:
    xorq %rbx, %rbx
    xorq %rcx, %rcx
    movb length, %cl

desapilar:

    lea newList, %rsi
    xorq %rdx, %rdx
    popq %rdx
    movb %dl, (%rsi, %rbx, 1)
    incq %rbx
    loop desapilar

intermedio2:
    xorq %rbx, %rbx
    xorq %rcx, %rcx
    movb length, %cl

mostrar:    
    lea format, %rdi
    lea newList, %r8
    xorq %rsi, %rsi
    movb (%r8, %rbx, 1), %sil
    xorq %rax, %rax
    pushq %rcx
    call printf
    popq %rcx
    incq %rbx
    loop mostrar

fin:
    movq %rbp, %rsp
    popq %rbp
    xorq %rax, %rax
    ret
