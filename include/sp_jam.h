#ifndef sp_jam_h
#define sp_jam_h

#include <PR/sp.h>

#define jamTRUEIMAGEH	240
#define jamTRUEIMAGEW	320
#define jamIMAGEH	256
#define jamIMAGEW	320
#define jamBLOCKSIZEW	32
#define jamBLOCKSIZEH	32
#define jamSCALEX	1.0
#define jamSCALEY	1.0
#define jamMODE	SP_Z | SP_OVERLAP | SP_TRANSPARENT

// extern varaibles 
extern Bitmap jam_bitmaps[];
extern Gfx jam_dl[];

#define NUM_jam_BMS  (sizeof(jam_bitmaps)/sizeof(Bitmap))

extern Sprite jam_sprite;

#endif 

