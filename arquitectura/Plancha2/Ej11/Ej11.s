.data
strError: .asciz "Ingrese al menos un argumento\n"
strFin: .asciz "Cantidad de argumentos ingresados: %d. La suma es: %d\n"

.text
.global main

main:
    
    # Prologo
    pushq %rbp
    movq %rsp, %rbp
    subq $0x18, %rsp

    # Chequeo cantidad argumentos
    cmp $0x1, %rdi
    jle error

    # Seteo variables
    movq %rdi, -0x8(%rbp) # argc
    movq %rsi, -0x10(%rbp) # Direccion de argv[0]
    movq $0x0, -0x18(%rbp) # Suma total
    movq %rdi, %rcx # Cortador de loop
    decq %rcx # Decremento, pues el primer argumento no sirve
    movq $0x1, %rbx # i, arranca de 1 pues arv[0] no sirve

sumar:

    movq -0x10(%rbp), %rsi # Direccion de argv[0]

    movq (%rsi, %rbx, 8), %rdx # rbx -> argv[i], i >= 1
    movq %rdx, %rdi # Primer argumento atoi
    xorq %rax, %rax # Limpio salida
    incq %rbx # Incremento i
    pushq %rcx # Guardo contador de loop
    call atoi
    popq %rcx # Recupero

    movq %rax, %rdx # Muevo rax a rbx para hacer el cuadrado
    mulq %rdx
    addq %rax, -0x18(%rbp) # Agrego al total
    loop sumar # Repito

fin:

    leaq strFin, %rdi # direccion de str, primer argumento printf
    movq -0x8(%rbp), %rsi # Cantidad de argumentos, segundo argumento printf
    movq -0x18(%rbp), %rdx # Suma total, tercer argumento printf
    xorq %rax, %rax # No hay punto flotante
    call printf
    xorq %rax, %rax # Ret en 0

    # Epilogo
    movq %rbp, %rsp
    popq %rbp
    ret


error:

    leaq strError, %rdi
    xorq %rax, %rax
    call printf
    xorq %rax, %rax
    movq %rbp, %rsp
    popq %rbp
    ret
