APPSOURCES = xf_mean_shift_tb.cpp 
EXECUTABLE = mean_shift.elf
VERBOSE = #-verbose
PLATFORM = <path-to-reVISION-platform>
SDSCC_FLAGS = -sds-pf ${PLATFORM} \
-sds-hw "xFMeanShift<1080,1920,250,250,10,4,7,1>" xf_mean_shift_tb.cpp -files ./include/imgproc/xf_mean_shift.hpp -clkid 2 -sds-end -dmclkid 2


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
	${RM} -rf _sds sd_card ${EXECUTABLE}.bit ${EXECUTABLE} ${OBJECTS} -rf example -rf src
copy:
	/bin/cp -prf ${XLNX_SRC_PATH}/meanshifttracking/example .
	/bin/cp -prf ${XLNX_SRC_PATH}/meanshifttracking/src .
