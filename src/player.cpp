#include <nusys.h>

#include "player.hpp"
#include "math.hpp"
#include "animator.hpp"

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

    // set up to start in flight for testing:
    mDirection = TVec3<f32>(0.0f, 0.0f, 0.0f);
    mRotation = TVec3<f32>(0.0f, 0.0f, 0.0f);

    //Set up model animator
    mAnim = new TAnimator(sizeof(mMeshes) / sizeof(Vtx*), mMeshes, mMeshSizes);
    mAnim->setAnimation(bird_Bird_FlyFlap_Length, mAnim_Flap);
    mState = PLAYERSTATE_FLAPPING;
}

void TPlayer::update()
{
    // ...
    //if (mPad->getAnalogX() != 0 || mPad->getAnalogY() != 0) {
    //    mAngle = TSine::atan2(-mPad->getAnalogX(), -mPad->getAnalogY());
    //}

    TMtx44 temp1, temp2, temp3;

    //find the camera
    s16 cameraAngle = mCamera->getAngle();
    TVec3<f32> up = TVec3<f32>(0.0f, 1.0f, 0.0f);   //Camera up
    TVec3<f32> forward = TVec3<f32>(TSine::ssin(cameraAngle), 0.0f, TSine::scos(cameraAngle));  //Camera forward
    TVec3<f32> right = TVec3<f32>(-forward.z(), 0.0f, forward.x()); //Camera right

    TVec3<f32> move{};
    switch (mState){
        case PLAYERSTATE_FLAPPING:
            if (mPad->getAnalogX() != 0 || mPad->getAnalogY() != 0) {
                mRotation = TVec3<s16>((s16)0, (s16)((s16)TSine::atan2(-mPad->getAnalogX(), mPad->getAnalogY()) + (s16)cameraAngle), (s16)0);
                move = (forward * (float)mPad->getAnalogY()) + (right * (float)mPad->getAnalogX()); //Move relative to camera
                move.normalize();
                mPosition += move * 10.0f;
            }
            
            if (mPad->isHeld(A))
                mPosition += TVec3<f32>(0.0f, 10.0f, 0.0f);
            if (mPad->isHeld(B))
                mPosition -= TVec3<f32>(0.0f, 10.0f, 0.0f);

            if (mPad->isPressed(Z)){    //Start flying
                // Set state and animation
                mState = PLAYERSTATE_FLYING;
                mAnim->setAnimation(bird_Bird_GlideFlap_Length, mAnim_GlideFlap, false);

                mFlappingWings = true;

                // Set initial flight direction to the facing direction
                mDirection.set(TSine::ssin(mRotation.y()), 0.0f, TSine::scos(mRotation.y()));

                // Set initial flight speed
                mSpeed = 25.0f;
            }
            break;
        case PLAYERSTATE_FLYING:
            TVec3<f32> fright = TVec3<f32>(-mDirection.z(), 0.0f, mDirection.x());  //Flight right

            // Flight controls
            temp1.rotateAxis(fright, TSine::fromDeg(1.0f * -mPad->getAnalogY() / 80.0f));
            temp2.rotateAxisY(TSine::fromDeg(1.0f * -mPad->getAnalogX() / 80.0f));
            TMtx44::concat(temp1, temp2, temp3);
            mDirection = temp3.mul(mDirection);

            // Apply visual rotation
            mRotation = TVec3<s16>((s16)-TSine::asin(mDirection.y()), TSine::atan2(mDirection.x(), mDirection.z()), (s16)0);
            mCamera->setAngle(mRotation.y());

            // Apply gravity
            mSpeed -= mDirection.dot(TVec3F(0.0f, 1.0f, 0.0f)) * 0.2f; // Going down Gravity
            if (mSpeed < 10.0f)
                mSpeed = 10.0f; // Min Speed
            if (mSpeed > 100.0f)
                mSpeed = 100.0f; // Max Speed

            if (mSpeed < 25.0f){ // Flapping speed
                if (mFlappingWings == false){
                    mAnim->setAnimation(bird_Bird_GlideFlap_Length, mAnim_GlideFlap, false);
                    mFlappingWings = true;
                }
                mSpeed += 0.02f;
            }

            // Move along movement vector
            mPosition += mDirection * mSpeed;

            // Stop flapping wings
            if (mFlappingWings && mAnim->isAnimationCompleted()){
                mFlappingWings = false;
                mAnim->setAnimation(bird_Bird_Glide_Length, mAnim_Glide);
            }

            if (mPad->isPressed(Z)){    //Return back to flapping
                mState = PLAYERSTATE_FLYING;
                mAnim->setAnimation(bird_Bird_FlyFlap_Length, mAnim_Flap);
            }
            break;
    }

    mCameraTarget = mPosition + (up * 128.0f);

    mAnim->update();
}

void TPlayer::draw()
{
    // ...
    
    //mtx.identity();
    //mtx.rotateEuler({0,angle,0});
    //mtx.floatToFixed(mtx, gBirdRot);

    TMtx44 temp1, temp2;
    
    mPosMtx.translate(mPosition);
    //mRotMtx.rotateAxis(TVec3F(0.0f, 0.0f, 1.0f), mRotation.z());
    temp1.rotateAxis(TVec3<f32>(-TSine::scos(mRotation.y()), 0.0f, TSine::ssin(mRotation.y())), -mRotation.x());
    temp2.rotateAxisY(mRotation.y());
    TMtx44::concat(temp1, temp2, mRotMtx);
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