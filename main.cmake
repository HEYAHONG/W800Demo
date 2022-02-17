#设置工程名
set(PROJECT_NAME W800Demo)

#设置源文件
list(APPEND MAIN_SRCS
main.c
ntp.c
wifinetwork.c
appstack/app.cpp
appstack/MQTT.cpp
cpp.cpp
cpp.c
)

#设置头文件
list(APPEND MAIN_INCLUDE_DIRS
./
appstack
)
