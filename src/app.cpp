#include <ultra64.h>
#include <PR/ramrom.h>

#include "app.hpp"
#include "game.hpp"

CApp::CApp()
: mMainThreadStack{}, mPiMessages{},
mFrameBuffers{nullptr}
{
}

CApp::~CApp()
{
}

void CApp::init(u32 mode, u32 color, bool useFifo)
{
    /* Initialize video */ 
    osCreateViManager(OS_PRIORITY_VIMGR);
    osViSetMode(&osViModeTable[mode]);
    
    /*
     * Start PI Mgr for access to cartridge
     */
    osCreatePiManager((OSPri)OS_PRIORITY_PIMGR, &mPiMessageQ, mPiMessages, 
		      kMaxPiMsg);

    // instantiate main game
    mGame = new TGame;

    // set framebuffer pointers
    mFrameBuffers[0] = cfb_16_a;
    mFrameBuffers[1] = cfb_16_b;

    // create DMA message queue
    osCreateMesgQueue(&mDmaMessageQ, &mDmaMessageBuffer, 1);

    // ...
}