.global main

main:
    movb $0xFF, %al
    ret


/**
int main(void) {

    return 0xFF;

    }
/