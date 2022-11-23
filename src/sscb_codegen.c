#include <stdio.h>
#include <stdlib.h>

#include "../include/sscb_codegen.h"
#include "../include/sscb_instructions.h"

#include "../include/codegen/intel_x86_64_linux.h"

#define WRITE(...) fprintf(file_ptr, __VA_ARGS__)

void codegen_intel_x86_64_linux(SSCB_PackedInstruction *instructions, unsigned int instruction_num) {
    printf("GENERATING INTEL x86_64 ASM...\n");

    FILE *file_ptr = fopen("codegen_intel_x86_64_linux.asm", "w");
    generate_intel_x86_64_linux_header(file_ptr);


    //TODO: find a way to reduce this from O(n^2)
    for (unsigned int i = 0; i < instruction_num - 1; i++) {
        SSCB_PackedInstruction ins = instructions[i];
        if (ins.instruction_type != INS_NOP) {
            if (ins.instruction_type != INS_LABELDEF && ins.instruction_type != INS_FUNCTIONDEF) {
                WRITE("%s ", intel_x86_64_linux_instructions[ins.instruction_type]);
            }
            for (unsigned int j = 0; j < ins.num_operands; j++) {
                switch (ins.operands[j].op_type) {
                    case OP_REG:
                        WRITE("%s, ", intel_x86_64_linux_registers[ins.operands[j].reg]);
                        break;
                    case OP_IMM:
                        WRITE("%d, ", ins.operands[j].imm);
                        break;
                    case OP_MEM:
                        WRITE("MEM");
                        break;
                    case OP_LABEL:
                        WRITE("%s", ins.operands[j].label);
                        break;
                }
            }
            if (ins.instruction_type == INS_LABELDEF || ins.instruction_type == INS_FUNCTIONDEF) {
                WRITE(":");
            }
            WRITE("\n");
        }
    }
}

void codegen_instructions(SSCB_PackedInstruction *instructions, unsigned int instruction_num, CodegenTarget target) {
    switch (target) {
        case INTEL_x86_64_LINUX:
            codegen_intel_x86_64_linux(instructions, instruction_num);
            break;
        default:
            printf("Unknown codegen target!\n");
            exit(1);
    }
}