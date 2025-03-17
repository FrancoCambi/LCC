.data
list: .long 10, 20, 30, 40, 50, 60, 70, 80, 90, 100
length: .byte 10
sumaStr: .asciz "Suma total: %d\n"

.text
.global main

main:

    pushq %rbp
    movq %rsp, %rbp
    xorq %rcx, %rcx
    movb length, %cl # Iterador (i)
    xorq %rbx, %rbx
    movl $0x0, -0x4(%rbp) # Holder de suma


sumar:

    lea list, %esi
    movl (%esi, %ebx, 4), %edx # edx -> list[i]
    addl %edx, -0x4(%rbp)
    incl %ebx
    loop sumar

fin:

    leaq sumaStr, %rdi
    movq -0x4(%rbp), %rsi
    call printf
    movq %rbp, %rsp
    popq %rbp
    xorq %rax, %rax
    ret

    