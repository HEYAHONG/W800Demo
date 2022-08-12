#设置工程名
set(PROJECT_NAME W800Demo)

file(GLOB MAIN_C_CPP_SOURCES *.c *.h *.cpp *.hpp appstack/*.c appstack/*.cpp appstack/*.h appstack/*.hpp )
#设置源文件
list(APPEND MAIN_SRCS
${MAIN_C_CPP_SOURCES}
)

#设置头文件
list(APPEND MAIN_INCLUDE_DIRS
./
appstack
)
