#pragma once

#include <nusys.h>

#include "math.hpp"
#include "dynlist.hpp"

#include "../models/cube/model_cube.h"

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

    virtual void init();
    virtual void update();
    virtual void draw();

    static Gfx * getMeshGfx(EObjType type);

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