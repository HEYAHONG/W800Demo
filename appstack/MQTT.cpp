#include "MQTT.hpp"
#include "string.h"
extern "C"
{
#include "MQTTFreeRTOS_LWIP.h"
#include "MQTTClient.h"
    extern void * cpp_malloc(size_t nsize);
    extern void cpp_free(void *p);
}
static const char * TAG="MQTT";


/*
MQTT相关测试
*/
struct Network mqttserver= {0};
struct MQTTClient mqttclient= {0};
uint8_t mqtttxbuff[1024]= {0};
uint8_t mqttrxbuff[1024]= {0};
static void mqttmessageHandler(MessageData*msg)
{
    char * topic=(char *)cpp_malloc(msg->topicName->lenstring.len+1);
    memset(topic,0,msg->topicName->lenstring.len+1);
    memcpy(topic,msg->topicName->lenstring.data,msg->topicName->lenstring.len);

    char  *payload =(char *)cpp_malloc(msg->message->payloadlen+1);
    memset(payload,0,msg->message->payloadlen+1);
    memcpy(payload,msg->message->payload,msg->message->payloadlen);

    printf("%s:topic:%s,data=%s,datalen=%uBytes\r\n",TAG,topic,(char *)payload,msg->message->payloadlen);
    MQTTPublish(&mqttclient,"/echo",msg->message);

    cpp_free(topic);
    cpp_free(payload);
}

void mqtt_test_task(void *arg)
{
    printf("%s:mqtt task start!!\r\n",TAG);
    while(true)
    {
        //测试MQTT连接
        printf("%s:mqtt test start!!\r\n",TAG);


        NetworkInit(&mqttserver);
        while(0!=NetworkConnect(&mqttserver,(char *)"didiyun.hyhsystem.cn",1883))
        {
            printf("%s:connect mqtt server!\r\n",TAG);
            vTaskDelay(3000);
        }

        MQTTClientInit(&mqttclient,&mqttserver,3000,mqtttxbuff,sizeof(mqtttxbuff),mqttrxbuff,sizeof(mqttrxbuff));


        MQTTPacket_connectData cfg=MQTTPacket_connectData_initializer;

        cfg.keepAliveInterval=0;

        if(SUCCESS!=MQTTConnect(&mqttclient,&cfg))
        {
            printf("%s:mqtt connect failed!!\r\n",TAG);
            continue;
        }

        if(SUCCESS!=MQTTSubscribe(&mqttclient,"+/#",QOS0,mqttmessageHandler))
        {
            printf("%s:mqtt subscribe failed!!\r\n",TAG);
            continue;
        }

        while(SUCCESS==MQTTYield(&mqttclient,10))
        {
            vTaskDelay(10);
        }

        printf("%s:mqtt yield failed!!restarting!!!\r\n",TAG);

        if(mqttserver.disconnect!=NULL)
        {
            mqttserver.disconnect(&mqttserver);
        }

    }

}


