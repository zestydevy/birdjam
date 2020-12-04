#ifndef sp_hud_digit9_h
#define sp_hud_digit9_h

#include <PR/sp.h>

#define hud_digit9TRUEIMAGEH	24
#define hud_digit9TRUEIMAGEW	19
#define hud_digit9IMAGEH	32
#define hud_digit9IMAGEW	32
#define hud_digit9BLOCKSIZEW	32
#define hud_digit9BLOCKSIZEH	32
#define hud_digit9SCALEX	1.0
#define hud_digit9SCALEY	1.0
#define hud_digit9MODE	SP_Z | SP_OVERLAP | SP_TRANSPARENT

// extern varaibles 
extern Bitmap hud_digit9_bitmaps[];
extern Gfx hud_digit9_dl[];

#define NUM_hud_digit9_BMS  (sizeof(hud_digit9_bitmaps)/sizeof(Bitmap))

extern Sprite hud_digit9_sprite;

#endif 

