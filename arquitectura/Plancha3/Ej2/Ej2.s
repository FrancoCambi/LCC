.global solve

solve:

    # Epilogo

    pushq %rbp
    movq %rsp, %rbp

    # Guardar los argumentos en la pila

    movss %xmm0, -0x4(%rbp) # a
    movss %xmm1, -0x8(%rbp) # b
    movss %xmm2, -0xc(%rbp) # c
    movss %xmm3, -0x10(%rbp) # d
    movss %xmm4, -0x14(%rbp) # e
    movss %xmm5, -0x18(%rbp) # f

    # Calcular el determinante de la matriz de coef
    # (a * e) - (b * d)

    mulss %xmm0, %xmm4
    mulss %xmm1, %xmm3
    subss %xmm3, %xmm4
    movss %xmm4, %xmm14 # El determinante esta en xmm14

    # Chequeo si el determinante es cero
    xorps %xmm15, %xmm15
    ucomiss %xmm15, %xmm14
    jz noSol

    # si hay solucio, seguimos
    # recuperamos datos perdidos

    movss -0x10(%rbp), %xmm3
    movss -0x14(%rbp), %xmm4

    # Realizamos el calculo de y
    # det(A| fila y) / det(A)

    mulss %xmm0, %xmm5 # a * f
    mulss %xmm2, %xmm3 # c * d
    subss %xmm3, %xmm5 # det(A| fila y)
    divss %xmm14, %xmm5 # Valor de y

    # Guardamos el valor de y

    movss %xmm5, -0x20(%rbp)

    # Recuperamos valores perdidos
    movss -0x10(%rbp), %xmm3
    movss -0x18(%rbp), %xmm5

    # Realizamos el calculo de x
    # det(A|fila x) / det(A)

    mulss %xmm2, %xmm4 # c * e
    mulss %xmm1, %xmm5 # b * f
    subss %xmm5, %xmm4 # Det(A| fila x)
    divss %xmm14, %xmm4 # Valor de x

    # Guardamos el valor de x
    movss %xmm4, -0x1c(%rbp)

    # Recuperamos datos perdidos
    movss -0x18(%rbp), %xmm5
    movss -0x14(%rbp), %xmm4


    # Guardamos en los punteros

    movq -0x1c(%rbp), %rdx
    movq %rdx, (%rdi)

    movq -0x20(%rbp), %rbx
    movq %rbx, (%rsi)

    xorq %rax, %rax
    jmp fin


noSol:
    movl $-1, %eax

fin:
    movq %rbp, %rsp
    popq %rbp
    ret

