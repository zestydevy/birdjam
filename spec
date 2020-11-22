/*
	ROM spec file

	Main memory map

  	0x80000000  exception vectors, ...
  	0x80000400  zbuffer (size 320*240*2)
  	0x80025c00  codesegment
	      :  
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
	name "object_models"
	flags OBJECT
	include "build/obj/model_balloon.o"
	include "build/obj/model_apple.o"
	include "build/obj/model_balloondeflated.o"
	include "build/obj/model_basket.o"
	include "build/obj/model_beehive.o"
	include "build/obj/model_beer.o"
	include "build/obj/model_bills.o"
	include "build/obj/model_card.o"
	include "build/obj/model_chair.o"
	include "build/obj/model_flower.o"
	include "build/obj/model_lunchtable.o"
	include "build/obj/model_melon.o"
	include "build/obj/model_necklace.o"
	include "build/obj/model_noodle.o"
	include "build/obj/model_ring.o"
	include "build/obj/model_soccer.o"
	include "build/obj/model_stick.o"
	include "build/obj/model_table.o"
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
	include "object_models"
	include "miditable"
	include "midibank"
	include "seq"
	include "sfx"
endwave
