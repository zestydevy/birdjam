#ifndef sp_hud_digit6_h
#define sp_hud_digit6_h

#include <PR/sp.h>

#define hud_digit6TRUEIMAGEH	24
#define hud_digit6TRUEIMAGEW	19
#define hud_digit6IMAGEH	32
#define hud_digit6IMAGEW	32
#define hud_digit6BLOCKSIZEW	32
#define hud_digit6BLOCKSIZEH	32
#define hud_digit6SCALEX	1.0
#define hud_digit6SCALEY	1.0
#define hud_digit6MODE	SP_Z | SP_OVERLAP | SP_TRANSPARENT

// extern varaibles 
extern Bitmap hud_digit6_bitmaps[];
extern Gfx hud_digit6_dl[];

#define NUM_hud_digit6_BMS  (sizeof(hud_digit6_bitmaps)/sizeof(Bitmap))

extern Sprite hud_digit6_sprite;

#endif 

