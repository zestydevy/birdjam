
#ifndef INCLUDE_SP_COUNTDOWN_H
#define INCLUDE_SP_COUNTDOWN_H

#include <PR/sp.h>

// -------------------------------------------------------------------------- //
// @hud_ready

#define hud_readyTRUEIMAGEH	52
#define hud_readyTRUEIMAGEW	222
#define hud_readyIMAGEH	64
#define hud_readyIMAGEW	224
#define hud_readyBLOCKSIZEW	32
#define hud_readyBLOCKSIZEH	32
#define hud_readySCALEX	1.0
#define hud_readySCALEY	1.0
#define hud_readyMODE	SP_Z | SP_OVERLAP | SP_TRANSPARENT

extern Bitmap hud_ready_bitmaps[];
extern Gfx hud_ready_dl[];

#define NUM_hud_ready_BMS  (sizeof(hud_ready_bitmaps)/sizeof(Bitmap))

extern Sprite hud_ready_sprite;

// -------------------------------------------------------------------------- //
// @hud_fly

#define hud_flyTRUEIMAGEH	52
#define hud_flyTRUEIMAGEW	122
#define hud_flyIMAGEH	64
#define hud_flyIMAGEW	128
#define hud_flyBLOCKSIZEW	32
#define hud_flyBLOCKSIZEH	32
#define hud_flySCALEX	1.0
#define hud_flySCALEY	1.0
#define hud_flyMODE	SP_Z | SP_OVERLAP | SP_TRANSPARENT

extern Bitmap hud_fly_bitmaps[];
extern Gfx hud_fly_dl[];

#define NUM_hud_fly_BMS  (sizeof(hud_fly_bitmaps)/sizeof(Bitmap))

extern Sprite hud_fly_sprite;

// -------------------------------------------------------------------------- //
// @hud_count3

#define hud_count3TRUEIMAGEH	95
#define hud_count3TRUEIMAGEW	76
#define hud_count3IMAGEH	96
#define hud_count3IMAGEW	96
#define hud_count3BLOCKSIZEW	32
#define hud_count3BLOCKSIZEH	32
#define hud_count3SCALEX	1.0
#define hud_count3SCALEY	1.0
#define hud_count3MODE	SP_Z | SP_OVERLAP | SP_TRANSPARENT

extern Bitmap hud_count3_bitmaps[];
extern Gfx hud_count3_dl[];

#define NUM_hud_count3_BMS  (sizeof(hud_count3_bitmaps)/sizeof(Bitmap))

extern Sprite hud_count3_sprite;

// -------------------------------------------------------------------------- //
// @hud_count2

#define hud_count2TRUEIMAGEH	95
#define hud_count2TRUEIMAGEW	76
#define hud_count2IMAGEH	96
#define hud_count2IMAGEW	96
#define hud_count2BLOCKSIZEW	32
#define hud_count2BLOCKSIZEH	32
#define hud_count2SCALEX	1.0
#define hud_count2SCALEY	1.0
#define hud_count2MODE	SP_Z | SP_OVERLAP | SP_TRANSPARENT

extern Bitmap hud_count2_bitmaps[];
extern Gfx hud_count2_dl[];

#define NUM_hud_count2_BMS  (sizeof(hud_count2_bitmaps)/sizeof(Bitmap))

extern Sprite hud_count2_sprite;

// -------------------------------------------------------------------------- //
// @hud_count1

#define hud_count1TRUEIMAGEH	95
#define hud_count1TRUEIMAGEW	76
#define hud_count1IMAGEH	96
#define hud_count1IMAGEW	96
#define hud_count1BLOCKSIZEW	32
#define hud_count1BLOCKSIZEH	32
#define hud_count1SCALEX	1.0
#define hud_count1SCALEY	1.0
#define hud_count1MODE	SP_Z | SP_OVERLAP | SP_TRANSPARENT

extern Bitmap hud_count1_bitmaps[];
extern Gfx hud_count1_dl[];

#define NUM_hud_count1_BMS  (sizeof(hud_count1_bitmaps)/sizeof(Bitmap))

extern Sprite hud_count1_sprite;

// -------------------------------------------------------------------------- //

#endif
