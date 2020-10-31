#include <ultra64.h>

#include "game.hpp"
#include "task.hpp"
#include "sprite.hpp"
#include "app.hpp"

<<<<<<< HEAD
#include "../models/bird/model_bird2.h"
#include "../models/sprites/black_sprite.h"
#include "../models/sprites/white_sprite.h"
=======
#include "../models/bird/model_bird.h"
>>>>>>> a91fbcf060922dc10043c3bd4eb9c5b865923d9c

// -------------------------------------------------------------------------- //
extern OSTask tlist;

TGame * TGame::sGameInstance{nullptr};
Dyn dyn;

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

    // set scene array's heap for TArray
    mSceneList.setHeap(THeap::getCurrentHeap());

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

    mTheta += 0.6f;

}

static void updateVertexPos(int size, Vtx vtx[], Vtx* anim[], int frame){
    int shake = (frame % 3) - 1;
    for (int i = 0; i < size; i++){
        vtx[i] = anim[frame][i];
    }
}

void TGame::draw()
{
    u16 perspNorm{0};
    
    guPerspective(&dyn.projection, &perspNorm,
		      mFov, 320.0/240.0, 100, 8000, 1.0);
    guLookAtReflect(&dyn.viewing, &(dyn.lookat[0]),
		       50, 0, 400,
		       0, 0, 0,
		       0, 1, 0);
	
    gSPLookAt(mDynDl++, &(dyn.lookat[0]));
    gSPPerspNormalize(mDynDl++, perspNorm);
    gSPMatrix(mDynDl++, OS_K0_TO_PHYSICAL(&(dyn.projection)),
		  G_MTX_PROJECTION|G_MTX_LOAD|G_MTX_NOPUSH);
    gSPMatrix(mDynDl++, OS_K0_TO_PHYSICAL(&(dyn.viewing)),
		  G_MTX_PROJECTION|G_MTX_MUL|G_MTX_NOPUSH);
	
    guTranslate(&dyn.letters_trans, -150.0f, 0.0f, -1000.0f);
    guScale(&dyn.letters_scale, 0.5f, 0.5f, 0.5f);
    guRotate(&dyn.letters_rotate, mTheta, 0.2, mTheta, 0.0);
    gSPMatrix(mDynDl++, OS_K0_TO_PHYSICAL(&(dyn.letters_trans)),
	      G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH);
    gSPMatrix(mDynDl++, OS_K0_TO_PHYSICAL(&(dyn.letters_scale)),
	      G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);
    gSPMatrix(mDynDl++, OS_K0_TO_PHYSICAL(&(dyn.letters_rotate)),
	      G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);
    gSPDisplayList(mDynDl++, letters_setup_dl);

    updateVertexPos(265, bird_Bird_mesh_vtx_0, bird_Bird_Walk_0, (mCurrentFrame / 4) % bird_Bird_Walk_Length);
    updateVertexPos(75, bird_Bird_mesh_vtx_1, bird_Bird_Walk_1, (mCurrentFrame / 4) % bird_Bird_Walk_Length);
    updateVertexPos(59, bird_Bird_mesh_vtx_2, bird_Bird_Walk_2, (mCurrentFrame / 4) % bird_Bird_Walk_Length);
    updateVertexPos(8, bird_Bird_mesh_vtx_3, bird_Bird_Walk_3, (mCurrentFrame / 4) % bird_Bird_Walk_Length);

    gSPDisplayList(mDynDl++, bird_Bird_mesh);

    TSprite::init();
    
    TSprite bo(&white_sprite, 0, 0);
    bo.mScale = {320.0f,240.0f};
    bo.mColor = {255,255,255,mWhiteAlpha};
    
    TSprite wo(&black_sprite, 0, 0);
    wo.mScale = {320.0f,240.0f};
    wo.mColor = {255,255,255,mBlackAlpha};
    
    bo.render();
    wo.render();
   
    TSprite::finalize();

    if (mCurrentFrame >= 80) {
        if (mBlackAlpha > 0) {
            mBlackAlpha -= 4;
        }
        if (mBlackAlpha < 4) {
            mBlackAlpha = 0;
        }
    }

    if (mCurrentFrame >= 110) {
        if (mWhiteAlpha > 0) {
            mWhiteAlpha -= 4;
        }
        if (mWhiteAlpha < 4) {
            mWhiteAlpha = 0;
        }
    }

    if (mCurrentFrame >= 115) {
            mFov -= 0.5f;
    }

    if (mFov < 40.0f) mFov = 40.0f;

    mCurrentFrame++;
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

Gfx ** TGame::getDynDL()
{
    return &mDynDl;
}

TDynList * TGame::getDynList()
{
    return mDynList;
}