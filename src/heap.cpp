
#include <ultra64.h>

#include "heap.hpp"

// -------------------------------------------------------------------------- //

extern "C" void bzero(void *, int);

// -------------------------------------------------------------------------- //

void * THeap::calloc(
  u32 amt, s32 aln
) {
  void * ptr = alloc(amt, aln);

  if (ptr == nullptr) {
    return nullptr;
  }

  bzero(ptr, (int)amt);
  return ptr;
}

// -------------------------------------------------------------------------- //

bool THeap::initHeapBase(
  void * head, u32 size
) {
  if (head == nullptr || size == 0) {
    return false;
  }

  mHeapHead = head;
  mHeapTail = addPtr(head, size);
  mHeapSize = size;
  mNumAlloc = 0;
  return true;
}

// -------------------------------------------------------------------------- //

TStackHeap::~TStackHeap() {}

// -------------------------------------------------------------------------- //

bool TStackHeap::init(
  void * head, u32 size
) {
  if (!initHeapBase(head, size)) {
    return false;
  }

  mAllocHead = mHeapHead;
  mAllocTail = mHeapTail;
  mNumAllocTail = 0;
  return true;
}

// -------------------------------------------------------------------------- //

u32 TStackHeap::getUsedSize() const {
  u32 head = ((u32)mAllocHead - (u32)mHeapHead);
  u32 tail = ((u32)mAllocTail - (u32)mHeapTail);
  return (head + tail);
}

// -------------------------------------------------------------------------- //

u32 TStackHeap::getFreeSize() const {
  return ((u32)mAllocTail - (u32)mAllocHead);
}

// -------------------------------------------------------------------------- //

void * TStackHeap::alloc(
  u32 amt, s32 aln
) {
  if (amt == 0) {
    return nullptr;
  }

  if (aln == 0) {
    aln = kStdAlign;
  }

  if (aln > 0) {
    return allocHead(amt, aln);
  } else {
    return allocTail(amt, -aln);
  }
}

// -------------------------------------------------------------------------- //

bool TStackHeap::free(void *) {
  return false;
}

// -------------------------------------------------------------------------- //

void TStackHeap::freeTail() {
  mAllocTail = mHeapTail;
  mNumAlloc -= mNumAllocTail;
  mNumAllocTail = 0;
}

// -------------------------------------------------------------------------- //

void TStackHeap::freeAll() {
  mAllocHead = mHeapHead;
  mAllocTail = mHeapTail;
  mNumAlloc = mNumAllocTail = 0;
}

// -------------------------------------------------------------------------- //

void * TStackHeap::allocHead(
  u32 amt, s32 aln
) {
  if (!isValidAlign(aln)) {
    return nullptr;
  }

  void * ptr = roundUpB(mAllocHead, aln);

  if (ptr >= mAllocTail) {
    return nullptr;
  }

  u32 len = ((u32)mAllocTail - (u32)ptr);

  if (len < amt) {
    return nullptr;
  }

  mAllocHead = addPtr(ptr, len);
  ++mNumAlloc;
  return ptr;
}

// -------------------------------------------------------------------------- //

void * TStackHeap::allocTail(
  u32 amt, s32 aln
) {
  if (!isValidAlign(aln)) {
    return nullptr;
  }

  void * ptr = roundDownB(subPtr(mAllocTail, amt), aln);

  if (ptr < mAllocHead || ptr >= mAllocTail) {
    return nullptr;
  }

  mAllocTail = ptr;
  ++mNumAllocTail;
  ++mNumAlloc;
  return ptr;
}

// -------------------------------------------------------------------------- //

void * operator new(
  size_t amt, THeap * heap, s32 aln
) throw() {
  if (heap == nullptr) {
    return nullptr;
  }

  return heap->alloc((u32)amt, aln);
}

// -------------------------------------------------------------------------- //

void * operator new[](
  size_t amt, THeap * heap, s32 aln
) throw() {
  if (heap == nullptr) {
    return nullptr;
  }

  return heap->alloc((u32)amt, aln);
}

// -------------------------------------------------------------------------- //

void operator delete(void *, size_t) {}

// -------------------------------------------------------------------------- //

void operator delete(
  void * ptr, THeap * heap, s32
) {
  if (heap == nullptr) {
    return;
  }

  heap->free(ptr);
}

// -------------------------------------------------------------------------- //

void operator delete[](
  void * ptr, THeap * heap, s32
) {
  if (heap == nullptr) {
    return;
  }

  heap->free(ptr);
}

// -------------------------------------------------------------------------- //
