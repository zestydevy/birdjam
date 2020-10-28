#pragma once
#include <ultra64.h>

#include "game.hpp"
#include "heap.hpp"

// -------------------------------------------------------------------------- //

size_t constexpr kStackSize = 0x2000;
size_t constexpr kMaxPiMsg = 8;
size_t constexpr kHeapLocation = 0x80200000;
size_t constexpr kHeapSize     = 0x1FFFFF;

extern u16 cfb_16_a[];
extern u16 cfb_16_b[];
extern u16 zbuffer[];
extern Gfx 	rspinit_dl[];
extern Gfx 	rdpinit_dl[];

extern char _codeSegmentEnd[];
extern char _staticSegmentRomStart[], _staticSegmentRomEnd[];

extern OSPiHandle * gHandler;

void idle(void * arg);
void bootApp(void * arg);

// -------------------------------------------------------------------------- //

class CApp
{
    public:
    
    CApp();
    ~CApp();
    void init(u32 mode, u32 color, u32 feature, bool useFifo);
    void setupStaticSegment(void * dest, u32 const & src);
    void run();

    OSThread mMainThread{};
    u64 mMainThreadStack[kStackSize/sizeof(u64)];

    private:

    u32 mClearColor{0};
    bool mFifo{false}; 
    
    OSMesg mPiMessages[kMaxPiMsg];
    OSMesg mDmaMessageBuffer{};
    OSMesg mRdpMessageBuffer{};
    OSMesg mDummyMessage{};
    OSMesg mVblankMessageBuffer{};

    OSMesgQueue mPiMessageQ{};
    OSMesgQueue	mDmaMessageQ{};
    OSMesgQueue mRdpMessageQ{};
    OSMesgQueue mVblankMessageQ{};

    static TBlockHeap * sCurrentHeap;
    TGame * mGame{nullptr};
    void * mFrameBuffers[2];
};

// -------------------------------------------------------------------------- //