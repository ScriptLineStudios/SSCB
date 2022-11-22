#include "sscb_virtual_machine.h"

typedef enum {
    INS_NOP = 0,
    INS_PUSH = 1,
    INS_POP = 2,
    INS_MOV = 3,
} SSCB_Instruction;

typedef enum {
    OK = 0,
    INSTRUCTION_DOES_NOT_EXIST = 1,
} SSCB_ErrorCode;

typedef enum {
    OP_REG = 0,
    OP_IMM = 1,
    OP_MEM = 3
} SSCB_OperandType;

typedef struct {
    SSCB_OperandType op_type;
    int imm;
    SSCB_Register reg;
    unsigned int mem;
} SSCB_Operand;

typedef struct {    
    SSCB_Instruction instruction_type;
    SSCB_Operand *operands;
    unsigned num_operands; 
} SSCB_PackedInstruction;
 
#define ADD_INS_1(type, ...) instruction_add(create_instruction(type, 1, __VA_ARGS__));
#define ADD_INS_2(type, ...) instruction_add(create_instruction(type, 2, __VA_ARGS__));
#define ADD_INS_3(type, ...) instruction_add(create_instruction(type, 3, __VA_ARGS__));
#define ADD_INS_4(type, ...) instruction_add(create_instruction(type, 4, __VA_ARGS__));

#define PUSH(...) ADD_INS_1(INS_PUSH, __VA_ARGS__);
#define POP(...)  ADD_INS_1(INS_POP, __VA_ARGS__);
#define MOV(...)  ADD_INS_2(INS_MOV, __VA_ARGS__);


#define IMM(i) imm_operand(i)
#define REG(r) reg_operand(r)
#define MEM(m) mem_operand(m)

void raise_fatal_error();
SSCB_Instruction *malloc_instruction(SSCB_Instruction *dst, size_t size);

SSCB_ErrorCode instruction_setup(void);

SSCB_Operand reg_operand(SSCB_Register reg);
SSCB_Operand imm_operand(int imm);
SSCB_Operand mem_operand(unsigned int mem_addr);

void print_instructions();

SSCB_PackedInstruction create_instruction(SSCB_Instruction instruction, int num_operands, ...);
SSCB_ErrorCode instruction_add(SSCB_PackedInstruction contents);
