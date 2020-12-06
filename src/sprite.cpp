
#include <nusys.h>

#include "array.hpp"
#include "dynlist.hpp"
#include "sprite.hpp"

// -------------------------------------------------------------------------- //

TDynList2 * TSprite::sDynList { nullptr };

// -------------------------------------------------------------------------- //

void TSprite::load(
    Sprite const & sprite
) {
    mSpriteData = sprite;
    mSpriteGfx.resize((u32)sprite.ndisplist);
    mSpriteData.rsp_dl = mSpriteGfx.data();
}

// -------------------------------------------------------------------------- //

void TSprite::preload(
    Sprite const & sprite
) {
    auto size = (u32)sprite.ndisplist;

    if (size > mSpriteGfx.size()) {
        mSpriteGfx.resize(size);
        mSpriteData.rsp_dl = mSpriteGfx.data();
    }
}

// -------------------------------------------------------------------------- //

TVec2S const &
TSprite::getPosition() const {
    return mPosition;
}

// -------------------------------------------------------------------------- //

void TSprite::setPosition(
    TVec2S const & pos
) {
    mPosition = pos;
}

// -------------------------------------------------------------------------- //

TVec2F const &
TSprite::getScale() const {
    return mScale;
}

// -------------------------------------------------------------------------- //

void TSprite::setScale(
    TVec2F const & scale
) {
    mScale = scale;
}

// -------------------------------------------------------------------------- //

TColor const &
TSprite::getColor() const {
    return mColor;
}

// -------------------------------------------------------------------------- //

void TSprite::setColor(
    TColor const & color
) {
    mColor = color;
}

// -------------------------------------------------------------------------- //

u32 TSprite::getAttributes() const {
    return mAttributes;
}

// -------------------------------------------------------------------------- //

void TSprite::setAttributes(
    u32 const attrib
) {
    mAttributes = attrib;
}

// -------------------------------------------------------------------------- //

void TSprite::setOnAttributes(
    u32 const mask
) {
    mAttributes |= mask;
}

// -------------------------------------------------------------------------- //

void TSprite::setOffAttributes(
    u32 const mask
) {
    mAttributes &= ~mask;
}

// -------------------------------------------------------------------------- //

void TSprite::draw() {
    mSpriteData.rsp_dl_next = mSpriteData.rsp_dl;
    spMove(&mSpriteData, mPosition.x(), mPosition.y());
    spScale(&mSpriteData, mScale.x(), mScale.y());
    spColor(&mSpriteData, mColor.r, mColor.g, mColor.b, mColor.a);
    spSetAttribute(&mSpriteData, mAttributes);
    gSPDisplayList(sDynList->pushDL(), spDraw(&mSpriteData));
}

// -------------------------------------------------------------------------- //

void TSprite::init(TDynList2 * dl) {
    sDynList = dl;
    auto gfx = sDynList->getDL();
    spInit(&gfx);
}

// -------------------------------------------------------------------------- //

void TSprite::finalize() {
    auto dl = sDynList->getDL();
    gSPDisplayList(dl, rdpinit_dl);
    gSPDisplayList(dl, rspinit_dl);
}

// -------------------------------------------------------------------------- //