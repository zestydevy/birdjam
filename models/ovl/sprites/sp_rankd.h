
#ifndef INCLUDE_SP_RANKA_H
#define INCLUDE_SP_RANKA_H

#include <PR/sp.h>

// -------------------------------------------------------------------------- //
// @result_birdd

#define result_birddTRUEIMAGEH	100
#define result_birddTRUEIMAGEW	100
#define result_birddIMAGEH	128
#define result_birddIMAGEW	128
#define result_birddBLOCKSIZEW	32
#define result_birddBLOCKSIZEH	32
#define result_birddSCALEX	1.0
#define result_birddSCALEY	1.0
#define result_birddMODE	SP_Z | SP_OVERLAP | SP_TRANSPARENT

extern Bitmap result_birdd_bitmaps[];
extern Gfx result_birdd_dl[];

#define NUM_result_birdd_BMS  (sizeof(result_birdd_bitmaps)/sizeof(Bitmap))

extern Sprite result_birdd_sprite;

// -------------------------------------------------------------------------- //

#endif
