#include <nusys.h>

#include "scene.hpp"
#include "heap.hpp"
#include "player.hpp"
#include "sprite.hpp"
#include "collision.h"
#include "../models/world/model_world_col.h"

#include "../models/world/model_world.h"
#include "../models/sprites/sprite_sky2.h"

// -------------------------------------------------------------------------- //

bool TScene::isInitialized()
{
    return (mStatus == ESceneState::RUNNING);
}


void TTestScene::init()
{
    // ...
    mStatus = ESceneState::RUNNING;
    mPad = new TPad(0);
    mCamera = new TCamera(mDynList);
    mBird = new TPlayer(mDynList);
    mCollision = new TCollision();

    mBird->init();
    mBird->setPad(mPad);
    mCamera->setPad(mPad);

    mBird->setCamera(mCamera);

    mBird->setPosition({0.0f,2500.0f,0.0f});
    mBird->setRotation({0,0,0});
    mBird->setScale({0.05f,0.05f,0.05f});

    for (int i = 0; i < 4; i++){
        mObjects[i] = new TStaticObject(mDynList);
        mObjects[i]->init();
        mObjects[i]->setPosition({0.0f,0.0f,0.0f});
        mObjects[i]->setScale(TVec3F(0.05f, 0.05f, 0.05f));
    }

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

        faces[i].v0 = TVec3F((float)worldcol_collision[vertStart + (v0i * 3) + 0], (float)worldcol_collision[vertStart + (v0i * 3) + 1], (float)worldcol_collision[vertStart + (v0i * 3) + 2]);
        faces[i].v1 = TVec3F((float)worldcol_collision[vertStart + (v1i * 3) + 0], (float)worldcol_collision[vertStart + (v1i * 3) + 1], (float)worldcol_collision[vertStart + (v1i * 3) + 2]);
        faces[i].v2 = TVec3F((float)worldcol_collision[vertStart + (v2i * 3) + 0], (float)worldcol_collision[vertStart + (v2i * 3) + 1], (float)worldcol_collision[vertStart + (v2i * 3) + 2]);
    }
    mCollision->startup(faces, faceSize);

    mBird->setCollision(mCollision);
}

void TTestScene::update()
{
    // ...
    mPad->read();
    mBird->update();

    if (mBird->mClosestFace != nullptr){
        TVec3F pt;
        mBird->mClosestFace->project(mBird->getPosition(), &pt);

        mObjects[0]->setPosition(mBird->mClosestFace->v0);
        mObjects[1]->setPosition(mBird->mClosestFace->v1);
        mObjects[2]->setPosition(mBird->mClosestFace->v2);
        mObjects[3]->setPosition(pt);
    }
}

void TTestScene::draw()
{
    //gSPDisplayList(mDynList->pushDL(), rdpinit_spr_dl);

    //gSPDisplayList(mDynList->pushDL(), rdpinit_dl);
	//gSPDisplayList(mDynList->pushDL(), rspinit_dl);
    
    mPad->read();
    mCamera->render();

    gSPDisplayList(mDynList->pushDL(), world_World_mesh);

    for (int i = 0; i < 4; i++)
        mObjects[i]->draw();

    mBird->draw();

    /*

    
    */
}

void TTestScene::exit()
{
    // ...
}

TPlayer * TTestScene::getPlayer() { return mBird; }

// -------------------------------------------------------------------------- //