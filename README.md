# SSCB
Simple Stack-based Compiler Backend. An easy to use compiler backend for generating, optimising and translating intermediate representation

# How it works
SSCB provides an easy to use API which allows you to generate intermediate representation (IR) which can then be optimised and compiled into different assembly languages. Small Example:

```C
#include "include/sscb_instructions.h"
#include "include/sscb_codegen.h"

int main(void) {
    instruction_setup();

    FUNCTIONEXTERN(FUNCTION("printf"));

    MOV(REG(R1), STRING("string_%d", 10)); 
    XOR(REG(RETURNREGISTER), REG(RETURNREGISTER));
    CALL(FUNCTION("printf"));
    RETURN();
    
    LABELDEF(STRING("string_%d", 10));
    DEFINEBYTE(STRING("`Helllo World!\\n`\n", 10));

    codegen_generated_instructions(INTEL_x86_64_LINUX);
    
    return 0;
}
```

##### Outline of the idea: https://docs.google.com/document/d/1SjRVg72Kb6y4kZf6pb-CG1xLP9F9fr01fhHzh6TqRO8/edit?usp=sharing
