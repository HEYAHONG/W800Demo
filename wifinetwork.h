#ifndef WIFINETWORK_H_INCLUDED
#define WIFINETWORK_H_INCLUDED

#include "appconfig.h"
#include "stdint.h"
#include "stdbool.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

#include "lwip/netif.h"

typedef struct
{
    bool isap;//是否为AP
    char ssid[33];
    char password[65];
    int  channel;

} wifinetwork_cfg_t;

typedef struct
{
    union
    {
        struct
        {
            uint32_t is_enable:1;//是否正常启动
            uint32_t is_ap:1;//是否为ap模式

            uint32_t is_connect_ap:1;//是否连接路由器
            uint32_t is_sta_ip_ok:1;//客户端模式是否分配到ip地址

            uint32_t is_ap_running:1;//是否成功打开AP
            uint32_t softap_sta_num:8;//AP模式的客户端数量
        };
        uint32_t status;
    };
    const struct netif *stanetif;//客户端模式下的网卡指针,用于读取IP地址等。可为NULL。
    const struct netif *apnetif;//AP模式下的网卡指针,用于读取IP地址等。可为NULL。
} wifinetwork_status_t;

//初始化wifinetwork
void wifinetwork_init();

void wifinetwork_set_config(wifinetwork_cfg_t cfg);

wifinetwork_cfg_t wifinetwork_get_config();

wifinetwork_status_t wifinetwork_get_status();

//反初始化wifinetwork
void wifinetwork_deinit();

#ifdef __cplusplus
};
#endif // __cplusplus

#endif // WIFINETWORK_H_INCLUDED
