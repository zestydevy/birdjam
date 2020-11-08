#include <nusys.h>

#include "app.hpp"
#include "sprite.hpp"

#include "../models/sprites/black_sprite.h"
#include "../models/sprites/white_sprite.h"
// -------------------------------------------------------------------------- //
TGame * TGame::sGameInstance{nullptr};

extern Gfx setup_rdpstate[];
extern Gfx setup_rspstate[];
// -------------------------------------------------------------------------- //

TGame::TGame()
{
    sGameInstance = this;
}

void TGame::init()
{
    // allocate dynamic display list
    mDynList = new TDynList2(2048, nullptr);

    // set current task to graphics task
    //mTask = &tlist;

    // set framebuffer pointers
    //mFrameBuffers[0] = cfb_16_a;
    //mFrameBuffers[1] = cfb_16_b;

    // set scene array's heap for TArray
    mSceneList.setHeap(THeap::getCurrentHeap());

    //initAudio();

    //TTask::build(ETaskCode::F3DEX2, true);
}

void TGame::update()
{
    mDynList->reset();

    initRcpSegment();
    initZBuffer();
    initFrameBuffer();

    // do rendering here
    
    TSprite::init(mDynList);
    
    TSprite bo(&white_sprite, 0, 0);
    bo.mScale = {320.0f,240.0f};
    bo.mColor = {255,255,255,255};

    bo.render();
    
    TSprite::finalize();

    // that's a wrap for this frame. finalize
    gDPFullSync(mDynList->pushDL());
	gSPEndDisplayList(mDynList->pushDL());

    nuGfxTaskStart(mDynList->getHead(),
        (s32)(mDynList->fetchCmdIndex()) * sizeof (Gfx),
	    NU_GFX_UCODE_F3DEX , NU_SC_NOSWAPBUFFER);

}

static void updateVertexPos(int size, Vtx vtx[], Vtx* anim[], int frame){
    int shake = (frame % 3) - 1;
    for (int i = 0; i < size; i++){
        vtx[i] = anim[frame][i];
    }
}

void TGame::draw()
{
    /*
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
    */
}

// tell the RCP where each segment is
void TGame::initRcpSegment()
{
    /* Setting the RSP segment register  */
    gSPSegment(mDynList->pushDL(), 0, 0x0);  /* For the CPU virtual address  */

    /* Setting RSP  */
    gSPDisplayList(mDynList->pushDL(), OS_K0_TO_PHYSICAL(setup_rspstate));

    /* Setting RDP  */
    gSPDisplayList(mDynList->pushDL(), OS_K0_TO_PHYSICAL(setup_rdpstate));
    
    /*
    gSPSegment(mDynDl++, 0, 0x0);	// K0 (physical) address segment
	gSPSegment(
        mDynDl++, STATIC_SEGMENT,
        osVirtualToPhysical(_codeSegmentEnd));
	
	gSPDisplayList(mDynDl++, rdpinit_dl);
	gSPDisplayList(mDynDl++, rspinit_dl);
	gDPSetDepthImage(mDynDl++, OS_K0_TO_PHYSICAL(zbuffer));
    */
}

void TGame::initZBuffer()
{
    gDPSetDepthImage(mDynList->pushDL(), OS_K0_TO_PHYSICAL(nuGfxZBuffer));
    gDPSetCycleType(mDynList->pushDL(), G_CYC_FILL);
    gDPSetColorImage(mDynList->pushDL(), G_IM_FMT_RGBA, G_IM_SIZ_16b,kResWidth,
        OS_K0_TO_PHYSICAL(nuGfxZBuffer));
    gDPSetFillColor(mDynList->pushDL(),(GPACK_ZDZ(G_MAXFBZ,0) << 16 |
        GPACK_ZDZ(G_MAXFBZ,0)));
    gDPFillRectangle(mDynList->pushDL(), 0, 0, kResWidth-1, kResHeight-1);
    gDPPipeSync(mDynList->pushDL());
}

void TGame::initFrameBuffer()
{
    gDPSetColorImage(mDynList->pushDL(), G_IM_FMT_RGBA, G_IM_SIZ_16b, kResWidth,
        osVirtualToPhysical(nuGfxCfb_ptr));
    gDPSetFillColor(mDynList->pushDL(), (GPACK_RGBA5551(0, 0, 0, 1) << 16 | 
        GPACK_RGBA5551(0, 0, 0, 1)));
    gDPFillRectangle(mDynList->pushDL(), 0, 0, kResWidth-1, kResHeight-1);
    gDPPipeSync(mDynList->pushDL());
}

void TGame::testRender(u32 taskNum)
{
    if(taskNum < 3)
    {
        TGame::getInstance()->update();
    }
}