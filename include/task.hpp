#pragma once

#include <ultra64.h>
#include "letters.h"
#include "game.hpp"

// -------------------------------------------------------------------------- //

enum ETaskCode : u32
{
    INVALID,
    F3DEX2,
    L3DEX2,
    S2DEX2,
};

// -------------------------------------------------------------------------- //

class TTask
{
    public:

    static void build(ETaskCode const & uCode, OSTask * task, bool fifo)
    {
        auto dynDl = TGame::getInstance()->getDynDL();
        auto dynList = TGame::getInstance()->getDynList();

        task->t.ucode_boot = (u64 *) rspbootTextStart;
	    task->t.ucode_boot_size = ((int)rspbootTextEnd - 
			(int)rspbootTextStart);
        
        switch(uCode)
        {
            case F3DEX2:
                
                if (fifo) {
                    // RSP FIFO -> RDP
                    task->t.ucode = (u64 *) gspF3DEX2_fifoTextStart;
		            task->t.ucode_data = (u64 *) gspF3DEX2_fifoDataStart; 
                } else {
                    // RSP XBUS -> RDP
                    task->t.ucode = (u64 *) gspF3DEX2_xbusTextStart;
		            task->t.ucode_data = (u64 *) gspF3DEX2_xbusDataStart; 
                }
                break;

            case L3DEX2:
                // not implemented, line 3D poopy
                break;
            case S2DEX2:
                // not implemented
                break;
        }
        
        task->t.data_ptr = (u64 *) dynList->mDl;
	    task->t.data_size = ((int)(*dynDl - dynList->mDl) *
			       sizeof (Gfx));

        osWritebackDCacheAll();
        
        osSpTaskStart(task);
    }
};

// -------------------------------------------------------------------------- //