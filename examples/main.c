#include <stdio.h>
#include <stdlib.h>

#include "../include/sscb_instructions.h"
#include "../include/sscb_codegen.h"

int main(void) {
    instruction_setup();

    FUNCTIONEXTERN(FUNCTION("printf"));

    MOV(REG(R1), STRING("string_%d", 10)); 
    XOR(REG(RETURNREGISTER), REG(RETURNREGISTER));
    CALL(FUNCTION("printf"));
    RETURN();
    
    LABELDEF(STRING("string_%d", 10));
    DEFINEBYTE(STRING("`Helllo World!\\n`\n", 10));

    //optimise_generated_instructions(1); //TODO: make passes actually work
    print_instructions();
    codegen_generated_instructions(INTEL_x86_64_LINUX);
    
    return 0;
}
