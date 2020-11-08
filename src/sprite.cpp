#include <nusys.h>

#include "sprite.hpp"

// -------------------------------------------------------------------------- //

TDynList2 * TSprite::sDynList{nullptr};

// -------------------------------------------------------------------------- //

void TSprite::render()
{
    mSprite->rsp_dl_next = mSprite->rsp_dl;
    
    spMove(mSprite, mPosition.x, mPosition.y);
    spScale(mSprite, mScale.x, mScale.y);
    spColor(mSprite, mColor.r, mColor.g, mColor.b, mColor.a);
    spSetAttribute( mSprite, mAttributes);
    
    gSPDisplayList(sDynList->pushDL(), spDraw(mSprite));
}