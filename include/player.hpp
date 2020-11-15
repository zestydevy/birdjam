#pragma once

#include <nusys.h>

#include "math.hpp"
#include "animator.hpp"
#include "dynlist.hpp"
#include "pad.hpp"

// -------------------------------------------------------------------------- //

class TPlayer
{
    public:

    TPlayer(TDynList2 * list)
        : mDynList{list} {}
    ~TPlayer() = default;

    void setPosition(TVec3<f32> const & pos);
    void setRotation(TVec3<f32> const & rot);
    void setScale(TVec3<f32> const & scale);

    TVec3<f32> const & getPosition() {return mPosition;}
    TVec3<f32> const & getRotation() {return mRotation;}
    TVec3<f32> const & getScale() {return mScale;}

    void init();
    void update();
    void draw();

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
    
    u32 mTag{0};
    u16 mAngle{0};
    TDynList2 * mDynList{nullptr};
    TAnimator * mAnim{nullptr};
    TPad * mPad{nullptr};

};

// -------------------------------------------------------------------------- //