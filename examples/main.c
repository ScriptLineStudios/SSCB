#include <stdio.h>
#include <stdlib.h>

#include "../include/sscb_instructions.h"
#include "../include/sscb_codegen.h"

int main(void) {
    instruction_setup();

    MOV(REG(R1), MEM("data", 0));
    QUEUE_1(INS_PUSH, IMM(10));
    QUEUE_2(INS_MOV, REG(R1), IMM(10));
    QUEUE_2(INS_ADD, REG(R1), IMM(10));


    LABELDEF(LABEL("format"));
    DEFINEBYTE(STRING("data 0", 0));
    EMPTY_QUEUE();


    optimise_generated_instructions(1); //TODO: make passes actually work
    codegen_generated_instructions(INTEL_x86_64_LINUX);
    
    return 0;
}
