#include <nusys.h>

#include "staticobj.hpp"
#include "camera.hpp"
#include "math.hpp"


#include "../models/static/cube/model_cube.h"
#include "../models/static/objects/balloon/model_balloon.h"
#include "../models/static/objects/lunchtable/model_lunchtable.h"
#include "../models/static/objects/chair/model_chair.h"
#include "../models/static/objects/basket/model_basket.h"
#include "../models/static/objects/beer/model_beer.h"
#include "../models/static/objects/noodle/model_noodle.h"
#include "../models/static/objects/melon/model_melon.h"
#include "../models/static/objects/apple/model_apple.h"
#include "../models/static/objects/balloon_deflated/model_balloondeflated.h"
#include "../models/static/objects/beehive/model_beehive.h"
#include "../models/static/objects/bills/model_bills.h"
#include "../models/static/objects/card/model_card.h"
#include "../models/static/objects/flower/model_flower.h"
#include "../models/static/objects/necklace/model_necklace.h"
#include "../models/static/objects/ring/model_ring.h"
#include "../models/static/objects/soccer/model_soccer.h"
#include "../models/static/objects/stick/model_stick.h"
#include "../models/static/objects/table/model_table.h"
#include "../models/static/cat/model_cat.h"
#include "../models/static/chicken/model_chicken.h"
#include "../models/static/critic/model_critic.h"
#include "../models/static/objects/n64/model_n64.h"
#include "../models/static/objects/store_b/model_storeb.h"
#include "../models/static/objects/store_e/model_storee.h"
#include "../models/static/objects/steppingstone/model_steppingstone.h"
#include "../models/static/objects/fence/model_fence.h"
#include "../models/static/objects/trunk/model_trunk.h"
#include "../models/static/objects/leaves/model_leaves.h"
#include "../models/static/objects/branch/model_branch.h"
#include "../models/static/objects/roots/model_roots.h"
#include "../models/static/objects/mailbox/model_mailbox.h"
#include "../models/static/nest/model_nest.h"
#include "../models/static/objects/baldtree/model_baldtree.h"
#include "../models/static/objects/baldhooktree/model_baldhooktree.h"
#include "../models/static/objects/deadtree/model_deadtree.h"
#include "../models/static/objects/tire/model_tire.h"
#include "../models/static/objects/toaster/model_toaster.h"
#include "../models/static/objects/plank/model_plank.h"
#include "../models/static/objects/trashcan/model_trashcan.h"
#include "../models/static/objects/pot/model_pot.h"
#include "../models/static/objects/bush/model_bush.h"
#include "../models/static/objects/lamp/model_lamp.h"

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
    mailbox_Mailbox_mesh,
    nest_Nest_mesh,
    treedead_Tree_Dead_mesh,
    tree2_bald_Tree_Bald_mesh,
    tree1_bald_TreeBald_mesh,
    tire_Tire_mesh,
    toaster_Toaster_mesh,
    plank_Plank_mesh,
    trashcan_TrashCan_mesh,
    pot_Pot_mesh,
    bush_Bush_mesh,
    lamp_Lamp_mesh,
    nullptr
};

// -------------------------------------------------------------------------- //

void TObject::setPosition(TVec3<f32> const & pos)
{
    mPosition = pos;
    mMtxNeedsUpdate = true;
}

void TObject::setRotation(TVec3<f32> const & rot)
{
    mRotation.set(rot.x(), rot.y(), rot.z());
    mMtxNeedsUpdate = true;
}

void TObject::setScale(TVec3<f32> const & scale)
{
    mScale = scale;
    mMtxNeedsUpdate = true;
}

void TObject::init()
{
    mInCamera = true;
    updateMtx();
}

void TObject::updateMtx()
{
    if (!mInCamera)
        return;

    TMtx44 temp1, temp2, temp3, mPosMtx, mScaleMtx;
    
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

    mMtxNeedsUpdate = false;
}

void TObject::update() {
    mInCamera = mAlwaysDraw || TCamera::checkVisible(mPosition);
    //mInCamera = true;
}

void TObject::draw()
{
    if (!mInCamera)
        return;

    if (mMtxNeedsUpdate)
        updateMtx();

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

const TObjectData & TObject::getNestObjectInfo(
    EObjType const type
) {
    if (type >= EObjType::INVALID) {
        return gObjectDataList[0];
    }

    return gObjectDataList[(u32)type];
}

// -------------------------------------------------------------------------- //