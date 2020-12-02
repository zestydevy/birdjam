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

#include <nusys.h>

#include "app.hpp"
#include "collider.hpp"
#include "heap.hpp"
#include "modelkeeper.hpp"

// -------------------------------------------------------------------------- //

extern "C" {

void mainproc(void)
{
  bootApp();
}

}

// -------------------------------------------------------------------------- //

void bootApp()
{
  THeap::init();

  CApp app = CApp();

  // 0.5 MB heap
  auto gameHeap = TBlockHeap(
  reinterpret_cast<void *>(kHeapLocation), kHeapSize);

  // set game heap as current heap
  THeap::setCurrentHeap(&gameHeap);

  app.init();
  app.run();

  while (1) {}
}

// -------------------------------------------------------------------------- //