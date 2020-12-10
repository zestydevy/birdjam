
#ifndef INCLUDE_SP_RANKA_H
#define INCLUDE_SP_RANKA_H

#include <PR/sp.h>

// -------------------------------------------------------------------------- //
// @result_birdb

#define result_birdbTRUEIMAGEH	100
#define result_birdbTRUEIMAGEW	100
#define result_birdbIMAGEH	128
#define result_birdbIMAGEW	128
#define result_birdbBLOCKSIZEW	32
#define result_birdbBLOCKSIZEH	32
#define result_birdbSCALEX	1.0
#define result_birdbSCALEY	1.0
#define result_birdbMODE	SP_Z | SP_OVERLAP | SP_TRANSPARENT

extern Bitmap result_birdb_bitmaps[];
extern Gfx result_birdb_dl[];

#define NUM_result_birdb_BMS  (sizeof(result_birdb_bitmaps)/sizeof(Bitmap))

extern Sprite result_birdb_sprite;

// -------------------------------------------------------------------------- //

#endif
