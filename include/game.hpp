#pragma once

#include <nusys.h>

//#include "dynlist.hpp"
#include "scene.hpp"
#include "array.hpp"
#include "dynlist.hpp"

#include "animator.hpp"

// ========================================================================== //

class TGame
{
    public:

    TGame();
    ~TGame() = delete;

    static inline TGame * getInstance()
    {
        return sGameInstance;
    }
    
    void init();
    void update();
    void draw();
    
    void initRcpSegment();
    void initZBuffer();
    void initFrameBuffer();

    static void testRender(u32 taskNum);

    private:

    float mTheta{0.0f};
    
    TArray<TScene *> mSceneList{};
    TDynList2 * mDynList{nullptr};

    protected:
    int mCurrentFrame = 0;
    u8 mBlackAlpha{255};
    u8 mWhiteAlpha{255};
    float mFov{84.0f};

    TAnimator * mBirdAnim;

    static TGame * sGameInstance;
};

// -------------------------------------------------------------------------- //
