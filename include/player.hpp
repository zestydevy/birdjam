#pragma once

#include <nusys.h>

#include "animator.hpp"
#include "camera.hpp"
#include "collider.hpp"
#include "collision.hpp"
#include "dynlist.hpp"
#include "math.hpp"
#include "pad.hpp"
#include "staticobj.hpp"

#include "../models/bird/model_bird.h"

enum playerstate_t : u16 {
    PLAYERSTATE_FALLING,    //Falling
    PLAYERSTATE_IDLE,       //Idle
    PLAYERSTATE_WALKING,    //Walking on ground
    PLAYERSTATE_FLAPPING,   //Precision slow fly controls
    PLAYERSTATE_FLYING,     //Plane fly controls
    PLAYERSTATE_STUNNED     //Hit a wall while flying
};

// -------------------------------------------------------------------------- //

class TPlayer :
    public TObject,
    public TSphereCollider
{

    public:

    TPlayer(TDynList2 * dl) :
        TObject { dl }
    {}

    virtual ~TPlayer() = default;

    void setPad(TPad * pad) {
        mPad = pad;
    }

    void setCamera(TCamera * camera) {
        mCamera = camera;
        mCamera->setTarget(&mCameraTarget);
    }

    TCollFace const * getGroundFace() const {
        return mGroundFace;
    }

    virtual void updateMtx() override;

    virtual void init() override;
    virtual void update() override;
    virtual void draw() override;

    //For debug only
    const TCollFace * mClosestFace;

    TVec3<f32> mHeldPos;

    protected:

    TAnimator * mAnim{nullptr};
    TPad * mPad{nullptr};

    TObject * mShadow{nullptr};

    TCamera * mCamera;
    TVec3<f32> mCameraTarget{};

    f32 mSpeed;
    bool mIsGround{false};
    TVec3<f32> mDirection{};
    TVec3<f32> mLastDirection{};
    TVec3F mCenter{};
    f32 mVelocity{0.0f};

    TCollFace const * mGroundFace { nullptr };

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

    bool mFlappingWings{false};
    bool mGoingFast{false};
    int mFlapTimer{0};
    float mStutterTimer{0.0f};

    s16 mBankAngle;

    playerstate_t mState;

    virtual void onCollide(TCollider *) override;
    void moveCameraRelative(TVec3F & move, TVec3F & forward, TVec3F & right);

};

// -------------------------------------------------------------------------- //