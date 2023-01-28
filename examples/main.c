#include <stdio.h>
#include <stdlib.h>

#include "../include/sscb_instructions.h"
#include "../include/sscb_codegen.h"

int main(void) {
    instruction_setup();
    
    MUL(REG(R1), REG(R2));

    optimise_generated_instructions(1); //TODO: make passes actually work
    codegen_generated_instructions(INTEL_x86_64_LINUX);
    
    return 0;
}
