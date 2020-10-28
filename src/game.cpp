#include <ultra64.h>

#include "game.hpp"
#include "task.hpp"
#include "app.hpp"

// -------------------------------------------------------------------------- //
extern OSTask tlist;

TGame * TGame::sGameInstance{nullptr};

// -------------------------------------------------------------------------- //

TGame::TGame()
{
    sGameInstance = this;
}

void TGame::init()
{
    // allocate dynamic display list
    mDynList = new TDynList;

    // set current task to graphics task
    mTask = &tlist;

    // set framebuffer pointers
    mFrameBuffers[0] = cfb_16_a;
    mFrameBuffers[1] = cfb_16_b;

    //TTask::build(ETaskCode::F3DEX2, true);
}

void TGame::update()
{
    mDynDl = mDynList->mDl;

    initRcpSegment();
    initZBuffer();
    initFrameBuffer();

    // do rendering here
    
    draw();

    // that's a wrap for this frame. finalize
    gDPFullSync(mDynDl++);
	gSPEndDisplayList(mDynDl++);
    
    TTask::build(ETaskCode::F3DEX2, mTask, true);

    osRecvMesg(mRdpMessageQ, mDummyMessage, OS_MESG_BLOCK);

    osViSwapBuffer(mFrameBuffers[mDrawBuffer]);
    
    if (MQ_IS_FULL(mVblankMessageQ))
	    osRecvMesg(mVblankMessageQ, mDummyMessage, OS_MESG_BLOCK);

    // wait for Vertical retrace to finish swap buffers
	osRecvMesg(mVblankMessageQ, mDummyMessage, OS_MESG_BLOCK);
	
    mDrawBuffer ^= 1;

}

void TGame::draw()
{

}

void TGame::setMessages(OSMesg * messages[4])
{
    mDmaMessageBuffer = messages[0];
    mRdpMessageBuffer = messages[1];
    mDummyMessage     = messages[2];
    mVblankMessageBuffer = messages[3];
}

void TGame::setMessageQueues(OSMesgQueue * queues[4])
{
    mPiMessageQ = queues[0];
    mDmaMessageQ = queues[1];
    mRdpMessageQ = queues[2];
    mVblankMessageQ = queues[3];
}

// tell the RCP where each segment is
void TGame::initRcpSegment()
{
    gSPSegment(mDynDl++, 0, 0x0);	// K0 (physical) address segment
	gSPSegment(
        mDynDl++, STATIC_SEGMENT,
        osVirtualToPhysical(_codeSegmentEnd));
	
	gSPDisplayList(mDynDl++, rdpinit_dl);
	gSPDisplayList(mDynDl++, rspinit_dl);
	gDPSetDepthImage(mDynDl++, OS_K0_TO_PHYSICAL(zbuffer));
}

void TGame::initZBuffer()
{
    gDPSetCycleType(mDynDl++, G_CYC_FILL);
	gDPSetColorImage(mDynDl++, G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WD,
			 OS_K0_TO_PHYSICAL(zbuffer));
	gDPSetFillColor(mDynDl++, 
			GPACK_ZDZ(G_MAXFBZ,0) << 16 | GPACK_ZDZ(G_MAXFBZ,0));
	gDPFillRectangle(mDynDl++, 0, 0, SCREEN_WD-1, SCREEN_HT-1);
}

void TGame::initFrameBuffer()
{
    gDPPipeSync(mDynDl++);
	gDPSetCycleType(mDynDl++, G_CYC_FILL);

	gDPSetColorImage(mDynDl++, G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WD, 
			 OS_K0_TO_PHYSICAL(mFrameBuffers[mDrawBuffer]));
	u32 clearcolor = ((GPACK_RGBA5551(255, 255, 255, 1) << 16) |
		      (GPACK_RGBA5551(255, 255, 255, 1)));
	gDPSetFillColor(mDynDl++, clearcolor);
	gDPFillRectangle(mDynDl++, 0, 0, SCREEN_WD-1, SCREEN_HT-1);
	gDPPipeSync(mDynDl++);
	gDPSetCycleType(mDynDl++, G_CYC_1CYCLE);
}

OSTask * TGame::getTask()
{
    return mTask;
}

Gfx * TGame::getDynDL()
{
    return mDynDl;
}

TDynList * TGame::getDynList()
{
    return mDynList;
}