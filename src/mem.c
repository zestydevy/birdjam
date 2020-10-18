#include <ultra64.h>

// ========================================================================== //

#include "mem.h"

// -------------------------------------------------------------------------- //

#define BLOCK_USED ((u32)0x0D15EA5E)
#define BLOCK_FREE ((u32)0xBAADF00D)

#define RoundDown16B(x) \
  ((u32)(x) & ~15)

#define RoundUp16B(x) \
  RoundDown16B((u32)(x) + 15)

// -------------------------------------------------------------------------- //

typedef struct MEMBlock MEMBlock;

struct MEMBlock {

  u32 type, size;
  MEMBlock * next;

};

// -------------------------------------------------------------------------- //

static void * sHeapHead;
static void * sHeapTail;
static MEMBlock * sHeapBlocks;
static u32 sHeapSize;

// -------------------------------------------------------------------------- //

void * memset(void *b, int c, int len)
{
  int i = 0;
  unsigned char * p = b;
  while(len > 0)
    {
      *p = c;
      p++;
      len--;
    }
  return(b);
}

static int MEMCoalesce(
  MEMBlock * block
) {
  if (block == NULL || block->next == NULL) {
    return 1;
  }

  if (block->type != BLOCK_FREE) {
    return 1;
  }

  if (block->next->type != BLOCK_FREE) {
    return 1;
  }

  block->next->type = 0; // prevent HOM while debugging
  block->size += (block->next->size + sizeof(MEMBlock));
  block->next = block->next->next;
  return 0;
}

// -------------------------------------------------------------------------- //

int MEMInit(
  void * head,
  u32 size
) {
  MEMBlock * block;
  void * tail;

  if (head == NULL) {
    return 1;
  }

  tail = (void *)((u32)head + size);
  block = (MEMBlock *)(RoundUp16B((u32)head + sizeof(MEMBlock)) - sizeof(MEMBlock));

  if ((u32)(block + sizeof(MEMBlock)) > (u32)tail) {
    return 1;
  }

  block->type = BLOCK_FREE;
  block->size = ((u32)tail - (u32)(block + sizeof(MEMBlock)));
  block->next = NULL;

  sHeapHead = head;
  sHeapTail = tail;
  sHeapSize = (block->size + sizeof(MEMBlock));
  sHeapBlocks = block;

  return 0;
}

// -------------------------------------------------------------------------- //

void * MEMAlloc(
  u32 amt
) {
  MEMBlock * block;
  MEMBlock * target;

  if (sHeapHead == NULL || amt == 0) {
    return NULL;
  }

  target = NULL;

  for (block = sHeapBlocks; (block != NULL); block = block->next) {
    if (block->type != BLOCK_FREE || block->size < amt) {
      continue;
    }

    if (target == NULL || target->size >= block->size) {
      target = block;

      if (target->size == amt) {
        break;
      }
    }
  }

  if (target == NULL) {
    return NULL;
  }

  target->type = BLOCK_USED;
  block = NULL;

  if ((target->size - amt) > sizeof(MEMBlock)) {
    block = (MEMBlock *)(
      RoundUp16B((u32)target + amt + sizeof(MEMBlock) * 2)
      - sizeof(MEMBlock)
    );

    // factored out adding sizeof(MEMBlock) to both sides a bit here
    if ((u32)block < ((u32)target + target->size)) {
      block->type = BLOCK_FREE;
      block->size = (((u32)target + target->size) - (u32)block);
      target->size = ((u32)block - ((u32)target + sizeof(MEMBlock)));
      block->next = target->next;
      target->next = block;
    }
  }

  return (void *)((u32)target + sizeof(MEMBlock));
}

// -------------------------------------------------------------------------- //

void * MEMCalloc(
  u32 amt
) {
  void * ptr;
  ptr = MEMAlloc(amt);

  if (ptr != NULL) {
    bzero(ptr, (int)amt);
  }

  return ptr;
}

// -------------------------------------------------------------------------- //

int MEMFree(
  void * ptr
) {
  MEMBlock * target;
  MEMBlock * block;
  MEMBlock * prev;

  if (sHeapHead == NULL) {
    return 1;
  }

  if (ptr == NULL) {
    return 0; // freeing null pointers is a no-op
  }

  if (ptr < (void *)sHeapBlocks || ptr >= sHeapTail) {
    return 1;
  }

  target = (MEMBlock *)((u32)ptr - sizeof(MEMBlock));

  if (target->type != BLOCK_USED) {
    return 1; // quick bail check
  }

  prev = NULL;

  for (
    block = sHeapBlocks;
    (block != NULL && ((u32)block + sizeof(MEMBlock)) != (u32)ptr);
    prev = block, block = block->next
  );

  if (block == NULL) {
    return 1;
  }

  block->type = BLOCK_FREE;
  MEMCoalesce(block);

  if (prev != NULL) {
    MEMCoalesce(prev);
  }

  return 0;
}

// -------------------------------------------------------------------------- //

u32 MEMFreeSize() {
  MEMBlock * block;
  u32 size;

  if (sHeapHead == NULL) {
    return 0;
  }

  size = 0;

  for (block = sHeapBlocks; block != NULL; block = block->next) {
    if (block->type == BLOCK_FREE) {
      size += (block->size + sizeof(MEMBlock));
    }
  }

  return size;
}

// -------------------------------------------------------------------------- //

u32 MEMUsedSize() {
  MEMBlock * block;
  u32 size;

  if (sHeapHead == NULL) {
    return 0;
  }

  size = 0;

  for (block = sHeapBlocks; block != NULL; block = block->next) {
    if (block->type == BLOCK_USED) {
      size += (block->size + sizeof(MEMBlock));
    }
  }

  return size;
}

// -------------------------------------------------------------------------- //

u32 MEMHeapSize() {
  if (sHeapHead == NULL) {
    return 0;
  }

  return sHeapSize;
}

// -------------------------------------------------------------------------- //

u32 MEMAllocSize() {
  MEMBlock * block;
  MEMBlock * largest;

  if (sHeapHead == NULL) {
    return 0;
  }

  largest = NULL;

  for (block = sHeapBlocks; block != NULL; block = block->next) {
    if (block->type != BLOCK_FREE) {
      continue;
    }

    if (largest == NULL || largest->size < block->size) {
      largest = block;
    }
  }

  if (largest == NULL) {
    return 0;
  }

  return largest->size;
}

// -------------------------------------------------------------------------- //

int MEMCheckHeap() {
  MEMBlock * block;
  u32 used, free;

  if (sHeapHead == NULL) {
    return 1;
  }

  used = free = 0;

  for (block = sHeapBlocks; block != NULL; block = block->next) {
    // this check is technically redundant on the first iteration
    if (block < sHeapBlocks) {
      return 1;
    }

    if ((void *)block >= sHeapTail) {
      return 1;
    }

    switch (block->type) {
      case BLOCK_FREE: {
        free += (block->size + sizeof(MEMBlock));
        break;
      }
      case BLOCK_USED: {
        used += (block->size + sizeof(MEMBlock));
        break;
      }
      default: {
        return 1;
      }
    }

    if (block->size > sHeapSize) {
      return 1;
    }

    if (
      (block->next != NULL) &&
      ((u32)block->next != ((u32)block + sizeof(MEMBlock) + block->size))
    ) {
      return 1;
    } else if (
      (block->next == NULL) &&
      (((u32)block + sizeof(MEMBlock) + block->size) != (u32)sHeapTail)
    ) {
      return 1;
    }
  }

  if ((used + free) != sHeapSize) {
    return 1;
  }

  return 0;
}

// -------------------------------------------------------------------------- //

// ========================================================================== //
