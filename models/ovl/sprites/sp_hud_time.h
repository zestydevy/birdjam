#ifndef sp_hud_time_h
#define sp_hud_time_h

#include <PR/sp.h>

#define hud_timeTRUEIMAGEH	26
#define hud_timeTRUEIMAGEW	84
#define hud_timeIMAGEH	32
#define hud_timeIMAGEW	96
#define hud_timeBLOCKSIZEW	32
#define hud_timeBLOCKSIZEH	32
#define hud_timeSCALEX	1.0
#define hud_timeSCALEY	1.0
#define hud_timeMODE	SP_Z | SP_OVERLAP | SP_TRANSPARENT

// extern varaibles 
extern Bitmap hud_time_bitmaps[];
extern Gfx hud_time_dl[];

#define NUM_hud_time_BMS  (sizeof(hud_time_bitmaps)/sizeof(Bitmap))

extern Sprite hud_time_sprite;

#endif 

