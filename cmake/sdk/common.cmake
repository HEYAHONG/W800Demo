#设置链接脚本
set(CMAKE_EXE_LINKER_FLAGS " ${CMAKE_EXE_LINKER_FLAGS} \
		-T${SDK_ROOT}/ld/w800/gcc_csky.ld \
        -Wl,-ckmap=${PROJECT_NAME}.map -Wl,--gc-sections -Wl,-zmax-page-size=1024 " )



#SDK头文件
list(APPEND SDK_INCLUDE_DIRS
${SDK_ROOT}/include
${SDK_ROOT}/include/app
${SDK_ROOT}/include/arch/xt804
${SDK_ROOT}/include/arch/xt804/csi_core
${SDK_ROOT}/include/arch/xt804/csi_dsp
${SDK_ROOT}/include/driver
${SDK_ROOT}/include/net
${SDK_ROOT}/include/os
${SDK_ROOT}/include/platform
${SDK_ROOT}/include/wifi
${SDK_ROOT}/include/bt

)
file(GLOB_RECURSE SDK_HEADERS
${SDK_ROOT}/include/*.h
)
list(APPEND SDK_SRCS
${SDK_HEADERS}
)

option(BUILD_SDK_DEMO "build demo source" OFF)
if(BUILD_SDK_DEMO)
add_definitions( "-DBUILD_SDK_DEMO=1" )
file(GLOB SDK_DEMO_C_CPP_SORCES
${SDK_ROOT}/demo/*.cpp
${SDK_ROOT}/demo/*.c
${SDK_ROOT}/demo/console/*.cpp
${SDK_ROOT}/demo/console/*.c
${SDK_ROOT}/demo/console/*.h
${SDK_ROOT}/demo/console/*.h
)
list(APPEND SDK_SRCS
${SDK_DEMO_C_CPP_SORCES}
)
endif()
list(APPEND SDK_INCLUDE_DIRS
${SDK_ROOT}/demo/
${SDK_ROOT}/demo/console/
)

#platform
file(GLOB_RECURSE SDK_PLATFORM_S_C_CPP_SORCES
${SDK_ROOT}/platform/arch/*.c
${SDK_ROOT}/platform/common/*.c
${SDK_ROOT}/platform/drivers/*.c
${SDK_ROOT}/platform/sys/*.c
${SDK_ROOT}/platform/common/*.h
${SDK_ROOT}/platform/drivers/*.h
${SDK_ROOT}/platform/sys/*.h
)
list(APPEND SDK_SRCS
${SDK_PLATFORM_S_C_CPP_SORCES}
)
list(APPEND SDK_INCLUDE_DIRS
${SDK_ROOT}/platform/common/params
${SDK_ROOT}/platform/common/task
${SDK_ROOT}/platform/sys
${SDK_ROOT}/platform/inc
)
#rtos
file(GLOB_RECURSE SDK_RTOS_S_C_CPP_SORCES
${SDK_ROOT}/src/os/rtos/*.c
${SDK_ROOT}/src/os/rtos/*.S
${SDK_ROOT}/src/os/rtos/*.h
)
list(APPEND SDK_SRCS
${SDK_RTOS_S_C_CPP_SORCES}
)
list(APPEND SDK_INCLUDE_DIRS
${SDK_ROOT}/src/os/rtos/include
)

#network
file(GLOB_RECURSE SDK_NETWORK_S_C_CPP_SORCES
${SDK_ROOT}/src/network/api2.0.3/*.c
${SDK_ROOT}/src/network/lwip2.0.3/sys_arch.c
${SDK_ROOT}/src/network/lwip2.0.3/api/*.c
${SDK_ROOT}/src/network/lwip2.0.3/core/*.c
${SDK_ROOT}/src/network/lwip2.0.3/netif/*.c
${SDK_ROOT}/src/network/*.h
)
list(REMOVE_ITEM  SDK_NETWORK_S_C_CPP_SORCES
${SDK_ROOT}/src/network/lwip2.0.3/core/timers.c
)
list(APPEND SDK_SRCS
${SDK_NETWORK_S_C_CPP_SORCES}
)
list(APPEND SDK_INCLUDE_DIRS
${SDK_ROOT}/src/network/api2.0.3/
${SDK_ROOT}/src/network/lwip2.0.3/include
)

#bt
file(GLOB_RECURSE SDK_BT_S_C_CPP_SORCES
${SDK_ROOT}/src/bt/blehost/*.c
${SDK_ROOT}/src/bt/blehost/*.h
)
list(APPEND SDK_SRCS
${SDK_BT_S_C_CPP_SORCES}
)
file(GLOB_RECURSE SDK_BT_S_C_CPP_HEADER_DIR LIST_DIRECTORIES true
${SDK_ROOT}/src/bt/blehost/*/include
)
list(APPEND SDK_INCLUDE_DIRS
${SDK_BT_S_C_CPP_HEADER_DIR}
)
#app
file(GLOB_RECURSE SDK_APP_S_C_CPP_SORCES
${SDK_ROOT}/src/app/*.c
${SDK_ROOT}/src/app/*.h
)
list(APPEND SDK_SRCS
${SDK_APP_S_C_CPP_SORCES}
)
file(GLOB_RECURSE SDK_APP_BTAPP_S_C_CPP_SORCES
${SDK_ROOT}/src/app/btapp/*.c
)
list(REMOVE_ITEM SDK_SRCS
${SDK_APP_BTAPP_S_C_CPP_SORCES}
${SDK_ROOT}/src/app/httpclient/wm_httpclient_if.c
${SDK_ROOT}/src/app/libcoap/address.c
${SDK_ROOT}/src/app/libcoap/async.c
${SDK_ROOT}/src/app/libcoap/block.c
${SDK_ROOT}/src/app/libcoap/coap_io.c
${SDK_ROOT}/src/app/libcoap/coap_io_lwip.c
${SDK_ROOT}/src/app/libcoap/coap_time.c
${SDK_ROOT}/src/app/libcoap/debug.c
${SDK_ROOT}/src/app/libcoap/encode.c
${SDK_ROOT}/src/app/libcoap/hashkey.c
${SDK_ROOT}/src/app/libcoap/mem_libcoap.c
${SDK_ROOT}/src/app/libcoap/net.c
${SDK_ROOT}/src/app/libcoap/option.c
${SDK_ROOT}/src/app/libcoap/pdu.c
${SDK_ROOT}/src/app/libcoap/resource.c
${SDK_ROOT}/src/app/libcoap/sr.c
${SDK_ROOT}/src/app/libcoap/subscribe.c
${SDK_ROOT}/src/app/libcoap/uri_libcoap.c
${SDK_ROOT}/src/app/libwebsockets-2.1-stable/minihuf.c
${SDK_ROOT}/src/app/libwebsockets-2.1-stable/minilex.c
${SDK_ROOT}/src/app/libwebsockets-2.1-stable/rewrite.c
${SDK_ROOT}/src/app/libwebsockets-2.1-stable/server.c
${SDK_ROOT}/src/app/libwebsockets-2.1-stable/server-handshake.c
${SDK_ROOT}/src/app/libwebsockets-2.1-stable/sha-1.c
${SDK_ROOT}/src/app/libwebsockets-2.1-stable/smtp.c
${SDK_ROOT}/src/app/libwebsockets-2.1-stable/ssl-http2.c
${SDK_ROOT}/src/app/libwebsockets-2.1-stable/ssl-server.c
${SDK_ROOT}/src/app/libwebsockets-2.1-stable/alloc.c
${SDK_ROOT}/src/app/libwebsockets-2.1-stable/daemonize.c
${SDK_ROOT}/src/app/libwebsockets-2.1-stable/extension.c
${SDK_ROOT}/src/app/libwebsockets-2.1-stable/extension-permessage-deflate.c
${SDK_ROOT}/src/app/libwebsockets-2.1-stable/getifaddrs.c
${SDK_ROOT}/src/app/libwebsockets-2.1-stable/hpack.c
${SDK_ROOT}/src/app/libwebsockets-2.1-stable/http2.c
${SDK_ROOT}/src/app/libwebsockets-2.1-stable/lejp.c
${SDK_ROOT}/src/app/libwebsockets-2.1-stable/lejp-conf.c
${SDK_ROOT}/src/app/libwebsockets-2.1-stable/libev.c
${SDK_ROOT}/src/app/libwebsockets-2.1-stable/libuv.c
${SDK_ROOT}/src/app/libwebsockets-2.1-stable/lws-plat-mbed3.c
${SDK_ROOT}/src/app/web/fsdata_ap_config.c
${SDK_ROOT}/src/app/web/fsdata.c

)

file(GLOB_RECURSE SDK_APP_S_C_CPP_HEADER_DIR LIST_DIRECTORIES true
${SDK_ROOT}/src/app/*/include
)
list(APPEND SDK_INCLUDE_DIRS
${SDK_APP_S_C_CPP_HEADER_DIR}
${SDK_ROOT}/src/app/wm_atcmd
${SDK_ROOT}/src/app/dhcpserver
${SDK_ROOT}/src/app/dnsserver
${SDK_ROOT}/src/app/httpclient
${SDK_ROOT}/src/app/mqtt
${SDK_ROOT}/src/app/ping
${SDK_ROOT}/src/app/iperf
)

#使用源代码编译的库文件
add_library(SDK_SOURCE_LIB STATIC ${SDK_SRCS})

list(APPEND SDK_LIBS
SDK_SOURCE_LIB
)

#预先编译的库文件
list(APPEND SDK_PRECOMPILED_LIBS
${SDK_ROOT}/lib/w800/libwlan.a
${SDK_ROOT}/lib/w800/libbtcontroller.a
${SDK_ROOT}/lib/w800/libdsp.a
${CMAKE_CURRENT_SOURCE_DIR}/lib/w800/libwmarch.a
)

#设置宏定义
add_definitions(" -DNIMBLE_FTR=1 -DWM_SWD_ENABLE=1 ")
