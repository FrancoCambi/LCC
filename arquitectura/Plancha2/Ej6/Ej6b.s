.data
list: .long 10, 20, 30, 40, 50, 60, 70, 80, 90, 100
length: .byte 10
sumaStr: .asciz "Suma total: %d\nMax: %d\nMin: %d\nPromedio: %d\n"

.text
.global main

main:

    pushq %rbp
    movq %rsp, %rbp
    xorq %rcx, %rcx
    movb length, %cl # Iterador (i)
    xorq %rbx, %rbx
    movl $0x0, -0x4(%rbp) # Holder de suma
    movl list, %eax # list[0]
    movl %eax, -0x8(%rbp) # Holder de max
    movl %eax, -0xc(%rbp) # Holder de min
    movl $0x0, -0x10(%rbp) # Holder de promedio
    lea list, %esi


mover:
    movl (%esi, %ebx, 4), %edx # edx -> list[i]

comparaMayor:
    cmpl -0x8(%rbp), %edx
    jle comparaMenor
    movl %edx, -0x8(%rbp)


comparaMenor:
    cmpl -0xc(%rbp), %edx
    ja sumar
    movl %edx, -0xc(%rbp)

sumar:

    addl %edx, -0x4(%rbp)
    incl %ebx
    loop mover

promedio:

    movl -0x4(%rbp), %eax
    idivb length
    movl %eax, -0x10(%rbp)

fin:

    leaq sumaStr, %rdi
    movq -0x4(%rbp), %rsi
    movq -0x8(%rbp), %rdx
    movq -0xc(%rbp), %rcx
    movq -0x10(%rbp), %r8
    call printf
    movq %rbp, %rsp
    popq %rbp
    xorq %rax, %rax
    ret

    