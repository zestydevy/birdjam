#include <nusys.h>

#include "player.hpp"
#include "math.hpp"
#include "animator.hpp"
#include "util.hpp"
#include "hud.hpp"
#include "menu.hpp"
#include "segment.h"

#include "score.hpp"

#include "../models//ovl/world/shadow.h"

const float BIRD_FLYGRAVITY = 1.2f * kInterval;
const float BIRD_FLYGRAVITY2 = 2.0f * kInterval;
const float BIRD_MAXSPEED = 600.0f * kInterval;
const float BIRD_INITSPEED = 420.0f * kInterval;
const float BIRD_FASTSPEED = 450.0f * kInterval; //When you start fast animation
const float BIRD_SLOWSPEED = 300.0f * kInterval; //When you start slow animation and speed up
const float BIRD_ACCEL = 0.7f * kInterval;    //Acceleration when below slowspeed
const float BIRD_SLOWACCEL = 1.2f * kInterval; //Acceleration when slowing down
const float BIRD_MINSPEED = 240.0f * kInterval;
const float BIRD_FLAPSPEED = 240.0f * kInterval;
const float BIRD_FLAPASCENDSPEED = 240.0f * kInterval;
const float BIRD_FLAPDESCENDSPEED = 240.0f * kInterval;
const float BIRD_BANKDEGREES = 45.0f;
const float BIRD_WINDRES = 0.42f * kInterval;
const float BIRD_GRAVITY = 150.0f * kInterval;
const float BIRD_FALLGRAVITY = 450.0f * kInterval;

const float BIRD_STUTTERDEG = 10.0f;

const float BIRD_RADIUS = 10.0f;

// -------------------------------------------------------------------------- //

TPlayer * gPlayer { nullptr };

// -------------------------------------------------------------------------- //

void TPlayer::init()
{
    TObject::init();


    // set up to start in flight for testing:
    mDirection = TVec3<f32>(0.0f, 0.0f, 0.0f);
    mRotation = TVec3<f32>(0.0f, 0.0f, 0.0f);
    mSpeed = 1.0f;

    //Load model from ROM
    if (TMenuScene::isFreedomMode()) {
        TUtil::toMemory(
            reinterpret_cast<void *>(_eagle_ovlSegmentStart), 
            _eagle_ovlSegmentRomStart, 
            _eagle_ovlSegmentRomEnd-_eagle_ovlSegmentRomStart
        );
        setMesh(bird_eagle_Bird_mesh);
        mAnim = new TAnimator(sizeof(mMeshesEagle) / sizeof(Vtx*), mMeshesEagle, mMeshSizesEagle);
    }
    else{
        TUtil::toMemory(
            reinterpret_cast<void *>(_bird_ovlSegmentStart), 
            _bird_ovlSegmentRomStart, 
            _bird_ovlSegmentRomEnd-_bird_ovlSegmentRomStart
        );
        setMesh(bird_Bird_mesh);
        mAnim = new TAnimator(sizeof(mMeshes) / sizeof(Vtx*), mMeshes, mMeshSizes);
    }

    //Set up model animator
    setAnimation(1, ANIM_IDLE);
    mState = PLAYERSTATE_FALLING;

    // shadow
    mShadow = new TObject(mDynList);
    mShadow->init();
    mShadow->setPosition({0.0f,0.0f,0.0f});
    mShadow->setScale(TVec3F(0.10f, 0.10f, 0.10f));
    mShadow->setMesh(shadow_Plane_mesh);

    initCollider(TAG_PLAYER, TAG_PLAYER, 0, 1);
    setCollideRadius(BIRD_RADIUS);
    setCollideCenter(mPosition);

    mCameraTarget = mPosition;

    gHud->startCountDown();
    mGameState = gameplaystate_t::PLAYERGAMESTATE_COUNTDOWN;
}

void TPlayer::setAnimation(int length, playeranim_t anim, bool loop, float timescale){
    if (TMenuScene::isFreedomMode())
    mAnim->setAnimation(*(mAnimLength_Eagle[anim]), mAnimSet_Eagle[anim], loop, timescale);
        else
    mAnim->setAnimation(*(mAnimLength_Normal[anim]), mAnimSet_Normal[anim], loop, timescale);
}

void TPlayer::startFlying(){
    // Set state and animation
    mState = PLAYERSTATE_FLYING;
    setAnimation(bird_Bird_GlideFlap_Length, ANIM_GLIDEFLAP, false, 0.25f);

    mPosition += TVec3F(0.0f, BIRD_RADIUS, 0.0f);

    mFlappingWings = true;

    // Set initial flight direction to the facing direction
    mDirection.set(TSine::ssin(mRotation.y()), 0.2f, TSine::scos(mRotation.y()));

    // Set initial flight speed
    mSpeed = BIRD_INITSPEED;
    mGoingFast = false;

    mCawing = false;

    mCamera->setMode(true);
}

void TPlayer::startIdle(){
    mState = PLAYERSTATE_FALLING;
    setAnimation(bird_Bird_GlideFlap_Length, ANIM_GLIDEFLAP, true, 0.0f);
    mRotation = TVec3<s16>((s16)0, mRotation.y(), (s16)0);

    mCamera->setMode(false);

    // Convert direction into velocity for flapping
    mDirection = mDirection * mSpeed;
    mSpeed = 1.0f;

    //land if we are on ground
    if (mGroundFace != nullptr) {
        float yPos = mGroundFace->calcYAt(mPosition.xz()) + BIRD_RADIUS;
        if (mPosition.y() - yPos <= BIRD_RADIUS)
            mPosition.y() = yPos;
        else
            mState = PLAYERSTATE_FALLING;
    }
    else
        mState = PLAYERSTATE_FALLING;

    mCawing = false;
}

void TPlayer::checkLateralCollision(){
    TVec3F nrmm = mDirection;
    nrmm.normalize();
    nrmm *= (BIRD_RADIUS / 2.0f);

    mGroundFace = TCollision::findGroundBelow(mPosition + nrmm, BIRD_RADIUS);  //recalc ground pos

    // attach to the closet point of the ground
    if (mGroundFace != nullptr && mGroundFace->nrm.y() > 0.707f) {
        float yPos = mGroundFace->calcYAt((mPosition + nrmm).xz()) + BIRD_RADIUS;
        if (mPosition.y() - yPos <= BIRD_RADIUS){
            mPosition.y() = yPos;

            mClosestFace = TCollision::findClosest(mPosition + nrmm , BIRD_RADIUS / 2.0f); //use closest face in front of player
        }
        else{
            setAnimation(bird_Bird_IdleFall_Length, ANIM_IDLEFALL, false, 0.25f);    //honestly the sonic fall walk looks better
            mState = PLAYERSTATE_FALLING;
        }
    }
    else{
        setAnimation(bird_Bird_IdleFall_Length, ANIM_IDLEFALL, false, 0.0f);
        mState = PLAYERSTATE_FALLING;
    }
}

void TPlayer::checkMeshCollision(const TCollFace * face, float radius){
    if (face != nullptr){  //collision!
        float d = -mDirection.dot(face->nrm);

        if (mState == playerstate_t::PLAYERSTATE_FLYING){
            if (mSlowingDown && mSpeed < BIRD_SLOWSPEED && TFlockObj::getFlockObj()->getSize() <= 0)
            {
                mState = PLAYERSTATE_FALLING;
                setAnimation(bird_Bird_GlideFlap_Length, ANIM_GLIDEFLAP, true, 0.0f);
                mRotation = TVec3<s16>((s16)0, mRotation.y(), (s16)0);

                mCamera->setMode(false);

                // Convert direction into velocity for flapping
                mDirection = mDirection * mSpeed;
                mSpeed = 1.0f;
            }
            else if (d > 0.1f){
                if (d > 0.9f){  //Head on crash
                    mLastDirection = mDirection;
                    mDirection += d * face->nrm * 2.0f;
                    mState = PLAYERSTATE_STUNNED;
                    setAnimation(bird_Bird_GlideCrash_Length, ANIM_GLIDECRASH, false, 0.4f);
                    mCamera->setMode(true);
                    playCrashSFX();
                }
                else{   //Bounce
                    mDirection += d * face->nrm * 2.0f;
                    mSpeed *= 1.0f - d;
                    mStutterTimer = 1.0f;
                    playStumbleSFX();
                }

                TFlockObj::getFlockObj()->dropTopObject();
            }
        }
        else if (d >= 0.0f){   //keep the player from going oob
            TVec3F p;
            face->project(mPosition, &p);
            mPosition = p + face->nrm * radius;
        }
    }
}

void TPlayer::hitObject(TVec3F point, EObjType type){
    if (type == EObjType::LEAVES)
        return;

    TVec3F nrm = mPosition - point;
    if (nrm.getSqrLength() <= 0.0f)
        nrm = TVec3F(0.0f, 1.0f, 0.0f);
    nrm.normalize();

    float d = -mDirection.dot(nrm);

    if (mState == playerstate_t::PLAYERSTATE_FLYING && d > 0.1f){
        if (d > 0.9f){  //Head on crash
            mLastDirection = mDirection;
            mDirection += d * nrm * 2.0f;
            mState = PLAYERSTATE_STUNNED;
            setAnimation(bird_Bird_GlideCrash_Length, ANIM_GLIDECRASH, false, 0.4f);
            playCrashSFX();
        }
        else{   //Bounce
            mDirection += d * nrm * 2.0f;
            mSpeed *= 1.0f - d;
            mStutterTimer = 1.0f;
            playStumbleSFX();
        }

        TFlockObj::getFlockObj()->dropTopObject();
    }
    else if (d >= 0.0f) {   //keep the player from going oob
        mPosition = point + nrm * BIRD_RADIUS;
    }
}

void TPlayer::collectObject(EObjType type){
    switch (type){
        case EObjType::BALLOON:
            playBalloonPopSFX();
            break;
        case EObjType::CHICKEN:
            playChickenSFX();
            break;
        case EObjType::CAT:
            playCatSFX();
            break;
        case EObjType::CRITIC:
            playCriticSFX();
            break;
    }
}
void TPlayer::passthroughObject(EObjType type){
    switch (type){
        case EObjType::LEAVES:
            playLeavesShuffleSFX();
            break;
    }
}

/* SFX */
void TPlayer::playCawSFX(){
    mCawTimer = 0.4f;
}
void TPlayer::playStumbleSFX(){}
void TPlayer::playCrashSFX(){}
void TPlayer::playBalloonPopSFX(){}
void TPlayer::playCatSFX(){}
void TPlayer::playChickenSFX(){}
void TPlayer::playLeavesShuffleSFX(){}
void TPlayer::playCriticSFX(){}

void TPlayer::update()
{
    TObject::update();

    // ...
    //if (mPad->getAnalogX() != 0 || mPad->getAnalogY() != 0) {
    //    mAngle = TSine::atan2(-mPad->getAnalogX(), -mPad->getAnalogY());
    //}

    mFlapTimer -= kInterval;
    mCawTimer -= kInterval;

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
    mStutterTimer -= kInterval;
    if (mStutterTimer < 0.0f)
        mStutterTimer = 0.0f;

    TVec3<f32> move = TVec3<f32>(0.0f, 0.0f, 0.0f);

    /* Ground check */
    mGroundFace = TCollision::findGroundBelow(mPosition, BIRD_RADIUS);

    /* Collision check */
    mClosestFace = TCollision::findClosest(mPosition, BIRD_RADIUS);

    // Set up held object positions
    mHeldPos[0] = mPosition + (TVec3F(0.0f, -1.0f, 0.0f) * BIRD_RADIUS);
    mHeldVel[0] = getVelocity();
    for (int i = TFlockObj::getFlockObj()->getNumObjects() - 1; i > 0; i--){   //Backwards so there is a 1 frame delay for each held object
        float r = TFlockObj::getFlockObj()->getObjRadius(i);
        TVec3F dif = mHeldPos[i] - mHeldPos[i-1];
        if (dif.getLength() > r){
            dif.normalize();
            dif *= r;
            TVec3F next = mHeldPos[i];
            next.moveTowards(mHeldPos[i-1] + dif, BIRD_FASTSPEED);
            mHeldVel[i] = (next - mHeldPos[i]);
            mHeldPos[i] = next;
        }
    }
    for (int i = TFlockObj::getFlockObj()->getNumObjects(); i < 32; i++){
        mHeldPos[i] = mPosition + (TVec3F(0.0f, -1.0f, 0.0f) * BIRD_RADIUS);
        mHeldVel[i] = TVec3F(0.0f, 0.0f, 0.0f);
    }

    float camDist = TMath<float>::clamp(TFlockObj::getFlockObj()->getChainLength(), 0.0f, 300.0f);

    switch (mState){
        
        // -------------------------------------------------------------------- //
        // walk controls
        case playerstate_t::PLAYERSTATE_FALLING:
            mAnim->setTimescale(0.25f);
            if (mClosestFace == nullptr || mClosestFace->nrm.y() <= 0.707f) {
                mVelocity += BIRD_FALLGRAVITY * kInterval;
                mVelocity = TMath<float>::clamp(mVelocity, -BIRD_FASTSPEED, BIRD_FASTSPEED);
                mPosition -= {0.0f, mVelocity, 0.0f};
            } else {
                // we touched the ground, idle
                mState = playerstate_t::PLAYERSTATE_IDLE;
                mVelocity = 0.0f;
                setAnimation(bird_Bird_Idle_Length, ANIM_IDLE);
                mIdleTimer = 0;
            }

            mCawing = false;
            
            moveCameraRelative(move, forward, right);
            
            mCameraTarget = mPosition + (up * 35.00f) + (mDirection * mSpeed * 10.0f);  //Target slightly above player and slightly in front of player

            // Switch to flying state
            if (canMove() && (mPad->isPressed(A) || mPad->isPressed(Z)))    //Start flying
                startFlying();
        break;

        // -------------------------------------------------------------------- //
        // idle. c'mon let's get a move on...
        case playerstate_t::PLAYERSTATE_IDLE:
            moveCameraRelative(move, forward, right);

            checkLateralCollision();


            if (!mCawing){
                if (mIdleTimer >= 5.0f && mIdleTimer <= 5.1f)
                    setAnimation(bird_Bird_IdlePreen_Length, ANIM_IDLEPREEN, false, 0.3f);
                else if (mIdleTimer > 5.1f && mAnim->isAnimationCompleted())
                    setAnimation(bird_Bird_Idle_Length, ANIM_IDLE);
                mIdleTimer += kInterval;
            }

            if (mPad->isPressed(L) && !mCawing && mCawTimer <= 0.0f){
                mCawing = true;
                setAnimation(bird_Bird_IdleCaw_Length, ANIM_IDLECAW, false, 0.4f);
                playCawSFX();
            }
            
            // played moved, change to walking state
            if (!mCawing){
                if (mPad->getAnalogX() != 0 || mPad->getAnalogY() != 0) {
                    mState = playerstate_t::PLAYERSTATE_WALKING;
                    setAnimation(bird_Bird_Walk_Length, ANIM_WALK, true, 0.3f);
                }

                if (canMove() && (mPad->isPressed(A) || mPad->isPressed(Z)))    //Start flying
                    startFlying();
            }
            else if (mAnim->isAnimationCompleted() && mCawTimer < 0.0f){
                mCawing = false;
                setAnimation(bird_Bird_IdleCaw_Length, ANIM_IDLECAW, false, -0.25f);
            }
        
        break;

        // -------------------------------------------------------------------- //
        // walking on the ground
        case playerstate_t::PLAYERSTATE_WALKING:{
            moveCameraRelative(move, forward, right);

            checkLateralCollision();

            mCameraTarget = mPosition + (up * 35.00f) + (mDirection * mSpeed * 10.0f);  //Target slightly above player and slightly in front of player

            // played moved, change to walking state
            if (mPad->getAnalogX() == 0 && mPad->getAnalogY() == 0) {
                // back to idle
                mState = playerstate_t::PLAYERSTATE_IDLE;
                setAnimation(bird_Bird_Idle_Length, ANIM_IDLE);
                mIdleTimer = 0.0f;
            }

            mAnim->setTimescale(move.getLength() * 0.1f);

            if (mPad->isPressed(L) && !mCawing && mCawTimer <= 0.0f){
                mCawing = true;
                setAnimation(bird_Bird_IdleCaw_Length, ANIM_IDLECAW, false, 0.4f);
                mState = playerstate_t::PLAYERSTATE_IDLE;
                playCawSFX();
            }

            // Switch to flying state
            if (!mCawing){
                if (canMove() && (mPad->isPressed(A) || mPad->isPressed(Z)))    //Start flying
                    startFlying();
            }
        }
        break;
        
        // -------------------------------------------------------------------- //
        /* Slow Flight */
        case playerstate_t::PLAYERSTATE_FLAPPING:
            mStutterTimer = 0.0f;

            if (mPad->getAnalogX() != 0 || mPad->getAnalogY() != 0) {
                move = (forward * (float)mPad->getAnalogY() / 160.0f) + (right * (float)mPad->getAnalogX() / 160.0f); //Move relative to camera
                move = move * BIRD_FLAPSPEED;
            }

            // Smooth acceleration
            mDirection.moveTowards(move, 0.5f);
            mRotation = TVec3<s16>((s16)0, (s16)TSine::atan2(mDirection.x(), mDirection.z()), (s16)0);
            mPosition += mDirection;
            
            if (mPad->isHeld(A))
                mPosition += TVec3<f32>(0.0f, BIRD_FLAPASCENDSPEED, 0.0f);
            if (mPad->isHeld(B))
                mPosition -= TVec3<f32>(0.0f, BIRD_FLAPDESCENDSPEED, 0.0f);

            if (mPad->isPressed(Z)){    //Start flying
                // Set state and animation
                mState = PLAYERSTATE_FLYING;
                setAnimation(bird_Bird_GlideFlap_Length, ANIM_GLIDEFLAP, false, 0.25f);

                mFlappingWings = true;

                // Set initial flight direction to the facing direction
                mDirection.set(TSine::ssin(mRotation.y()), 0.0f, TSine::scos(mRotation.y()));

                // Set initial flight speed
                mSpeed = BIRD_INITSPEED;
                mGoingFast = false;

                mCamera->setMode(true);
            }

            // Configure the camera (position is handled by the camera itself)
            mCameraTarget = mPosition + (up * 35.00f) + (mDirection * mSpeed * 10.0f);  //Target slightly above player and slightly in front of player

            if (mClosestFace != nullptr) {
                // we touched the ground, idle
                mState = playerstate_t::PLAYERSTATE_IDLE;
                mVelocity = 0.0f;
                setAnimation(bird_Bird_Idle_Length, ANIM_IDLE);
                mIdleTimer = 0.0f;
                mCawing = false;
            }
            break;

        // -------------------------------------------------------------------- //
        /* Free flight */
        case playerstate_t::PLAYERSTATE_FLYING:
            fright = TVec3<f32>(-mDirection.z(), 0.0f, mDirection.x());  //Flight right
            fback = TVec3<f32>(-mDirection.x(), -mDirection.y(), -mDirection.z());  //Flight back


            temp1.rotateAxis(fright, TSine::fromDeg(90.0f));
            up = temp1.mul(mDirection);  //Flight back

            //mHeldPos = mPosition - (up * BIRD_RADIUS);

            // Flight controls
            if (canMove()){
                temp1.rotateAxis(fright, TSine::fromDeg(60.0f * -mPad->getAnalogY() / 80.0f * kInterval));
                temp2.rotateAxisY(TSine::fromDeg(60.0f * -mPad->getAnalogX() / 80.0f * kInterval));
                TMtx44::concat(temp1, temp2, temp3);
                mDirection = temp3.mul(mDirection);
            }

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
            mSpeed -= mDirection.dot(TVec3F(0.0f, 1.0f, 0.0f)) * (mDirection.y() < 0.0f ? BIRD_FLYGRAVITY2 : BIRD_FLYGRAVITY); // Going down Gravity
            mSpeed -= BIRD_WINDRES;
            if (mSpeed < BIRD_MINSPEED)
                mSpeed = BIRD_MINSPEED; // Min Speed
            if (mSpeed > BIRD_MAXSPEED)
                mSpeed = BIRD_MAXSPEED; // Max Speed

            animRate = (mSpeed - BIRD_MINSPEED) / (BIRD_FASTSPEED - BIRD_MINSPEED) * 0.075f;

            if (((canMove() && mPad->isHeld(A)) || mSpeed < BIRD_SLOWSPEED) && !mSlowingDown && mSpeed < BIRD_FASTSPEED){ // Flapping speed - when you hold A, or when going too slow. Can't do this when going too fast.
                mGoingFast = false;
                if (mFlapTimer < 0.0f && mFlappingWings == false){
                    setAnimation(bird_Bird_GlideFlap_Length, ANIM_GLIDEFLAP, false, 0.25f);
                    mFlappingWings = true;
                }
                mSpeed += BIRD_ACCEL;
            }
            if (canMove() && mPad->isHeld(B)){
                animRate = 0.25f;
                if (!mSlowingDown){
                    setAnimation(bird_Bird_FlyFlap_Length, ANIM_FLAP, true, 0.25f);
                    mPitchModifier = -30.0f;
                }
                if (mPitchModifier < 15.0f){            //Move bird's pitch to make it look like its fighting against wind.
                    mPitchModifier += 75.0f * kInterval;
                    if (mPitchModifier > 15.0f)
                        mPitchModifier = 15.0f;
                }
                mSpeed -= BIRD_SLOWACCEL;
                mSlowingDown = true;
            }
            else if (mSlowingDown)
            {
                mGoingFast = false;
                mSlowingDown = false;
                setAnimation(bird_Bird_GlideFlap_Length, ANIM_GLIDEFLAP, false, 0.25f);
                mFlappingWings = true;
            }
            else
            {
                if (mPitchModifier > 0.0f)              //Restore pitch to normal
                    mPitchModifier -= 75.0f * kInterval;
                if (mPitchModifier < 0.0f)
                        mPitchModifier = 0.0f;
            }

            if (mPad->isPressed(L) && !mCawing && mCawTimer <= 0.0f){
                //mCawing = true;
                //setAnimation(bird_Bird_GlideCaw_Length, ANIM_GLIDECAW, false, 0.25f);
                playCawSFX();
            }
            //if (mCawing)
            //    mAnim->setTimescale(0.25f);

            // Move along movement vector
            mPosition += mDirection * mSpeed;
            
            // Fast movement animation
            if (!mCawing){
                if (mSpeed > BIRD_FASTSPEED && !mFlappingWings && !mSlowingDown){
                    if (!mGoingFast){
                        setAnimation(bird_Bird_GlideFast_Length, ANIM_GLIDEFAST, true, 0.0f);
                        mGoingFast = true;
                    }
                    mAnim->setFrame((mSpeed - BIRD_FASTSPEED) / (BIRD_MAXSPEED - BIRD_FASTSPEED));
                }
                else if (mGoingFast && !mSlowingDown) {
                    setAnimation(bird_Bird_Glide_Length, ANIM_GLIDE, true, animRate);
                    mGoingFast = false;
                }

                // Stop flapping wings
                if (mFlappingWings && mAnim->isAnimationCompleted() && !mSlowingDown){
                    mFlappingWings = false;
                    setAnimation(bird_Bird_Glide_Length, ANIM_GLIDE, true, animRate);
                    mFlapTimer = 0.133f;
                }

                if (!mFlappingWings && !mGoingFast)
                mAnim->setTimescale(animRate); // Shake faster from wind
            }
            //else if (mAnim->isAnimationCompleted()){
                //mCawing = false;
                //setAnimation(bird_Bird_GlideCaw_Length, ANIM_GLIDECAW, false, -0.25f);
           // }

            //if (mPad->isPressed(Z))    //Return back to flapping
            //    startIdle();

            //Add in pitch animation
            mRotation.x() += TSine::fromDeg(-mPitchModifier);

            if (canMove()){
                // Configure the camera
                mCamera->setPosition(mPosition + (fback * (150.0f + camDist)));
                mCameraTarget.lerpTime(mPosition + (up * 30.00f) + (mDirection * mSpeed * 20.0f), 0.1f, kInterval);  //Target slightly above player and slightly in front of player

                //Flight camera controls
                if (mPad->isHeld(C_DOWN))
                    mCameraTarget += (up * -10.00f);
                if (mPad->isHeld(C_UP))
                    mCameraTarget += (up * 10.00f);
                if (mPad->isHeld(C_LEFT))
                    mCameraTarget += (fright * -20.00f);
                if (mPad->isHeld(C_RIGHT))
                    mCameraTarget += (fright * 20.00f);

                if (mPad->isHeld(R)){
                    mCamera->setPosition(mPosition + (mDirection * BIRD_RADIUS));
                    mCameraTarget = mPosition + (mDirection * BIRD_RADIUS * 2.0f);
                    mCamera->jumpToTarget();
                }
            }
            break;

        // -------------------------------------------------------------------- //
        /* Stun after head on crash */
        case playerstate_t::PLAYERSTATE_STUNNED:
            fright = TVec3<f32>(-mLastDirection.z(), 0.0f, mLastDirection.x());  //Flight right
            fback = TVec3<f32>(-mLastDirection.x(), -mLastDirection.y(), -mLastDirection.z());  //Flight back

            //Restore flight after crash animation
            if (mAnim->isAnimationCompleted()){
                startFlying();
            }

            // Move along movement vector
            mPosition += mDirection * mSpeed;

            // Configure the camera
            mCamera->setPosition(mPosition + (fback * (150.0f + camDist)));
            mCameraTarget = mPosition + (up * 60.00f) + (mLastDirection * mSpeed * 20.0f);  //Target slightly above player and slightly in front of player
            break;
    }

    //Mesh collision
    checkMeshCollision(mClosestFace, BIRD_RADIUS);
    //float carryrad = TFlockObj::getFlockObj()->getRadius();
    //if (carryrad > 0.0f){
    //    mClosestFaceCarry = TCollision::findClosest(mHeldPos, TMath<float>::max(BIRD_RADIUS, carryrad));
    //    checkMeshCollision(mClosestFaceCarry, carryrad);
    //}

    //Object collision
    setCollideCenter(mPosition);

    //Adjust FOV based on speed
    if (canMove()){
        float fov = ((mSpeed - BIRD_SLOWSPEED) / (BIRD_FASTSPEED - BIRD_SLOWSPEED)) * (75.0f - 45.0f) + 45.0f;
        fov = TMath<float>::clamp(fov, 45.0f, 75.0f);
        mCamera->setFOV(mCamera->getFOV() * 0.25f + (fov * 0.75f));
    }

    // set shadow position and rotation to floor
    if (getGroundFace() != nullptr) {
        TVec3F pt = getPosition();
        pt.y() = getGroundFace()->calcYAt(pt.xz()) + 1.0f;
        mShadow->setPosition(pt);
        mShadow->setRotation(TVec3<s16>((s16)TSine::atan2(mGroundFace->nrm.z(), mGroundFace->nrm.y()), (s16)0, (s16)-TSine::atan2(mGroundFace->nrm.x(), mGroundFace->nrm.y())));
    }
    else if (mPosition.y() < 0.0f){
        mPosition.y() = 0.0f;   //if they somehow got underground
    }

    //OOB Check
    if (mPosition.y() < -BIRD_RADIUS && (mState == playerstate_t::PLAYERSTATE_FALLING || mState == playerstate_t::PLAYERSTATE_WALKING))
        startFlying();  //no more jesus bird
    mPosition.x() = TMath<float>::clamp(mPosition.x(), -4500.0f, 3600.0f);
    mPosition.y() = TMath<float>::clamp(mPosition.y(), -BIRD_RADIUS, 3000.0f);
    mPosition.z() = TMath<float>::clamp(mPosition.z(), -4200.0f, 4200.0f);

    //Game state and HUD check
    if (gHud->isTimeUp() && mGameState != gameplaystate_t::PLAYERGAMESTATE_FINISHED){
        mGameState = gameplaystate_t::PLAYERGAMESTATE_FINISHED;

        mEndCameraAngle = 0;
        mEndCameraDistance = 300.0f + TNest::getNestObject()->getSize() / 8.0f;
        mEndCameraTimer = 0.0f;
        
        mCamera->setMode(true);

        //Drop everything and don't pick anything new up
        TFlockObj::getFlockObj()->dropAllObjects();
        TFlockObj::getFlockObj()->setActive(false);
    }
    if (mGameState == gameplaystate_t::PLAYERGAMESTATE_COUNTDOWN){
        if (gHud->isCountedDown()){
            mGameState = gameplaystate_t::PLAYERGAMESTATE_FLIGHT;
            TFlockObj::startHighlightTimer();
            if (mPad->isHeld(A))
                startFlying();
        }
    }
    else if (mGameState == gameplaystate_t::PLAYERGAMESTATE_FINISHED){
        mEndCameraAngle += TSine::fromDeg(15.0f * kInterval);
        mCameraTarget = TNest::getNestObject()->getPosition();

        float dy = TNest::getNestObject()->getTopY() - mCameraTarget.y();
        mCameraTarget.y() = TNest::getNestObject()->getTopY() + dy * -(TSine::scos(TSine::fromDeg(mEndCameraTimer * 12.0f)) + 1.0f) / 2.0f;

        mCamera->setPosition(
            TNest::getNestObject()->getPosition() +
            TVec3F(0.0f, TNest::getNestObject()->getTopY() + (dy * ((TSine::scos(TSine::fromDeg(mEndCameraTimer * 12.0f)) + 1.0f) / 4.0f)), 0.0f) + 
            (mEndCameraDistance * TVec3F(TSine::scos(TSine::fromDeg(mEndCameraTimer * -12.0f)), 0.0f, TSine::ssin(TSine::fromDeg(mEndCameraTimer * -12.0f))))
            );

        mCamera->setFOV(45.0f);

        mEndCameraTimer += kInterval;
    }

    updateBlkMap();
    mAnim->update();
}

void TPlayer::updateMtx()
{
    TMtx44 temp1, temp2, temp3, mPosMtx, mScaleMtx;
    
    mPosMtx.translate(mPosition);
    temp1.rotateAxis(TVec3<f32>(-TSine::scos(mRotation.y()), 0.0f, TSine::ssin(mRotation.y())), -mRotation.x());
    temp2.rotateAxisY(mRotation.y());
    TMtx44::concat(temp1, temp2, temp3);
    temp1.rotateAxis(temp3.mul(TVec3<f32>(0.0f, 0.0f, 1.0f)), mRotation.z());
    TMtx44::concat(temp1, temp3, mRotMtx);
    mScaleMtx.scale(mScale);

    //Combine mtx
    TMtx44::concat(mPosMtx, mRotMtx, temp1);
    TMtx44::concat(temp1, mScaleMtx, temp2);

    TMtx44::floatToFixed(temp2, mFMtx);
    TMtx44::floatToFixed(mRotMtx, mFRotMtx);

    mMtxNeedsUpdate = false;
}

void TPlayer::draw()
{
    if (mGroundFace != nullptr) {
        mShadow->draw();
    }

    //setMesh(bird_Bird_mesh);
    
    updateMtx();
    TObject::draw();
    
#if 0
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
#endif
}

// -------------------------------------------------------------------------- //

void TPlayer::onCollide(
    TCollider * const other
) {
    // TODO
}

// -------------------------------------------------------------------------- //

// move player relative to camera
void TPlayer::moveCameraRelative(TVec3F & move, TVec3F & forward, TVec3F & right, float multiplier)
{
    // make sure bird is moving relative to the camera
    if (mPad->getAnalogX() != 0 || mPad->getAnalogY() != 0) {
        move = (forward * (float)mPad->getAnalogY() / 160.0f) + (right * (float)mPad->getAnalogX() / 160.0f); //Move relative to camera
        move = move * BIRD_FLAPSPEED * multiplier;
    }

    if (!canMove())
        move = TVec3F(0.0f, 0.0f, 0.0f);

    // Smooth acceleration
    mDirection.lerpTime(move, 0.1f, kInterval);
    mRotation = TVec3<s16>((s16)0, (s16)TSine::atan2(mDirection.x(), mDirection.z()), (s16)0);
    mPosition += mDirection;
}

// -------------------------------------------------------------------------- //