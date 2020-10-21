#pragma once

#include <ultra64.h>
#include "letters.h"

// ========================================================================== //

enum ETaskCode : u32
{
    INVALID,
    F3DEX2,
    L3DEX2,
    S2DEX2,
};

class TTask
{
    public:

    static inline void build(ETaskCode const & uCode, bool fifo)
    {
        switch(uCode)
        {
            case F3DEX2:
                break;
            case L3DEX2:
                break;
            case S2DEX2:
                break;
        }
    }

    private:

    OSTask * mTask{nullptr};
};