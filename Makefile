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

# CFLAGS  += $(shell pkg-config --cflags opencv)
# LDFLAGS += $(shell pkg-config --libs   opencv)


########## rules ##########

SOURCE_DIR := src
SOURCE_CPP := $(SOURCE_DIR)/VideoContentExtractor.cpp
# SOURCE_CPP := $(SOURCE_DIR)/VideoContentExtractor.cpp
CC=g++
SOURCES=BruteForceNNF.cpp DescriptorComparator.cpp Descriptor.cpp DescriptorExtractor.cpp Detector.cpp EdgeHistogramExtractor.cpp EuclideanComparator.cpp ExtractorFactory.cpp GrayHistogramExtractor.cpp ManhattanComparator.cpp NearestNeighborFinder.cpp Utils.cpp VideoContentExtractor.cpp

BUILD_DIR := build
EXE_CPP   := $(BUILD_DIR)/Detector$(SUFFIX_EXE)
# CPP_FILES := $(wildcard src/*.cpp)
CPP_FILES=BruteForceNNF.cpp DescriptorComparator.cpp Descriptor.cpp DescriptorExtractor.cpp EdgeHistogramExtractor.cpp EuclideanComparator.cpp ExtractorFactory.cpp GrayHistogramExtractor.cpp ManhattanComparator.cpp NearestNeighborFinder.cpp Utils.cpp
EXTRACTOR_SRC=VideoContentExtractor.cpp
DETECTOR_SRC=Detector.cpp

OBJ_FILES := $(addprefix obj/,$(notdir $(CPP_FILES:.cpp=.o)))
EXTRACTOR_OBJ := $(addprefix obj/,$(notdir $(EXTRACTOR_SRC:.cpp=.o)))
DETECTOR_OBJ := $(addprefix obj/,$(notdir $(DETECTOR_SRC:.cpp=.o)))


all: detector extractor

# all: $(SOURCES) $(EXECUTABLE)    
detector: $(OBJ_FILES) $(DETECTOR_OBJ)
	g++ -std=c++0x $(CFLAGS) -o $@ $^ $(LDFLAGS) 

extractor: $(OBJ_FILES) $(EXTRACTOR_OBJ) 
	g++ -std=c++0x $(CFLAGS) -o $@ $^ $(LDFLAGS) 
	# g++ -std=c++0x $(CFLAGS) -o $(EXE_CPP) $(SOURCE_CPP) $(LDFLAGS)

obj/%.o: src/%.cpp
	g++ -std=c++0x $(CFLAGS) -c -o $@ $<

clean:
	rm obj/* extractor detector