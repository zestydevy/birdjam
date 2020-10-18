
#include "include/letters.h"

/*
 * ROM spec file
 */
beginseg
	name "code"
	flags BOOT OBJECT
	entry boot
	stack gBootStack + STACKSIZE
	include "codesegment.o"
	include "$(ROOT)/usr/lib/PR/rspboot.o"
	include "$(ROOT)/usr/lib/PR/gspF3DEX2.xbus.o"
	include "$(ROOT)/usr/lib/PR/gspF3DEX2.fifo.o"
endseg

beginseg
        name "zbuffer"
        flags OBJECT
        address 0x80118000
        include "build/obj/zbuffer.o"
endseg

beginseg
	name "cfb"
	flags OBJECT
	address 0x8013d800
	include "build/obj/cfb.o"
endseg

beginseg
	name "static"
	flags OBJECT
	number STATIC_SEGMENT
	include "build/obj/static.o"
endseg

beginwave
	name "bird"
	include "code"
	include "static"
	include "cfb"
	include "zbuffer"
endwave
