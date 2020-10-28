#include "task.hpp"

// -------------------------------------------------------------------------- //

extern u64 rdp_output[];
extern u64 dram_stack[];

// -------------------------------------------------------------------------- //

// has to be in BSS
OSTask tlist
{
    M_GFXTASK,			/* task type */
    OS_TASK_DP_WAIT,		/* task flags */
    NULL,			/* boot ucode pointer (fill in later) */
    0,				/* boot ucode size (fill in later) */
    NULL,			/* task ucode pointer (fill in later) */
    SP_UCODE_SIZE,		/* task ucode size */
    NULL,			/* task ucode data pointer (fill in later) */
    SP_UCODE_DATA_SIZE,		/* task ucode data size */
    &dram_stack[0],		/* task dram stack pointer */
    SP_DRAM_STACK_SIZE8,	/* task dram stack size */
    &rdp_output[0],		/* task fifo buffer ptr start */
    &rdp_output[0]+RDP_OUTPUT_LEN, /* task fifo buffer ptr end */
    NULL,			/* task data pointer (fill in later) */
    0,				/* task data size (fill in later) */
    NULL,			/* task yield buffer ptr (not used here) */
    0				/* task yield buffer size (not used here) */
};

// -------------------------------------------------------------------------- //