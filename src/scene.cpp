
#include <nusys.h>

#include "audio.hpp"
#include "collision.h"
#include "graphic.h"
#include "heap.hpp"
#include "menu.hpp"
#include "player.hpp"
#include "rank.hpp"
#include "scene.hpp"
#include "scenedata.h"
#include "segment.h"
#include "sprite.hpp"
#include "staticobj.hpp"
#include "util.hpp"

#include "../scene/object_info.h"

#include "../scene/scene_world.h"
#include "../models/ovl/world/model_world_col.h"
#include "../models/ovl/world/model_world.h"
#include "../models/ovl/world/model_distant.h"
#include "../models/ovl/world/model_sky.h"
#include "../models/ovl/world/shadow.h"
#include "../models/ovl/world/model_window.h"

//#include "../models/static/sprites/sprite_time.h"
#include "../models/static/sprites/sprite_items.h"
#include "../models/ovl/sprites/sprite_logo.h"
#include "../models/ovl/sprites/sprite_numfont.h"
#include "../models/ovl/sprites/sp_hud.h"

#include "../models/static/highlight/model_highlightring.h"


// -------------------------------------------------------------------------- //

extern Gfx rdpinit_spr_dl[];
extern Gfx rdpinit_dl[];
extern Gfx rspinit_dl[];

// -------------------------------------------------------------------------- //

Lights2 litc2 = gdSPDefLights2(
    0x5, 0x5, 0x5, /* ambient color */
    100, 100, 0,   /* light color */
    -32, -64, -32, /* normal */
    50, 50, 0,     /* light color */
    15, 30, 120    /* normal */
);

Gfx letters_setup_dl[] = {
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsSPSetGeometryMode(
        G_ZBUFFER | G_SHADE | G_SHADING_SMOOTH |
        G_CULL_BACK | G_LIGHTING
    ), gsSPSetLights2(litc2),
    gsDPSetCombineMode (G_CC_SHADE, G_CC_SHADE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsSPEndDisplayList(),
};

// -------------------------------------------------------------------------- //

bool TScene::isInitialized()
{
    return (mStatus == ESceneState::RUNNING);
}

// -------------------------------------------------------------------------- //

void TScene::loadObjects(TSceneEntry const list[])
{
    s32 size = list[0].id;
    list = reinterpret_cast<const TSceneEntry *>(&list[1]);
    // mObjList.reserve((u32)size);

    for(int i = 0; i < size; ++i) {
        
        if (list[i].id >= EObjType::INVALID) {
            // wtf kind of model are you tryin to load
            return;
        }

        TObject * obj = nullptr;
        auto type = (EObjType)list[i].id;

        switch(list[i].id) {
            case EObjType::PLAYERSTART:
                gPlayer->setPosition({list[i].positionX, list[i].positionY, list[i].positionZ});
                break;
            case EObjType::DEBUG_CUBE:
                obj = new TObject(mDynList);
                obj->setMesh(TObject::getMeshGfx(type));
                break;
            case EObjType::NEST:
                obj = new TNest(mDynList);
                obj->setMesh(TObject::getMeshGfx(type));
                break;
            default: 
                switch (TObject::getNestObjectInfo((EObjType)list[i].id).colType){
                    case 0:
                        obj = new TNestObjSphere(mDynList, type);
                        break;
                    case 1:
                        obj = new TNestObjBox(mDynList, type);
                        break;
                }
                break;
        }

        if (obj == nullptr) {
            continue;
        }

        obj->setPosition({list[i].positionX, list[i].positionY, list[i].positionZ});
        obj->setRotation({TSine::fromDeg(list[i].rotationX), TSine::fromDeg(list[i].rotationY), TSine::fromDeg(list[i].rotationZ)});
        obj->setScale({list[i].scaleX, list[i].scaleY, list[i].scaleZ});
        obj->init();

        mObjList.push(obj);
    }
}

// -------------------------------------------------------------------------- //

void TLogoScene::init()
{
    mStatus = ESceneState::RUNNING;

    // turn on screen
    //nuGfxDisplayOn();

    // load logo into memory
    TUtil::toMemory(
        reinterpret_cast<void *>(_codeSegmentEnd), 
        _logo_ovlSegmentRomStart, 
        _logo_ovlSegmentRomEnd-_logo_ovlSegmentRomStart
    );

    mTimer = new TTimer;
    mShowTimer = new TTimer;

    // fade timer
    mTimer->start(3);
    // scene start timer
    mShowTimer->start(1);

    // move logo off-screen
    mLogoX = 512;
}

// -------------------------------------------------------------------------- //

void TLogoScene::update()
{
    // wait two seconds to boot
    if (mShowTimer != nullptr) {
        runBootTimer();
    }
    
    // fade if we reached two seconds
    if (mTimer != nullptr) {
        runLogoTimer();
    }
}

// -------------------------------------------------------------------------- //

void TLogoScene::draw()
{
    // ...
}

void TLogoScene::draw2D()
{

    TSprite logo = TSprite();
    logo.load(logo_sprite);
    logo.setPosition(TVec2S{mLogoX, mLogoY});
    logo.setScale(TVec2F{1.0f, 1.0f});
    logo.setColor({255,255,255,mAlpha});
    logo.setAttributes(SP_FRACPOS | SP_TRANSPARENT);
    logo.draw();
}

TScene * TLogoScene::exit()
{
    // turn off screen
    //nuGfxDisplayOff();

    return new TMenuScene { mDynList };

}

// -------------------------------------------------------------------------- //

void TLogoScene::runBootTimer()
{
    if (mShowTimer->update()) {
        delete mShowTimer;
        mShowTimer = nullptr;
        mLogoX = 40;        // move logo on screen
        TAudio::playSound(ESfxType::SFX_CAW);
    }
}

// -------------------------------------------------------------------------- //

void TLogoScene::runLogoTimer()
{
    if (mTimer->update()) {
        mAlpha -= 4;
        if (mAlpha <= 4) {
            mAlpha = 0;

            delete mTimer;
            mTimer = nullptr;

            mStatus = ESceneState::EXITING;     // exit scene
        }
    }
}

// -------------------------------------------------------------------------- //

void TTestScene::loadCollision(const s16 collision[], TCollFace * dest, int offset){
    u16 vertStart = 2;
    u16 vertSize = collision[1];
    u16 faceStart = vertSize * 3 + 4;
    u16 faceSize = collision[faceStart - 1];
    for (int i = 0; i < faceSize; i++){
        s16 v0i = collision[faceStart + (i * 3) + 0];
        s16 v1i = collision[faceStart + (i * 3) + 1];
        s16 v2i = collision[faceStart + (i * 3) + 2];

        dest[i + offset].vtx[0] = TVec3F((float)collision[vertStart + (v0i * 3) + 0], (float)collision[vertStart + (v0i * 3) + 1], (float)collision[vertStart + (v0i * 3) + 2]);
        dest[i + offset].vtx[1] = TVec3F((float)collision[vertStart + (v1i * 3) + 0], (float)collision[vertStart + (v1i * 3) + 1], (float)collision[vertStart + (v1i * 3) + 2]);
        dest[i + offset].vtx[2] = TVec3F((float)collision[vertStart + (v2i * 3) + 0], (float)collision[vertStart + (v2i * 3) + 1], (float)collision[vertStart + (v2i * 3) + 2]);
    }
}

// -------------------------------------------------------------------------- //

const EButton CACHE_CODE[] = {UP, UP, DOWN, DOWN, LEFT, RIGHT, LEFT, RIGHT, B, A};

void TTestScene::init()
{
    mStatus = ESceneState::RUNNING;

    TAudio::stopMusic();
    TAudio::playMusic(EBgm::BGM_FLY);
    TAudio::fadeMusic(1.0F);

    // turn on screen
    nuGfxDisplayOn();

    // load bird and world models into memory
    TUtil::toMemory(
        reinterpret_cast<void *>(_world_ovlSegmentStart), 
        _world_ovlSegmentRomStart, 
        _world_ovlSegmentRomEnd-_world_ovlSegmentRomStart
    );

    // create this before any game objects
    TCollider::startup(nullptr, 10, 512.0F);

    gRank.reset();

    mPad = new TPad { 0 };
    gHud = new THud { mPad };
    gHud->init();

    mCamera = new TCamera(mDynList);
    mBird = new TPlayer(mDynList);
    mFlock = new TFlockObj(mDynList);
    mSky = new TObject(mDynList);
    mSky->mAlwaysDraw = true;
    mObjList.setHeap(THeap::getCurrentHeap());

    mBird->setPad(mPad);
    mCamera->setPad(mPad);

    mBird->setCamera(mCamera);

    mBird->setPosition({0.0f,2500.0f,0.0f});
    mBird->setRotation({0,0,0});
    mBird->setScale({0.03f,0.03f,0.03f});

    mFlock->setPosition(mBird->getPosition());
    mFlock->init();

    mSky->setPosition({0.0f,-2000.0f,0.0f});
    mSky->setScale(TVec3F(80.0f, 80.0f, 80.0f));
    mSky->setMesh(sky_Sphere_mesh);
    mSky->init();

    TObject * window = new TObject(mDynList);
    window->setPosition(mBird->getPosition() + TVec3F(0.0f, 50.0f, 0.0f));
    window->setScale({0.05f,0.05f,0.05f});
    window->setRotation({0,0,0});
    window->setMesh(window_HeldWindow_mesh);
    window->mAlwaysDraw = true;
    window->init();
    mObjList.push(window);

    loadObjects(scene_world);

    mBird->init();

    mCamera->jumpToTarget();

//    for (int i = 0; i < 4; i++){
//        mObjects[i] = new TObject(mDynList);
//        mObjects[i]->init();
//        mObjects[i]->setPosition({0.0f,0.0f,0.0f});
//        mObjects[i]->setScale(TVec3F(0.05f, 0.05f, 0.05f));
//        mObjects[i]->setMesh(cube_Cube_mesh);
//    }

    //Load scene collision
    u16 vertSize = worldcol_collision[1];
    u16 faceStart = vertSize * 3 + 4;
    u16 faceSizeMain = worldcol_collision[faceStart - 1];   //main world face count

    vertSize = worldcol_layer2[1];
    faceStart = vertSize * 3 + 4;
    u16 faceSizeL2 = worldcol_layer2[faceStart - 1];        //layer 2 face count

    vertSize = worldcol_layer3[1];
    faceStart = vertSize * 3 + 4;
    u16 faceSizeL3 = worldcol_layer3[faceStart - 1];        //layer 3 face count

    //@miluaces, add layer 4
    vertSize = worldcol_layer4[1];
    faceStart = vertSize * 3 + 4;
    u16 faceSizeL4 = worldcol_layer4[faceStart - 1];        //layer 4 face count

    vertSize = worldcol_layernest[1];
    faceStart = vertSize * 3 + 4;
    u16 faceSizeNest = worldcol_layernest[faceStart - 1];        //save nest layer for last

    u16 faceSize = faceSizeMain + faceSizeL2 + faceSizeL3 + faceSizeL4 + faceSizeNest;
    mCollisionFaces = new TCollFace[faceSize];
    loadCollision(worldcol_collision, mCollisionFaces);
    loadCollision(worldcol_layer2, mCollisionFaces, faceSizeMain);
    loadCollision(worldcol_layer3, mCollisionFaces, faceSizeMain + faceSizeL2);
    loadCollision(worldcol_layer4, mCollisionFaces, faceSizeMain + faceSizeL2 + faceSizeL3);
    loadCollision(worldcol_layernest, mCollisionFaces, faceSizeMain + faceSizeL2 + faceSizeL3 + faceSizeL4);

    mColL2Start = faceSizeMain;
    mColL2End = mColL2Start + faceSizeL2;
    mColL3Start = mColL2End;
    mColL3End = mColL3Start + faceSizeL3;
    mColL4Start = mColL3End;
    mColL4End = mColL4Start + faceSizeL4;

    TCollision::startup(
        mCollisionFaces, faceSize, nullptr,
        (faceSize * 1.5f), 10, 768.0F
    );

    mCurrentLayer = 0;
}

void TTestScene::clearCollisions(int start, int end){
    for (int i = start; i < end; i++){
        mCollisionFaces[i].setPassThru(true);
    }
}

void TTestScene::update()
{
    //Add layers
    //if (mCurrentLayer == 2 && TFlockObj::getFlockObj()->maxCarryWeight() < SIZE_LAYER2){
    //    clearCollisions(mColL3Start, mColL3End);
    //    mCurrentLayer--;
    //}
    //if (mCurrentLayer == 1 && TFlockObj::getFlockObj()->maxCarryWeight() < SIZE_LAYER1){
    //    clearCollisions(mColL2Start, mColL2End);
    //    mCurrentLayer--;
    //}

    //Remove layers
    if (mCurrentLayer == 0 && TFlockObj::getFlockObj()->canGrabObject(SIZE_LAYER1)){
        clearCollisions(mColL2Start, mColL2End);
        mCurrentLayer++;

        for (int i = 0; i < mObjList.capacity(); ++i) 
            mObjList[i]->increaseRadius(SIZE_LAYER1);
    }
    if (mCurrentLayer == 1 && TFlockObj::getFlockObj()->canGrabObject(SIZE_LAYER2)){
        clearCollisions(mColL3Start, mColL3End);
        mCurrentLayer++;

        //for (int i = 0; i < mObjList.capacity(); ++i) 
            //mObjList[i]->increaseRadius(SIZE_LAYER2);
    }
    if (mCurrentLayer == 2 && TFlockObj::getFlockObj()->canGrabObject(SIZE_LAYER3)){
        clearCollisions(mColL4Start, mColL4End);
        mCurrentLayer++;

        //for (int i = 0; i < mObjList.capacity(); ++i) 
            //mObjList[i]->increaseRadius(SIZE_LAYER3);
    }

    TCollider::frameBegin();

    mPad->read();
    mBird->update();

//    if (mBird->mClosestFace != nullptr){
//        TVec3F pt;
//        mBird->mClosestFace->project(mBird->getPosition(), &pt);
//
//        mObjects[0]->setPosition(mBird->mClosestFace->vtx[0]);
//        mObjects[1]->setPosition(mBird->mClosestFace->vtx[1]);
//        mObjects[2]->setPosition(mBird->mClosestFace->vtx[2]);
//        mObjects[3]->setPosition(pt);
//    }

    for (int i = 0; i < mObjList.capacity(); ++i) {
        mObjList[i]->update();
    }

    mFlock->update();
    gHud->update();

    if (gHud->isExit()) {
        mStatus = ESceneState::EXITING;
        return;
    }

    if (mPad->isPressed(CACHE_CODE[mCheatState])){
        mCheatState++;

        if (mCheatState == sizeof(CACHE_CODE) / sizeof(EButton)){
            TFlockObj::getFlockObj()->incFlock(0, SIZE_LAYER3);
            TNest::startEndGame();
            mCheatState = 0;
        }
    }
    else if (mPad->isPressed((EButton)(A | B | UP | LEFT | RIGHT | DOWN)))
        mCheatState = 0;

    TCollider::frameEnd();

    mCamera->update();
}

// -------------------------------------------------------------------------- //

const Gfx dlCleanup[] = {
    gsDPPipeSync(),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsDPSetTextureLUT(G_TT_NONE),
    gsSPSetGeometryMode(G_CULL_BACK),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsSPEndDisplayList(),
};

const Gfx dlCleanup2[] = {
    gsDPPipeSync(),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetTextureLUT(G_TT_NONE),
    gsSPSetGeometryMode(G_CULL_BACK),
	gsSPSetGeometryMode(G_LIGHTING),
	gsSPClearGeometryMode(G_TEXTURE_GEN),
	gsDPSetCombineLERP(0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT, 0, 0, 0, SHADE, 0, 0, 0, ENVIRONMENT),
	gsSPTexture(65535, 65535, 0, 0, 0),
	gsSPEndDisplayList(),
};

// -------------------------------------------------------------------------- //

void TTestScene::drawObjects(EDrawLayer layer){
    const Gfx * last = nullptr;
    for (int i = 0; i < mObjList.capacity(); ++i) {
        //Check if this object is to be drawn on this layer
        if (mObjList[i]->mDrawLayer == layer){
            const Gfx * type = mObjList[i]->getGraphicsInitializer();
            //Check if we are drawing the same object as the previous iteration
            if (type != last){
                //Check if the previous object needs to be deinitialized first
                if (last != nullptr)
                    gSPDisplayList(mDynList->pushDL(), dlCleanup2);

                //Check if we need to initialize the new one
                if (type != nullptr)      
                    gSPDisplayList(mDynList->pushDL(), type);

                last = type;
            }

            //Draw like normal
            mObjList[i]->draw();
        }
    }
    if (last != nullptr)   //Deinitialize last object if needed
        gSPDisplayList(mDynList->pushDL(), dlCleanup2);
}

// -------------------------------------------------------------------------- //

void TTestScene::draw()
{
    gSPDisplayList(mDynList->pushDL(), letters_setup_dl);
    //gSPDisplayList(mDynList->pushDL(), rdpinit_spr_dl);

    //gSPDisplayList(mDynList->pushDL(), rdpinit_dl);
    //gSPDisplayList(mDynList->pushDL(), rspinit_dl);

    mCamera->render();

    gSPDisplayList(mDynList->pushDL(), world_World_mesh);
    gSPDisplayList(mDynList->pushDL(), distant_Distant_mesh);

    //for (int i = 0; i < 4; i++)
        //mObjects[i]->draw();

    mSky->draw();

    gSPDisplayList(mDynList->pushDL(), highlightring_HighlightRing_init);
    for (int i = 0; i < mObjList.capacity(); ++i)
        mObjList[i]->drawRing();
    gSPDisplayList(mDynList->pushDL(), highlightring_HighlightRing_cleanup);

    drawObjects(EDrawLayer::PREWINDOW);

    mBird->draw();
    mFlock->draw();

    if (TFlockObj::getFlockObj()->getCapacity() > 0.0f)
        mCamera->drawWindow();

    drawObjects(EDrawLayer::POSTWINDOW);
}

void TTestScene::draw2D() {
    gHud->draw();
}

// -------------------------------------------------------------------------- //

TScene *
TTestScene::exit() {
    return new TMenuScene { mDynList };
}

// -------------------------------------------------------------------------- //

TPlayer * TTestScene::getPlayer() { return mBird; }

// -------------------------------------------------------------------------- //