
#pragma once

#ifdef _cplusplus
extern "C"{
#endif

#include <nusys.h>
#include "math.h"
#include <stdbool.h> 

#define SIZE_TINY 0.1f
#define SIZE_JEWELRY 0.25f
#define SIZE_SMALL 0.5f
#define SIZE_MED 1.25f
#define SIZE_ANIMAL 3.5f
#define SIZE_LARGE 5.0f
#define SIZE_MAN 10.0f
#define SIZE_LAYER1 15.0f
#define SIZE_MASSIVE 25.0f
#define SIZE_GIANT 40.0f
#define SIZE_LAYER2 60.0f
#define SIZE_LAYER3 150.0f
#define SIZE_IMPOSSIBLE 10000.0f

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