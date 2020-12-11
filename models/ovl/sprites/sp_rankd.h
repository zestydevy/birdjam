
#ifndef INCLUDE_SP_RANKD_H
#define INCLUDE_SP_RANKD_H

#include <PR/sp.h>

// -------------------------------------------------------------------------- //
// @result_rankd

#define result_rankdTRUEIMAGEH	49
#define result_rankdTRUEIMAGEW	41
#define result_rankdIMAGEH	64
#define result_rankdIMAGEW	64
#define result_rankdBLOCKSIZEW	32
#define result_rankdBLOCKSIZEH	32
#define result_rankdSCALEX	1.0
#define result_rankdSCALEY	1.0
#define result_rankdMODE	SP_Z | SP_OVERLAP | SP_TRANSPARENT

extern Bitmap result_rankd_bitmaps[];
extern Gfx result_rankd_dl[];

#define NUM_result_rankd_BMS  (sizeof(result_rankd_bitmaps)/sizeof(Bitmap))

extern Sprite result_rankd_sprite;

// -------------------------------------------------------------------------- //
// @result_stard

#define result_stardTRUEIMAGEH	62
#define result_stardTRUEIMAGEW	62
#define result_stardIMAGEH	64
#define result_stardIMAGEW	64
#define result_stardBLOCKSIZEW	32
#define result_stardBLOCKSIZEH	32
#define result_stardSCALEX	1.0
#define result_stardSCALEY	1.0
#define result_stardMODE	SP_Z | SP_OVERLAP | SP_TRANSPARENT

extern Bitmap result_stard_bitmaps[];
extern Gfx result_stard_dl[];

#define NUM_result_stard_BMS  (sizeof(result_stard_bitmaps)/sizeof(Bitmap))

extern Sprite result_stard_sprite;

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
