#pragma once

#include <ultra64.h>

#include "dynlist.hpp"
#include "scene.hpp"
#include "array.hpp"

// ========================================================================== //

struct Dyn
{
	Mtx	projection;
	Mtx	viewing;

	Mtx	projectionBG;
	Mtx	viewingBG;
        Mtx     identity;

	LookAt	lookat[2];
	Hilite	hilite[2];

        Mtx     letters_scale;
        Mtx     letters_rotate;
        Mtx     letters_trans;

	Gfx	glist[2048];
};

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
    
    void setMessages(OSMesg * messages[4]);
    void setMessageQueues(OSMesgQueue * queues[4]);
    void initRcpSegment();
    void initZBuffer();
    void initFrameBuffer();

    OSTask * getTask();
    Gfx * getDynDL();
    TDynList * getDynList();

    private:

    void * mFrameBuffers[2];
    u32 mDrawBuffer{0};
    OSTask * mTask{nullptr};
    TDynList * mDynList{nullptr};
    Gfx * mDynDl{nullptr};
    float mTheta{0.0f};
    
    TArray<TScene *> mSceneList{};
    
    // OS messages and queues
    OSMesg * mDmaMessageBuffer{nullptr};
    OSMesg * mRdpMessageBuffer{nullptr};
    OSMesg * mDummyMessage{nullptr};
    OSMesg * mVblankMessageBuffer{nullptr};

    OSMesgQueue * mPiMessageQ{nullptr};
    OSMesgQueue	* mDmaMessageQ{nullptr};
    OSMesgQueue * mRdpMessageQ{nullptr};
    OSMesgQueue * mVblankMessageQ{nullptr};


    protected:

    static TGame * sGameInstance;
};

// -------------------------------------------------------------------------- //
