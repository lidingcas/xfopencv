APPSOURCES = xf_custom_convolution_tb.cpp 
EXECUTABLE = customconv.elf
VERBOSE = #-verbose
PLATFORM = <path-to-reVISION-platform>
SDSCC_FLAGS = -sds-pf ${PLATFORM} -std=c++11 ${VERBOSE} \
-sds-hw "xFfilter2D<0,3,3,0,0,1080,1920,1>" xf_custom_convolution_tb.cpp -files ./include/imgproc/xf_custom_convolution.hpp -clkid 2 -sds-end -dmclkid 2
#xFfilter2D<XF_BORDER_CONSTANT,FILTER_WIDTH,FILTER_HEIGHT,XF_8UC1,XF_16SC1,HEIGHT, WIDTH,XF_NPPC1>

CC = sds++ ${SDSCC_FLAGS}

IDIRS = -I. -I${SYSROOT}/usr/include -I ./include

LDIRS = --sysroot=${SYSROOT} -L=/lib -L=/usr/lib -Wl,-rpath-link=${SYSROOT}/lib,-rpath-link=${SYSROOT}/usr/lib

LLIBS = -lopencv_imgcodecs -lopencv_core -llzma -ltiff -lpng16 -lz -ljpeg -lopencv_imgproc -ldl -lrt -lwebp -lopencv_features2d -lopencv_flann 
#LLIBS = -lopencv_core -lopencv_imgproc -lopencv_imgcodecs 
#OLEVEL = -ggdb
CFLAGS = -O3 -Wall ${OLEVEL} -c ${IDIRS} -DHLS_NO_XIL_FPO_LIB
LFLAGS = ${OLEVEL} ${LDIRS} ${LLIBS}

SOURCES := $(patsubst %,./%,$(APPSOURCES))
OBJECTS := $(APPSOURCES:.cpp=.o)
DEPS := $(OBJECTS:.o=.d)
.PHONY: all
all: ${EXECUTABLE}
${EXECUTABLE}: ${OBJECTS}
	${CC} ${OBJECTS} ${LFLAGS} -o $@
-include ${DEPS}
%.o: %.cpp
	${CC} ${CFLAGS} $< -o $@
clean:
	${RM} ${EXECUTABLE} ${OBJECTS}
ultraclean: clean
	${RM} -rf _sds sd_card ${EXECUTABLE}.bit ${EXECUTABLE} ${OBJECTS}
copy:
	/bin/cp -prf ${XLNX_SRC_PATH}/customconv/example .
	/bin/cp -prf ${XLNX_SRC_PATH}/customconv/src .
