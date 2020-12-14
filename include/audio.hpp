#pragma once

#include <nusys.h>
#include <nualstl_n.h>

#include "array.hpp"

// -------------------------------------------------------------------------- //

enum ESfxType : musHandle
{
    BGM_N64_L                = 0,
    BGM_N64_R                = 1,
    SFX_CAW                  = 2,
    SFX_BIRD_FLAP            = 3,
    SFX_BIRD_WALL_HIT        = 4,
    SFX_BORGAR               = 5,
    SFX_FREEDOM              = 6,
    BGM_FUNK_COMP_L          = 7,
    BGM_FUNK_COMP_R          = 8,
    SFX_GRAB                 = 9,
    SFX_MENU_BACK            = 10,
    SFX_MENU_PAGE            = 11,
    SFX_MENU_SELECT          = 12,
    BGM_SONG_COMP_L          = 13,
    BGM_SONG_COMP_R          = 14,
};

enum EBgm : musHandle
{
    BGM_TEST = 0,
    BGM_FUNK = BGM_FUNK_COMP_L,
    BGM_FLY = BGM_SONG_COMP_L,
};

class TAudio
{
    public:
    
    static void init();
    static void playSound(ESfxType const sound);
    static void playMusic(EBgm const music);
    static void stopMusic(EBgm const music);

    private:

    static u8 * sBankBuffer;
    static u8 * sMusicBuffer;
    static u8 * sSfxBuffer;

    static musHandle mBgmL;
    static musHandle mBgmR;
    
    static TArray<musHandle> sHandleList;

};

// -------------------------------------------------------------------------- //