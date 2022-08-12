

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_C_COMPILER csky-elfabiv2-gcc)
set(CMAKE_CXX_COMPILER csky-elfabiv2-g++)
set(CMAKE_ADDR2LINE csky-elfabiv2-addr2line)
set(CMAKE_AR csky-elfabiv2-ar)
set(CMAKE_RANLIB csky-elfabiv2-ranlib)
set(CMAKE_CXX_COMPILER_AR csky-elfabiv2-ar)
set(CMAKE_CXX_COMPILER_RANLIB csky-elfabiv2-ranlib)
set(CMAKE_C_COMPILER_AR csky-elfabiv2-ar)
set(CMAKE_C_COMPILER_RANLIB csky-elfabiv2-ranlib)
set(CMAKE_Fortran_COMPILER csky-elfabiv2-gfortan)
set(CMAKE_OBJCOPY csky-elfabiv2-objcopy)
set(CMAKE_OBJDUMP csky-elfabiv2-objdump)
set(CMAKE_RC_COMPILER csky-elfabiv2-windres)
set(CMAKE_READELF csky-elfabiv2-readelf)
set(CMAKE_STRIP csky-elfabiv2-strip)
set(CMAKE_LINKER csky-elfabiv2-ld)

set(CMAKE_EXECUTABLE_SUFFIX_ASM .elf)
set(CMAKE_EXECUTABLE_SUFFIX_C .elf)
set(CMAKE_EXECUTABLE_SUFFIX_CXX .elf)

execute_process(COMMAND ${CMAKE_C_COMPILER} -dumpversion OUTPUT_VARIABLE gcc_version OUTPUT_STRIP_TRAILING_WHITESPACE)

set(CMAKE_C_COMPILER_FORCED TRUE)
set(CMAKE_CXX_COMPILER_FORCED TRUE)
