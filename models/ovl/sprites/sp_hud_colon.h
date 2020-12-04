#ifndef sp_hud_colon_h
#define sp_hud_colon_h

#include <PR/sp.h>

#define hud_colonTRUEIMAGEH	24
#define hud_colonTRUEIMAGEW	19
#define hud_colonIMAGEH	32
#define hud_colonIMAGEW	32
#define hud_colonBLOCKSIZEW	32
#define hud_colonBLOCKSIZEH	32
#define hud_colonSCALEX	1.0
#define hud_colonSCALEY	1.0
#define hud_colonMODE	SP_Z | SP_OVERLAP | SP_TRANSPARENT

// extern varaibles 
extern Bitmap hud_colon_bitmaps[];
extern Gfx hud_colon_dl[];

#define NUM_hud_colon_BMS  (sizeof(hud_colon_bitmaps)/sizeof(Bitmap))

extern Sprite hud_colon_sprite;

#endif 

