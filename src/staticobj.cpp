#include <nusys.h>

#include "staticobj.hpp"
#include "math.hpp"

#include "../models/objects/balloon/model_balloon.h"
#include "../models/objects/lunchtable/model_lunchtable.h"
#include "../models/objects/chair/model_chair.h"
#include "../models/objects/basket/model_basket.h"
#include "../models/objects/beer/model_beer.h"
#include "../models/objects/noodle/model_noodle.h"
#include "../models/objects/melon/model_melon.h"
#include "../models/objects/apple/model_apple.h"
#include "../models/objects/balloon_deflated/model_balloondeflated.h"
#include "../models/objects/beehive/model_beehive.h"
#include "../models/objects/bills/model_bills.h"
#include "../models/objects/card/model_card.h"
#include "../models/objects/flower/model_flower.h"
#include "../models/objects/necklace/model_necklace.h"
#include "../models/objects/ring/model_ring.h"
#include "../models/objects/soccer/model_soccer.h"
#include "../models/objects/stick/model_stick.h"
#include "../models/objects/table/model_table.h"
#include "../models/cat/model_cat.h"
#include "../models/chicken/model_chicken.h"
#include "../models/critic/model_critic.h"
#include "../models/objects/n64/model_n64.h"
#include "../models/objects/store_b/model_storeb.h"
#include "../models/objects/store_e/model_storee.h"
#include "../models/objects/steppingstone/model_steppingstone.h"
#include "../models/objects/fence/model_fence.h"
#include "../models/objects/trunk/model_trunk.h"
#include "../models/objects/leaves/model_leaves.h"
#include "../models/objects/branch/model_branch.h"
#include "../models/objects/roots/model_roots.h"


// -------------------------------------------------------------------------- //

static Gfx * gObjMeshList[] =
{
    nullptr,
    cube_Cube_mesh,
    balloon_Balloon_mesh,
    lunchtable_Table_mesh,
    chair_Chair_mesh,
    basket_Basket_mesh,
    beer_Beer_mesh,
    noodle_Noodle_mesh,
    melon_Melon_mesh,
    apple_Apple_mesh,
    balloon_deflated_Balloon_Deflated_mesh,
    beehive_Beehive_mesh,
    bills_Bills_mesh,
    card_Cube_mesh,
    flower_Head_mesh,
    necklace_Necklace_mesh,
    ring_Ring_mesh,
    zedball_Zedball_mesh,
    stick_Stick1_mesh,
    table_Table_mesh,
    cat_Cat_mesh,
    chicken_Chicken_mesh,
    critic_Critic_mesh,
    n64_N_mesh,
    store_e_E_mesh,
    store_b_B_mesh,
    steppingstone_SteppingStone_mesh,
    fence_Fence_mesh,
    trunk_Trunk_mesh,
    leaves_Leaves_mesh,
    branch_Branch_mesh,
    roots_Roots_mesh,
    nullptr
};

// -------------------------------------------------------------------------- //

void TObject::setPosition(TVec3<f32> const & pos)
{
    mPosition = pos;
    updateMtx();
}

void TObject::setRotation(TVec3<f32> const & rot)
{
    mRotation.set(rot.x(), rot.y(), rot.z());
    updateMtx();
}

void TObject::setScale(TVec3<f32> const & scale)
{
    mScale = scale;
    updateMtx();
}

void TObject::init()
{
    updateMtx();
}

void TObject::updateMtx()
{
    TMtx44 temp1, temp2, temp3;
    
    mPosMtx.translate(mPosition);
    temp1.rotateAxisX(mRotation.x());
    temp2.rotateAxisY(mRotation.y());
    temp3.rotateAxisZ(mRotation.z());
    TMtx44::concat(temp2, temp1, mRotMtx);
    TMtx44::concat(mRotMtx, temp3, mRotMtx);
    mScaleMtx.scale(mScale);

    TMtx44::floatToFixed(mPosMtx, mFPosMtx);
    TMtx44::floatToFixed(mRotMtx, mFRotMtx);
    TMtx44::floatToFixed(mScaleMtx, mFScaleMtx);
}

void TObject::update() {}

void TObject::draw()
{
    gSPMatrix(mDynList->pushDL(), OS_K0_TO_PHYSICAL(&mFPosMtx),
	      G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_PUSH);
    gSPMatrix(mDynList->pushDL(), OS_K0_TO_PHYSICAL(&mFRotMtx),
	      G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);
    gSPMatrix(mDynList->pushDL(), OS_K0_TO_PHYSICAL(&mFScaleMtx),
	      G_MTX_MODELVIEW|G_MTX_MUL|G_MTX_NOPUSH);
        
    if (mMesh != nullptr) {
        gSPDisplayList(mDynList->pushDL(), mMesh);
    }

    gSPPopMatrix(mDynList->pushDL(), G_MTX_MODELVIEW);
}

// -------------------------------------------------------------------------- //

Gfx * TObject::getMeshGfx(
    EObjType const type
) {
    if (type >= EObjType::INVALID) {
        return nullptr;
    }

    return gObjMeshList[(u32)type];
}

// -------------------------------------------------------------------------- //