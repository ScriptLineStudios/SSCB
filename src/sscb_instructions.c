#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdarg.h>

#include "../include/sscb_instructions.h"
#include "../include/sscb_optimizer.h"
#include "../include/sscb_codegen.h"

unsigned int instruction_num;
SSCB_PackedInstruction *instructions;

unsigned int number_queued_instructions;
SSCB_PackedInstruction *queued_instructions;


void raise_fatal_error() {
    fprintf(stderr, "SSCB FAILED WITH FATAL ERROR\n");
    exit(1);
}

char *get_instruction_as_string(SSCB_PackedInstruction instruction) {
    switch ((SSCB_Instruction)instruction.instruction_type) {
        case 0:
            return "NO-OP";
        case 1:
            return "PUSH";
        case 2:
            return "POP";
        case 3:
            return "MOV";
        case 4:
            return "JMP";
        case 5:
            return "CMP";
        case 6:
            return "JNZ";
        case 7:
            return "LABEL-DEF";
        case 8:
            return "FUNCTION-DEF";
        case 9:
            return "FUNCTION-EXTERN";
        case 10:
            return "ADD";
        case 11:
            return "SUB";
        case 12:
            return "DIV";
        case 13:
            return "MUL";
        case 14:
            return "CALL";
        case 15:
            return "RETURN";
        case 16:
            return "DEFINE BYTE";
        case 17:
            return "XOR";
        default:
            return "UNKNOWN";
    }
}   

void print_instructions() {
    printf("Dumping Instructions... %d\n", instruction_num);
    for (unsigned int i = 0; i < instruction_num - 1; i++) {
        SSCB_PackedInstruction ins = instructions[i];
        char *type = get_instruction_as_string(ins);
        printf("%s ", type);

        for (unsigned int j = 0; j < ins.num_operands; j++) {
            SSCB_Operand op = ins.operands[j];
            if (op.op_type == OP_REG) {
                printf("(REG: %d) ", op.reg + 1);
            }
            else if (op.op_type == OP_IMM) {
                printf("(IMM: %d) ", op.imm);
            }
            else if (op.op_type == OP_MEM) {
                printf("(MEM: %d) ", op.mem_addr);
            }
            else if (op.op_type == OP_LABEL) {
                printf("(LABEL: %s) ", op.label);
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

SSCB_Operand mem_operand(const char *label, unsigned int mem_addr) {
    SSCB_Operand operand;
    operand.label = label;
    operand.mem_addr = mem_addr;
    operand.op_type = OP_MEM;
    return operand;
}

SSCB_Operand label_operand(const char *label, ...) {
    char *string = malloc(sizeof(char *) * 256);
    va_list ptr;
    va_start(ptr, label);
    
    vsnprintf(string, 256, label, ptr); 
    
    SSCB_Operand operand;
    operand.label = string;
    operand.op_type = OP_LABEL;
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
    number_queued_instructions = 0;
    queued_instructions = malloc(sizeof(SSCB_PackedInstruction) * 1000);
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

void optimise_generated_instructions(int passes) {
    OptimisationAnalysis analysis = optimize_instructions(instructions, instruction_num, passes);
    instructions = analysis.new_instructions;
    instruction_num = analysis.number_instructions;
}

void codegen_generated_instructions(int target) {
    codegen_instructions(instructions, instruction_num, target);
}