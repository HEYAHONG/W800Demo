
cmake_minimum_required(VERSION 3.10)

include(${CMAKE_CURRENT_SOURCE_DIR}/main.cmake)

if(NOT DEFINED PROJECT_NAME)
	set(PROJECT_NAME w800)
endif()

#设置编译工具链及选项
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/toolchain.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/option.cmake)

project(${PROJECT_NAME} C CXX ASM)

#设置SDK所在目录
set(SDK_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/wm_sdk_w800)

#包含SDK相关cmake（提供变量SDK_INCLUDE_DIRS(头文件目录) SDK_LIBS(库列表) SDK_PRECOMPILED_LIBS(预编译库列表)）
include(${CMAKE_SOURCE_DIR}/cmake/sdk/common.cmake)


#添加SimpleMQTTGateWayStack库
add_subdirectory(lib/SimpleMQTTGateWayStack/lib)

#添加MQTT移植
file(GLOB  PAHO_PORT_C_FILES lib/MQTT/*.c)
list(APPEND PAHO_SRCS
${PAHO_MQTTPACKET_C_FILES}
${PAHO_PORT_C_FILES}
)
add_library(PAHO_MQTT STATIC ${PAHO_SRCS})
target_include_directories(PAHO_MQTT
PUBLIC lib/MQTT/
PRIVATE ${SDK_INCLUDE_DIRS}
)
target_compile_definitions(PAHO_MQTT
PUBLIC MQTTCLIENT_PLATFORM_HEADER=MQTTFreeRTOS_LWIP.h MQTT_TASK
)
target_link_libraries(PAHO_MQTT SMGS)
list(APPEND LIBS
PAHO_MQTT
)


if(NOT DEFINED MAIN_SRCS)
	set(MAIN_SRCS ${SDK_ROOT}/app/main.c )
endif()




list(APPEND MAIN_SRCS
)

#Kconfig(使用Kconfig进行配置)
option(USE_KCONFIG "use kconfig" OFF)

if(${USE_KCONFIG})

    add_definitions(" -DUSE_KCONFIG=1 ")

    find_program(PYTHON
               NAMES python3 python python2
               REQUIRED
               )
    message("python path: ${PYTHON}")
    #安装依赖
    execute_process(COMMAND ${PYTHON} -m pip install -r  ${CMAKE_CURRENT_SOURCE_DIR}/requirement.txt
                      RESULT_VARIABLE PYTHON_INSTALL_RESULT)
    if(PYTHON_INSTALL_RESULT EQUAL 0)
    message("install from requirement.txt success")
    else()
    message(FATAL_ERROR "install from requirement.txt error")
    endif()

    #生成config.h
    add_custom_command(OUTPUT config.h
                    COMMAND ${PYTHON} -m genconfig --header-path config.h
                    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                    )


    if(CMAKE_HOST_WIN32)
        #menuconfig 目标(windows)
        add_custom_target(menuconfig cmd.exe /C start cmd.exe /c ${PYTHON} -m menuconfig
                  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                  USES_TERMINAL
                  )
    else()
        #menuconfig 目标(非windows)
        add_custom_target(menuconfig  ${PYTHON} -m menuconfig
                  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                  USES_TERMINAL
                  )
    endif()

    #将config.h添加至MAIN_SRCS
    list(APPEND MAIN_SRCS
         config.h )


endif()


if(NOT DEFINED MAIN_INCLUDE_DIRS)
	set(MAIN_INCLUDE_DIRS ./)
endif()

list(APPEND  MAIN_INCLUDE_DIRS  ${SDK_INCLUDE_DIRS})




#设置头文件
include_directories(${MAIN_INCLUDE_DIRS})


#添加可执行文件
add_executable(${PROJECT_NAME} ${MAIN_SRCS})
target_link_libraries(${PROJECT_NAME}  ${SDK_LIBS}  "-Wl,--whole-archive"  ${SDK_PRECOMPILED_LIBS} "-Wl,--no-whole-archive" ${LIBS} )

#生成bin文件
add_custom_target(${PROJECT_NAME}.bin ALL
				 COMMAND ${CMAKE_OBJCOPY} --output-target=binary  ${PROJECT_NAME}.elf ${PROJECT_NAME}.bin
				 DEPENDS ${PROJECT_NAME}
				 )

#准备wm_tool
find_program(WM_TOOL
               NAMES wm_tool
               PATHS ${SDK_ROOT}/tools/w800/ ${CMAKE_BINARY_DIR}/
               NO_CACHE
               )
if(NOT EXISTS ${WM_TOOL})
    message("wm_tool is not found,try to compile!")
    #使用C编译器编译
    find_program(CC NAMES cc gcc REQUIRED)
    message("cc path: ${CC}")
    execute_process(COMMAND ${CC} -pthread  ${SDK_ROOT}/tools/w800/wm_tool.c -lz  -o ${CMAKE_BINARY_DIR}/wm_tool)
    find_program(WM_TOOL
               NAMES wm_tool
               PATHS  ${CMAKE_BINARY_DIR}/ ${SDK_ROOT}/tools/w800/
               NO_CACHE
               REQUIRED
               )
    message("wm_tool path: ${WM_TOOL}" )
else()
    message("wm_tool path: ${WM_TOOL}" )
endif()


set(GREATE_IMG_STEP1_FLAGS  -b ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.bin  -fc 0 -it 1 -ih 80D0000 -ra 80D0400 -ua 8010000 -nh 0 -un 0 -vs G01.00.02  -o ${PROJECT_NAME})
set(GREATE_IMG_STEP2_FLAGS  -b ${SDK_ROOT}/tools/w800/w800_secboot.bin -fc 0 -it 0 -ih 8002000 -ra 8002400 -ua 8010000 -nh 80D0000 -un 0 -o w800_secboot)
set(GREATE_IMG_STEP3_FLAGS  -b ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.img  -fc 1 -it 1 -ih 80D0000 -ra 80D0400 -ua 8010000 -nh 0 -un 0 -vs G01.00.02 -o ${PROJECT_NAME})
set(GREATE_IMG_STEP4_FLAGS  -b ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.img  -sb  w800_secboot.img -fc 1 -it 1 -ih 80D0000 -ra 80D0400 -ua 8010000 -nh 0 -un 0 -vs G01.00.02  -o ${PROJECT_NAME})

#生成其它镜像文件（包括fls文件）
add_custom_target(${PROJECT_NAME}.fls ALL
				 COMMAND ${WM_TOOL} ${GREATE_IMG_STEP1_FLAGS}
				 COMMAND ${WM_TOOL} ${GREATE_IMG_STEP2_FLAGS}
				 COMMAND ${WM_TOOL} ${GREATE_IMG_STEP3_FLAGS}
				 COMMAND ${WM_TOOL} ${GREATE_IMG_STEP4_FLAGS}
				 DEPENDS ${PROJECT_NAME}.bin
				 )


##默认的烧录串口
##环境变量
if(NOT DEFINED ENV{WM_PORT})
    set(ENV{WM_PORT} ttyUSB0)
endif()

#flash目标
add_custom_target(flash
                   COMMAND ${WM_TOOL} -c $ENV{WM_PORT} -eo all -dl ${PROJECT_NAME}.fls
                   DEPENDS ${PROJECT_NAME}.fls
                  )
#run目标
add_custom_target(run
                   COMMAND ${WM_TOOL} -c $ENV{WM_PORT} -eo all -dl ${PROJECT_NAME}.fls -sl str -ws 115200
                   DEPENDS ${PROJECT_NAME}.fls
                  )

