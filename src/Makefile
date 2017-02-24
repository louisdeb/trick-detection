DEFINES+=PROJECT_CONF_H=\"project-conf.h\"
CONTIKI_PROJECT = sounds
PROJECT_SOURCEFILES += mpu_reader.c

all: $(CONTIKI_PROJECT)

TARGET=srf06-cc26xx
BOARD=sensortag/cc2650
CPU_FAMILY=cc26xx
CONTIKI_WITH_RIME = 1

CONTIKI = ../contiki
include $(CONTIKI)/Makefile.include