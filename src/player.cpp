#include <nusys.h>

#include "player.hpp"
#include "math.hpp"

#include "../models/bird/model_bird.h"

// -------------------------------------------------------------------------- //

void TPlayer::setPosition(TVec3<f32> const & pos)
{
    mPosition.set(pos.x(), pos.y(), pos.z());
}

void TPlayer::setRotation(TVec3<f32> const & rot)
{
    mRotation.set(rot.x(), rot.y(), rot.z());
}

void TPlayer::setScale(TVec3<f32> const & scale)
{
    mScale.set(scale.x(), scale.y(), scale.z());
}

void TPlayer::init()
{
    // ...
    mPosMtx.identity();
    mRotMtx.identity();
    mScaleMtx.identity();
}

void TPlayer::update()
{
    // ...
    //if (mPad->getAnalogX() != 0 || mPad->getAnalogY() != 0) {
    //    mAngle = TSine::atan2(-mPad->getAnalogX(), -mPad->getAnalogY());
    //}
}

void TPlayer::draw()
{
    // ...
    
    //mtx.identity();
    //mtx.rotateEuler({0,angle,0});
    //mtx.floatToFixed(mtx, gBirdRot);
    
    mPosMtx.translate(mPosition);
    mRotMtx.rotateAxis(mRotation, mAngle);
    mScaleMtx.scale(mScale);

    TMtx44::floatToFixed(mPosMtx, mFPosMtx);
    TMtx44::floatToFixed(mRotMtx, mFRotMtx);
    TMtx44::floatToFixed(mScaleMtx, mFScaleMtx);
    
    gSPMatrix(mDynList->pushDL(), OS_K0_TO_PHYSICAL(&mFPosMtx),
	      G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);
    gSPMatrix(mDynList->pushDL(), OS_K0_TO_PHYSICAL(&mFScaleMtx),
	      G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);
    gSPMatrix(mDynList->pushDL(), OS_K0_TO_PHYSICAL(&mFRotMtx),
	      G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);
        
    gSPDisplayList(mDynList->pushDL(), bird_Bird_mesh);
}

// -------------------------------------------------------------------------- //