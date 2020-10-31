#pragma once

#include <ultra64.h>

#include "game.hpp"
#include "app.hpp"

// -------------------------------------------------------------------------- //

template<typename T>
    struct TVec2
    {
        T x;
        T y;
    };

    struct TColor
    {
        u8 r;
        u8 g;
        u8 b;
        u8 a;
    };

class TSprite
{
    public:
    
    inline TSprite(Sprite * sprite, s32 x, s32 y)
        : mSprite{sprite}
    {
      mPosition.x = x;
      mPosition.y = y;
    }
    ~TSprite() = default;

    // initializes S2DEX. call before utilizing sprites
    static inline void init()
    {
        auto dl = TGame::getInstance()->getDynDL();
        spInit(dl);
    }

    // call after sprites are finished rendering.
    // S2DEX's spFinish is broken so this is necessary
    static inline void finalize()
    {
        auto dl = TGame::getInstance()->getDynDL();
        auto gp = *dl;
        gSPDisplayList(gp++, rdpinit_dl);
	    gSPDisplayList(gp++, rspinit_dl);
        *dl = gp;
    }

    void render();

    TVec2<s32> mPosition{};
    TVec2<float> mScale{1.0f};
    TColor mColor{255};

    private:
    
    Sprite * mSprite{nullptr};

    u32 mAttributes{SP_TRANSPARENT};

};