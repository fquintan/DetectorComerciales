IS_WINDOWS    := n
IS_DEBUG      := y
USE_PKGCONFIG := y

CFLAGS   += -Wall -Wextra -pedantic -Wno-unused-function 

LDFLAGS  += -lpthread -lm

ifeq ($(IS_WINDOWS),y)

	SUFFIX_EXE  := .exe
	
	ifeq ($(IS_DEBUG),y)
		CFLAGS += -O0 -ggdb
	else
		CFLAGS += -O2
	endif
	
else
	SUFFIX_EXE  := 
	
	ifeq ($(IS_DEBUG),y)
		CFLAGS += -O0 -ggdb
	else
		CFLAGS += -O3
	endif
endif

ifeq ($(USE_PKGCONFIG),y)

	ifneq ($(shell pkg-config --exists opencv && echo ok),ok)
		$(warning pkg-config can't find required library "opencv")
	endif
	
	CFLAGS  += $(shell pkg-config --cflags opencv)
	LDFLAGS += $(shell pkg-config --libs   opencv)

else

	OPENCV_HEADERS  := C:\...\opencv-2.4.9\include
	OPENCV_LIBS     := C:\...\opencv-2.4.9\...\bin
	CFLAGS  += -I$(OPENCV_HEADERS)
	LDFLAGS += -L$(OPENCV_LIBS) -lopencv_core249 -lopencv_highgui249 -lopencv_imgproc249
	
endif

CFLAGS  += $(shell pkg-config --cflags opencv)
LDFLAGS += $(shell pkg-config --libs   opencv)


########## rules ##########

SOURCE_DIR := src
SOURCE_CPP := $(SOURCE_DIR)/*.cpp

BUILD_DIR := build
EXE_CPP   := $(BUILD_DIR)/Detector$(SUFFIX_EXE)

.PHONY: all clean

all: $(EXE_CPP)
	
$(EXE_CPP): $(SOURCE_CPP) 
	mkdir -p $(BUILD_DIR)
	g++ -std=c++0x $(CFLAGS) -o $(EXE_CPP) $(SOURCE_CPP) $(LDFLAGS)

	
clean:
	rm -rf $(BUILD_DIR)
