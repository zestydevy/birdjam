
#ifndef INCLUDE_SP_RANKA_H
#define INCLUDE_SP_RANKA_H

#include <PR/sp.h>

// -------------------------------------------------------------------------- //
// @result_birda

#define result_birdaTRUEIMAGEH	100
#define result_birdaTRUEIMAGEW	100
#define result_birdaIMAGEH	128
#define result_birdaIMAGEW	128
#define result_birdaBLOCKSIZEW	32
#define result_birdaBLOCKSIZEH	32
#define result_birdaSCALEX	1.0
#define result_birdaSCALEY	1.0
#define result_birdaMODE	SP_Z | SP_OVERLAP | SP_TRANSPARENT

extern Bitmap result_birda_bitmaps[];
extern Gfx result_birda_dl[];

#define NUM_result_birda_BMS  (sizeof(result_birda_bitmaps)/sizeof(Bitmap))

extern Sprite result_birda_sprite;

// -------------------------------------------------------------------------- //

#endif
