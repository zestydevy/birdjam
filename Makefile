include $(ROOT)/usr/include/make/PRdefs

PROJECT = bird

NUSYSINCDIR  = /usr/include/n64/nusys
NUSYSLIBDIR  = /usr/lib/n64/nusys

LIB = $(ROOT)/usr/lib
LPR = $(LIB)/PR
INC = $(ROOT)/usr/include

NUAUDIOLIB = -lnualstl_n_d -ln_mus_d -ln_audio_sc

OPTIMIZER       = -O1
LCDEFS          = -DNDEBUG -DF3DEX_GBI_2
N64LIB          = -lultra_rom
CFLAGS := $(CFLAGS) -G 0 -I. -Iinclude -I$(NUSYSINCDIR) -I$(ROOT)/usr/include/PR
CXXFLAGS := $(CXXFLAGS) -DNDEBUG -DF3DEX_GBI_2 -G 0 -std=c++20 -fno-builtin -fno-exceptions -fno-rtti -Iinclude -I$(NUSYSINCDIR) -I$(ROOT)/usr/include/PR

APP =		$(PROJECT).out

TARGETS =	$(PROJECT).n64

HFILES  := $(wildcard include/*.h) $(wildcard models/*.h) $(wildcard models/*/*.h) $(wildcard models/objects/*/*.h)

CODEFILES   := $(wildcard src/*.c)
CXXFILES    := $(wildcard src/*.cpp)
DATAFILES   := $(wildcard data/*.c)
MODELFILES  := $(wildcard models/*/*.c)
MODELOFILES := $(wildcard models/objects/*/*.c)
LIBFILES    := $(wildcard lib/*.o)

OBJPATH		= 	./build/obj

CODEOBJECTS =	$(CODEFILES:.c=.o) $(CXXFILES:.cpp=.o) $(MODELFILES:.c=.o) 
CODEOBJNAME =   $(notdir $(CODEOBJECTS))
CODEOBJPATH =   $(addprefix $(OBJPATH)/,$(CODEOBJNAME))

DATAOBJECTS =	$(DATAFILES:.c=.o) $(MODELOFILES:.c=.o)
DATAOBJNAME =   $(notdir $(DATAOBJECTS))
DATAOBJPATH =   $(addprefix $(OBJPATH),$(DATAOBJECTS))

CODESEGMENT =	codesegment.o

OBJECTS =	$(TEXHFILES) $(CODESEGMENT) $(DATAOBJECTS)

LCINCS =	-I. -I$(NUSYSINCDIR) -I$(ROOT)/usr/include/PR
LCOPTS =	-G 0
LDIRT  =	$(APP) $(TARGETS)

LDFLAGS =	$(MKDEPOPT) -L$(LIB) -L$(NUSYSLIBDIR) $(NUAUDIOLIB) -lnusys_d -lultra_d -L$(N64_LIBGCCDIR) -lgcc  -lnustd

default: $(TARGETS)

include $(COMMONRULES)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $(OBJPATH)/$(notdir $@) $<
	
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $(OBJPATH)/$(notdir $@) $<

$(CODESEGMENT):	$(TEXHFILES) $(CODEOBJECTS)
		$(LD) -o $(CODESEGMENT) -r $(CODEOBJPATH) $(LIBFILES) $(LDFLAGS) -Map=$(PROJECT).map

$(TARGETS) $(APP):      spec $(OBJECTS)
	$(MAKEROM) spec -I$(NUSYSINCDIR) -r $(TARGETS) -m -s 10 -e $(APP)
	makemask $(TARGETS)
	@mv $(PROJECT).map codesegment.o a.out $(APP) $(TARGETS) "./build"
	mono ~/Desktop/tool/n64fix_6102.exe ./build/bird.n64
	wine ~/Desktop/tool/rn64crc -u ./build/bird.n64
	sudo ~/Desktop/tool/64d -l ./build/bird.n64 -c 6102 -z
