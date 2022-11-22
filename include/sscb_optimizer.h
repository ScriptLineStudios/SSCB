#pragma once

typedef struct {
    SSCB_PackedInstruction *new_instructions;
    int number_instructions;
} OptimisationAnalysis;

OptimisationAnalysis optimize_instructions(SSCB_PackedInstruction *instructions, int instruction_num, int passes);