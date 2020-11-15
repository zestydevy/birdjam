#include <nusys.h>

#include "camera.hpp"
#include "pad.hpp"
#include "math.hpp"
#include "util.hpp"
// -------------------------------------------------------------------------- //

TCamera::TCamera(TDynList2 * list)
{
    mDynList = list;
    
    mPosMtx.identity();
    mRotMtx.identity();
    mScaleMtx.identity();

    mPosition.set(0.0f, 0.0f, 0.0f);
    mRotation.set(0.0f, 0.0f, 0.0f);
    mScale.set(1.0f, 1.0f, 1.0f);
}

void TCamera::render()
{    
    guPerspective(&mProjectionMtx, &mPersp,
		      mFov, 320.0/240.0, 40, 40000, 1.0);
    guLookAtReflect(&mFViewMtx, mLookAtMtx,
		       50, 0, 400,
		       0, 0, 0,
		       0, 1, 0);
	
    gSPLookAt(mDynList->pushDL(), mLookAtMtx);
    gSPPerspNormalize(mDynList->pushDL(), mPersp);
    gSPMatrix(mDynList->pushDL(), OS_K0_TO_PHYSICAL(&mProjectionMtx),
		  G_MTX_PROJECTION|G_MTX_LOAD|G_MTX_NOPUSH);
    gSPMatrix(mDynList->pushDL(), OS_K0_TO_PHYSICAL(&mFViewMtx),
		  G_MTX_PROJECTION|G_MTX_MUL|G_MTX_NOPUSH);

    float x = mTarget->x() + TSine::ssin(mAngle) * mDistance;
    float z = mTarget->z() + TSine::scos(mAngle) * mDistance;

    //mPosition.set(x, 0.0f, z);
    mOldPos.lerp({x, mTarget->y(), z}, 4.0f * kInterval);

    mViewMtx.lookAt(mOldPos, mTarget->xyz(), {0.0f,1.0f,0.0f});
    mPosMtx.translate(mPosition);
    mRotMtx.rotateAxis(mRotation, 0);
    mScaleMtx.scale(mScale);

    TMtx44::floatToFixed(mPosMtx, mFPosMtx);
    TMtx44::floatToFixed(mRotMtx, mFRotMtx);
    TMtx44::floatToFixed(mScaleMtx, mFScaleMtx);
    TMtx44::floatToFixed(mViewMtx, mFViewMtx);
    
    gSPMatrix(mDynList->pushDL(), OS_K0_TO_PHYSICAL(&mFPosMtx),
	      G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);
    gSPMatrix(mDynList->pushDL(), OS_K0_TO_PHYSICAL(&mFScaleMtx),
	      G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);
    gSPMatrix(mDynList->pushDL(), OS_K0_TO_PHYSICAL(&mFRotMtx),
	      G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);

    if (mPad->isHeld(EButton::C_LEFT)) {
        mAngle += 300;
    }

    if (mPad->isHeld(EButton::C_RIGHT)) {
        mAngle -= 300;
    }

    if (mPad->isHeld(EButton::C_UP)) {
        mDistance += 35.0f;
    }

    if (mPad->isHeld(EButton::C_DOWN)) {
        mDistance -= 35.0f;
    }
}

// -------------------------------------------------------------------------- //