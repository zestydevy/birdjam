
#ifndef INCLUDE_SP_RANKF_H
#define INCLUDE_SP_RANKF_H

#include <PR/sp.h>

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
