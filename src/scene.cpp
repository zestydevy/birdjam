#include <nusys.h>

#include "scene.hpp"
#include "heap.hpp"
#include "player.hpp"
#include "sprite.hpp"
#include "staticobj.hpp"
#include "collision.h"
#include "util.hpp"
#include "audio.hpp"

#include "scenedata.h"
#include "segment.h"

#include "../scene/object_info.h"

#include "../scene/scene_world.h"
#include "../models/ovl/world/model_world_col.h"
#include "../models/ovl/world/model_world.h"
#include "../models/ovl/world/model_distant.h"
#include "../models/ovl/world/model_sky.h"
#include "../models/ovl/world/shadow.h"

#include "../models/static/sprites/sprite_time.h"
#include "../models/static/sprites/sprite_items.h"
#include "../models/ovl/sprites/sprite_logo.h"
#include "../models/ovl/sprites/sprite_numfont.h"

// -------------------------------------------------------------------------- //

extern Gfx rdpinit_spr_dl[];
extern Gfx rdpinit_dl[];
extern Gfx rspinit_dl[];
//he didnt think i would do it
#define BIG_CHUNGUS 9999.9f
#define BIGGER_CHUNGUS TVec3F(BIG_CHUNGUS, BIG_CHUNGUS, BIG_CHUNGUS)

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
    gSPDisplayList(mDynList->pushDL(), rdpinit_spr_dl);
    TSprite::init(mDynList);

    TSprite timeSpr = TSprite(&logo_sprite, mLogoX, mLogoY);
    timeSpr.mScale = {1.0f,1.0f};
    timeSpr.mColor = {255,255,255,mAlpha};
    timeSpr.mAttributes = SP_TRANSPARENT;
    timeSpr.render();

    gSPDisplayList(mDynList->pushDL(), rdpinit_dl);
	gSPDisplayList(mDynList->pushDL(), rspinit_dl);
}

TScene * TLogoScene::exit()
{
    // turn off screen
    //nuGfxDisplayOff();

    // destroy scene
    delete this;

    return new TTestScene("world", mDynList);

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

void TTestScene::init()
{
    mStatus = ESceneState::RUNNING;

    // turn on screen
    nuGfxDisplayOn();
    
    // load bird and world models into memory
    TUtil::toMemory(
        reinterpret_cast<void *>(_codeSegmentEnd), 
        _bird_ovlSegmentRomStart, 
        _bird_ovlSegmentRomEnd-_bird_ovlSegmentRomStart
    );

    // create this before any game objects
    TCollider::startup(nullptr, 10, 512.0F);

    mPad = new TPad(0);
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

    vertSize = worldcol_layernest[1];
    faceStart = vertSize * 3 + 4;
    u16 faceSizeNest = worldcol_layernest[faceStart - 1];        //save nest layer for last

    u16 faceSize = faceSizeMain + faceSizeL2 + faceSizeL3 + faceSizeNest;
    mCollisionFaces = new TCollFace[faceSize];
    loadCollision(worldcol_collision, mCollisionFaces);
    loadCollision(worldcol_layer2, mCollisionFaces, faceSizeMain);
    loadCollision(worldcol_layer3, mCollisionFaces, faceSizeMain + faceSizeL2);
    loadCollision(worldcol_layernest, mCollisionFaces, faceSizeMain + faceSizeL2 + faceSizeL3);

    mColL2Start = faceSizeMain;
    mColL2End = mColL2Start + faceSizeL2;
    mColL3Start = mColL2End;
    mColL3End = mColL3Start + faceSizeL3;

    TCollision::startup(
        mCollisionFaces, faceSize, nullptr,
        (faceSize * 1.5f), 24, 256.0F
    );

    mCurrentLayer = 0;
}

void TTestScene::clearCollisions(int start, int end){
    for (int i = start; i < end; i++){
        mCollisionFaces[i].vtx[0] = BIGGER_CHUNGUS;
        mCollisionFaces[i].vtx[1] = BIGGER_CHUNGUS;
        mCollisionFaces[i].vtx[2] = BIGGER_CHUNGUS;
    }
    TCollision::calc();
}

void TTestScene::update()
{
    if (mCurrentLayer == 0 && TFlockObj::getFlockObj()->getStrength() > SIZE_LAYER1){
        clearCollisions(mColL2Start, mColL2End);
        mCurrentLayer++;
    }
    else if (mCurrentLayer == 1 && TFlockObj::getFlockObj()->getStrength() > SIZE_LAYER2){
        clearCollisions(mColL3Start, mColL3End);
        mCurrentLayer++;
    }

    TCollider::frameBegin();

    // ...
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

    TCollider::frameEnd();
}

// -------------------------------------------------------------------------- //

void TTestScene::draw()
{
    //gSPDisplayList(mDynList->pushDL(), rdpinit_spr_dl);

    //gSPDisplayList(mDynList->pushDL(), rdpinit_dl);
	//gSPDisplayList(mDynList->pushDL(), rspinit_dl);
    
    mCamera->render();

    gSPDisplayList(mDynList->pushDL(), world_World_mesh);
    gSPDisplayList(mDynList->pushDL(), distant_Distant_mesh);

    //for (int i = 0; i < 4; i++)
        //mObjects[i]->draw();
    
    mSky->draw();

    for (int i = 0; i < mObjList.capacity(); ++i) {
        mObjList[i]->draw();
    }

    mBird->draw();

    mFlock->draw();

    /*

    
    */
}

void TTestScene::draw2D()
{
    TSprite timeSpr = TSprite(&time_sprite, 20, 15);
    timeSpr.setScale(TVec3F(1.0f,1.0f,1.0f));
    timeSpr.setColor({255,255,255,255});
    timeSpr.setAttribute(SP_TRANSPARENT);
    
    TSprite dig1Spr = TSprite(&num_0_sprite, 24, 35);
    dig1Spr.setScale(TVec3F(1.0f,1.0f,1.0f));
    dig1Spr.setColor({255,255,255,255});
    dig1Spr.setAttribute(SP_TRANSPARENT);

    TSprite dig2Spr = TSprite(&num_0_sprite, 42, 35);
    dig2Spr.setScale(TVec3F(1.0f,1.0f,1.0f));
    dig2Spr.setColor({255,255,255,255});
    dig2Spr.setAttribute(SP_TRANSPARENT);
    
    timeSpr.render();
    dig1Spr.render();
    dig2Spr.render();
}

// -------------------------------------------------------------------------- //

TScene * TTestScene::exit()
{
    // ...
    return nullptr;
}

// -------------------------------------------------------------------------- //

TPlayer * TTestScene::getPlayer() { return mBird; }

// -------------------------------------------------------------------------- //