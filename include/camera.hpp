#pragma once

#include <nusys.h>

#include "math.hpp"
#include "dynlist.hpp"
#include "pad.hpp"

// -------------------------------------------------------------------------- //

class TCamera
{
    public:

    TCamera(TDynList2 * list);
    ~TCamera() = default;

    void render();
    void setPad(TPad * pad) {mPad = pad;}

    Mtx mProjectionMtx{};
    Mtx mFViewMtx{};
    Mtx mIdentityMtx{};

    Mtx mBgProjMtx{};
    Mtx mViewBgMtx{};

    LookAt mLookAtMtx[2];
    Hilite mHilite[2];

    float mFov{44.0f};
    TDynList2 * mDynList{nullptr};

    private:

    TVec3<f32> mPosition{};
    TVec3<f32> mRotation{};
    TVec3<f32> mScale{};
    
    TMtx44 mPosMtx{};
    TMtx44 mRotMtx{};
    TMtx44 mScaleMtx{};

    Mtx mFPosMtx{};
    Mtx mFRotMtx{};
    Mtx mFScaleMtx{};

    TMtx44 mViewMtx{};
    TVec3<f32> mOldPos{};

    TPad * mPad{nullptr};
    u16 mPersp{0};
    u16 mAngle{0};
    f32 mDistance{0.0f};

};

// -------------------------------------------------------------------------- //