
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

TBlockHeap::~TBlockHeap() {}

// -------------------------------------------------------------------------- //

bool TBlockHeap::init(
  void * head, u32 size
) {
  if (size < sizeof(TBlock)) {
    return false;
  }

  if (!initHeapBase(head, size)) {
    return false;
  }

  mFreeList = (TBlock *)mHeapHead;
  mFreeList->init(kBlockFree, (size - sizeof(TBlock)));
  mAllocHead = mAllocTail = nullptr;
  mNumAllocTail = 0;
  return true;
}

// -------------------------------------------------------------------------- //

u32 TBlockHeap::getUsedSize() const {
  u32 size = 0;

  for (auto b = mAllocHead; (b != nullptr); b = b->next) {
    size += calcBlockSize(b);
  }

  for (auto b = mAllocTail; (b != nullptr); b = b->next) {
    size += calcBlockSize(b);
  }

  return size;
}

// -------------------------------------------------------------------------- //

u32 TBlockHeap::getFreeSize() const {
  u32 size = 0;

  for (auto b = mFreeList; (b != nullptr); b = b->next) {
    size += calcBlockSize(b);
  }

  return size;
}

// -------------------------------------------------------------------------- //

void * TBlockHeap::alloc(
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

bool TBlockHeap::free(void * ptr) {
  if (!isPtrBlock(ptr)) {
    return false;
  }

  TBlock * blk = getPtrBlock(ptr);
  TBlock * prev;

  switch (blk->type) {
    case kBlockHead: {
      removeBlock(blk, &mAllocHead);
      break;
    }
    case kBlockTail: {
      removeBlock(blk, &mAllocTail);
      break;
    }
    default: {
      return false;
    }
  }

  u32 size = (blk->size + blk->ofs);
  blk = subPtr(blk, blk->ofs);
  blk->init(kBlockFree, size);
  prev = insertBlock(blk, &mFreeList);
  joinBlock(blk);

  if (prev != nullptr) {
    joinBlock(prev);
  }

  return true;
}

// -------------------------------------------------------------------------- //

void TBlockHeap::freeTail() {
  TBlock * b = mAllocTail;
  TBlock * prev;

  while (b != nullptr) {
    removeBlock(b, &mAllocTail);
    prev = insertBlock(b, &mFreeList);
    joinBlock(b);

    if (prev != nullptr) {
      joinBlock(prev);
    }

    b = b->next;
  }

  mAllocTail = nullptr;
  mNumAlloc -= mNumAllocTail;
  mNumAllocTail = 0;
}

// -------------------------------------------------------------------------- //

void TBlockHeap::freeAll() {
  mFreeList = (TBlock *)mHeapHead;
  mFreeList->init(kBlockFree, (mHeapSize - sizeof(TBlock)));
  mAllocHead = mAllocTail = nullptr;
  mNumAlloc = mNumAllocTail = 0;
}

// -------------------------------------------------------------------------- //

void * TBlockHeap::allocHead(
  u32 amt, s32 aln
) {
  if (!isValidAlign(aln)) {
    return nullptr;
  }

  TBlock * b = mFreeList;
  TBlock * splits[3];

  while (b != nullptr) {
    if (!splitBlockHead(b, splits, amt, aln)) {
      b = b->next;
      continue;
    }

    ++mNumAlloc;
    return getBlockPtr(splits[1]);
  }

  return nullptr;
}

// -------------------------------------------------------------------------- //

void * TBlockHeap::allocTail(
  u32 amt, s32 aln
) {
  if (!isValidAlign(aln)) {
    return nullptr;
  }

  TBlock * b = mFreeList;
  TBlock * splits[2];

  while (b != nullptr) {
    if (!splitBlockTail(b, splits, amt, aln)) {
      b = b->next;
      continue;
    }

    ++mNumAlloc;
    ++mNumAllocTail;
    return getBlockPtr(splits[1]);
  }

  return nullptr;
}

// -------------------------------------------------------------------------- //

TBlockHeap::TBlock *
TBlockHeap::insertBlock(
  TBlock * blk,
  TBlock ** list
) {
  TBlock * b = *list;
  TBlock * prev = nullptr;

  while (b != nullptr) {
    if (b > blk) {
      break;
    }

    prev = b;
    b = b->next;
  }

  blk->next = b;

  if (prev != nullptr) {
    prev->next = blk;
  } else {
    *list = blk;
  }

  return prev;
}

// -------------------------------------------------------------------------- //

TBlockHeap::TBlock *
TBlockHeap::removeBlock(
  TBlock * blk,
  TBlock ** list
) {
  TBlock * b = *list;
  TBlock * prev = nullptr;

  while (b != nullptr) {
    if (b != blk) {
      prev = b;
      b = b->next;
      continue;
    }

    if (prev != nullptr) {
      prev->next = b->next;
    } else {
      *list = b->next;
    }

    return prev;
  }

  return nullptr;
}

// -------------------------------------------------------------------------- //

bool TBlockHeap::splitBlockHead(
  TBlock * blk,
  TBlock * splits[3],
  u32 amt, s32 aln
) {
  void * start = getBlockPtr(blk);
  void * ptr = roundUpB(start, aln);
  void * end = getBlockEnd(blk);

  if (ptr > end) {
    return false;
  }

  u32 size = ((u32)end - (u32)ptr);
  u32 ofs = ((u32)ptr - (u32)start);

  if (size < amt) {
    return false;
  }

  TBlock * a = nullptr;
  TBlock * b = nullptr;
  removeBlock(blk, &mFreeList);

  if ((size - amt) > sizeof(TBlock)) {
    b = (TBlock *)addPtr(ptr, amt);
    b->init(kBlockFree, (size - amt - sizeof(TBlock)));
    size = amt;
  }

  if (ofs > sizeof(TBlock)) {
    a = blk;
    blk = addPtr(blk, ofs);
    a->init(kBlockFree, (ofs - sizeof(TBlock)));
    ofs = 0;
  } else {
    blk = addPtr(blk, ofs);
  }

  blk->init(kBlockHead, size, ofs);
  insertBlock(blk, &mAllocHead);

  if (a != nullptr) {
    insertBlock(a, &mFreeList);
  }

  if (b != nullptr) {
    insertBlock(b, &mFreeList);
  }

  if (splits != nullptr) {
    splits[0] = a;
    splits[1] = blk;
    splits[2] = b;
  }

  return true;
}

// -------------------------------------------------------------------------- //

bool TBlockHeap::splitBlockTail(
  TBlock * blk,
  TBlock * splits[2],
  u32 amt, s32 aln
) {
  void * end = getBlockEnd(blk);
  void * ptr = roundDownB(subPtr(end, amt), aln);
  void * start = getBlockPtr(blk);

  if (ptr < start) {
    return false;
  }

  u32 size = ((u32)end - (u32)ptr);
  u32 ofs = ((u32)ptr - (u32)start);

  if (size < amt) {
    return false;
  }

  TBlock * a = nullptr;
  removeBlock(blk, &mFreeList);

  if (ofs > sizeof(TBlock)) {
    a = blk;
    blk = addPtr(blk, ofs);
    a->init(kBlockFree, (ofs - sizeof(TBlock)));
    ofs = 0;
  } else {
    blk = addPtr(blk, ofs);
  }

  blk->init(kBlockTail, size, ofs);
  insertBlock(blk, &mAllocTail);

  if (a != nullptr) {
    insertBlock(a, &mFreeList);
  }

  if (splits != nullptr) {
    splits[0] = a;
    splits[1] = blk;
  }

  return true;
}

// -------------------------------------------------------------------------- //

bool TBlockHeap::joinBlock(TBlock * blk) {
  if (blk->next == nullptr) {
    return false;
  }

  if (blk->next->type != kBlockFree) {
    return false;
  }

  if (getBlockEnd(blk) != blk->next) {
    return false;
  }

  blk->next->type = 0;
  blk->size += calcBlockSize(blk->next);
  return true;
}

// -------------------------------------------------------------------------- //

bool TBlockHeap::isPtrBlock(void * ptr) const {
  if (ptr == nullptr) {
    return false;
  }

  if (ptr < mHeapHead || ptr >= mHeapTail) {
    return false;
  }

  TBlock const * blk = getPtrBlock(ptr);

  if ((void *)blk < mHeapHead) {
    return false;
  }

  switch (blk->type) {
    case kBlockHead:
    case kBlockTail:
    case kBlockFree: {
      break;
    }
    default: {
      return false;
    }
  }

  return true;
}

// -------------------------------------------------------------------------- //

void * TBlockHeap::getBlockPtr(TBlock * blk) {
  return addPtr(blk, sizeof(TBlock));
}

// -------------------------------------------------------------------------- //

void * TBlockHeap::getBlockEnd(TBlock * blk) {
  return addPtr(blk, (sizeof(TBlock) + blk->size));
}

// -------------------------------------------------------------------------- //

TBlockHeap::TBlock *
TBlockHeap::getPtrBlock(void * ptr) {
  return (TBlock *)subPtr(ptr, sizeof(TBlock));
}

// -------------------------------------------------------------------------- //

u32 TBlockHeap::calcBlockSize(
  TBlock const * blk
) {
  return (sizeof(TBlock) + blk->size + blk->ofs);
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
