#ifndef sp_hud_digit4_h
#define sp_hud_digit4_h

#include <PR/sp.h>

#define hud_digit4TRUEIMAGEH	24
#define hud_digit4TRUEIMAGEW	19
#define hud_digit4IMAGEH	32
#define hud_digit4IMAGEW	32
#define hud_digit4BLOCKSIZEW	32
#define hud_digit4BLOCKSIZEH	32
#define hud_digit4SCALEX	1.0
#define hud_digit4SCALEY	1.0
#define hud_digit4MODE	SP_Z | SP_OVERLAP | SP_TRANSPARENT

// extern varaibles 
extern Bitmap hud_digit4_bitmaps[];
extern Gfx hud_digit4_dl[];

#define NUM_hud_digit4_BMS  (sizeof(hud_digit4_bitmaps)/sizeof(Bitmap))

extern Sprite hud_digit4_sprite;

#endif 

