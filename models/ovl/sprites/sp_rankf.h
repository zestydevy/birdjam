
#ifndef INCLUDE_SP_RANKF_H
#define INCLUDE_SP_RANKF_H

#include <PR/sp.h>

// -------------------------------------------------------------------------- //
// @result_rankf

#define result_rankfTRUEIMAGEH	49
#define result_rankfTRUEIMAGEW	36
#define result_rankfIMAGEH	64
#define result_rankfIMAGEW	64
#define result_rankfBLOCKSIZEW	32
#define result_rankfBLOCKSIZEH	32
#define result_rankfSCALEX	1.0
#define result_rankfSCALEY	1.0
#define result_rankfMODE	SP_Z | SP_OVERLAP | SP_TRANSPARENT

extern Bitmap result_rankf_bitmaps[];
extern Gfx result_rankf_dl[];

#define NUM_result_rankf_BMS  (sizeof(result_rankf_bitmaps)/sizeof(Bitmap))

extern Sprite result_rankf_sprite;

// -------------------------------------------------------------------------- //
// @result_birdf

#define result_birdfTRUEIMAGEH	100
#define result_birdfTRUEIMAGEW	100
#define result_birdfIMAGEH	128
#define result_birdfIMAGEW	128
#define result_birdfBLOCKSIZEW	32
#define result_birdfBLOCKSIZEH	32
#define result_birdfSCALEX	1.0
#define result_birdfSCALEY	1.0
#define result_birdfMODE	SP_Z | SP_OVERLAP | SP_TRANSPARENT

extern Bitmap result_birdf_bitmaps[];
extern Gfx result_birdf_dl[];

#define NUM_result_birdf_BMS  (sizeof(result_birdf_bitmaps)/sizeof(Bitmap))

extern Sprite result_birdf_sprite;

// -------------------------------------------------------------------------- //

#endif
