#include <nusys.h>
#include <os_internal.h>

#include "app.hpp"

TBlockHeap * CApp::sCurrentHeap;

// -------------------------------------------------------------------------- //

static OSMesgQueue sErrorMsgQ;
static OSMesg  sErrorMsg; 
static OSThread sErrorThread;
static u8 sErrorStack[kStackSize];

// -------------------------------------------------------------------------- //

void CApp::init()
{
    nuGfxInit();
    nuContInit();
    
    // instantiate main game
    mGame = new TGame;

    osCreateMesgQueue(&sErrorMsgQ, &sErrorMsg, 1);
    osCreateThread(&sErrorThread, 5, (void(*)(void *))appError, nullptr,
           sErrorStack+kStackSize/8, (OSPri)OS_PRIORITY_APPMAX);

    osStartThread(&sErrorThread);
    
    /*
    // initialize VI manager
    //osCreateViManager(OS_PRIORITY_VIMGR);
    //osViSetMode(&osViModeTable[mode]);
    
    // initialize PI manager for PI access
    osCreatePiManager((OSPri)OS_PRIORITY_PIMGR, &mPiMessageQ, mPiMessages, 
		      kMaxPiMsg);

    // set framebuffer pointers
    mFrameBuffers[0] = cfb_16_a;
    mFrameBuffers[1] = cfb_16_b;

    // create DMA message queue
    osCreateMesgQueue(&DmaMessageQ, &DmaMessageBuffer, 1);

    // create RDP message queue and interrupt
    osCreateMesgQueue(&mRdpMessageQ, &mRdpMessageBuffer, 1);
    osSetEventMesg(OS_EVENT_DP, &mRdpMessageQ, mDummyMessage);

    // create and set v-blank event 
    osCreateMesgQueue(&mVblankMessageQ, &mVblankMessageBuffer, 1);
    osViSetEvent(&mVblankMessageQ, mDummyMessage, 1);

    // VI features
    //osViSetSpecialFeatures(feature);
    
    mClearColor = color;
    mFifo = useFifo;
    */
}

// -------------------------------------------------------------------------- //

void CApp::setupStaticSegment(void * dest, u32 const & src)
{
    /*
    OSIoMesg dmaIOMessageBuf{};

    dmaIOMessageBuf.hdr.pri      = OS_MESG_PRI_NORMAL;
    dmaIOMessageBuf.hdr.retQueue = &DmaMessageQ;
    dmaIOMessageBuf.dramAddr     = dest;
    dmaIOMessageBuf.devAddr      = src;
    dmaIOMessageBuf.size         = _staticSegmentRomEnd-_staticSegmentRomStart;

    osEPiStartDma(gHandler, &dmaIOMessageBuf, OS_READ);
    
    // wait for DMA to finish
    osRecvMesg(&DmaMessageQ, &mDummyMessage, OS_MESG_BLOCK);
    */
}

// -------------------------------------------------------------------------- //

void CApp::run()
{   
    mGame->init();

    nuGfxFuncSet(TGame::testRender);
    nuGfxDisplayOn();

    while (true)
    {
        // ...
    }
}

// -------------------------------------------------------------------------- //

void CApp::appError(void * arg)
{
    OSMesg msg;
    
    osSetEventMesg(OS_EVENT_FAULT, &sErrorMsgQ, (OSMesg)0x10);

    auto last = (OSThread *)NULL;
    while (true) {
        // before error...
        (void) osRecvMesg(&sErrorMsgQ, (OSMesg *)&msg, OS_MESG_BLOCK);

        // after error...
        auto curr = __osGetCurrFaultedThread();
        if (curr) {
            //printFaultData(curr);
        }
    }
}