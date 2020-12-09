
#ifndef INCLUDE_SP_RANKA_H
#define INCLUDE_SP_RANKA_H

#include <PR/sp.h>

// -------------------------------------------------------------------------- //
// @result_birdc

#define result_birdcTRUEIMAGEH	100
#define result_birdcTRUEIMAGEW	100
#define result_birdcIMAGEH	128
#define result_birdcIMAGEW	128
#define result_birdcBLOCKSIZEW	32
#define result_birdcBLOCKSIZEH	32
#define result_birdcSCALEX	1.0
#define result_birdcSCALEY	1.0
#define result_birdcMODE	SP_Z | SP_OVERLAP | SP_TRANSPARENT

extern Bitmap result_birdc_bitmaps[];
extern Gfx result_birdc_dl[];

#define NUM_result_birdc_BMS  (sizeof(result_birdc_bitmaps)/sizeof(Bitmap))

extern Sprite result_birdc_sprite;

// -------------------------------------------------------------------------- //

#endif
