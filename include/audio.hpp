#pragma once

#include <nusys.h>
#include <nualstl_n.h>

#include "array.hpp"

// -------------------------------------------------------------------------- //

enum ESfxType : musHandle
{
    BGM_MAIN_L = 0,
    BGM_MAIN_R,
    SFX_CAW,
};

class TAudio
{
    public:
    
    static void init();
    static void playSound(ESfxType const sound);

    private:

    static u8 * sBankBuffer;
    static u8 * sMusicBuffer;
    static u8 * sSfxBuffer;
    
    static TArray<musHandle> sHandleList;

};

// -------------------------------------------------------------------------- //