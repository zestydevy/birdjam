#ifdef _cplusplus
extern "C"{
#endif

#ifndef INCLUDE_SCENEDATA_H
#define INCLUDE_SCENEDATA_H

#include <ultra64.h>

typedef struct TSceneEntry
{
    s32 id;

    float positionX;
    float positionY;
    float positionZ;

    float rotationX;
    float rotationY;
    float rotationZ;

    float scaleX;
    float scaleY;
    float scaleZ;
};

enum EObject
{
    OBJECT_NULL = 0,
    OBJECT_CUBE,
    OBJECT_BALLOON,
    OBJECT_LUNCHTABLE,
};

#endif

#ifdef _cplusplus
}
#endif