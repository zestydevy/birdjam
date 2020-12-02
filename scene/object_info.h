
#ifdef _cplusplus
extern "C"{
#endif

#include <nusys.h>
#include "math.h"
#include <stdbool.h> 

struct TObjectData{
    Gfx * mesh;
    char name[16];
    s16 colType;
    bool hasMeshCol;
    
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