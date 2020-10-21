#include <ultra64.h>
#include <PR/ramrom.h>

#include "app.hpp"
#include "game.hpp"

CApp::CApp()
: mMainThreadStack{}, mPiMessages{},
mFrameBuffers{}
{
}

CApp::~CApp()
{
}

void CApp::init(u32 mode, u32 color, u32 feature, bool useFifo)
{
    // initialize VI manager
    osCreateViManager(OS_PRIORITY_VIMGR);
    osViSetMode(&osViModeTable[mode]);
    
    // initialize PI manager for PI access
    osCreatePiManager((OSPri)OS_PRIORITY_PIMGR, &mPiMessageQ, mPiMessages, 
		      kMaxPiMsg);

    // instantiate main game
    mGame = new TGame;

    // set framebuffer pointers
    mFrameBuffers[0] = cfb_16_a;
    mFrameBuffers[1] = cfb_16_b;

    // create DMA message queue
    osCreateMesgQueue(&mDmaMessageQ, &mDmaMessageBuffer, 1);

    // create RDP message queue and interrupt
    osCreateMesgQueue(&mRdpMessageQ, &mRdpMessageBuffer, 1);
    osSetEventMesg(OS_EVENT_DP, &mRdpMessageQ, mDummyMessage);

    // create and set v-blank event 
    osCreateMesgQueue(&mVblankMessageQ, &mVblankMessageBuffer, 1);
    osViSetEvent(&mVblankMessageQ, mDummyMessage, 1);

    // VI features
    osViSetSpecialFeatures(feature);

    mClearColor = color;
    mFifo = useFifo;
}

void CApp::setupStaticSegment(void * dest, u32 const & src)
{
    OSIoMesg dmaIOMessageBuf{};

    dmaIOMessageBuf.hdr.pri      = OS_MESG_PRI_NORMAL;
    dmaIOMessageBuf.hdr.retQueue = &mDmaMessageQ;
    dmaIOMessageBuf.dramAddr     = dest;
    dmaIOMessageBuf.devAddr      = src;
    dmaIOMessageBuf.size         = _staticSegmentRomEnd-_staticSegmentRomStart;

    osEPiStartDma(gHandler, &dmaIOMessageBuf, OS_READ);
    
    // wait for DMA to finish
    osRecvMesg(&mDmaMessageQ, &mDummyMessage, OS_MESG_BLOCK);
}

void CApp::update()
{

}