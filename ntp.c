#include "ntp.h"
#include "time.h"
#include "stdio.h"
#include "wm_rtc.h"
#include "stdlib.h"

static const char *TAG="ntp";

static const char * ntp_server_list[]=
{
#if CONFIG_PROTOCOL_NTP == 1
CONFIG_PROTOCOL_NTP_SERVER_1_IP,
CONFIG_PROTOCOL_NTP_SERVER_2_IP,
CONFIG_PROTOCOL_NTP_SERVER_3_IP
#else
"",
"",
""
#endif // CONFIG_PROTOCOL_NTP
};

static __unused const char *tz=CONFIG_PROTOCOL_NTP_TIMEZONE;

void ntp_init()
{
#if 0
     //minilibc不支持
    {
        //设置时区
        setenv("TZ",tz,1);
        tzset();
    }
#endif

    for(size_t i=0;i<(sizeof(ntp_server_list)/sizeof(ntp_server_list[0]));i++)
    {
        tls_ntp_set_server((char *)ntp_server_list[i],i);
    }
}

static TickType_t last_check_tick=0;
static const int check_interval=
#if CONFIG_PROTOCOL_NTP == 1
CONFIG_PROTOC_NTP_CHECK_TIME_INTERVAL;
#else
0;
#endif // CONFIG_PROTOCOL_NTP

static void check_time()
{
    time_t ntp_time_cnt=tls_ntp_client();
    {
        struct tm m_tm={0};
        m_tm=*localtime(&ntp_time_cnt);
        if(m_tm.tm_year>(2020-1900))
        {
            ntp_time_cnt=tls_ntp_client();
#if 0
	    //minilibc不支持时区
            {//由于SDK加了8小时，此处应减去8小时获得真正的时间戳
                ntp_time_cnt-=8*3600;
            }
#endif
            m_tm=*localtime(&ntp_time_cnt);
            //时间有效
            printf("%s:time %04d/%02d/%02d %02d:%02d:%02d\r\n",TAG,m_tm.tm_year+1900,m_tm.tm_mon+1,m_tm.tm_mday,m_tm.tm_hour,m_tm.tm_min,m_tm.tm_sec);
            tls_set_rtc(&m_tm);
        }
    }
};


void ntp_loop()
{
    if(check_interval==0)
    {
        //未启用ntp，不做任何操作
        return;
    }
    if(last_check_tick==0)
    {
        check_time();
        last_check_tick=xTaskGetTickCount();
    }
    else
    {
        if((xTaskGetTickCount()-last_check_tick)>pdMS_TO_TICKS(check_interval*1000))
        {
            check_time();
            last_check_tick=xTaskGetTickCount();
        }
    }
}
