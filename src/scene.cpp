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

//#include "../models/static/sprites/sprite_time.h"
#include "../models/static/sprites/sprite_items.h"
#include "../models/ovl/sprites/sprite_logo.h"
#include "../models/ovl/sprites/sprite_numfont.h"
#include "../models/ovl/sprites/sp_hud.h"

// -------------------------------------------------------------------------- //

extern Gfx rdpinit_spr_dl[];
extern Gfx rdpinit_dl[];
extern Gfx rspinit_dl[];

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
#if 0 // please help me fix this zest
    gSPDisplayList(mDynList->pushDL(), rdpinit_spr_dl);
    TSprite::init(mDynList);

    TSprite timeSpr = TSprite(&logo_sprite, mLogoX, mLogoY);
    timeSpr.mScale = {1.0f,1.0f};
    timeSpr.mColor = {255,255,255,mAlpha};
    timeSpr.mAttributes = SP_TRANSPARENT;
    timeSpr.render();

    gSPDisplayList(mDynList->pushDL(), rdpinit_dl);
	gSPDisplayList(mDynList->pushDL(), rspinit_dl);
#endif
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

    gHud = new THud {};
    gHud->init();

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
}

void TTestScene::draw2D() {
    gHud->draw();
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