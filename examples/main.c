#include <stdio.h>
#include <stdlib.h>

#include "../include/sscb_instructions.h"
#include "../include/sscb_codegen.h"

int main(void) {
    instruction_setup();

    FUNCTIONEXTERN(FUNCTION("printf"));
    MOV(REG(R2), IMM(2));
    LABELDEF(LABEL("jump_pos"));
    ADD(REG(R2), REG(R2));
    MOV(REG(R1), REG(R2));
    MOV(REG(ARGREGISTER1), LABEL("format"));
    MOV(REG(ARGREGISTER2), REG(R1));
    XOR(REG(R1), REG(R1));
    CALL(FUNCTION("printf"));
    JMP(LABEL("jump_pos"));

    LABELDEF(LABEL("format"));
    DEFINEBYTE(STRING("%s, 10", "`%d`"));

    optimise_generated_instructions(1); //TODO: make passes actually work
    codegen_generated_instructions(INTEL_x86_64_LINUX);
    
    return 0;
}
