
#ifndef INCLUDE_SP_RANKB_H
#define INCLUDE_SP_RANKB_H

#include <PR/sp.h>

// -------------------------------------------------------------------------- //
// @result_rankb

#define result_rankbTRUEIMAGEH	49
#define result_rankbTRUEIMAGEW	39
#define result_rankbIMAGEH	64
#define result_rankbIMAGEW	64
#define result_rankbBLOCKSIZEW	32
#define result_rankbBLOCKSIZEH	32
#define result_rankbSCALEX	1.0
#define result_rankbSCALEY	1.0
#define result_rankbMODE	SP_Z | SP_OVERLAP | SP_TRANSPARENT

extern Bitmap result_rankb_bitmaps[];
extern Gfx result_rankb_dl[];

#define NUM_result_rankb_BMS  (sizeof(result_rankb_bitmaps)/sizeof(Bitmap))

extern Sprite result_rankb_sprite;

// -------------------------------------------------------------------------- //
// @result_starb

#define result_starbTRUEIMAGEH	95
#define result_starbTRUEIMAGEW	92
#define result_starbIMAGEH	96
#define result_starbIMAGEW	96
#define result_starbBLOCKSIZEW	32
#define result_starbBLOCKSIZEH	32
#define result_starbSCALEX	1.0
#define result_starbSCALEY	1.0
#define result_starbMODE	SP_Z | SP_OVERLAP | SP_TRANSPARENT

extern Bitmap result_starb_bitmaps[];
extern Gfx result_starb_dl[];

#define NUM_result_starb_BMS  (sizeof(result_starb_bitmaps)/sizeof(Bitmap))

extern Sprite result_starb_sprite;

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
