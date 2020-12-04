#ifndef sp_hud_digit1_h
#define sp_hud_digit1_h

#include <PR/sp.h>

#define hud_digit1TRUEIMAGEH	24
#define hud_digit1TRUEIMAGEW	19
#define hud_digit1IMAGEH	32
#define hud_digit1IMAGEW	32
#define hud_digit1BLOCKSIZEW	32
#define hud_digit1BLOCKSIZEH	32
#define hud_digit1SCALEX	1.0
#define hud_digit1SCALEY	1.0
#define hud_digit1MODE	SP_Z | SP_OVERLAP | SP_TRANSPARENT

// extern varaibles 
extern Bitmap hud_digit1_bitmaps[];
extern Gfx hud_digit1_dl[];

#define NUM_hud_digit1_BMS  (sizeof(hud_digit1_bitmaps)/sizeof(Bitmap))

extern Sprite hud_digit1_sprite;

#endif 

