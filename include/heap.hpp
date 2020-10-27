
#ifndef INCLUDE_HEAP_HPP
#define INCLUDE_HEAP_HPP

#include <ultra64.h>

// -------------------------------------------------------------------------- //

class THeap {

  public:

  inline void * getHeapHead() const { return mHeapHead; }
  inline void * getHeapTail() const { return mHeapTail; }
  inline u32 getHeapSize() const { return mHeapSize; }

  inline u32 getNumAlloc() const { return mNumAlloc; }
  virtual u32 getUsedSize() const = 0; // total used size
  virtual u32 getFreeSize() const = 0; // total free size

  virtual void * alloc(u32 amt, s32 align = 0) = 0;
  void * calloc(u32 amt, s32 align);
  virtual bool free(void * ptr) = 0;
  virtual void freeTail() = 0;
  virtual void freeAll() = 0;

  static THeap * getCurrentHeap();
  static THeap * setCurrentHeap(THeap *);

  protected:

  static constexpr s32 kStdAlign = 8; // 64-bit N64 alignment
  static constexpr s32 kMaxAlign = 128;

  THeap() = default;
  virtual ~THeap();

  static THeap * sCurrentHeap;
  void * mHeapHead { nullptr };
  void * mHeapTail { nullptr };
  u32 mHeapSize { 0 };
  u32 mNumAlloc { 0 };

  bool initHeapBase(void * head, u32 size);

  static inline bool isValidAlign(s32 aln) {
    if (aln <= 0 || aln > kMaxAlign) {
      return false;
    }

    return ((aln & (aln - 1)) == 0); // power of 2
  }

  template<typename T>
  static inline T roundDownB(T amt, s32 aln) {
    u32 mask = (u32)(aln - 1);
    return (T)((u32)amt & ~mask);
  }

  template<typename T>
  static inline T roundUpB(T amt, s32 aln) {
    u32 mask = (u32)(aln - 1);
    return (T)(((u32)amt + mask) & ~mask);
  }

  template<typename TPtr, typename TOfs>
  static inline TPtr addPtr(TPtr ptr, TOfs ofs) {
    return (TPtr)((u32)ptr + ofs);
  }

  template<typename TPtr, typename TOfs>
  static inline TPtr subPtr(TPtr ptr, TOfs ofs) {
    return (TPtr)((u32)ptr - ofs);
  }

};

// -------------------------------------------------------------------------- //

class TStackHeap final :
  public THeap
{

  public:

  TStackHeap() = default;
  inline TStackHeap(void * heap, u32 size) { init(heap, size); }
  virtual ~TStackHeap() override;

  bool init(void * heap, u32 size);

  virtual u32 getUsedSize() const override;
  virtual u32 getFreeSize() const override;

  virtual void * alloc(u32 amt, s32 aln = 0) override;
  virtual bool free(void * ptr) override;
  virtual void freeTail() override;
  virtual void freeAll() override;

  protected:

  void * mAllocHead { nullptr };
  void * mAllocTail { nullptr };
  u32 mNumAllocTail { 0 };

  void * allocHead(u32 amt, s32 aln);
  void * allocTail(u32 amt, s32 aln);

};

// -------------------------------------------------------------------------- //

class TBlockHeap final :
  public THeap
{

  public:

  TBlockHeap() = default;
  inline TBlockHeap(void * head, u32 size) { init(head, size); }
  virtual ~TBlockHeap() override;

  bool init(void * head, u32 size);

  virtual u32 getUsedSize() const override;
  virtual u32 getFreeSize() const override;

  virtual void * alloc(u32 amt, s32 aln = 0) override;
  virtual bool free(void * ptr) override;
  virtual void freeTail() override;
  virtual void freeAll() override;

  protected:

  static constexpr u32 kBlockHead = 0x0D15EA5E;
  static constexpr u32 kBlockTail = 0x0BADF00D;
  static constexpr u32 kBlockFree = 0xFEEDFACE;

  struct TBlock {

    u32 type;
    u32 size : 24;
    u32 ofs : 8;
    TBlock * next;

    inline void init(
      u32 type, u32 size = 0,
      u32 ofs = 0, TBlock * next = nullptr
    ) {
      this->type = type;
      this->size = size;
      this->ofs = ofs;
      this->next = next;
    }

  };

  TBlock * mAllocHead { nullptr };
  TBlock * mAllocTail { nullptr };
  TBlock * mFreeList { nullptr };
  u32 mNumAllocTail { 0 };

  void * allocHead(u32, s32);
  void * allocTail(u32, s32);

  TBlock * insertBlock(TBlock *, TBlock **);
  TBlock * removeBlock(TBlock *, TBlock **);
  bool splitBlockHead(TBlock *, TBlock * [3], u32, s32);
  bool splitBlockTail(TBlock *, TBlock * [2], u32, s32);
  static bool joinBlock(TBlock *);

  bool isPtrBlock(void *) const;
  static void * getBlockPtr(TBlock *);
  static void * getBlockEnd(TBlock *);
  static TBlock * getPtrBlock(void *);
  static u32 calcBlockSize(TBlock const *);

};

// -------------------------------------------------------------------------- //

void * operator new(size_t amt);
void * operator new(size_t amt, s32 aln);
void * operator new(size_t amt, THeap * heap, s32 aln = 0);

void * operator new[](size_t amt);
void * operator new[](size_t amt, s32 aln);
void * operator new[](size_t amt, THeap * heap, s32 aln = 0);

void operator delete(void * ptr);
void operator delete(void * ptr, size_t);
void operator delete(void * ptr, s32);
void operator delete(void * ptr, THeap * heap, s32 = 0);

void operator delete[](void * ptr);
void operator delete[](void * ptr, s32);
void operator delete[](void * ptr, THeap * heap, s32 = 0);

// -------------------------------------------------------------------------- //

#endif
