#include <ultra64.h>

#include "sprite.hpp"

// -------------------------------------------------------------------------- //

void TSprite::render()
{
    mSprite->rsp_dl_next = mSprite->rsp_dl;
    
    spMove(mSprite, mPosition.x, mPosition.y);
    spScale(mSprite, mScale.x, mScale.y);
    spColor(mSprite, mColor.r, mColor.g, mColor.b, mColor.a);
    spSetAttribute( mSprite, mAttributes);
    
    auto dl = TGame::getInstance()->getDynDL();
    auto gp = *dl;
    gSPDisplayList(gp++, spDraw(mSprite));
    *dl = gp;
}