.global convert

convert:

    # Prologo
    pushq %rbp
    movq %rsp, %rbp

    cvtsi2sd %rdi, %xmm1 # Convierto rdi a doble prec
    movq $0x3ff8000000000000, %rax # Paso 1.5 a rax
    movq %rax, -0x8(%rbp) # De rax a pila
    movsd -0x8(%rbp), %xmm2 # De pila convertido a doble
    mulsd %xmm2 , %xmm0 # Multiplico 3.5 * 1.5
    addsd %xmm1, %xmm0 # Sumo y queda guardado en el retorno
    
    # Epilogo
    movq %rbp, %rsp
    popq %rbp
    ret

