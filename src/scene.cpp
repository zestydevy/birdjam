#include <nusys.h>

#include "scene.hpp"
#include "heap.hpp"
#include "player.hpp"
#include "sprite.hpp"
#include "staticobj.hpp"
#include "collision.h"
#include "util.hpp"

#include "scenedata.h"
#include "segment.h"

#include "../scene/scene_world.h"
#include "../models/ovl/world/model_world_col.h"
#include "../models/ovl/world/model_world.h"
#include "../models/ovl/world/model_distant.h"
#include "../models/ovl/world/model_sky.h"
#include "../models/ovl/world/shadow.h"

// -------------------------------------------------------------------------- //

bool TScene::isInitialized()
{
    return (mStatus == ESceneState::RUNNING);
}


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
            case EObjType::DEBUG_CUBE:
                obj = new TObject(mDynList);
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

void TTestScene::init()
{
    // ...
    mStatus = ESceneState::RUNNING;

    TUtil::toMemory(reinterpret_cast<void *>(_codeSegmentEnd), _bird_ovlSegmentRomStart, _bird_ovlSegmentRomEnd-_bird_ovlSegmentRomStart);

    // create this before any game objects
    TCollider::startup(nullptr, 10, 512.0F);

    mPad = new TPad(0);
    mCamera = new TCamera(mDynList);
    mBird = new TPlayer(mDynList);
    mFlock = new TFlockObj(mDynList);
    mSky = new TObject(mDynList);
    mObjList.setHeap(THeap::getCurrentHeap());

    mBird->init();
    mBird->setPad(mPad);
    mCamera->setPad(mPad);

    mBird->setCamera(mCamera);

    mBird->setPosition({0.0f,2500.0f,0.0f});
    mBird->setRotation({0,0,0});
    mBird->setScale({0.03f,0.03f,0.03f});

    mFlock->setPosition(mBird->getPosition());
    mFlock->init();

    mSky->init();
    mSky->setPosition({0.0f,-2000.0f,0.0f});
    mSky->setScale(TVec3F(80.0f, 80.0f, 80.0f));
    mSky->setMesh(sky_Sphere_mesh);

    loadObjects(scene_world);

//    for (int i = 0; i < 4; i++){
//        mObjects[i] = new TObject(mDynList);
//        mObjects[i]->init();
//        mObjects[i]->setPosition({0.0f,0.0f,0.0f});
//        mObjects[i]->setScale(TVec3F(0.05f, 0.05f, 0.05f));
//        mObjects[i]->setMesh(cube_Cube_mesh);
//    }

    //Load scene collision
    u16 vertStart = 2;
    u16 vertSize = worldcol_collision[1];
    u16 faceStart = vertSize * 3 + 4;
    u16 faceSize = worldcol_collision[faceStart - 1];
    TCollFace * faces = new TCollFace[faceSize];
    for (int i = 0; i < faceSize; i++){
        s16 v0i = worldcol_collision[faceStart + (i * 3) + 0];
        s16 v1i = worldcol_collision[faceStart + (i * 3) + 1];
        s16 v2i = worldcol_collision[faceStart + (i * 3) + 2];

        faces[i].vtx[0] = TVec3F((float)worldcol_collision[vertStart + (v0i * 3) + 0], (float)worldcol_collision[vertStart + (v0i * 3) + 1], (float)worldcol_collision[vertStart + (v0i * 3) + 2]);
        faces[i].vtx[1] = TVec3F((float)worldcol_collision[vertStart + (v1i * 3) + 0], (float)worldcol_collision[vertStart + (v1i * 3) + 1], (float)worldcol_collision[vertStart + (v1i * 3) + 2]);
        faces[i].vtx[2] = TVec3F((float)worldcol_collision[vertStart + (v2i * 3) + 0], (float)worldcol_collision[vertStart + (v2i * 3) + 1], (float)worldcol_collision[vertStart + (v2i * 3) + 2]);
    }

    TCollision::startup(
        faces, faceSize, nullptr,
        (faceSize * 2), 10, 512.0F
    );
}

void TTestScene::update()
{
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

void TTestScene::exit()
{
    // ...
}

TPlayer * TTestScene::getPlayer() { return mBird; }

// -------------------------------------------------------------------------- //