#ifndef sp_hud_digit7_h
#define sp_hud_digit7_h

#include <PR/sp.h>

#define hud_digit7TRUEIMAGEH	24
#define hud_digit7TRUEIMAGEW	19
#define hud_digit7IMAGEH	32
#define hud_digit7IMAGEW	32
#define hud_digit7BLOCKSIZEW	32
#define hud_digit7BLOCKSIZEH	32
#define hud_digit7SCALEX	1.0
#define hud_digit7SCALEY	1.0
#define hud_digit7MODE	SP_Z | SP_OVERLAP | SP_TRANSPARENT

// extern varaibles 
extern Bitmap hud_digit7_bitmaps[];
extern Gfx hud_digit7_dl[];

#define NUM_hud_digit7_BMS  (sizeof(hud_digit7_bitmaps)/sizeof(Bitmap))

extern Sprite hud_digit7_sprite;

#endif 

