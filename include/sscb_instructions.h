#pragma once

#include "sscb_virtual_machine.h"

typedef enum {
    INS_NOP = 0,
    INS_PUSH = 1,
    INS_POP = 2,
    INS_MOV = 3,
    INS_JMP = 4,
    INS_CMP = 5, 
    INS_JNZ = 6,
    INS_LABELDEF = 7,
    INS_FUNCTIONDEF = 8,
    INS_FUNCTIONEXTERN = 9,
    INS_ADD = 10,
    INS_SUB = 11,
    INS_DIV = 12,
    INS_MUL = 13,
    INS_CALL = 14,
    INS_RETURN = 15,
    INS_DB = 16,
    INS_XOR = 17,
    INS_JNE = 18,
    INS_JE =  19,
    INS_PUSHFLAGS = 20,
    INS_OR = 21,
    INS_NOT = 22,
} SSCB_Instruction;

typedef enum {
    OK = 0,
    INSTRUCTION_DOES_NOT_EXIST = 1,
} SSCB_ErrorCode;

typedef enum {
    OP_REG = 0,
    OP_IMM = 1,
    OP_MEM = 3,
    OP_LABEL = 4
} SSCB_OperandType;

typedef struct {
    SSCB_OperandType op_type;
    int imm;
    SSCB_Register reg;
    unsigned int mem_addr;
    const char *label;
} SSCB_Operand;

typedef struct {    
    SSCB_Instruction instruction_type;
    SSCB_Operand *operands;
    unsigned int num_operands; 
} SSCB_PackedInstruction;
 
#define ADD_INS_0(type)      instruction_add(create_instruction(type, 0))
#define ADD_INS_1(type, ...) instruction_add(create_instruction(type, 1, __VA_ARGS__))
#define ADD_INS_2(type, ...) instruction_add(create_instruction(type, 2, __VA_ARGS__))
#define ADD_INS_3(type, ...) instruction_add(create_instruction(type, 3, __VA_ARGS__))
#define ADD_INS_4(type, ...) instruction_add(create_instruction(type, 4, __VA_ARGS__))

#define PUSH(...)           ADD_INS_1(INS_PUSH, __VA_ARGS__)
#define POP(...)            ADD_INS_1(INS_POP, __VA_ARGS__)
#define MOV(...)            ADD_INS_2(INS_MOV, __VA_ARGS__)
#define CMP(...)            ADD_INS_2(INS_CMP, __VA_ARGS__)
#define JMP(...)            ADD_INS_1(INS_JMP, __VA_ARGS__)
#define JNZ(...)            ADD_INS_1(INS_JNZ, __VA_ARGS__)
#define JNE(...)            ADD_INS_1(INS_JNE, __VA_ARGS__)
#define JE(...)             ADD_INS_1(INS_JE, __VA_ARGS__)
#define LABELDEF(...)       ADD_INS_1(INS_LABELDEF, __VA_ARGS__)
#define FUNCTIONDEF(...)    ADD_INS_1(INS_FUNCTIONDEF, __VA_ARGS__)
#define FUNCTIONEXTERN(...) ADD_INS_1(INS_FUNCTIONEXTERN, __VA_ARGS__)
#define XOR(...)            ADD_INS_2(INS_XOR, __VA_ARGS__)
#define OR(...)             ADD_INS_2(INS_OR, __VA_ARGS__)
#define NOT(...)            ADD_INS_2(INS_NOT, __VA_ARGS__)
#define ADD(...)            ADD_INS_2(INS_ADD, __VA_ARGS__)
#define SUB(...)            ADD_INS_2(INS_SUB, __VA_ARGS__)
#define DIV(...)            ADD_INS_2(INS_DIV, __VA_ARGS__)
#define MUL(...)            ADD_INS_2(INS_MUL, __VA_ARGS__)
#define CALL(...)           ADD_INS_1(INS_CALL, __VA_ARGS__)
#define RETURN()            ADD_INS_0(INS_RETURN)
#define DEFINEBYTE(...)     ADD_INS_1(INS_DB, __VA_ARGS__)
#define PUSH_FLAGS(...)     ADD_INS_0(INS_PUSHFLAGS)

extern SSCB_PackedInstruction *queued_instructions;
extern unsigned int number_queued_instructions;

#define QUEUE_0(type)      queued_instructions[number_queued_instructions++] = create_instruction(type, 0)
#define QUEUE_1(type, ...) queued_instructions[number_queued_instructions++] = create_instruction(type, 1, __VA_ARGS__)
#define QUEUE_2(type, ...) queued_instructions[number_queued_instructions++] = create_instruction(type, 2, __VA_ARGS__)
#define QUEUE_3(type, ...) queued_instructions[number_queued_instructions++] = create_instruction(type, 3, __VA_ARGS__)
#define QUEUE_4(type, ...) queued_instructions[number_queued_instructions++] = create_instruction(type, 4, __VA_ARGS__)

#define EMPTY_QUEUE() for (unsigned int i = 0; i < number_queued_instructions; i++) {instruction_add(queued_instructions[i]);}

#define IMM(i) imm_operand(i)
#define REG(r) reg_operand(r)
#define MEM(m, i) mem_operand(m, i)
#define LABEL(m) label_operand(m)
#define FUNCTION(m) label_operand(m) //litrally just an alias
#define STRING(m, ...) label_operand(m, __VA_ARGS__) //litrally just a fancy alias

void raise_fatal_error();
SSCB_Instruction *malloc_instruction(SSCB_Instruction *dst, size_t size);

SSCB_ErrorCode instruction_setup(void);

SSCB_Operand reg_operand(SSCB_Register reg);
SSCB_Operand imm_operand(int imm);
SSCB_Operand mem_operand(const char *label, unsigned int mem_addr);
SSCB_Operand label_operand(const char *label, ...);

void print_instructions();

SSCB_PackedInstruction create_instruction(SSCB_Instruction instruction, int num_operands, ...);
SSCB_ErrorCode instruction_add(SSCB_PackedInstruction contents);
void optimise_generated_instructions(int passes);

#include "sscb_codegen.h"
void codegen_generated_instructions(int target);


