#ifndef MEM_H
#define MEM_H

#include <ultra64.h>
// -------------------------------------------------------------------------- //

void * memset(void *, int, size_t);

int MEMInit(void *, u32);

void * MEMAlloc(u32);
void * MEMCalloc(u32);
int MEMFree(void *);

u32 MEMFreeSize();
u32 MEMUsedSize();
u32 MEMHeapSize();
u32 MEMAllocSize();

int MEMCheckHeap();

// -------------------------------------------------------------------------- //

#endif
