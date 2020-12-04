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

    mDistance = 300.0f;

    mExternallyControlled = false;
}

void TCamera::render()
{    
    if (mDistance < 150.0f)
        mDistance = 150.0f;
    if (mDistance > 600.0f)
        mDistance = 600.0f;

    guPerspective(&mProjectionMtx, &mPersp,
		      mFov, 320.0/240.0, 5, 8000, 1.0);
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

    //get current target distance
    TVec3F dif = (*mTarget - mPosition);
    float pdist = dif.getLength();

    bool moveCamera = mPad->isHeld(EButton::C_LEFT) || mPad->isHeld(EButton::C_RIGHT) || mPad->isHeld(EButton::C_UP) || mPad->isHeld(EButton::C_DOWN);
    if (mPad->isHeld(EButton::C_LEFT))
        mAngle += 300.0;
    if (mPad->isHeld(EButton::C_RIGHT))
        mAngle -= 300.0;
    if (mPad->isHeld(EButton::C_UP))
        mDistance -= 3.50f;
    if (mPad->isHeld(EButton::C_DOWN))
        mDistance += 3.50f;

    float x = mPosition.x();
    float y = mPosition.y();
    float z = mPosition.z();
    if (!mExternallyControlled && (moveCamera || pdist > mDistance || pdist < mDistance * 0.75f)){
        if (pdist > mDistance)      // Clamp camera distance between max and half max;
            pdist = mDistance;
        if (pdist < mDistance * 0.75f)
            pdist = mDistance * 0.75f;

        if (!moveCamera)
            mAngle = TSine::atan2(dif.x(), dif.z());
        x = mTarget->x() - TSine::ssin(mAngle) * pdist;
        y = mTarget->y() + 20.00f;
        z = mTarget->z() - TSine::scos(mAngle) * pdist;
        mPosition.set(x, y, z);
    }

    //mPosition.set(x, 0.0f, z);
    mOldPos.lerp({x, y, z}, 4.0f * kInterval);
    mViewMtx.lookAt(mOldPos * 0.1f, mTarget->xyz() * 0.1f, {0.0f,1.0f,0.0f});
    mRotMtx.rotateAxis(mRotation, 0);
    mScaleMtx.scale(mScale * 0.1f);

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
}

// -------------------------------------------------------------------------- //