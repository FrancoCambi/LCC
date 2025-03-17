
.text
.global fact

fact:
    pushq %rbp
    movq %rsp, %rbp
    movq $0x1, %rax
    cmpl $0x1, %edi
    jle base

    decl %edi
    call fact
    incl %edi
    mull %edi
    movq %rbp, %rsp
    popq %rbp
    ret


base:
    movq %rbp, %rsp
    popq %rbp
    ret


