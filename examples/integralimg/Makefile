APPSOURCES = xf_integral_image_tb.cpp 
EXECUTABLE = integralimg.elf
VERBOSE = #-verbose
PLATFORM = <path-to-reVISION-platform>
SDSCC_FLAGS = -sds-pf ${PLATFORM} -std=c++11 ${VERBOSE} \
-sds-hw "xFIntegralImage<0,3,1080,1920,1>" xf_integral_image_tb.cpp -files ./include/imgproc/xf_integral_image.hpp -clkid 2 -sds-end -dmclkid 2
#xFIntegralImage<XF_8UC1,XF_32UC1,HEIGHT, WIDTH,XF_NPPC1>

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
	/bin/cp -prf ${XLNX_SRC_PATH}/integralimg/example .
	/bin/cp -prf ${XLNX_SRC_PATH}/integralimg/src .
