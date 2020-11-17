#include <nusys.h>

#include "player.hpp"
#include "math.hpp"
#include "animator.hpp"

const float BIRD_FLYGRAVITY = 0.2f;
const float BIRD_MAXSPEED = 75.0f;
const float BIRD_FASTSPEED = 50.0f; //When you start fast animation
const float BIRD_SLOWSPEED = 25.0f; //When you start slow animation and speed up
const float BIRD_ACCEL = 0.5f;      //Acceleration when below slowspeed
const float BIRD_MINSPEED = 10.0f;
const float BIRD_FLAPSPEED = 10.0f;
const float BIRD_FLAPASCENDSPEED = 10.0f;
const float BIRD_FLAPDESCENDSPEED = 10.0f;
const float BIRD_BANKDEGREES = 45.0f;

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

    mFlapTimer--;

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

                mPosition += move * BIRD_FLAPSPEED;
            }
            
            if (mPad->isHeld(A))
                mPosition += TVec3<f32>(0.0f, BIRD_FLAPASCENDSPEED, 0.0f);
            if (mPad->isHeld(B))
                mPosition -= TVec3<f32>(0.0f, BIRD_FLAPDESCENDSPEED, 0.0f);

            if (mPad->isPressed(Z)){    //Start flying
                // Set state and animation
                mState = PLAYERSTATE_FLYING;
                mAnim->setAnimation(bird_Bird_GlideFlap_Length, mAnim_GlideFlap, false, 0.25f);

                mFlappingWings = true;

                // Set initial flight direction to the facing direction
                mDirection.set(TSine::ssin(mRotation.y()), 0.0f, TSine::scos(mRotation.y()));

                // Set initial flight speed
                mSpeed = 25.0f;
                mGoingFast = false;

                mCamera->setMode(true);
            }
            break;
        case PLAYERSTATE_FLYING:
            TVec3<f32> fright = TVec3<f32>(-mDirection.z(), 0.0f, mDirection.x());  //Flight right
            TVec3<f32> fback = TVec3<f32>(-mDirection.x(), -mDirection.y(), -mDirection.z());  //Flight back

            temp1.rotateAxis(fright, TSine::fromDeg(90.0f));
            up = temp1.mul(mDirection);  //Flight back

            // Flight controls
            temp1.rotateAxis(fright, TSine::fromDeg(1.0f * -mPad->getAnalogY() / 80.0f));
            temp2.rotateAxisY(TSine::fromDeg(1.0f * -mPad->getAnalogX() / 80.0f));
            TMtx44::concat(temp1, temp2, temp3);
            mDirection = temp3.mul(mDirection);

            //Clamp y direction
            if (mDirection.y() > 0.9f)
                mDirection.set(mDirection.x(), 0.9f, mDirection.z());
            if (mDirection.y() < -0.9f)
                mDirection.set(mDirection.x(), -0.9f, mDirection.z());
            mDirection.normalize();

            // Apply visual rotation
            s16 bankTarget = TSine::fromDeg(mPad->getAnalogX() / 80.0f * BIRD_BANKDEGREES);
            mBankAngle = (mBankAngle * 7 + bankTarget) / 8;
            mRotation = TVec3<s16>((s16)-TSine::asin(mDirection.y()), TSine::atan2(mDirection.x(), mDirection.z()), mBankAngle);
            mCamera->setAngle(mRotation.y());

            // Apply gravity
            mSpeed -= mDirection.dot(TVec3F(0.0f, 1.0f, 0.0f)) * BIRD_FLYGRAVITY; // Going down Gravity
            if (mSpeed < BIRD_MINSPEED)
                mSpeed = BIRD_MINSPEED; // Min Speed
            if (mSpeed > BIRD_MAXSPEED)
                mSpeed = BIRD_MAXSPEED; // Max Speed

            if (mSpeed < BIRD_SLOWSPEED && mFlapTimer < 0){ // Flapping speed
                mGoingFast = false;
                if (mFlappingWings == false){
                    mAnim->setAnimation(bird_Bird_GlideFlap_Length, mAnim_GlideFlap, false, 0.25f);
                    mFlappingWings = true;
                }
                mSpeed += BIRD_ACCEL;
            }

            // Move along movement vector
            mPosition += mDirection * mSpeed;

            float glideAnimRate = (mSpeed - BIRD_MINSPEED) / (BIRD_FASTSPEED - BIRD_MINSPEED) * 0.15f;

            // Fast movement animation
            if (mSpeed > BIRD_FASTSPEED && !mFlappingWings){
                if (!mGoingFast){
                    mAnim->setAnimation(bird_Bird_GlideFast_Length, mAnim_GlideFast, true, 0.0f);
                    mGoingFast = true;
                }
                mAnim->setFrame((mSpeed - BIRD_FASTSPEED) / (BIRD_MAXSPEED - BIRD_FASTSPEED));
            }
            else if (mGoingFast) {
                mAnim->setAnimation(bird_Bird_Glide_Length, mAnim_Glide, true, glideAnimRate);
                mGoingFast = false;
            }

            // Stop flapping wings
            if (mFlappingWings && mAnim->isAnimationCompleted()){
                mFlappingWings = false;
                mAnim->setAnimation(bird_Bird_Glide_Length, mAnim_Glide, true, glideAnimRate);
                mFlapTimer = 8;
            }

            if (!mFlappingWings && !mGoingFast)
                mAnim->setTimescale(glideAnimRate); // Shake faster from wind

            if (mPad->isPressed(Z)){    //Return back to flapping
                mState = PLAYERSTATE_FLAPPING;
                mAnim->setAnimation(bird_Bird_FlyFlap_Length, mAnim_Flap);
                mRotation = TVec3<s16>((s16)0, mRotation.y(), (s16)0);

                mCamera->setMode(false);
            }

            mCamera->setPosition(mPosition + (fback * 1500.0f));
            break;
    }

    mCameraTarget = mPosition + (up * 350.0f);

    mAnim->update();
}

void TPlayer::draw()
{
    // ...
    
    //mtx.identity();
    //mtx.rotateEuler({0,angle,0});
    //mtx.floatToFixed(mtx, gBirdRot);

    TMtx44 temp1, temp2, temp3;
    
    mPosMtx.translate(mPosition);
    temp1.rotateAxis(TVec3<f32>(-TSine::scos(mRotation.y()), 0.0f, TSine::ssin(mRotation.y())), -mRotation.x());
    temp2.rotateAxisY(mRotation.y());
    TMtx44::concat(temp1, temp2, temp3);
    temp1.rotateAxis(temp3.mul(TVec3<f32>(0.0f, 0.0f, 1.0f)), mRotation.z());
    TMtx44::concat(temp1, temp3, mRotMtx);
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