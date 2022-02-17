
#include "app.h"
#include "MQTT.hpp"


static const char * TAG="app";

char macaddrstr[20]={0};

void app_init()
{
    printf("%s:Init\r\n",TAG);

    {
        //处理MAC地址

        for(size_t i=0;i<MACADDR_LENGTH;i++)
        {
            char buff[10]={0};
            sprintf(buff,"%02X",macaddr[i]);
            strcat(macaddrstr,buff);
        }

        printf("%s:our mac is %s\r\n",TAG,macaddrstr);
    }

    //初始化MQTT
    MQTT_Init();

}

void app_loop()
{
    vTaskDelay(1);
}
