#include <stdio.h>
#include <stdlib.h>

#include "../include/sscb_instructions.h"

int main(void) {
    instruction_setup();
    ADD_INS(INS_PUSH, 1, imm_operand(1));
    ADD_INS(INS_PUSH, 1, imm_operand(10));
    ADD_INS(INS_PUSH, 1, reg_operand(R1));

    print_instructions();
    return 0;
}
