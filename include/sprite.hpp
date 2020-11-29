#pragma once

#include <nusys.h>

#include "dynlist.hpp"
#include "math.hpp"
#include "app.hpp"

// -------------------------------------------------------------------------- //

struct TColor
{
    u8 r;
    u8 g;
    u8 b;
    u8 a;
};

extern Gfx rspinit_dl[];
extern Gfx rdpinit_dl[];
extern Gfx rdpinit_spr_dl[];

class TSprite
{
    public:
    
    inline TSprite(Sprite * sprite, s32 x, s32 y)
        : mSprite{sprite}
    {
      mPosition.x() = x;
      mPosition.y() = y;
    }
    ~TSprite() = default;

    // initializes S2DEX. call before utilizing sprites
    static inline void init(TDynList2 * list)
    {
        sDynList = list;
        auto dl = sDynList->getDL();
        spInit(&dl);
    }

    // call after sprites are finished rendering.
    static inline void finalize()
    {
        auto dl = sDynList->getDL();
        gSPDisplayList(dl, rdpinit_dl);
	    gSPDisplayList(dl, rspinit_dl);
    }

    void render();

    TVec2<s32> mPosition{};
    TVec2<float> mScale{};
    TColor mColor{255};
    u32 mAttributes{SP_FASTCOPY};

    private:
    
    Sprite * mSprite{nullptr};
    static TDynList2 * sDynList;

};
