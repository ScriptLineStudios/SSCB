#include <stdio.h>
#include <stdlib.h>

#include "../include/sscb_instructions.h"
#include "../include/sscb_codegen.h"

int main(void) {
    instruction_setup();

    PUSH(IMM(10));
    PUSH(IMM(20));
    CALL(FUNCTION("add"));
    RETURN();

    FUNCTIONDEF(FUNCTION("add"));
    POP(REG(R1));
    POP(REG(R2));
    ADD(REG(R1), REG(R2));
    PUSH(REG(R1));

    //optimise_generated_instructions(1); //TODO: make passes actually work
    print_instructions();
    codegen_generated_instructions(INTEL_x86_64_LINUX);
    
    return 0;
}
