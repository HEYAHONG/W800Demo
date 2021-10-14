#include "wm_include.h"
#include "wifinetwork.h"
#include "string.h"
#include "lwip/netif.h"
#include "wm_netif.h"

static const char *TAG="wifinetwork";

static wifinetwork_cfg_t config=
#if CONFIG_WIFI_NETWORK == 1
{
#if CONFIG_WIFI_NETWORK_STA == 1
    .isap=false,
    .ssid=CONFIG_WIFI_NETWORK_ROUTER_AP_SSID,
    .password=CONFIG_WIFI_NETWORK_ROUTER_AP_PASSWORD,
    .channel=0,
#endif // CONFIG_WIFI_NETWORK_STA
#if CONFIG_WIFI_NETWORK_SOFTAP == 1
    .isap=true,
    .ssid=CONFIG_WIFI_NETWORK_AP_SSID,
    .password=CONFIG_WIFI_NETWORK_AP_PASSWORD,
    .channel=CONFIG_WIFI_NETWORK_AP_CHANNEL,
#endif // CONFIG_WIFI_NETWORK_SOFTAP

};
#else
    {
        0
    };
#endif // CONFIG_WIFI_NETWORK


static wifinetwork_status_t wifinet_status= {0};

static void apsta_client_event(u8 *mac, enum tls_wifi_client_event_type event)
{
    if(event== WM_WIFI_CLIENT_EVENT_ONLINE)
    {
        wifinet_status.softap_sta_num++;
    }
    else
    {
        wifinet_status.softap_sta_num--;
    }
    wm_printf("client %M is %s\r\n", mac, event ? "offline" : "online");
}

static void con_net_status_changed_event(u8 status )
{
    struct netif *nf = tls_get_netif();

    wifinet_status.stanetif=nf;
    wifinet_status.apnetif=nf->next;

    switch(status)
    {
    case NETIF_WIFI_JOIN_SUCCESS:
    {
        printf("%s:NETIF_WIFI_JOIN_SUCCESS\n",TAG);
        wifinet_status.status=0;
        wifinet_status.is_enable=1;
        wifinet_status.is_ap=0;
        wifinet_status.is_connect_ap=1;
    }
    break;
    case NETIF_WIFI_JOIN_FAILED:
    {
        printf("%s:NETIF_WIFI_JOIN_FAILED\n",TAG);
        wifinet_status.status=0;
    }
    break;
    case NETIF_WIFI_DISCONNECTED:
    {
        printf("%s:NETIF_WIFI_DISCONNECTED\n",TAG);
        wifinet_status.status=0;
    }
    break;
    case NETIF_IP_NET_UP:
    {
        wifinet_status.is_sta_ip_ok=1;
        printf("%s:NETIF_IP_NET_UP\n",TAG);
        {
            struct netif *tmp=nf;
            while(tmp!=NULL)
            {
                printf("%s:netif name:%c%c%u\r\n",TAG,tmp->name[0],tmp->name[1],tmp->num);
                print_ipaddr(&tmp->ip_addr);
                print_ipaddr(&tmp->gw);
                print_ipaddr(&tmp->netmask);
                tmp=tmp->next;
            }
        }
    }
    break;
    case NETIF_WIFI_SOFTAP_SUCCESS:
    {
        wm_printf("%s:softap create success\n",TAG);
        wifinet_status.status=0;
        wifinet_status.is_enable=1;
        wifinet_status.is_ap=1;
    }
    break;
    case NETIF_WIFI_SOFTAP_FAILED:
    {
        wm_printf("%s:softap create failed\n",TAG);
        wifinet_status.status=0;
    }
    break;
    case NETIF_WIFI_SOFTAP_CLOSED:
    {
        wm_printf("%s:softap closed\n",TAG);
        wifinet_status.status=0;
    }
    break;
    case NETIF_IP_NET2_UP:
    {
        wifinet_status.is_ap_running=1;
        wm_printf("%s:softap ok\n",TAG);
        {
            struct netif *tmp=nf;
            while(tmp!=NULL)
            {
                printf("%s:netif name:%c%c%u\r\n",TAG,tmp->name[0],tmp->name[1],tmp->num);
                print_ipaddr(&tmp->ip_addr);
                print_ipaddr(&tmp->gw);
                print_ipaddr(&tmp->netmask);
                tmp=tmp->next;
            }
        };
    }
    break;
    default:
    {
        printf("%s:UNKONWN STATE:%d\n",TAG,status);
    }
    break;
    }
}

static int wifinetwork_sta_connect_net(char *ssid, char *pwd)
{
    struct tls_param_ip *ip_param = NULL;
    u8 wireless_protocol = 0;

    if (!ssid)
    {
        return WM_FAILED;
    }
    tls_wifi_disconnect();

    tls_param_get(TLS_PARAM_ID_WPROTOCOL, (void *) &wireless_protocol, TRUE);
    if (TLS_PARAM_IEEE80211_INFRA != wireless_protocol)
    {
        tls_wifi_softap_destroy();
        wireless_protocol = TLS_PARAM_IEEE80211_INFRA;
        tls_param_set(TLS_PARAM_ID_WPROTOCOL, (void *) &wireless_protocol, FALSE);
    }

    tls_wifi_set_oneshot_flag(0);

    ip_param = tls_mem_alloc(sizeof(struct tls_param_ip));
    if (ip_param)
    {
        tls_param_get(TLS_PARAM_ID_IP, ip_param, FALSE);
        ip_param->dhcp_enable = TRUE;
        tls_param_set(TLS_PARAM_ID_IP, ip_param, FALSE);
        tls_mem_free(ip_param);
    }

    tls_wifi_connect((u8 *)ssid, strlen(ssid), (u8 *)pwd, strlen(pwd));
    printf("%s:please wait connect net(%s)......\n",TAG,ssid);

    return WM_SUCCESS;
}

static int create_soft_ap(char *apssid, char *appwd)
{
    struct tls_softap_info_t apinfo;
    struct tls_ip_info_t ipinfo;
    u8 ret = 0;

    memset(&apinfo, 0, sizeof(apinfo));
    memset(&ipinfo, 0, sizeof(ipinfo));

    u8 *ssid =(u8 *) CONFIG_WIFI_NETWORK_AP_SSID;
    u8 ssid_len = strlen(CONFIG_WIFI_NETWORK_AP_SSID);

    if (apssid)
    {
        ssid_len = strlen(apssid);
        MEMCPY(apinfo.ssid, apssid, ssid_len);
        apinfo.ssid[ssid_len] = '\0';
    }
    else
    {
        MEMCPY(apinfo.ssid, ssid, ssid_len);
        apinfo.ssid[ssid_len] = '\0';
    }

    apinfo.encrypt = strlen(appwd) ? IEEE80211_ENCRYT_CCMP_WPA2 : IEEE80211_ENCRYT_NONE;
    apinfo.channel = config.channel; /*channel*/
    apinfo.keyinfo.format = 1; /*format:0,hex, 1,ascii*/
    apinfo.keyinfo.index = 1;  /*wep index*/
    apinfo.keyinfo.key_len = strlen(appwd); /*key length*/
    MEMCPY(apinfo.keyinfo.key, appwd, strlen(appwd));

    /*ip information:ip address,mask, DNS name*/
    ipinfo.ip_addr[0] = 192;
    ipinfo.ip_addr[1] = 168;
    ipinfo.ip_addr[2] = 8;
    ipinfo.ip_addr[3] = 1;
    ipinfo.netmask[0] = 255;
    ipinfo.netmask[1] = 255;
    ipinfo.netmask[2] = 255;
    ipinfo.netmask[3] = 0;
    MEMCPY(ipinfo.dnsname, CONFIG_WIFI_NETWORK_AP_DNSNAME, sizeof( CONFIG_WIFI_NETWORK_AP_DNSNAME));

    ret = tls_wifi_softap_create((struct tls_softap_info_t * )&apinfo, (struct tls_ip_info_t * )&ipinfo);
    wm_printf("%s:ap create %s ! \n",TAG,(ret == WM_SUCCESS) ? "Successfully" : "Error");

    return ret;
}

static void wifinetwork_sta_init()
{
    wifinetwork_sta_connect_net(config.ssid,config.password);
}

static void wifinetwork_ap_init()
{
    create_soft_ap(config.ssid,config.password);
}

void wifinetwork_init()
{
    tls_netif_add_status_event(con_net_status_changed_event);
    tls_wifi_softap_client_event_register(apsta_client_event);
    if(config.isap)
    {

        wifinetwork_ap_init();
    }
    else
    {
        wifinetwork_sta_init();
    }
}

void wifinetwork_set_config(wifinetwork_cfg_t cfg)
{
    config=cfg;
}

wifinetwork_cfg_t wifinetwork_get_config()
{
    return config;
}

wifinetwork_status_t wifinetwork_get_status()
{
    return wifinet_status;
}

void wifinetwork_deinit()
{
    tls_netif_remove_status_event(con_net_status_changed_event);
    tls_wifi_softap_client_event_register(NULL);
    tls_wifi_disconnect();
    tls_wifi_softap_destroy();
    tls_wifi_set_oneshot_flag(0);
}
