#include <stdio.h>
#include <stdlib.h>

#include "../include/sscb_instructions.h"
#include "../include/sscb_codegen.h"

int main(void) {
    instruction_setup();

    // MOV(REG(R1), IMM(10));
    // MOV(REG(R2), IMM(20));
    // CALL(FUNCTION("add"));
    // PUSH(REG(RETURNREGISTER));
    // RETURN();

    // FUNCTIONDEF(FUNCTION("add"));
    // ADD(REG(R1), REG(R2));
    // MOV(REG(RETURNREGISTER), REG(R1));
    // RETURN();

    // LABELDEF(STRING("string_%d", 10));
    // DEFINEBYTE(STRING("\"Helllo World!\"", 10));
    // DEFINEBYTE(IMM(0));
    FUNCTIONEXTERN(FUNCTION("exit"));
    MOV(REG(R1), IMM(0))
    CALL(FUNCTION("exit"));


    //optimise_generated_instructions(1); //TODO: make passes actually work
    print_instructions();
    codegen_generated_instructions(INTEL_x86_64_LINUX);
    
    return 0;
}
