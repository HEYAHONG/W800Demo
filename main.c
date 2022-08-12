#include "wm_include.h"
#include "stdbool.h"
#include "appconfig.h"
#include "app.h"
#include "wifinetwork.h"
#include "ntp.h"

uint8_t macaddr[MACADDR_LENGTH]={0};

extern size_t  tls_mem_get_avail_heapsize();
static const char * TAG="main";
static  OS_STK  main_task_stack[2048];
static void main_task(void *arg)
{

#if CONFIG_WIFI_NETWORK == 1
    //初始化WIFINetwork
    wifinetwork_init();
    tls_get_mac_addr(macaddr);
#endif // CONFIG_WIFI_NETWORK

#if CONFIG_PROTOCOL_NTP == 1
    ntp_init();
#endif // CONFIG_PROTOCOL_NTP

    app_init();

    wm_printf("%s:free memory %d bytes\r\n",TAG,tls_mem_get_avail_heapsize());
    wm_printf("%s:main task running\r\ntick=%lu\r\n",TAG,xTaskGetTickCount());


    while(true)
    {
        app_loop();
#if CONFIG_PROTOCOL_NTP == 1
        ntp_loop();
#endif // CONFIG_PROTOCOL_NTP
    }
}


void UserMain(void)
{
    wm_printf("\nMain Started\n");
    tls_os_task_create(NULL,"main",main_task,NULL,(void *)main_task_stack,sizeof(main_task_stack),32,0);
}

