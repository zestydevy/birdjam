#pragma once

#include <nusys.h>

float constexpr kFrameRate = 60.0f;
float constexpr kInterval = 1.0f / kFrameRate;

class TUtil
{
    public:

    static void toMemory(void * dest, void * src, s32 size);
};