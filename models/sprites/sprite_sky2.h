#ifndef sp_sky_h
#define sp_sky_h

#include <PR/sp.h>

#define skyTRUEIMAGEH	240
#define skyTRUEIMAGEW	320
#define skyIMAGEH	256
#define skyIMAGEW	320
#define skyBLOCKSIZEW	32
#define skyBLOCKSIZEH	32
#define skySCALEX	1.0
#define skySCALEY	1.0
#define skyMODE	SP_Z | SP_OVERLAP | SP_TRANSPARENT

// extern varaibles 
extern Bitmap sky_bitmaps[];
extern Gfx sky_dl[];

#define NUM_sky_BMS  (sizeof(sky_bitmaps)/sizeof(Bitmap))

extern Sprite sky_sprite;

#endif 

#if 0	/* Image preview */
+------------------------------------------------+
|CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC|
|CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC|
|CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC|
|CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC@@|
|CCCCCCCCCCCC@@@@@CCCCCCCCCCCCCCCCCCCCCCCCCCC@CCC|
|CCCCCCCCCCCCCCCC@@@@CCCCCCCCCCCCCCCCCCCC@@@CCCCC|
|CC@@CCC@@@CCCCCCCCCCCCCCCCCCCCCCCCCCCC@@CCCCCCCC|
|CC@@@@@@@@@CCCCCCCCCCCCCCCCCCCC@@@@CCCCCC@@@@@C@|
|CCCCC@@@@@@@CCCCCCCCCCCCCCCCCCCCCCCCCC@@@@@@@@@@|
|@@CCCCCC@@@@@@@@CCCCCCCCCCCCCCCCCCCC@@@@@@@@@@@@|
|CC@@@CCCCCC@@@@@@CCCCCCCC@@CCCCC@@@@@@@@@@@@@CCC|
|CCCCC@@@CCCCCCCC@@CCCCCCCCCCC@@@@@@@@@@CCCCCCCCC|
|@@CCCCCCC@@@@@CCCCCCCC@CCCCCCCCCCCCCCCCCCCCCC@@@|
|CCCCC@CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC@@@CCCCC|
|@CCCCCCCCC@@CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC@@|
|@@CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC@@@@@@|
|@@@@CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC@@@@@@|
|@@@@CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC@@@@@@@@|
|@@@@@@@@CCCCCCCCCCCCCCCCCCCCCCCCCCCC@CC@@@@@@@@@|
|@@@@@@@@@@C@@@C@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@|
|@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@|
|@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@|
|@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@|
|@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@|
+------------------------------------------------+
#endif

