/*
	ROM spec file

	Main memory map

  	0x80000000  exception vectors, ...
  	0x80000400  zbuffer (size 320*240*2)
  	0x80025c00  codesegment
	0x80119e40
	      :  
  	0x8020F800  Game Heap
	0x8030F800  Audio Heap
  	0x8038F800  cfb 16b 3buffer (size 320*240*2*3)

   	Copyright (C) 1997-1999, NINTENDO Co,Ltd.	
*/

#include <nusys.h>

/* Use all graphic an N_audio Micro codes */
beginseg
	name	"code"
	flags	BOOT OBJECT
	entry 	nuBoot
	address NU_SPEC_BOOT_ADDR
        stack   NU_SPEC_BOOT_STACK
	include "codesegment.o"
	include "$(ROOT)/usr/lib/PR/n_aspMain.o"
	include "$(ROOT)/usr/lib/PR/rspboot.o"
	include "$(ROOT)/usr/lib/PR/gspF3DEX2.fifo.o"
	include "$(ROOT)/usr/lib/PR/gspL3DEX2.fifo.o"
	include "$(ROOT)/usr/lib/PR/gspF3DEX2.Rej.fifo.o"
        include "$(ROOT)/usr/lib/PR/gspF3DEX2.NoN.fifo.o"
        include "$(ROOT)/usr/lib/PR/gspF3DLX2.Rej.fifo.o"
	include "$(ROOT)/usr/lib/PR/gspS2DEX2.fifo.o"
endseg

beginseg
	name "world_ovl"
	after "code"
	flags OBJECT
	include "build/obj/shadow.o"
	include "build/obj/model_window.o"
	include "build/obj/model_world.o"
	include "build/obj/model_world_col.o"
	include "build/obj/model_world_col2.o"
	include "build/obj/model_world_col3.o"
	include "build/obj/model_world_col4.o"
	include "build/obj/model_world_col_nest.o"
	include "build/obj/model_sky.o"
	include "build/obj/model_distant.o"

	include "build/obj/sprite_numfont.o"
	include "build/obj/sp_hud.o"
endseg

beginseg
	name "bird_ovl"
	after "world_ovl"
	flags OBJECT
	include "build/obj/Bird_Walk.o"
	include "build/obj/Bird_IdlePreen.o"
	include "build/obj/Bird_IdleCaw.o"
	include "build/obj/Bird_Idle.o"
	include "build/obj/Bird_GlideFlap.o"
	include "build/obj/Bird_GlideFast.o"
	include "build/obj/Bird_GlideCrash.o"
	include "build/obj/Bird_Glide.o"
	include "build/obj/Bird_FlyStart.o"
	include "build/obj/Bird_FlyFlap.o"
	include "build/obj/Bird_IdleFall.o"
	include "build/obj/Bird_GlideUTurn.o"
	include "build/obj/model_bird.o"
endseg

beginseg
	name "eagle_ovl"
	after "world_ovl"
	flags OBJECT
	include "build/obj/Eagle_Walk.o"
	include "build/obj/Eagle_IdlePreen.o"
	include "build/obj/Eagle_IdleCaw.o"
	include "build/obj/Eagle_Idle.o"
	include "build/obj/Eagle_GlideFlap.o"
	include "build/obj/Eagle_GlideFast.o"
	include "build/obj/Eagle_GlideCrash.o"
	include "build/obj/Eagle_Glide.o"
	include "build/obj/Eagle_FlyStart.o"
	include "build/obj/Eagle_FlyFlap.o"
	include "build/obj/Eagle_IdleFall.o"
	include "build/obj/Eagle_GlideUTurn.o"
	include "build/obj/model_eagle.o"
endseg

beginseg
	name "countdown_ovl"
	after "bird_ovl"
	flags OBJECT

	include "build/obj/sp_countdown.o"
endseg

beginseg
	name "result_ovl"
	after "bird_ovl"
	flags OBJECT

	include "build/obj/sp_result.o"
endseg

beginseg
	name "ranka_ovl"
	after "result_ovl"
	flags OBJECT

	include "build/obj/sp_ranka.o"
endseg

beginseg
	name "rankb_ovl"
	after "result_ovl"
	flags OBJECT

	include "build/obj/sp_rankb.o"
endseg

beginseg
	name "rankc_ovl"
	after "result_ovl"
	flags OBJECT

	include "build/obj/sp_rankc.o"
endseg

beginseg
	name "rankd_ovl"
	after "result_ovl"
	flags OBJECT

	include "build/obj/sp_rankd.o"
endseg

beginseg
	name "rankf_ovl"
	after "result_ovl"
	flags OBJECT

	include "build/obj/sp_rankf.o"
endseg

beginseg
	name "logo_ovl"
	after "code"
	flags OBJECT
	include "build/obj/sprite_logo.o"
endseg

beginseg
	name "midibank"
	flags RAW
	include "sound/n64st1.wbk"
endseg

beginseg
	name "miditable"
	flags RAW
	include "sound/n64st1.ptr"
endseg

beginseg
	name "seq"
	flags RAW
	include "sound/N64ST1.bin"
endseg

beginseg
	name "sfx"
	flags RAW
	include "sound/N64ST1.bfx"
endseg


beginwave
	name	"bird"
	include	"code"
	include "world_ovl"
	include "bird_ovl"
	include "eagle_ovl"
	include "countdown_ovl"
	include "result_ovl"
	include "ranka_ovl"
	include "rankb_ovl"
	include "rankc_ovl"
	include "rankd_ovl"
	include "rankf_ovl"
	include "logo_ovl"
	include "miditable"
	include "midibank"
	include "seq"
	include "sfx"
endwave