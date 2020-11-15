#include <nusys.h>

#include "scene.hpp"
#include "heap.hpp"
#include "player.hpp"
#include "sprite.hpp"

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

    mBird->init();
    mBird->setPad(mPad);
    mCamera->setPad(mPad);

    mBird->setCamera(mCamera);

    mBird->setPosition({0.0f,2500.0f,0.0f});
    mBird->setRotation({0,0,0});
    mBird->setScale({0.3f,0.3f,0.3f});
}

void TTestScene::update()
{
    // ...
    mPad->read();
    mBird->update();
}

void TTestScene::draw()
{
    //gSPDisplayList(mDynList->pushDL(), rdpinit_spr_dl);

    //gSPDisplayList(mDynList->pushDL(), rdpinit_dl);
	//gSPDisplayList(mDynList->pushDL(), rspinit_dl);
    
    mPad->read();
    mCamera->render();

    gSPDisplayList(mDynList->pushDL(), world_World_mesh);

    mBird->draw();

    /*

    
    */
}

void TTestScene::exit()
{
    // ...
}

// -------------------------------------------------------------------------- //