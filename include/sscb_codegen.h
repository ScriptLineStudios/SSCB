#pragma once

#include "sscb_instructions.h"

typedef enum {
    INTEL_x86_64_LINUX = 0
} CodegenTarget;

void codegen_instructions(SSCB_PackedInstruction *instructions, unsigned int instruction_num, CodegenTarget target);