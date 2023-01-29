#pragma once

char *intel_x86_64_linux_registers[] = {"rax", "rbx", "rcx", "rdx", "r8", "r9", "r10", "r11", "r12", "r13", "rax", 
"rdi", "rsi", "rdx", "rcx", "r8", "r9"};
char *intel_x86_64_linux_instructions[] = {
    "nop", "push", "pop", "mov", "jmp", "cmp", "jnz", ":", ":", "extern", "add", "sub", "div", "mul", "call", "ret", "db", "xor", "jne", "je", "pushf", "or", "not",
};

#define WRITE(...) fprintf(file_ptr, __VA_ARGS__)

void generate_intel_x86_64_linux_header(FILE *file_ptr) {
    WRITE(";; Intel x86_64 Linux: Generated by the SSCB backend. Designed to be assembled with NASM and linked with GCC\n");
    WRITE("global main\n");
    WRITE("section .text\n");
    WRITE("main:\n");
}

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
                        WRITE("[%s+%d], ", ins.operands[j].label, ins.operands[j].mem_addr);
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