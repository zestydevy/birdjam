#ifndef sp_hud_digit8_h
#define sp_hud_digit8_h

#include <PR/sp.h>

#define hud_digit8TRUEIMAGEH	24
#define hud_digit8TRUEIMAGEW	19
#define hud_digit8IMAGEH	32
#define hud_digit8IMAGEW	32
#define hud_digit8BLOCKSIZEW	32
#define hud_digit8BLOCKSIZEH	32
#define hud_digit8SCALEX	1.0
#define hud_digit8SCALEY	1.0
#define hud_digit8MODE	SP_Z | SP_OVERLAP | SP_TRANSPARENT

// extern varaibles 
extern Bitmap hud_digit8_bitmaps[];
extern Gfx hud_digit8_dl[];

#define NUM_hud_digit8_BMS  (sizeof(hud_digit8_bitmaps)/sizeof(Bitmap))

extern Sprite hud_digit8_sprite;

#endif 

