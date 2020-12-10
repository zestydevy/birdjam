
#ifndef INCLUDE_SP_HUD_H
#define INCLUDE_SP_HUD_H

#include <PR/sp.h>

// -------------------------------------------------------------------------- //
// @hud_time

#define hud_timeTRUEIMAGEH	26
#define hud_timeTRUEIMAGEW	84
#define hud_timeIMAGEH	32
#define hud_timeIMAGEW	96
#define hud_timeBLOCKSIZEW	32
#define hud_timeBLOCKSIZEH	32
#define hud_timeSCALEX	1.0
#define hud_timeSCALEY	1.0
#define hud_timeMODE	SP_Z | SP_OVERLAP | SP_TRANSPARENT

extern Bitmap hud_time_bitmaps[];
extern Gfx hud_time_dl[];

#define NUM_hud_time_BMS  (sizeof(hud_time_bitmaps)/sizeof(Bitmap))

extern Sprite hud_time_sprite;

// -------------------------------------------------------------------------- //
// @hud_colon

#define hud_colonTRUEIMAGEH	24
#define hud_colonTRUEIMAGEW	19
#define hud_colonIMAGEH	32
#define hud_colonIMAGEW	32
#define hud_colonBLOCKSIZEW	32
#define hud_colonBLOCKSIZEH	32
#define hud_colonSCALEX	1.0
#define hud_colonSCALEY	1.0
#define hud_colonMODE	SP_Z | SP_OVERLAP | SP_TRANSPARENT

extern Bitmap hud_colon_bitmaps[];
extern Gfx hud_colon_dl[];

#define NUM_hud_colon_BMS  (sizeof(hud_colon_bitmaps)/sizeof(Bitmap))

extern Sprite hud_colon_sprite;

// -------------------------------------------------------------------------- //
// @hud_digit0

#define hud_digit0TRUEIMAGEH	24
#define hud_digit0TRUEIMAGEW	19
#define hud_digit0IMAGEH	32
#define hud_digit0IMAGEW	32
#define hud_digit0BLOCKSIZEW	32
#define hud_digit0BLOCKSIZEH	32
#define hud_digit0SCALEX	1.0
#define hud_digit0SCALEY	1.0
#define hud_digit0MODE	SP_Z | SP_OVERLAP | SP_TRANSPARENT

extern Bitmap hud_digit0_bitmaps[];
extern Gfx hud_digit0_dl[];

#define NUM_hud_digit0_BMS  (sizeof(hud_digit0_bitmaps)/sizeof(Bitmap))

extern Sprite hud_digit0_sprite;

// -------------------------------------------------------------------------- //
// @hud_digit1

#define hud_digit1TRUEIMAGEH	24
#define hud_digit1TRUEIMAGEW	19
#define hud_digit1IMAGEH	32
#define hud_digit1IMAGEW	32
#define hud_digit1BLOCKSIZEW	32
#define hud_digit1BLOCKSIZEH	32
#define hud_digit1SCALEX	1.0
#define hud_digit1SCALEY	1.0
#define hud_digit1MODE	SP_Z | SP_OVERLAP | SP_TRANSPARENT

extern Bitmap hud_digit1_bitmaps[];
extern Gfx hud_digit1_dl[];

#define NUM_hud_digit1_BMS  (sizeof(hud_digit1_bitmaps)/sizeof(Bitmap))

extern Sprite hud_digit1_sprite;

// -------------------------------------------------------------------------- //
// @hud_digit2

#define hud_digit2TRUEIMAGEH	24
#define hud_digit2TRUEIMAGEW	19
#define hud_digit2IMAGEH	32
#define hud_digit2IMAGEW	32
#define hud_digit2BLOCKSIZEW	32
#define hud_digit2BLOCKSIZEH	32
#define hud_digit2SCALEX	1.0
#define hud_digit2SCALEY	1.0
#define hud_digit2MODE	SP_Z | SP_OVERLAP | SP_TRANSPARENT

extern Bitmap hud_digit2_bitmaps[];
extern Gfx hud_digit2_dl[];

#define NUM_hud_digit2_BMS  (sizeof(hud_digit2_bitmaps)/sizeof(Bitmap))

extern Sprite hud_digit2_sprite;

// -------------------------------------------------------------------------- //
// @hud_digit3

#define hud_digit3TRUEIMAGEH	24
#define hud_digit3TRUEIMAGEW	19
#define hud_digit3IMAGEH	32
#define hud_digit3IMAGEW	32
#define hud_digit3BLOCKSIZEW	32
#define hud_digit3BLOCKSIZEH	32
#define hud_digit3SCALEX	1.0
#define hud_digit3SCALEY	1.0
#define hud_digit3MODE	SP_Z | SP_OVERLAP | SP_TRANSPARENT

extern Bitmap hud_digit3_bitmaps[];
extern Gfx hud_digit3_dl[];

#define NUM_hud_digit3_BMS  (sizeof(hud_digit3_bitmaps)/sizeof(Bitmap))

extern Sprite hud_digit3_sprite;

// -------------------------------------------------------------------------- //
// @hud_digit4

#define hud_digit4TRUEIMAGEH	24
#define hud_digit4TRUEIMAGEW	19
#define hud_digit4IMAGEH	32
#define hud_digit4IMAGEW	32
#define hud_digit4BLOCKSIZEW	32
#define hud_digit4BLOCKSIZEH	32
#define hud_digit4SCALEX	1.0
#define hud_digit4SCALEY	1.0
#define hud_digit4MODE	SP_Z | SP_OVERLAP | SP_TRANSPARENT

extern Bitmap hud_digit4_bitmaps[];
extern Gfx hud_digit4_dl[];

#define NUM_hud_digit4_BMS  (sizeof(hud_digit4_bitmaps)/sizeof(Bitmap))

extern Sprite hud_digit4_sprite;

// -------------------------------------------------------------------------- //
// @hud_digit5

#define hud_digit5TRUEIMAGEH	24
#define hud_digit5TRUEIMAGEW	19
#define hud_digit5IMAGEH	32
#define hud_digit5IMAGEW	32
#define hud_digit5BLOCKSIZEW	32
#define hud_digit5BLOCKSIZEH	32
#define hud_digit5SCALEX	1.0
#define hud_digit5SCALEY	1.0
#define hud_digit5MODE	SP_Z | SP_OVERLAP | SP_TRANSPARENT

extern Bitmap hud_digit5_bitmaps[];
extern Gfx hud_digit5_dl[];

#define NUM_hud_digit5_BMS  (sizeof(hud_digit5_bitmaps)/sizeof(Bitmap))

extern Sprite hud_digit5_sprite;

// -------------------------------------------------------------------------- //
// @hud_digit6

#define hud_digit6TRUEIMAGEH	24
#define hud_digit6TRUEIMAGEW	19
#define hud_digit6IMAGEH	32
#define hud_digit6IMAGEW	32
#define hud_digit6BLOCKSIZEW	32
#define hud_digit6BLOCKSIZEH	32
#define hud_digit6SCALEX	1.0
#define hud_digit6SCALEY	1.0
#define hud_digit6MODE	SP_Z | SP_OVERLAP | SP_TRANSPARENT

extern Bitmap hud_digit6_bitmaps[];
extern Gfx hud_digit6_dl[];

#define NUM_hud_digit6_BMS  (sizeof(hud_digit6_bitmaps)/sizeof(Bitmap))

extern Sprite hud_digit6_sprite;

// -------------------------------------------------------------------------- //
// @hud_digit7

#define hud_digit7TRUEIMAGEH	24
#define hud_digit7TRUEIMAGEW	19
#define hud_digit7IMAGEH	32
#define hud_digit7IMAGEW	32
#define hud_digit7BLOCKSIZEW	32
#define hud_digit7BLOCKSIZEH	32
#define hud_digit7SCALEX	1.0
#define hud_digit7SCALEY	1.0
#define hud_digit7MODE	SP_Z | SP_OVERLAP | SP_TRANSPARENT

extern Bitmap hud_digit7_bitmaps[];
extern Gfx hud_digit7_dl[];

#define NUM_hud_digit7_BMS  (sizeof(hud_digit7_bitmaps)/sizeof(Bitmap))

extern Sprite hud_digit7_sprite;

// -------------------------------------------------------------------------- //
// @hud_digit8

#define hud_digit8TRUEIMAGEH	24
#define hud_digit8TRUEIMAGEW	19
#define hud_digit8IMAGEH	32
#define hud_digit8IMAGEW	32
#define hud_digit8BLOCKSIZEW	32
#define hud_digit8BLOCKSIZEH	32
#define hud_digit8SCALEX	1.0
#define hud_digit8SCALEY	1.0
#define hud_digit8MODE	SP_Z | SP_OVERLAP | SP_TRANSPARENT

extern Bitmap hud_digit8_bitmaps[];
extern Gfx hud_digit8_dl[];

#define NUM_hud_digit8_BMS  (sizeof(hud_digit8_bitmaps)/sizeof(Bitmap))

extern Sprite hud_digit8_sprite;

// -------------------------------------------------------------------------- //
// @hud_digit9

#define hud_digit9TRUEIMAGEH	24
#define hud_digit9TRUEIMAGEW	19
#define hud_digit9IMAGEH	32
#define hud_digit9IMAGEW	32
#define hud_digit9BLOCKSIZEW	32
#define hud_digit9BLOCKSIZEH	32
#define hud_digit9SCALEX	1.0
#define hud_digit9SCALEY	1.0
#define hud_digit9MODE	SP_Z | SP_OVERLAP | SP_TRANSPARENT

extern Bitmap hud_digit9_bitmaps[];
extern Gfx hud_digit9_dl[];

#define NUM_hud_digit9_BMS  (sizeof(hud_digit9_bitmaps)/sizeof(Bitmap))

extern Sprite hud_digit9_sprite;

// -------------------------------------------------------------------------- //
// @hud_score

#define hud_scoreTRUEIMAGEH	27
#define hud_scoreTRUEIMAGEW	100
#define hud_scoreIMAGEH	32
#define hud_scoreIMAGEW	128
#define hud_scoreBLOCKSIZEW	32
#define hud_scoreBLOCKSIZEH	32
#define hud_scoreSCALEX	1.0
#define hud_scoreSCALEY	1.0
#define hud_scoreMODE	SP_Z | SP_OVERLAP | SP_TRANSPARENT

extern Bitmap hud_score_bitmaps[];
extern Gfx hud_score_dl[];

#define NUM_hud_score_BMS  (sizeof(hud_score_bitmaps)/sizeof(Bitmap))

extern Sprite hud_score_sprite;

// -------------------------------------------------------------------------- //
// @hud_dot

#define hud_dotTRUEIMAGEH	10
#define hud_dotTRUEIMAGEW	8
#define hud_dotIMAGEH	32
#define hud_dotIMAGEW	32
#define hud_dotBLOCKSIZEW	32
#define hud_dotBLOCKSIZEH	32
#define hud_dotSCALEX	1.0
#define hud_dotSCALEY	1.0
#define hud_dotMODE	SP_Z | SP_OVERLAP | SP_TRANSPARENT

extern Bitmap hud_dot_bitmaps[];
extern Gfx hud_dot_dl[];

#define NUM_hud_dot_BMS  (sizeof(hud_dot_bitmaps)/sizeof(Bitmap))

extern Sprite hud_dot_sprite;

// -------------------------------------------------------------------------- //
// @hud_ft

#define hud_ftTRUEIMAGEH	14
#define hud_ftTRUEIMAGEW	20
#define hud_ftIMAGEH	32
#define hud_ftIMAGEW	32
#define hud_ftBLOCKSIZEW	32
#define hud_ftBLOCKSIZEH	32
#define hud_ftSCALEX	1.0
#define hud_ftSCALEY	1.0
#define hud_ftMODE	SP_Z | SP_OVERLAP | SP_TRANSPARENT

extern Bitmap hud_ft_bitmaps[];
extern Gfx hud_ft_dl[];

#define NUM_hud_ft_BMS  (sizeof(hud_ft_bitmaps)/sizeof(Bitmap))

extern Sprite hud_ft_sprite;

// -------------------------------------------------------------------------- //

#endif
