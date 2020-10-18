/* ----------------------------------------------------
 ######  ### ######  ######           #    #    #     # 
 #     #  #  #     # #     #          #   # #   ##   ## 
 #     #  #  #     # #     #          #  #   #  # # # # 
 ######   #  ######  #     #          # #     # #  #  # 
 #     #  #  #   #   #     #    #     # ####### #     # 
 #     #  #  #    #  #     #    #     # #     # #     # 
 ######  ### #     # ######      #####  #     # #     # 
-----------------------------------------------------*/

#include <ultra64.h>

#include "letters.h"
extern "C" {
#include "mem.h"
}
#include "app.hpp"
#include "game.hpp"

u64	gBootStack[STACKSIZE/sizeof(u64)];

static OSThread	sIdleThread;
static u64 sIdleThreadStack[STACKSIZE/sizeof(u64)];

#define NUM_PI_MSGS     8
    
static OSMesg PiMessages[NUM_PI_MSGS];
static OSMesgQueue PiMessageQ;

int constexpr kHeapLocation = 0x80200000;
int constexpr kHeapSize     = 0x1FFFFF;

OSPiHandle * gHandler;

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

void idle(void * arg)
{
   // 1 MB heap
   MEMInit(reinterpret_cast<void *>(kHeapLocation), kHeapSize);
   
   CApp app = CApp();

   osCreateThread(&app.mMainThread, 3, bootApp, &app,
		   app.mMainThreadStack+STACKSIZE/sizeof(u64), 10);
   osStartThread(&app.mMainThread);

   osSetThreadPri( 0, 0 );
    
   for(;;);
}

void bootApp(void * arg)
{
    CApp * app = reinterpret_cast<CApp *>(arg);
    app->init(OS_VI_NTSC_LAN1, GPACK_RGBA5551(0, 0, 0, 1), true);
}

void * operator new(size_t count)
{
  return MEMAlloc(count);
}

void operator delete(void * block)
{
  MEMFree(block);
}

void * operator new[](size_t count)
{
  return MEMAlloc(count);
}

void operator delete[](void * block)
{
  MEMFree(block);
}