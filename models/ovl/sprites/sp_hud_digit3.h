#ifndef sp_hud_digit3_h
#define sp_hud_digit3_h

#include <PR/sp.h>

#define hud_digit3TRUEIMAGEH	24
#define hud_digit3TRUEIMAGEW	19
#define hud_digit3IMAGEH	32
#define hud_digit3IMAGEW	32
#define hud_digit3BLOCKSIZEW	32
#define hud_digit3BLOCKSIZEH	32
#define hud_digit3SCALEX	1.0
#define hud_digit3SCALEY	1.0
#define hud_digit3MODE	SP_Z | SP_OVERLAP | SP_TRANSPARENT

// extern varaibles 
extern Bitmap hud_digit3_bitmaps[];
extern Gfx hud_digit3_dl[];

#define NUM_hud_digit3_BMS  (sizeof(hud_digit3_bitmaps)/sizeof(Bitmap))

extern Sprite hud_digit3_sprite;

#endif 

