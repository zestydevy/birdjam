
#ifndef INCLUDE_SP_RANKA_H
#define INCLUDE_SP_RANKA_H

#include <PR/sp.h>

// -------------------------------------------------------------------------- //
// @result_stara

#define result_staraTRUEIMAGEH	100
#define result_staraTRUEIMAGEW	84
#define result_staraIMAGEH	128
#define result_staraIMAGEW	96
#define result_staraBLOCKSIZEW	32
#define result_staraBLOCKSIZEH	32
#define result_staraSCALEX	1.0
#define result_staraSCALEY	1.0
#define result_staraMODE	SP_Z | SP_OVERLAP | SP_TRANSPARENT

extern Bitmap result_stara_bitmaps[];
extern Gfx result_stara_dl[];

#define NUM_result_stara_BMS  (sizeof(result_stara_bitmaps)/sizeof(Bitmap))

extern Sprite result_stara_sprite;

// -------------------------------------------------------------------------- //
// @result_ranka

#define result_rankaTRUEIMAGEH	49
#define result_rankaTRUEIMAGEW	44
#define result_rankaIMAGEH	64
#define result_rankaIMAGEW	64
#define result_rankaBLOCKSIZEW	32
#define result_rankaBLOCKSIZEH	32
#define result_rankaSCALEX	1.0
#define result_rankaSCALEY	1.0
#define result_rankaMODE	SP_Z | SP_OVERLAP | SP_TRANSPARENT

extern Bitmap result_ranka_bitmaps[];
extern Gfx result_ranka_dl[];

#define NUM_result_ranka_BMS  (sizeof(result_ranka_bitmaps)/sizeof(Bitmap))

extern Sprite result_ranka_sprite;

// -------------------------------------------------------------------------- //
// @result_birda

#define result_birdaTRUEIMAGEH	83
#define result_birdaTRUEIMAGEW	81
#define result_birdaIMAGEH	96
#define result_birdaIMAGEW	96
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
