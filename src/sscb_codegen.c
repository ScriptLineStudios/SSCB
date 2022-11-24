#include <stdio.h>
#include <stdlib.h>

#include "../include/sscb_codegen.h"
#include "../include/sscb_instructions.h"

#include "../include/codegen/intel_x86_64_linux.h"
#include "../include/codegen/intel_x86_linux.h"

void codegen_instructions(SSCB_PackedInstruction *instructions, unsigned int instruction_num, CodegenTarget target) {
    switch (target) {
        case INTEL_x86_64_LINUX:
            codegen_intel_x86_64_linux(instructions, instruction_num);
            break;
        case INTEL_x86_LINUX:
            codegen_intel_x86_linux(instructions, instruction_num);
            break;
        default:
            printf("Unknown codegen target!\n");
            exit(1);
    }
}