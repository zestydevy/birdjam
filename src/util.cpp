#include <nusys.h>

#include "util.hpp"

// -------------------------------------------------------------------------- //

void TUtil::toMemory(void * dest, void * src, s32 size)
{
    // transfer size can't be an odd number
    if (size & 1) {
        ++size;
    }
    
    nuPiReadRom(reinterpret_cast<u32>(src), dest, size);

    // invalidate data cache
    osInvalDCache(dest, size);
}

// -------------------------------------------------------------------------- //