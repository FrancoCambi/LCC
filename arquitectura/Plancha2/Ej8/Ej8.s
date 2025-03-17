.data
format: .asciz "%ld\n"
formatEx: .asciz "%x\n"
i: .quad 0x00000010

.text
.global main

main:

    pushq %rbp
    movq %rsp, %rbp

    movq $format, %rdi # El primer argumento es el formato.
    movq $1234, %rsi # El valor a imprimir.
    xorq %rax, %rax # Cantidad de valores de punto flotante.
    call printf

    #a
    leaq formatEx, %rdi
    movq %rsp, %rsi
    xorq %rax, %rax
    call printf

    #b
    leaq formatEx, %rdi
    leaq format, %rsi
    xorq %rax, %rax
    call printf

    #c
    leaq formatEx, %rdi
    leaq formatEx, %rsi
    xorq %rax, %rax
    call printf

    #d
    leaq format, %rdi
    movq (%rsp), %rsi
    xorq %rax, %rax
    call printf

    #e
    leaq format, %rdi
    addq $8, %rsp
    movq (%rsp), %rsi
    xorq %rax, %rax
    call printf

    #f
    leaq format, %rdi
    movq i, %rsi
    xorq %rax, %rax
    call printf

    #g
    leaq format, %rdi
    leaq i, %rsi
    xorq %rax, %rax
    call printf

    movq %rbp, %rsp
    popq %rbp
