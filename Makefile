#compile main.cpp:
TARGET = Epic_Sathe
OBJS = source/main.o

#To build for custom firmware:
BUILD_PRX = 1
PSP_FW_VERSION=371

#set FLAGS
CFLAGS = -G2 -Wall -O2 -g
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)
LIBDIR =
LDFLAGS =

#linked libraries
MYLIBS= -lpspnet_adhocmatching -lpspnet_adhoc -lpspnet_adhocctl 
STDLIBS= -losl -lpng -lz -lpsphprm -lpspsdk -lpspctrl -lpspumd -lpsprtc -lpsppower -lpspgu \
-lpspgum -lpspaudiolib -lpspaudio -lpsphttp -lpspssl -lpspwlan -lm -ljpeg
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
