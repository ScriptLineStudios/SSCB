#include <stdio.h>
#include <stdlib.h>

#include "../include/sscb_instructions.h"
#include "../include/sscb_optimizer.h"

int main(void) {
    instruction_setup();

    LABELDEF(LABEL("Hello World"));
    PUSH(IMM(1));
    POP(REG(R1));
    PUSH(IMM(200));
    POP(REG(R2));
    JMP(LABEL("Hello World"));

    optimise_generated_instructions(1);
    print_instructions();
    
    return 0;
}
