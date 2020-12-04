#include <nusys.h>

#include "sprite.hpp"

// -------------------------------------------------------------------------- //

TDynList2 * TSprite::sDynList{nullptr};

// -------------------------------------------------------------------------- //

void TSprite::setPosition(TVec3S const & pos)
{
    mPosition.x() = pos.x(); 
    mPosition.y() = pos.y();
}

void TSprite::setScale(TVec3F const & scale)
{
    mScale.x() = scale.x();
    mScale.y() = scale.y(); 
}

void TSprite::setColor(TColor const & color)
{
    mColor = color;
}

void TSprite::setAttribute(u32 const attrib)
{
    mAttributes = attrib;
}

void TSprite::setTexture(void * buffer)
{
    mSprite->bitmap->buf = buffer;
}

void TSprite::render()
{
    mSprite->rsp_dl_next = mSprite->rsp_dl;
    
    spMove(mSprite, mPosition.x(), mPosition.y());
    spScale(mSprite, mScale.x(), mScale.y());
    spColor(mSprite, mColor.r, mColor.g, mColor.b, mColor.a);
    spSetAttribute( mSprite, mAttributes);
    
    gSPDisplayList(sDynList->pushDL(), spDraw(mSprite));
}

// -------------------------------------------------------------------------- //