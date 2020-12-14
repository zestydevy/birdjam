#pragma once

#include <nusys.h>
#include <nualstl_n.h>

#include "array.hpp"

// -------------------------------------------------------------------------- //

enum ESfxType : musHandle
{
    SFX_BIRD_FLAP            = 0,
    SFX_BIRD_WALL_HIT        = 1,
    SFX_BORGAR               = 2,
    SFX_COUNTDOWN_GO         = 3,
    SFX_COUNTDOWN_NUMBER     = 4,
    SFX_CAW                  = 5,
    SFX_FREEDOM              = 6,
    BGM_FUNK_COMP_L          = 7,
    BGM_FUNK_COMP_R          = 8,
    SFX_GRAB                 = 9,
    SFX_MENU_BACK            = 10,
    SFX_MENU_PAGE            = 11,
    SFX_MENU_SELECT          = 12,
    BGM_N64_L                = 13,
    BGM_N64_R                = 14,
    SFX_POP                  = 15,
    SFX_REALEAGLE1           = 16,
    BGM_SONG_COMP_L          = 17,
    BGM_SONG_COMP_R          = 18,
    SFX_TIMEOUT              = 19,
    SFX_WOOSH                = 20,
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
    static void stopMusic();

    private:

    static u8 * sBankBuffer;
    static u8 * sMusicBuffer;
    static u8 * sSfxBuffer;

    static musHandle mBgmL;
    static musHandle mBgmR;
    
    static TArray<musHandle> sHandleList;

};

// -------------------------------------------------------------------------- //