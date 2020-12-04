#ifndef sp_hud_digit5_h
#define sp_hud_digit5_h

#include <PR/sp.h>

#define hud_digit5TRUEIMAGEH	24
#define hud_digit5TRUEIMAGEW	19
#define hud_digit5IMAGEH	32
#define hud_digit5IMAGEW	32
#define hud_digit5BLOCKSIZEW	32
#define hud_digit5BLOCKSIZEH	32
#define hud_digit5SCALEX	1.0
#define hud_digit5SCALEY	1.0
#define hud_digit5MODE	SP_Z | SP_OVERLAP | SP_TRANSPARENT

// extern varaibles 
extern Bitmap hud_digit5_bitmaps[];
extern Gfx hud_digit5_dl[];

#define NUM_hud_digit5_BMS  (sizeof(hud_digit5_bitmaps)/sizeof(Bitmap))

extern Sprite hud_digit5_sprite;

#endif 

