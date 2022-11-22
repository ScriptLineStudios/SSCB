#include <stdio.h>
#include <stdlib.h>

#include "../include/sscb_instructions.h"

int main(void) {
    instruction_setup();

    PUSH(IMM(1));
    POP(REG(R1));
    MOV(REG(R1), IMM(100));
    
    print_instructions();
    return 0;
}
