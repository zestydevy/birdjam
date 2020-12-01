#pragma once

#include <nusys.h>

#include "math.hpp"
#include "dynlist.hpp"

#include "../models/static/cube/model_cube.h"
#include "../scene/object_info.h"

// -------------------------------------------------------------------------- //

enum EObjType : s16
{
    NONE = 0,
    DEBUG_CUBE,
    BALLOON,
    LUNCHTABLE,
    CHAIR,
    BASKET,
    BEER,
    NOODLE,
    MELON,
    APPLE,
    BALLOON_DEFLATED,
    BEEHIVE,
    BILLS,
    CARD,
    FLOWER,
    NECKLACE,
    RING,
    SOCCER,
    STICK,
    TABLE,
    CAT,
    CHICKEN,
    CRITIC,
    LOGO,
    STORE_E,
    STORE_B,
    STEPPINGSTONE,
    FENCE,
    TRUNK,
    LEAVES,
    BRANCH,
    ROOTS,
    INVALID
};

// -------------------------------------------------------------------------- //

class TObject
{
    public:

    TObject(TDynList2 * list)
        : mDynList{list} {}
    virtual ~TObject() = default;

    void setPosition(TVec3<f32> const & pos);
    void setRotation(TVec3<f32> const & rot);
    void setScale(TVec3<f32> const & scale);
    inline void setMesh(Gfx * mesh) {mMesh = mesh;}

    TVec3<f32> const & getPosition() {return mPosition;}
    TVec3<s16> const & getRotation() {return mRotation;}
    TVec3<f32> const & getScale() {return mScale;}

    virtual void updateMtx();

    virtual void init();
    virtual void update();
    virtual void draw();

    static Gfx * getMeshGfx(EObjType type);
    static const TObjectData & getNestObjectInfo(EObjType type);

    protected:

    TVec3<f32> mPosition{};
    TVec3<s16> mRotation{};
    TVec3<f32> mScale{};
    
    TMtx44 mPosMtx{};
    TMtx44 mRotMtx{};
    TMtx44 mScaleMtx{};

    Mtx mFPosMtx{};
    Mtx mFRotMtx{};
    Mtx mFScaleMtx{};
    
    u32 mTag{0};
    Gfx * mMesh{nullptr};
    TDynList2 * mDynList{nullptr};
};

// -------------------------------------------------------------------------- //