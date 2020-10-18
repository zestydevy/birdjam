#pragma once
#include <ultra64.h>

#include "game.hpp"

size_t constexpr kStackSize = 0x4000;
size_t constexpr kMaxPiMsg = 8;
extern u16 cfb_16_a[];
extern u16 cfb_16_b[];
extern u16 zbuffer[];

void idle(void * arg);
void bootApp(void * arg);

class CApp
{
    public:
    CApp();
    ~CApp();
    void init(u32 mode, u32 color, bool useFifo);
    void setup();

    OSThread mMainThread{};
    u64 mMainThreadStack[kStackSize/sizeof(u64)];
    OSMesg mPiMessages[kMaxPiMsg];
    OSMesg mDmaMessageBuffer{};
    OSMesgQueue mPiMessageQ{};
    OSMesgQueue	mDmaMessageQ{};
    TGame * mGame{nullptr};
    void * mFrameBuffers[2];
};