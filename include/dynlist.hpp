#pragma once

#include <ultra64.h>

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