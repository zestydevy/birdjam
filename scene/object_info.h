
#pragma once

#ifdef _cplusplus
extern "C"{
#endif

#include <nusys.h>
#include "math.h"
#include <stdbool.h> 

#define SIZE_LAYER1 5.0f
#define SIZE_LAYER2 20.0f
#define SIZE_LAYER3 40.0f

struct TObjectData{
    Gfx * mesh;
    char name[16];
    s16 colType;
    bool hasMeshCol;
    
    float sizex;
    float sizey;
    float sizez;

    float mass;
    s16 value;
};

extern const struct TObjectData gObjectDataList[];

#ifdef _cplusplus
}
#endif