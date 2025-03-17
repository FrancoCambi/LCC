.data
num: .byte 5
result: .asciz "Resultado: %d\n"

.text
.global main

main:


    pushq %rbp
    movq %rsp, %rbp
    xorq %rcx, %rcx
    movb num, %cl
    movq $0x1, %rax
    cmpb $0x1, %cl
    jle fin

iterar: 

    mulb %cl
    loop iterar

fin: 

    movq %rax, -0x4(%rbp)
    leaq result, %rdi
    movq -0x4(%rbp), %rsi
    call printf
    movq %rbp, %rsp
    popq %rbp
    xorq %rax, %rax
    ret


