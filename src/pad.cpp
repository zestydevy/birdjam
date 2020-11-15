#include <nusys.h>

#include "pad.hpp"

// -------------------------------------------------------------------------- //

NUContData TPad::sConts[kMaxControllers];

// -------------------------------------------------------------------------- //

TPad::TPad(s32 contNum)
{
    mPadNum = contNum;
}

// -------------------------------------------------------------------------- //

void TPad::init()
{
    auto pattern = nuContInit();
}

// -------------------------------------------------------------------------- //

void TPad::read()
{
    mPrevButton = sConts[mPadNum].button;
    nuContDataGetEx(sConts, mPadNum);
    mAnalogX = sConts[mPadNum].stick_x;
    mAnalogY = sConts[mPadNum].stick_y;
}

// -------------------------------------------------------------------------- //

bool TPad::isPressed(EButton const button)
{
    return (sConts[mPadNum].trigger & (static_cast<u16>(button)));
}

// -------------------------------------------------------------------------- //

bool TPad::isHeld(EButton const button)
{
    return (sConts[mPadNum].button & static_cast<u16>(button));
}

// -------------------------------------------------------------------------- //

bool TPad::isReleased(EButton const button)
{
    return (!(sConts[mPadNum].button & static_cast<u16>(button)) && 
        (mPrevButton & static_cast<u16>(button)));
}

// -------------------------------------------------------------------------- //

s8 TPad::getAnalogX()
{
    return mAnalogX;
}

// -------------------------------------------------------------------------- //

s8 TPad::getAnalogY()
{
    return mAnalogY;
}

// -------------------------------------------------------------------------- //