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

#include "../models/ovl/bird/model_bird.h"

enum playerstate_t : u16 {
    PLAYERSTATE_FALLING,    //Falling
    PLAYERSTATE_IDLE,       //Idle
    PLAYERSTATE_WALKING,    //Walking on ground
    PLAYERSTATE_FLAPPING,   //Precision slow fly controls
    PLAYERSTATE_FLYING,     //Plane fly controls
    PLAYERSTATE_UTURN,
    PLAYERSTATE_STUNNED,     //Hit a wall while flying
};

enum gameplaystate_t : u16 {
    PLAYERGAMESTATE_FREEFLIGHT,
    PLAYERGAMESTATE_COUNTDOWN,
    PLAYERGAMESTATE_FLIGHT,
    PLAYERGAMESTATE_FINISHED
};


// -------------------------------------------------------------------------- //

class TPlayer;

extern TPlayer * gPlayer;

// -------------------------------------------------------------------------- //

class TPlayer :
    public TObject,
    public TSphereCollider
{

    public:

    TPlayer(TDynList2 * dl) :
        TObject { dl }
    {
        gPlayer = this;
    }

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

    TVec3F getVelocity() {
        return mDirection * mSpeed;
    }

    bool canPickupObjects() { return mState == playerstate_t::PLAYERSTATE_FLYING; }

    virtual void updateMtx() override;

    virtual void init() override;
    virtual void update() override;
    virtual void draw() override;

    void hitObject(TVec3F point, EObjType type);
    void collectObject(EObjType type);
    void passthroughObject(EObjType type);

    const TCollFace * mClosestFace;
    const TCollFace * mClosestFaceCarry;

    const TVec3<f32> & getHeldPosition(int idx = 0) { return mHeldPos[idx]; }
    TVec3<f32> mHeldPos[32];

    void startFreeFlight() { mGameState = gameplaystate_t::PLAYERGAMESTATE_FREEFLIGHT; }

    protected:
    void startFlying();
    void startIdle();
    void checkLateralCollision();
    void checkMeshCollision(const TCollFace * face, float radius);

    bool canMove() { return mGameState == gameplaystate_t::PLAYERGAMESTATE_FLIGHT || mGameState == gameplaystate_t::PLAYERGAMESTATE_FREEFLIGHT; }

    /* sfx */
    void playCawSFX();
    void playStumbleSFX();
    void playCrashSFX();
    void playBalloonPopSFX();
    void playCatSFX();
    void playChickenSFX();
    void playLeavesShuffleSFX();
    void playCriticSFX();

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
    Vtx** mAnim_IdlePreen[4] = {bird_Bird_IdlePreen_0, bird_Bird_IdlePreen_1, bird_Bird_IdlePreen_2, bird_Bird_IdlePreen_3};        //Idle preen
    Vtx** mAnim_Walk[4] = {bird_Bird_Walk_0, bird_Bird_Walk_1, bird_Bird_Walk_2, bird_Bird_Walk_3};                                 //Walking
    Vtx** mAnim_Glide[4] = {bird_Bird_Glide_0, bird_Bird_Glide_1, bird_Bird_Glide_2, bird_Bird_Glide_3};                            //Gliding
    Vtx** mAnim_GlideFast[4] = {bird_Bird_GlideFast_0, bird_Bird_GlideFast_1, bird_Bird_GlideFast_2, bird_Bird_GlideFast_3};        //Gliding Fast
    Vtx** mAnim_GlideCaw[4] = {bird_Bird_GlideCaw_0, bird_Bird_GlideCaw_1, bird_Bird_GlideCaw_2, bird_Bird_GlideCaw_3};             //Glide caw
    Vtx** mAnim_GlideCrash[4] = {bird_Bird_GlideCrash_0, bird_Bird_GlideCrash_1, bird_Bird_GlideCrash_2, bird_Bird_GlideCrash_3};   //Stunned animation 
    Vtx** mAnim_GlideFlap[4] = {bird_Bird_GlideFlap_0, bird_Bird_GlideFlap_1, bird_Bird_GlideFlap_2, bird_Bird_GlideFlap_3};        //Flapping wings while gliding
    Vtx** mAnim_Flap[4] = {bird_Bird_FlyFlap_0, bird_Bird_FlyFlap_1, bird_Bird_FlyFlap_2, bird_Bird_FlyFlap_3};                     //Flapping wings while stationary
    Vtx** mAnim_IdleFall[4] = {bird_Bird_IdleFall_0, bird_Bird_IdleFall_1, bird_Bird_IdleFall_2, bird_Bird_IdleFall_3};             //Falling
    Vtx** mAnim_IdleCaw[4] = {bird_Bird_IdleCaw_0, bird_Bird_IdleCaw_1, bird_Bird_IdleCaw_2, bird_Bird_IdleCaw_3};                  //Cawing while stationary
    Vtx** mAnim_GlideUTurn[4] = {bird_Bird_GlideUTurn_0, bird_Bird_GlideUTurn_1, bird_Bird_GlideUTurn_2, bird_Bird_GlideUTurn_3};   //UTurn

    bool mCawing{false};
    bool mFlappingWings{false};
    bool mSlowingDown{false};
    bool mGoingFast{false};
    
    float mPitchModifier {0.0f};

    float mIdleTimer{0.0f};
    float mStutterTimer{0.0f};
    float mCawTimer {0.0f};
    float mFlapTimer{0};

    s16 mBankAngle;

    playerstate_t mState;
    gameplaystate_t mGameState;

    virtual void onCollide(TCollider *) override;
    void moveCameraRelative(TVec3F & move, TVec3F & forward, TVec3F & right, float multiplier = 1.0f);

};

// -------------------------------------------------------------------------- //