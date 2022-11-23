#pragma once

// typedef enum {
//     INS_NOP = 0,
//     INS_PUSH = 1,
//     INS_POP = 2,
//     INS_MOV = 3,
//     INS_JMP = 4,
//     INS_CMP = 5, 
//     INS_JNZ = 6,
//     INS_LABELDEF = 7,
//     INS_FUNCTIONDEF = 8,
//     INS_FUNCTIONEXTERN = 9,
// } SSCB_Instruction;

char *intel_x86_64_linux_registers[] = {"rdi", "rsi", "rdx", "rcx", "r8", "r9", "r10", "r11", "r12", "r13", "rax"};
char *intel_x86_64_linux_instructions[] = {
    "nop", "push", "pop", "mov", "jmp", "cmp", "jnz", ":", ":", "extern", "add", "sub", "div", "mul", "call", "ret", "db"
};

#define WRITE(...) fprintf(file_ptr, __VA_ARGS__)

void generate_intel_x86_64_linux_header(FILE *file_ptr) {
    WRITE(";; Intel x86_64 Linux: Generated by the SSCB backend. Designed to be assembled with NASM and linked with GCC\n");
    WRITE("global main\n");
    WRITE("section .text\n");
    WRITE("main:\n");
}