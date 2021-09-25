

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_C_COMPILER csky-abiv2-elf-gcc)
set(CMAKE_CXX_COMPILER csky-abiv2-elf-g++)
set(CMAKE_ADDR2LINE csky-abiv2-elf-addr2line)
set(CMAKE_AR csky-abiv2-elf-ar)
set(CMAKE_RANLIB csky-abiv2-elf-ranlib)
set(CMAKE_CXX_COMPILER_AR csky-abiv2-elf-ar)
set(CMAKE_CXX_COMPILER_RANLIB csky-abiv2-elf-ranlib)
set(CMAKE_C_COMPILER_AR csky-abiv2-elf-ar)
set(CMAKE_C_COMPILER_RANLIB csky-abiv2-elf-ranlib)
set(CMAKE_Fortran_COMPILER csky-abiv2-elf-gfortan)
set(CMAKE_OBJCOPY csky-abiv2-elf-objcopy)
set(CMAKE_OBJDUMP csky-abiv2-elf-objdump)
set(CMAKE_RC_COMPILER csky-abiv2-elf-windres)
set(CMAKE_READELF csky-abiv2-elf-readelf)
set(CMAKE_STRIP csky-abiv2-elf-strip)
set(CMAKE_LINKER csky-abiv2-elf-ld)

set(CMAKE_EXECUTABLE_SUFFIX_ASM .elf)
set(CMAKE_EXECUTABLE_SUFFIX_C .elf)
set(CMAKE_EXECUTABLE_SUFFIX_CXX .elf)

execute_process(COMMAND ${CMAKE_C_COMPILER} -dumpversion OUTPUT_VARIABLE gcc_version OUTPUT_STRIP_TRAILING_WHITESPACE)

