
#ifdef _cplusplus
extern "C"{
#endif

#include <nusys.h>
#include "math.h"

struct TObjectData{
    Gfx * mesh;
    char name[16];
    s16 colType;
    
    float sizex;
    float sizey;
    float sizez;

    float offsetx;
    float offsety;
    float offsetz;

    float mass;
    s16 value;
};

extern const struct TObjectData gObjectDataList[];

#ifdef _cplusplus
}
#endif