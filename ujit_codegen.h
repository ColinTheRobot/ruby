#ifndef UJIT_CODEGEN_H
#define UJIT_CODEGEN_H 1

#include "stddef.h"
#include "ujit_core.h"

// Code blocks we generate code into
codeblock_t* cb;
codeblock_t* ocb;

// Code generation state
typedef struct JITState
{
    // Block version being compiled
    block_t* block;

    // Instruction sequence this is associated with
    const rb_iseq_t *iseq;

    // Index of the current instruction being compiled
    uint32_t insn_idx;

    // Current PC
    VALUE *pc;

} jitstate_t;

// Code generation function signature
typedef bool (*codegen_fn)(jitstate_t* jit, ctx_t* ctx);

// Meta-information associated with a given opcode
typedef struct OpDesc
{
    // Code generation function
    codegen_fn gen_fn;

    // Indicates that this is a branch instruction
    // which terminates a block
    bool is_branch;

} opdesc_t;

uint8_t* ujit_gen_entry(block_t* block);

uint32_t ujit_gen_code(block_t* block);

void ujit_init_codegen(void);

#endif // #ifndef UJIT_CODEGEN_H