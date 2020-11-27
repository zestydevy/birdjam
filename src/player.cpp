#include <nusys.h>

#include "player.hpp"
#include "math.hpp"
#include "animator.hpp"

#include "../models/world/shadow.h"

const float BIRD_FLYGRAVITY = 0.02f;
const float BIRD_MAXSPEED = 12.0f;
const float BIRD_FASTSPEED = 9.0f; //When you start fast animation
const float BIRD_SLOWSPEED = 6.0f; //When you start slow animation and speed up
const float BIRD_ACCEL = 0.05f;    //Acceleration when below slowspeed
const float BIRD_MINSPEED = 4.0f;
const float BIRD_FLAPSPEED = 4.0f;
const float BIRD_FLAPASCENDSPEED = 4.0f;
const float BIRD_FLAPDESCENDSPEED = 4.0f;
const float BIRD_BANKDEGREES = 45.0f;
const float BIRD_WINDRES = 0.0075f;

const float BIRD_STUTTERDEG = 10.0f;

const float BIRD_RADIUS = 35.0f;

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
    mSpeed = 1.0f;

    //Set up model animator
    mAnim = new TAnimator(sizeof(mMeshes) / sizeof(Vtx*), mMeshes, mMeshSizes);
    mAnim->setAnimation(bird_Bird_FlyFlap_Length, mAnim_Flap);
    mState = PLAYERSTATE_FLAPPING;

    // shadow
    mShadow = new TStaticObject(mDynList);
    mShadow->init();
    mShadow->setPosition({0.0f,0.0f,0.0f});
    mShadow->setScale(TVec3F(0.15f, 0.15f, 0.15f));
    mShadow->setMesh(shadow_Plane_mesh);
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

    TVec3<f32> fright;  //Flight right
    TVec3<f32> fback;  //Flight back

    float animRate = 0.25f;

    // Crash stutter effect timer
    mStutterTimer -= 0.016f;
    if (mStutterTimer < 0.0f)
        mStutterTimer = 0.0f;

    TVec3<f32> move = TVec3<f32>(0.0f, 0.0f, 0.0f);
    switch (mState){
        /* Slow Flight */
        case playerstate_t::PLAYERSTATE_FLAPPING:
            mStutterTimer = 0.0f;

            if (mPad->getAnalogX() != 0 || mPad->getAnalogY() != 0) {
                move = (forward * (float)mPad->getAnalogY() / 160.0f) + (right * (float)mPad->getAnalogX() / 160.0f); //Move relative to camera
                move = move * BIRD_FLAPSPEED;
            }

            // Smooth acceleration
            mDirection.lerp(move, 0.1f);
            mRotation = TVec3<s16>((s16)0, (s16)TSine::atan2(mDirection.x(), mDirection.z()), (s16)0);
            mPosition += mDirection;
            
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

            // Configure the camera (position is handled by the camera itself)
            mCameraTarget = mPosition + (up * 60.00f) + (mDirection * mSpeed * 10.0f);  //Target slightly above player and slightly in front of player
            break;

        /* Free flight */
        case playerstate_t::PLAYERSTATE_FLYING:
            fright = TVec3<f32>(-mDirection.z(), 0.0f, mDirection.x());  //Flight right
            fback = TVec3<f32>(-mDirection.x(), -mDirection.y(), -mDirection.z());  //Flight back

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
            mBankAngle = (mBankAngle * 7 + TSine::fromDeg(mPad->getAnalogX() / 80.0f * BIRD_BANKDEGREES)) / 8 + TSine::fromDeg(TSine::scos(TSine::fromDeg(mStutterTimer * 1440.0f)) * mStutterTimer * BIRD_STUTTERDEG);
            mRotation = TVec3<s16>((s16)-TSine::asin(mDirection.y()), TSine::atan2(mDirection.x(), mDirection.z()), mBankAngle);
            mCamera->setAngle(mRotation.y());

            // Apply gravity
            mSpeed -= mDirection.dot(TVec3F(0.0f, 1.0f, 0.0f)) * BIRD_FLYGRAVITY; // Going down Gravity
            mSpeed -= BIRD_WINDRES;
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

            animRate = (mSpeed - BIRD_MINSPEED) / (BIRD_FASTSPEED - BIRD_MINSPEED) * 0.075f;

            // Fast movement animation
            if (mSpeed > BIRD_FASTSPEED && !mFlappingWings){
                if (!mGoingFast){
                    mAnim->setAnimation(bird_Bird_GlideFast_Length, mAnim_GlideFast, true, 0.0f);
                    mGoingFast = true;
                }
                mAnim->setFrame((mSpeed - BIRD_FASTSPEED) / (BIRD_MAXSPEED - BIRD_FASTSPEED));
            }
            else if (mGoingFast) {
                mAnim->setAnimation(bird_Bird_Glide_Length, mAnim_Glide, true, animRate);
                mGoingFast = false;
            }

            // Stop flapping wings
            if (mFlappingWings && mAnim->isAnimationCompleted()){
                mFlappingWings = false;
                mAnim->setAnimation(bird_Bird_Glide_Length, mAnim_Glide, true, animRate);
                mFlapTimer = 8;
            }

            if (!mFlappingWings && !mGoingFast)
                mAnim->setTimescale(animRate); // Shake faster from wind

            if (mPad->isPressed(Z)){    //Return back to flapping
                mState = PLAYERSTATE_FLAPPING;
                mAnim->setAnimation(bird_Bird_FlyFlap_Length, mAnim_Flap);
                mRotation = TVec3<s16>((s16)0, mRotation.y(), (s16)0);

                mCamera->setMode(false);

                // Convert direction into velocity for flapping
                mDirection = mDirection * mSpeed;
                mSpeed = 1.0f;
            }

            // Configure the camera
            mCamera->setPosition(mPosition + (fback * 150.0f));
            mCameraTarget.lerp(mPosition + (up * 80.00f) + (mDirection * mSpeed * 20.0f), 0.1f);  //Target slightly above player and slightly in front of player
            break;

        /* Stun after head on crash */
        case playerstate_t::PLAYERSTATE_STUNNED:
            fright = TVec3<f32>(-mLastDirection.z(), 0.0f, mLastDirection.x());  //Flight right
            fback = TVec3<f32>(-mLastDirection.x(), -mLastDirection.y(), -mLastDirection.z());  //Flight back

            //Restore flight after crash animation
            if (mAnim->isAnimationCompleted()){
                mState = PLAYERSTATE_FLAPPING;
                mAnim->setAnimation(bird_Bird_FlyFlap_Length, mAnim_Flap);
                mRotation = TVec3<s16>((s16)0, mRotation.y(), (s16)0);

                mCamera->setMode(false);

                // Convert direction into velocity for flapping
                mDirection = mDirection * mSpeed;
                mSpeed = 1.0f;
            }

            // Move along movement vector
            mPosition += mDirection * mSpeed;

            // Configure the camera
            mCamera->setPosition(mPosition + (fback * 150.0f));
            mCameraTarget = mPosition + (up * 80.00f) + (mLastDirection * mSpeed * 20.0f);  //Target slightly above player and slightly in front of player
            break;
    }

    /* Collision check */
    mClosestFace = TCollision::findClosest(mPosition, BIRD_RADIUS);

    if (mClosestFace != nullptr){  //collision!
        float d = -mDirection.dot(mClosestFace->nrm);

        if (mState == playerstate_t::PLAYERSTATE_FLYING && d > 0.1f){
            if (d > 0.9f){  //Head on crash
                mLastDirection = mDirection;
                mDirection += d * mClosestFace->nrm * 2.0f;
                mState = PLAYERSTATE_STUNNED;
                mAnim->setAnimation(bird_Bird_GlideFlap_Length, mAnim_GlideFlap, false, 0.25f);
            }
            else{   //Bounce
                mDirection += d * mClosestFace->nrm * 2.0f;
                mSpeed *= 1.0f - d;
                mStutterTimer = 1.0f;
            }
        }
        else{   //keep the player from going oob
            TVec3F p;
            mClosestFace->project(mPosition, &p);
            mPosition = p + mClosestFace->nrm * BIRD_RADIUS;
        }
    }

    mGroundFace = TCollision::findGroundBelow(
        mPosition, BIRD_RADIUS
    );

    // set shadow position and rotation to floor
    TVec3F pt = getPosition();
    pt.y() = getGroundFace()->calcYAt(pt.xz()) + 1.0f;
    mShadow->setPosition(pt);
    mShadow->setRotation(TVec3<s16>((s16)TSine::asin(mGroundFace->nrm.z()), (s16)TSine::ssin(mGroundFace->nrm.x()), (s16)TSine::scos(mGroundFace->nrm.z())));

    mAnim->update();
}

void TPlayer::draw()
{
    // ...
    
    //mtx.identity();
    //mtx.rotateEuler({0,angle,0});
    //mtx.floatToFixed(mtx, gBirdRot);

    mShadow->draw();
    
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
	      G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_PUSH);
    gSPMatrix(mDynList->pushDL(), OS_K0_TO_PHYSICAL(&mFScaleMtx),
	      G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_PUSH);
    gSPMatrix(mDynList->pushDL(), OS_K0_TO_PHYSICAL(&mFRotMtx),
	      G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_PUSH);
        
    gSPDisplayList(mDynList->pushDL(), bird_Bird_mesh);

    gSPPopMatrix(mDynList->pushDL(), G_MTX_MODELVIEW);
    gSPPopMatrix(mDynList->pushDL(), G_MTX_MODELVIEW);
    gSPPopMatrix(mDynList->pushDL(), G_MTX_MODELVIEW);
}

// -------------------------------------------------------------------------- //