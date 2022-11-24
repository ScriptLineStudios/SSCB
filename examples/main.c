#include <stdio.h>
#include <stdlib.h>

#include "../include/sscb_instructions.h"
#include "../include/sscb_codegen.h"

int main(void) {
    instruction_setup();

    FUNCTIONEXTERN(FUNCTION("printf"));
    FUNCTIONEXTERN(FUNCTION("exit"));

    MOV(REG(ARGREGISTER1), STRING("string_%d", 10)); 
    XOR(REG(RETURNREGISTER), REG(RETURNREGISTER));
    CALL(FUNCTION("printf"));
    MOV(REG(ARGREGISTER1), IMM(0));
    CALL(FUNCTION("exit"));
    RETURN();

    LABELDEF(STRING("string_%d", 10));
    DEFINEBYTE(STRING("`Helllo World!\\n`", 10));

    optimise_generated_instructions(1); //TODO: make passes actually work
    //print_instructions();
    codegen_generated_instructions(INTEL_x86_LINUX);
    
    return 0;
}
