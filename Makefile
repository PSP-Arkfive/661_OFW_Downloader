TARGET = eboot

OBJS = main.o

CFLAGS = -O0 -G0 -g -Wall -DDEBUG
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti -nostartfiles
ASFLAGS = $(CFLAGS)


LIBS += \
	-lpsphttp \
	-lpspdownloader_debug \
	-lpspkubridge


PSP_EBOOT_TITLE = 661 OFW Downloader


PSP_FW_VERSION=661


BUILD_PRX = 1


EXTRA_TARGETS = EBOOT.PBP

PSPSDK=$(shell psp-config -p)
include $(PSPSDK)/lib/build.mak
