
#ifndef INCLUDE_SP_MENU_H
#define INCLUDE_SP_MENU_H

#include <PR/sp.h>

// -------------------------------------------------------------------------- //
// @menu_bg

#define menu_bgTRUEIMAGEH	240
#define menu_bgTRUEIMAGEW	320
#define menu_bgIMAGEH	256
#define menu_bgIMAGEW	320
#define menu_bgBLOCKSIZEW	32
#define menu_bgBLOCKSIZEH	32
#define menu_bgSCALEX	1.0
#define menu_bgSCALEY	1.0
#define menu_bgMODE	SP_Z | SP_OVERLAP | SP_TRANSPARENT

extern Bitmap menu_bg_bitmaps[];
extern Gfx menu_bg_dl[];

#define NUM_menu_bg_BMS  (sizeof(menu_bg_bitmaps)/sizeof(Bitmap))

extern Sprite menu_bg_sprite;

// -------------------------------------------------------------------------- //
// @menu_logo

#define menu_logoTRUEIMAGEH	83
#define menu_logoTRUEIMAGEW	280
#define menu_logoIMAGEH	96
#define menu_logoIMAGEW	288
#define menu_logoBLOCKSIZEW	32
#define menu_logoBLOCKSIZEH	32
#define menu_logoSCALEX	1.0
#define menu_logoSCALEY	1.0
#define menu_logoMODE	SP_Z | SP_OVERLAP | SP_TRANSPARENT

extern Bitmap menu_logo_bitmaps[];
extern Gfx menu_logo_dl[];

#define NUM_menu_logo_BMS  (sizeof(menu_logo_bitmaps)/sizeof(Bitmap))

extern Sprite menu_logo_sprite;

// -------------------------------------------------------------------------- //
// @menu_bird

#define menu_birdTRUEIMAGEH	63
#define menu_birdTRUEIMAGEW	93
#define menu_birdIMAGEH	64
#define menu_birdIMAGEW	96
#define menu_birdBLOCKSIZEW	32
#define menu_birdBLOCKSIZEH	32
#define menu_birdSCALEX	1.0
#define menu_birdSCALEY	1.0
#define menu_birdMODE	SP_Z | SP_OVERLAP | SP_TRANSPARENT

extern Bitmap menu_bird_bitmaps[];
extern Gfx menu_bird_dl[];

#define NUM_menu_bird_BMS  (sizeof(menu_bird_bitmaps)/sizeof(Bitmap))

extern Sprite menu_bird_sprite;

// -------------------------------------------------------------------------- //
// @menu_swoop

#define menu_swoopTRUEIMAGEH	32
#define menu_swoopTRUEIMAGEW	230
#define menu_swoopIMAGEH	32
#define menu_swoopIMAGEW	256
#define menu_swoopBLOCKSIZEW	32
#define menu_swoopBLOCKSIZEH	32
#define menu_swoopSCALEX	1.0
#define menu_swoopSCALEY	1.0
#define menu_swoopMODE	SP_Z | SP_OVERLAP | SP_TRANSPARENT

extern Bitmap menu_swoop_bitmaps[];
extern Gfx menu_swoop_dl[];

#define NUM_menu_swoop_BMS  (sizeof(menu_swoop_bitmaps)/sizeof(Bitmap))

extern Sprite menu_swoop_sprite;

// -------------------------------------------------------------------------- //
// @menu_left

#define menu_leftTRUEIMAGEH	35
#define menu_leftTRUEIMAGEW	23
#define menu_leftIMAGEH	64
#define menu_leftIMAGEW	32
#define menu_leftBLOCKSIZEW	32
#define menu_leftBLOCKSIZEH	32
#define menu_leftSCALEX	1.0
#define menu_leftSCALEY	1.0
#define menu_leftMODE	SP_Z | SP_OVERLAP | SP_TRANSPARENT

extern Bitmap menu_left_bitmaps[];
extern Gfx menu_left_dl[];

#define NUM_menu_left_BMS  (sizeof(menu_left_bitmaps)/sizeof(Bitmap))

extern Sprite menu_left_sprite;

// -------------------------------------------------------------------------- //
// @menu_right

#define menu_rightTRUEIMAGEH	35
#define menu_rightTRUEIMAGEW	23
#define menu_rightIMAGEH	64
#define menu_rightIMAGEW	32
#define menu_rightBLOCKSIZEW	32
#define menu_rightBLOCKSIZEH	32
#define menu_rightSCALEX	1.0
#define menu_rightSCALEY	1.0
#define menu_rightMODE	SP_Z | SP_OVERLAP | SP_TRANSPARENT

extern Bitmap menu_right_bitmaps[];
extern Gfx menu_right_dl[];

#define NUM_menu_right_BMS  (sizeof(menu_right_bitmaps)/sizeof(Bitmap))

extern Sprite menu_right_sprite;

// -------------------------------------------------------------------------- //
// @menu_practice

#define menu_practiceTRUEIMAGEH	57
#define menu_practiceTRUEIMAGEW	159
#define menu_practiceIMAGEH	64
#define menu_practiceIMAGEW	160
#define menu_practiceBLOCKSIZEW	32
#define menu_practiceBLOCKSIZEH	32
#define menu_practiceSCALEX	1.0
#define menu_practiceSCALEY	1.0
#define menu_practiceMODE	SP_Z | SP_OVERLAP | SP_TRANSPARENT

extern Bitmap menu_practice_bitmaps[];
extern Gfx menu_practice_dl[];

#define NUM_menu_practice_BMS  (sizeof(menu_practice_bitmaps)/sizeof(Bitmap))

extern Sprite menu_practice_sprite;

// -------------------------------------------------------------------------- //
// @menu_time

#define menu_timeTRUEIMAGEH	57
#define menu_timeTRUEIMAGEW	133
#define menu_timeIMAGEH	64
#define menu_timeIMAGEW	160
#define menu_timeBLOCKSIZEW	32
#define menu_timeBLOCKSIZEH	32
#define menu_timeSCALEX	1.0
#define menu_timeSCALEY	1.0
#define menu_timeMODE	SP_Z | SP_OVERLAP | SP_TRANSPARENT

extern Bitmap menu_time_bitmaps[];
extern Gfx menu_time_dl[];

#define NUM_menu_time_BMS  (sizeof(menu_time_bitmaps)/sizeof(Bitmap))

extern Sprite menu_time_sprite;

// -------------------------------------------------------------------------- //
// @menu_freedom

#define menu_freedomTRUEIMAGEH	57
#define menu_freedomTRUEIMAGEW	155
#define menu_freedomIMAGEH	64
#define menu_freedomIMAGEW	160
#define menu_freedomBLOCKSIZEW	32
#define menu_freedomBLOCKSIZEH	32
#define menu_freedomSCALEX	1.0
#define menu_freedomSCALEY	1.0
#define menu_freedomMODE	SP_Z | SP_OVERLAP | SP_TRANSPARENT

extern Bitmap menu_freedom_bitmaps[];
extern Gfx menu_freedom_dl[];

#define NUM_menu_freedom_BMS  (sizeof(menu_freedom_bitmaps)/sizeof(Bitmap))

extern Sprite menu_freedom_sprite;

// -------------------------------------------------------------------------- //
// @menu_300

#define menu_300TRUEIMAGEH	33
#define menu_300TRUEIMAGEW	74
#define menu_300IMAGEH	64
#define menu_300IMAGEW	96
#define menu_300BLOCKSIZEW	32
#define menu_300BLOCKSIZEH	32
#define menu_300SCALEX	1.0
#define menu_300SCALEY	1.0
#define menu_300MODE	SP_Z | SP_OVERLAP | SP_TRANSPARENT

extern Bitmap menu_300_bitmaps[];
extern Gfx menu_300_dl[];

#define NUM_menu_300_BMS  (sizeof(menu_300_bitmaps)/sizeof(Bitmap))

extern Sprite menu_300_sprite;

// -------------------------------------------------------------------------- //
// @menu_500

#define menu_500TRUEIMAGEH	33
#define menu_500TRUEIMAGEW	73
#define menu_500IMAGEH	64
#define menu_500IMAGEW	96
#define menu_500BLOCKSIZEW	32
#define menu_500BLOCKSIZEH	32
#define menu_500SCALEX	1.0
#define menu_500SCALEY	1.0
#define menu_500MODE	SP_Z | SP_OVERLAP | SP_TRANSPARENT

extern Bitmap menu_500_bitmaps[];
extern Gfx menu_500_dl[];

#define NUM_menu_500_BMS  (sizeof(menu_500_bitmaps)/sizeof(Bitmap))

extern Sprite menu_500_sprite;

// -------------------------------------------------------------------------- //
// @menu_700

#define menu_700TRUEIMAGEH	33
#define menu_700TRUEIMAGEW	73
#define menu_700IMAGEH	64
#define menu_700IMAGEW	96
#define menu_700BLOCKSIZEW	32
#define menu_700BLOCKSIZEH	32
#define menu_700SCALEX	1.0
#define menu_700SCALEY	1.0
#define menu_700MODE	SP_Z | SP_OVERLAP | SP_TRANSPARENT

extern Bitmap menu_700_bitmaps[];
extern Gfx menu_700_dl[];

#define NUM_menu_700_BMS  (sizeof(menu_700_bitmaps)/sizeof(Bitmap))

extern Sprite menu_700_sprite;

// -------------------------------------------------------------------------- //
// @menu_start

#define menu_startTRUEIMAGEH	45
#define menu_startTRUEIMAGEW	42
#define menu_startIMAGEH	64
#define menu_startIMAGEW	64
#define menu_startBLOCKSIZEW	32
#define menu_startBLOCKSIZEH	32
#define menu_startSCALEX	1.0
#define menu_startSCALEY	1.0
#define menu_startMODE	SP_Z | SP_OVERLAP | SP_TRANSPARENT

extern Bitmap menu_start_bitmaps[];
extern Gfx menu_start_dl[];

#define NUM_menu_start_BMS  (sizeof(menu_start_bitmaps)/sizeof(Bitmap))

extern Sprite menu_start_sprite;

// -------------------------------------------------------------------------- //
// @menu_ok

#define menu_okTRUEIMAGEH	52
#define menu_okTRUEIMAGEW	113
#define menu_okIMAGEH	64
#define menu_okIMAGEW	128
#define menu_okBLOCKSIZEW	32
#define menu_okBLOCKSIZEH	32
#define menu_okSCALEX	1.0
#define menu_okSCALEY	1.0
#define menu_okMODE	SP_Z | SP_OVERLAP | SP_TRANSPARENT

extern Bitmap menu_ok_bitmaps[];
extern Gfx menu_ok_dl[];

#define NUM_menu_ok_BMS  (sizeof(menu_ok_bitmaps)/sizeof(Bitmap))

extern Sprite menu_ok_sprite;

// -------------------------------------------------------------------------- //
// @menu_unlock0

#define menu_unlock0TRUEIMAGEH	60
#define menu_unlock0TRUEIMAGEW	137
#define menu_unlock0IMAGEH	64
#define menu_unlock0IMAGEW	160
#define menu_unlock0BLOCKSIZEW	32
#define menu_unlock0BLOCKSIZEH	32
#define menu_unlock0SCALEX	1.0
#define menu_unlock0SCALEY	1.0
#define menu_unlock0MODE	SP_Z | SP_OVERLAP | SP_TRANSPARENT

extern Bitmap menu_unlock0_bitmaps[];
extern Gfx menu_unlock0_dl[];

#define NUM_menu_unlock0_BMS  (sizeof(menu_unlock0_bitmaps)/sizeof(Bitmap))

extern Sprite menu_unlock0_sprite;

// -------------------------------------------------------------------------- //

#endif
