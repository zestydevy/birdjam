#ifndef sp_hud_digit0_h
#define sp_hud_digit0_h

#include <PR/sp.h>

#define hud_digit0TRUEIMAGEH	24
#define hud_digit0TRUEIMAGEW	19
#define hud_digit0IMAGEH	32
#define hud_digit0IMAGEW	32
#define hud_digit0BLOCKSIZEW	32
#define hud_digit0BLOCKSIZEH	32
#define hud_digit0SCALEX	1.0
#define hud_digit0SCALEY	1.0
#define hud_digit0MODE	SP_Z | SP_OVERLAP | SP_TRANSPARENT

// extern varaibles 
extern Bitmap hud_digit0_bitmaps[];
extern Gfx hud_digit0_dl[];

#define NUM_hud_digit0_BMS  (sizeof(hud_digit0_bitmaps)/sizeof(Bitmap))

extern Sprite hud_digit0_sprite;

#endif 

