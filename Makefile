TARGET = eboot

OBJS = main.o

#LIBS = -lpspnet_apctl -lpsphttp -lpspnet_resolver -lpspnet_inet -lpspnet -lpsputility -lpspsdk

LIBS += \
	-lpspgu \
    -lpspnet \
    -lpspnet_inet \
    -lpspnet_apctl \
    -lpspnet_resolver \
    -lpsphttp \
    -lpsputility \
    -lpspnet_adhoc \
    -lpspnet_adhocctl \
    -lpspnet_adhocmatching \
	-lpspkubridge


PSP_EBOOT_TITLE = 661 OFW Downloader


EXTRA_TARGETS = EBOOT.PBP

PSPSDK=$(shell psp-config -p)
include $(PSPSDK)/lib/build.mak
