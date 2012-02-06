#compile main.cpp and load.o and save.o logo.png:
TARGET = Epic_Sathe
OBJS = source/main.o

#To build for custom firmware:
BUILD_PRX = 1
PSP_FW_VERSION=371

#set CFLAGS to -G0 (do not set to -G4 or -G2)
CFLAGS = -G0 -Wall -O2 -g
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)
LIBDIR =
LDFLAGS =

#linked libraries
STDLIBS= -losl -lpng -lz \
         -lpsphprm -lpspsdk -lpspctrl -lpspumd -lpsprtc -lpsppower -lpspgu -lpspgum  -lpspaudiolib -lpspaudio -lpsphttp -lpspssl -lpspwlan \
         -lpspnet_adhocmatching -lpspnet_adhoc -lpspnet_adhocctl -lm -ljpeg
LIBS=$(STDLIBS) $(MYLIBS)

#OUTPUT FILE: EBOOT.PBP
#EBOOT TITLE: Epic Sathe
#EBOOT ICON:  ICON0.png
#EBOOT PIC1:  PIC1.png
#EBOOT ATR3:  SND0.at3
EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = Epic Sathe
PSP_EBOOT_ICON = resource/ICON0.png
PSP_EBOOT_PIC1 = resource/PIC1.png
PSP_EBOOT_SND0 = resource/SND0.at3

#locate build.mak
PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak
	
#V@ughn
