
#ifndef INCLUDE_DYNLIST2_HPP
#define INCLUDE_DYNLIST2_HPP

#include <ultra64.h>

#include "heap.hpp"

// -------------------------------------------------------------------------- //

class TDynList
{
    public:

    TDynList()
    {
        mDl = new Gfx[2048];
    }

    ~TDynList()
    {
        delete mDl;
    }

    Mtx mProjectionMtx{};
    Mtx mViewMtx{};
    Mtx mIdentityMtx{};

    Mtx mBgProjMtx{};
    Mtx mViewBgMtx{};

    LookAt mLookAtMtx[2];
    Hilite mHilite[2];

    Gfx * mDl;

    private:
};

// -------------------------------------------------------------------------- //

class TDynList2 {

  public:

  TDynList2(u32 len = 2048, THeap * heap = nullptr);
  ~TDynList2();

  void reset();

  Gfx * getDL() const;
  Gfx * pushDL();

  static Mtx const & getIdentityMtx();

  Mtx const & getProjMtx() const { return mProjMtx; }
  void setProjMtx(Mtx const & mtx) { mProjMtx = mtx; }

  Mtx const & getViewMtx() const { return mViewMtx; }
  void setViewMtx(Mtx const & mtx) { mViewMtx = mtx; }

  private:

  Mtx mProjMtx, mViewMtx;
  THeap * mHeap { nullptr };
  Gfx * mGfxAry { nullptr };
  u32 mMaxNumGfx { 0 };
  u32 mNumGfx { 0 };

};

// -------------------------------------------------------------------------- //

#endif
