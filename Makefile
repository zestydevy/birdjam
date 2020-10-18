
include $(ROOT)/usr/include/make/PRdefs

PROJECT = bird

FINAL = YES
ifeq ($(FINAL), YES)
OPTIMIZER       = -O1
LCDEFS          = -DNDEBUG -D_FINALROM -DF3DEX_GBI_2
N64LIB          = -lultra_rom
CFLAGS := $(CFLAGS) -std=gnu90 -Iinclude -G 0
CXXFLAGS := $(CXXFLAGS) -std=c++17 -Iinclude -G 0 -fno-unroll-loops -ffast-math -fno-exceptions -fno-rtti
else
OPTIMIZER       = -g -std=gnu90
LCDEFS          = -DDEBUG -DF3DEX_GBI_2
N64LIB          = -lultra_d
endif

APP =		$(PROJECT).out

TARGETS =	$(PROJECT).n64

HFILES  := $(wildcard include/*.h)

CODEFILES   := $(wildcard src/*.c)
CXXFILES    := $(wildcard src/*.cpp)
DATAFILES   := $(wildcard data/*.c)

CODEOBJECTS =	$(CODEFILES:.c=.o) $(CXXFILES:.cpp=.o)
CODEOBJNAME =   $(notdir $(CODEOBJECTS))
CODEOBJPATH =   $(addprefix build/obj/,$(CODEOBJNAME))

DATAOBJECTS =	$(DATAFILES:.c=.o)
DATAOBJNAME =   $(notdir $(DATAOBJECTS))
DATAOBJPATH =   $(addprefix build/obj/,$(DATAOBJECTS))

CODESEGMENT =	codesegment.o

OBJECTS =	$(TEXHFILES) $(CODESEGMENT) $(DATAOBJECTS)

#LCINCS =	-I./include
LCOPTS =	-G 0
LDIRT  =	$(APP) *.so

LDFLAGS =	$(MKDEPOPT)  -L$(ROOT)/usr/lib -L$(ROOT)/usr/lib/PR $(N64LIB) -L$(N64_LIBGCCDIR) -lgcc 

default:	$(TARGETS)

include $(COMMONRULES)

$(CODESEGMENT):	$(TEXHFILES) $(CODEOBJECTS)
		@mkdir -p "build/obj"
		@mv $(CODEOBJECTS) "build/obj/"
		$(LD) -o $(CODESEGMENT) -r $(CODEOBJPATH) $(LDFLAGS)

ifeq ($(FINAL), YES)
$(TARGETS) $(APP):      spec $(OBJECTS)
	@mv $(DATAOBJECTS) "build/obj/"
	$(MAKEROM) -s 9 -r $(TARGETS) -e $(APP) spec
	makemask $(TARGETS)
	@mv codesegment.o a.out $(APP) $(TARGETS) "./build"
else
$(TARGETS) $(APP):      spec $(OBJECTS)
	$(MAKEROM) -r $(TARGETS) -e $(APP) spec
endif


