#ifndef sp_hud_score_h
#define sp_hud_score_h

#include <PR/sp.h>

#define hud_scoreTRUEIMAGEH	27
#define hud_scoreTRUEIMAGEW	100
#define hud_scoreIMAGEH	32
#define hud_scoreIMAGEW	128
#define hud_scoreBLOCKSIZEW	32
#define hud_scoreBLOCKSIZEH	32
#define hud_scoreSCALEX	1.0
#define hud_scoreSCALEY	1.0
#define hud_scoreMODE	SP_Z | SP_OVERLAP | SP_TRANSPARENT

// extern varaibles 
extern Bitmap hud_score_bitmaps[];
extern Gfx hud_score_dl[];

#define NUM_hud_score_BMS  (sizeof(hud_score_bitmaps)/sizeof(Bitmap))

extern Sprite hud_score_sprite;

#endif 

