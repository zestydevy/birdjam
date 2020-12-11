
#ifndef INCLUDE_SP_RANKC_H
#define INCLUDE_SP_RANKC_H

#include <PR/sp.h>

// -------------------------------------------------------------------------- //
// @result_rankc

#define result_rankcTRUEIMAGEH	49
#define result_rankcTRUEIMAGEW	38
#define result_rankcIMAGEH	64
#define result_rankcIMAGEW	64
#define result_rankcBLOCKSIZEW	32
#define result_rankcBLOCKSIZEH	32
#define result_rankcSCALEX	1.0
#define result_rankcSCALEY	1.0
#define result_rankcMODE	SP_Z | SP_OVERLAP | SP_TRANSPARENT

extern Bitmap result_rankc_bitmaps[];
extern Gfx result_rankc_dl[];

#define NUM_result_rankc_BMS  (sizeof(result_rankc_bitmaps)/sizeof(Bitmap))

extern Sprite result_rankc_sprite;

// -------------------------------------------------------------------------- //
// @result_starc

#define result_starcTRUEIMAGEH	85
#define result_starcTRUEIMAGEW	82
#define result_starcIMAGEH	96
#define result_starcIMAGEW	96
#define result_starcBLOCKSIZEW	32
#define result_starcBLOCKSIZEH	32
#define result_starcSCALEX	1.0
#define result_starcSCALEY	1.0
#define result_starcMODE	SP_Z | SP_OVERLAP | SP_TRANSPARENT

extern Bitmap result_starc_bitmaps[];
extern Gfx result_starc_dl[];

#define NUM_result_starc_BMS  (sizeof(result_starc_bitmaps)/sizeof(Bitmap))

extern Sprite result_starc_sprite;

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
