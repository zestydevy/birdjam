#pragma once

#include <nusys.h>

#include "math.hpp"
#include "animator.hpp"
#include "dynlist.hpp"
#include "pad.hpp"
#include "camera.hpp"
#include "collision.hpp"

#include "../models/bird/model_bird.h"

enum playerstate_t : u16 {
    PLAYERSTATE_WALKING,    //Walking on ground
    PLAYERSTATE_FLAPPING,   //Precision slow fly controls
    PLAYERSTATE_FLYING,     //Plane fly controls
    PLAYERSTATE_STUNNED     //Hit a wall while flying
};

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

    void setPad(TPad * pad) {mPad = pad;}
    void setCamera(TCamera * camera) {mCamera = camera; mCamera->setTarget(&mCameraTarget);}
    void setCollision(TCollision * collision) {mCollision = collision;}

    TVec3<f32> const & getPosition() {return mPosition;}
    TVec3<s16> const & getRotation() {return mRotation;}
    TVec3<f32> const & getScale() {return mScale;}

    void init();
    void update();
    void draw();

    //For debug only
    const TCollFace * mClosestFace;

    private:

    TVec3<f32> mPosition{};
    TVec3<s16> mRotation{};
    TVec3<f32> mScale{};
    
    TMtx44 mPosMtx{};
    TMtx44 mRotMtx{};
    TMtx44 mScaleMtx{};

    Mtx mFPosMtx{};
    Mtx mFRotMtx{};
    Mtx mFScaleMtx{};
    
    u32 mTag{0};
    TDynList2 * mDynList{nullptr};
    TAnimator * mAnim{nullptr};
    TPad * mPad{nullptr};

    TCollision * mCollision;

    TCamera * mCamera;
    TVec3<f32> mCameraTarget{};

    f32 mSpeed;
    TVec3<f32> mDirection{};
    TVec3<f32> mLastDirection{};

    /* Mesh Info */
    Vtx* mMeshes[4] = {bird_Bird_mesh_vtx_0, bird_Bird_mesh_vtx_1, bird_Bird_mesh_vtx_2, bird_Bird_mesh_vtx_3};
    int mMeshSizes[4] = {265, 75, 59, 8};

    /* Animations */
    Vtx** mAnim_Idle[4] = {bird_Bird_Idle_0, bird_Bird_Idle_1, bird_Bird_Idle_2, bird_Bird_Idle_3};                                 //Idle standing
    Vtx** mAnim_Walk[4] = {bird_Bird_Walk_0, bird_Bird_Walk_1, bird_Bird_Walk_2, bird_Bird_Walk_3};                                 //Walking
    Vtx** mAnim_Glide[4] = {bird_Bird_Glide_0, bird_Bird_Glide_1, bird_Bird_Glide_2, bird_Bird_Glide_3};                            //Gliding
    Vtx** mAnim_GlideFast[4] = {bird_Bird_GlideFast_0, bird_Bird_GlideFast_1, bird_Bird_GlideFast_2, bird_Bird_GlideFast_3};        //Gliding Fast
    //Vtx** mAnim_GlideCrash[4] = {bird_Bird_GlideCrash_0, bird_Bird_GlideCrash_1, bird_Bird_GlideCrash_2, bird_Bird_GlideCrash_3};   //Stunned animation 
    Vtx** mAnim_GlideFlap[4] = {bird_Bird_GlideFlap_0, bird_Bird_GlideFlap_1, bird_Bird_GlideFlap_2, bird_Bird_GlideFlap_3};        //Flapping wings while gliding
    Vtx** mAnim_Flap[4] = {bird_Bird_FlyFlap_0, bird_Bird_FlyFlap_1, bird_Bird_FlyFlap_2, bird_Bird_FlyFlap_3};                     //Flapping wings while stationary

    bool mFlappingWings;
    bool mGoingFast;
    int mFlapTimer;
    float mStutterTimer;

    s16 mBankAngle;

    playerstate_t mState;
};

// -------------------------------------------------------------------------- //