#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/sscb_instructions.h"
#include "../include/sscb_optimizer.h"

OptimisationAnalysis optimize_instructions(SSCB_PackedInstruction *instructions, int instruction_num, int passes) {
    int new_instruction_count = 1;
    SSCB_PackedInstruction *new_instruction_list = malloc(sizeof(SSCB_PackedInstruction) * new_instruction_count);

    SSCB_Instruction prev_instruction;
    SSCB_Operand *prev_operands = malloc(sizeof(SSCB_Operand) * 6); //6 should be more than enough

    for (int pass = 0; pass < passes; pass++) {
        for (int i = 0; i < instruction_num - 1; i++) {
            SSCB_PackedInstruction ins = instructions[i];

            new_instruction_list[new_instruction_count - 1] = ins;

            if (prev_instruction == INS_PUSH && ins.instruction_type == INS_POP) {
                new_instruction_list[new_instruction_count - 2] = create_instruction(INS_NOP, 0);        
                new_instruction_list[new_instruction_count - 1] = create_instruction(INS_MOV, 2, ins.operands[0], prev_operands[0]);        
            }
            new_instruction_count++;

            prev_instruction = ins.instruction_type;
            prev_operands = ins.operands;
        }
    }
     
    OptimisationAnalysis analysis;
    
    analysis.new_instructions = new_instruction_list;
    analysis.number_instructions = new_instruction_count;

    return analysis;
}