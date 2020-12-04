#ifndef sp_hud_digit2_h
#define sp_hud_digit2_h

#include <PR/sp.h>

#define hud_digit2TRUEIMAGEH	24
#define hud_digit2TRUEIMAGEW	19
#define hud_digit2IMAGEH	32
#define hud_digit2IMAGEW	32
#define hud_digit2BLOCKSIZEW	32
#define hud_digit2BLOCKSIZEH	32
#define hud_digit2SCALEX	1.0
#define hud_digit2SCALEY	1.0
#define hud_digit2MODE	SP_Z | SP_OVERLAP | SP_TRANSPARENT

// extern varaibles 
extern Bitmap hud_digit2_bitmaps[];
extern Gfx hud_digit2_dl[];

#define NUM_hud_digit2_BMS  (sizeof(hud_digit2_bitmaps)/sizeof(Bitmap))

extern Sprite hud_digit2_sprite;

#endif 

