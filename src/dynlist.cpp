
#include <nusys.h>

#include "dynlist.hpp"
#include "heap.hpp"

// -------------------------------------------------------------------------- //

TDynList2::TDynList2(
  u32 len, THeap * heap
) {
  if (heap == nullptr) {
    heap = THeap::getCurrentHeap();
  }

  mHeap = heap;
  mGfxAry = new(mHeap) Gfx[len];
  mMaxNumGfx = len;

  mProjMtx = getIdentityMtx();
  mViewMtx = getIdentityMtx();
}

// -------------------------------------------------------------------------- //

TDynList2::~TDynList2() {
  delete[] mGfxAry;
}

// -------------------------------------------------------------------------- //

void TDynList2::reset() {
  mNumGfx = 0;
}

// -------------------------------------------------------------------------- //

u32 TDynList2::fetchCmdIndex() {
  return mNumGfx;
}

// -------------------------------------------------------------------------- //

Gfx * TDynList2::getDL() const {
  if (mNumGfx >= mMaxNumGfx) {
    return nullptr;
  }

  return &mGfxAry[mNumGfx];
}

// -------------------------------------------------------------------------- //

Gfx * TDynList2::pushDL() {
  Gfx * list = getDL();

  if (list != nullptr) {
    ++mNumGfx;
  }

  return list;
}

// -------------------------------------------------------------------------- //

Gfx * TDynList2::getHead() {
  return mGfxAry;
}

// -------------------------------------------------------------------------- //

Mtx const &
TDynList2::getIdentityMtx() {
  static bool init { false };
  static Mtx mtx;

  if (!init) {
    guMtxIdent(&mtx);
    init = true;
  }

  return mtx;
}

// -------------------------------------------------------------------------- //
