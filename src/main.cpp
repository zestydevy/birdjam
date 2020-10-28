/* ----------------------------------------------------
 ######  ### ######  ######           #    #    #     # 
 #     #  #  #     # #     #          #   # #   ##   ## 
 #     #  #  #     # #     #          #  #   #  # # # # 
 ######   #  ######  #     #          # #     # #  #  # 
 #     #  #  #   #   #     #    #     # ####### #     # 
 #     #  #  #    #  #     #    #     # #     # #     # 
 ######  ### #     # ######      #####  #     # #     # 
-----------------------------------------------------*/

// -------------------------------------------------------------------------- //

#include <ultra64.h>

#include "letters.h"
#include "app.hpp"
#include "game.hpp"

// -------------------------------------------------------------------------- //

u64	gBootStack[STACKSIZE/sizeof(u64)];

static OSThread	sIdleThread;
static u64 sIdleThreadStack[STACKSIZE/sizeof(u64)];
    
static OSMesg PiMessages[kMaxPiMsg];
static OSMesgQueue PiMessageQ;

OSPiHandle * gHandler;

// -------------------------------------------------------------------------- //

extern "C" {

int boot(void)
{
    osInitialize();

    gHandler = osCartRomInit();

    osCreateThread(&sIdleThread, 1, idle, (void *)0,
		   sIdleThreadStack+STACKSIZE/sizeof(u64), 10);
    osStartThread(&sIdleThread);

    /* never reached */
    return 0;
}
}

// -------------------------------------------------------------------------- //

void idle(void * arg)
{  
  CApp app = CApp();

  osCreateThread(&app.mMainThread, 3, bootApp, &app,
    app.mMainThreadStack+STACKSIZE/sizeof(u64), 10);
  osStartThread(&app.mMainThread);

  osSetThreadPri( 0, 0 );
    
  for(;;);
}

// -------------------------------------------------------------------------- //

void bootApp(void * arg)
{
  CApp * app = reinterpret_cast<CApp *>(arg);

  // 1 MB heap
  auto gameHeap = TBlockHeap(
     reinterpret_cast<void *>(kHeapLocation), kHeapSize);

  // set game heap as current heap
  THeap::setCurrentHeap(&gameHeap);
    
  app->init(
    OS_VI_NTSC_LAN1, 
    GPACK_RGBA5551(0, 0, 0, 1), 
    OS_VI_DITHER_FILTER_ON, 
    true);

  app->setupStaticSegment(
    _codeSegmentEnd, 
    reinterpret_cast<u32>(_staticSegmentRomStart));
    
  app->run();
}

// -------------------------------------------------------------------------- //