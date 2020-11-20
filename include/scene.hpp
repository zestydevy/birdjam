#pragma once

#include <nusys.h>

#include "dynlist.hpp"
#include "camera.hpp"
#include "pad.hpp"
#include "player.hpp"
#include "collision.hpp"
#include "staticobj.hpp"

// -------------------------------------------------------------------------- //

enum ESceneState : u32
{
    IDLE = 0,
    RUNNING,
    EXITING,
};

// -------------------------------------------------------------------------- //

class TScene
{
    public:

    inline TScene(char * name, TDynList2 * list)
        : mName{name}, mDynList{list} {};

    ~TScene() = default;
    
    virtual void init() = 0;
    virtual void update() = 0;
    virtual void draw() = 0;
    virtual void exit() = 0;

    inline char * getName() {return mName;}
    ESceneState getState() {return mStatus;}
    bool isInitialized();
    virtual TPlayer * getPlayer() {return nullptr;}

    ESceneState mStatus{ESceneState::IDLE};
    TDynList2 * mDynList{nullptr};

    private:

    char * mName{nullptr};
};

// -------------------------------------------------------------------------- //

class TTestScene final
    : public TScene
{
    public:

    TTestScene(char * name, TDynList2 * list)
        : TScene(name, list) {};

    virtual void init() override;
    virtual void update() override;
    virtual void draw() override;
    virtual void exit() override;
    virtual TPlayer * getPlayer() override {return mBird;}

    private:

    TCamera * mCamera{nullptr};
    TPad * mPad{nullptr};
    TPlayer * mBird{nullptr};

    TStaticObject * mObjects[4];
    
    TCollision * mCollision{nullptr};
};

// -------------------------------------------------------------------------- //