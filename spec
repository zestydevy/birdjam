/*
	ROM spec file

	Main memory map

  	0x80000000  exception vectors, ...
  	0x80000400  zbuffer (size 320*240*2)
  	0x80025c00  codesegment
	      :  
  	0x8028F800  Game Heap
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
	name "bird_ovl"
	after "code"
	flags OBJECT
	include "build/obj/model_bird.o"
	include "build/obj/Bird_Walk.o"
	include "build/obj/Bird_IdlePreen.o"
	include "build/obj/Bird_IdleCaw.o"
	include "build/obj/Bird_Idle.o"
	include "build/obj/Bird_GlideFlap.o"
	include "build/obj/Bird_GlideFast.o"
	include "build/obj/Bird_GlideCrash.o"
	include "build/obj/Bird_GlideCaw.o"
	include "build/obj/Bird_Glide.o"
	include "build/obj/Bird_FlyStart.o"
	include "build/obj/Bird_FlyFlap.o"
	include "build/obj/Bird_IdleFall.o"

	include "build/obj/shadow.o"
	include "build/obj/model_worldstress.o"
	include "build/obj/model_world.o"
	include "build/obj/model_world_col.o"
	include "build/obj/model_world_col2.o"
	include "build/obj/model_world_col3.o"
	include "build/obj/model_world_col_nest.o"
	include "build/obj/model_sky.o"
	include "build/obj/model_distant.o"
	include "build/obj/col_worldstress.o"
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
	include "bird_ovl"
	include "logo_ovl"
	include "miditable"
	include "midibank"
	include "seq"
	include "sfx"
endwave