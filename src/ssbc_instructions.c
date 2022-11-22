#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>

#include "../include/sscb_instructions.h"

void raise_fatal_error() {
    fprintf(stderr, "SSCB FAILED WITH FATAL ERROR");
    exit(1);
}

unsigned int instruction_num;
SSCB_PackedInstruction *instructions;

void print_instructions() {
    printf("Dumping Instructions...\n");
    for (unsigned int i = 0; i < instruction_num - 1; i++) {
        SSCB_PackedInstruction ins = instructions[i];
        if (ins.instruction_type == INS_PUSH) {
            printf("PUSH: ");
        }   

        for (unsigned int j = 0; j < ins.num_operands; j++) {
            SSCB_Operand op = ins.operands[j];
            if (op.op_type == OP_REG) {
                printf("(REG: %d) ", op.reg + 1);
            }
            else if (op.op_type == OP_IMM) {
                printf("(IMM: %d) ", op.imm);
            }
            else if (op.op_type == OP_MEM) {
                printf("(MEM: %d) ", op.mem);
            }
        }
        printf("\n");
    }
}

SSCB_PackedInstruction *malloc_instructions(SSCB_PackedInstruction *dst, size_t size) {
    dst = (SSCB_PackedInstruction *)malloc(size);
    if (dst == NULL) {
        raise_fatal_error();
    }
    return dst;
}

SSCB_PackedInstruction *realloc_instructions(SSCB_PackedInstruction *dst, size_t size) {
    dst = realloc((void*)dst, size);
    if (dst == NULL) {
        raise_fatal_error();
    }
    return dst;
}

SSCB_Operand reg_operand(SSCB_Register reg) {
    SSCB_Operand operand;
    operand.reg = reg;
    operand.op_type = OP_REG;
    return operand;
}

SSCB_Operand imm_operand(int imm) {
    SSCB_Operand operand;
    operand.imm = imm;
    operand.op_type = OP_IMM;
    return operand;
}

SSCB_Operand mem_operand(unsigned int mem_addr) {
    SSCB_Operand operand;
    operand.mem = mem_addr;
    operand.op_type = OP_MEM;
    return operand;
}

SSCB_PackedInstruction create_instruction(SSCB_Instruction instruction, int num_operands, ...) {
    SSCB_PackedInstruction *ret = malloc(sizeof(SSCB_PackedInstruction));
    
    va_list list;
    va_start(list, num_operands);
    SSCB_Operand *operands = malloc(sizeof(SSCB_Operand) * num_operands);
    for (int i = 0; i < num_operands; i++) {
        SSCB_Operand op = va_arg(list, SSCB_Operand);
        operands[i] = op;
    }
    ret->instruction_type = instruction;
    ret->operands = operands;
    ret->num_operands = num_operands;
    return *ret;
}

SSCB_ErrorCode instruction_setup(void) {
    instruction_num = 1;
    instructions = malloc_instructions(instructions, sizeof(SSCB_PackedInstruction) * instruction_num);
    return OK;
} 

SSCB_ErrorCode instruction_add(SSCB_PackedInstruction contents) {
    instructions = realloc_instructions(instructions, sizeof(SSCB_PackedInstruction) * (instruction_num));
    instructions[instruction_num - 1] = contents;
    instruction_num++;
    return OK;
}