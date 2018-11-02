ifeq ($(plat),B2)
export ARCH = B2
else ifeq ($(plat),hi3516a)
export ARCH = hi3516a
else ifeq ($(plat),hi3519)
export ARCH = hi3519
else ifeq ($(plat),hi3516d)
export ARCH = hi3516d
else ifeq ($(plat),hi3516cv300)
export ARCH = hi3516cv300
else ifeq ($(plat),i686)
export ARCH = i686
else ifeq ($(plat),i386)
export ARCH = i386
endif

ifeq ($(ARCH),)
export ARCH = i686
endif

ifeq ($(ARCH),B2)
export PLATFORM = arm-hisiv500-linux
export CROSS_COMPILE = arm-hisiv500-linux-
else ifeq ($(ARCH),hi3516a)
export PLATFORM = arm-hisiv400-linux
export CROSS_COMPILE = arm-hisiv400-linux-
else ifeq ($(ARCH),hi3516d)
export PLATFORM = arm-hisiv400-linux
export CROSS_COMPILE = arm-hisiv400-linux-
else ifeq ($(ARCH),hi3516cv300)
export PLATFORM = arm-hi3516cv300-linux
export CROSS_COMPILE = arm-hi3516cv300-linux-
else ifeq ($(ARCH),hi3519)
export PLATFORM = arm-hisiv600-linux
export CROSS_COMPILE = arm-hisiv600-linux-
else ifeq ($(ARCH),i686)
export PLATFORM =
export CROSS_COMPILE = 
export CFLAGS +=
else ifeq ($(ARCH),i386)
export PLATFORM =
export CROSS_COMPILE = 
export CFLAGS += -m32
endif

#编译选项
#export CFLAGS += -Wall -O2 -g -Wno-deprecated -fpic -D_FILE_OFFSET_BITS=64 
#export CCFLAGS += $(CFLAGS) -std=c++11
export LDFLAGS +=
export IFLAGS += $(foreach dir, $(DEPEND_HEAD_FILE_PATH), -I$(dir))


