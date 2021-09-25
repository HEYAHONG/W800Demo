

set(CMAKE_C_FLAGS " ${CMAKE_C_FLAGS} -Wall     -DTLS_CONFIG_CPU_XT804=1   -DGCC_COMPILE=1   -O2 -g -mcpu=ck804ef     -std=gnu99     -mhard-float   -fdata-sections -ffunction-sections ")
set(CMAKE_CXX_FLAGS " ${CMAKE_CXX_FLAGS} -Wall  -DTLS_CONFIG_CPU_XT804=1  -DGCC_COMPILE=1    -O2 -g -mcpu=ck804ef     -std=c++11     -mhard-float          -fdata-sections      -ffunction-sections" )
                 
set(CMAKE_ASM_FLAGS " ${CMAKE_ASM_FLAGS} -Wall   -DTLS_CONFIG_CPU_XT804=1 -DGCC_COMPILE=1     -O2 -mcpu=ck804ef     -mhard-float   -fdata-sections   -ffunction-sections    " )


set(CMAKE_EXE_LINKER_FLAGS " ${CMAKE_EXE_LINKER_FLAGS}  \
		-mcpu=ck804ef \
    	-nostartfiles \
    	-mhard-float \
    	-lm  ")


set(BUILD_SHARED_LIBS OFF)

