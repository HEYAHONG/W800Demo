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
MQTT相关
*/
struct Network mqttserver= {0};
struct MQTTClient mqttclient= {0};
uint8_t mqtttxbuff[1024]= {0};
uint8_t mqttrxbuff[1024]= {0};

const int keepalive=10;

static void mqttmessageHandler(MessageData*msg)
{
    char * topic=(char *)cpp_malloc(msg->topicName->lenstring.len+1);
    memset(topic,0,msg->topicName->lenstring.len+1);
    memcpy(topic,msg->topicName->lenstring.data,msg->topicName->lenstring.len);

    char  *payload =(char *)cpp_malloc(msg->message->payloadlen+1);
    memset(payload,0,msg->message->payloadlen+1);
    memcpy(payload,msg->message->payload,msg->message->payloadlen);

    printf("%s:topic:%s,data=%s,datalen=%uBytes\r\n",TAG,topic,(char *)payload,msg->message->payloadlen);
    //MQTTPublish(&mqttclient,"/echo",msg->message);

    cpp_free(topic);
    cpp_free(payload);
}



//执行ping
static bool mqtt_ping(MQTTClient * client)
{

    if(client==NULL || client->buf ==NULL || client->buf_size ==0 || client->ipstack==NULL || client->ipstack->mqttwrite==NULL)
    {
        return false;//参数有误
    }

    uint8_t buff[8]= {0};
    int len=MQTTSerialize_pingreq(buff,sizeof(buff));
    return len==client->ipstack->mqttwrite(client->ipstack,buff,len,1000);
}

static void mqtt_receive_task(void *arg)
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

        //使用keepalive选项
        cfg.keepAliveInterval=keepalive;

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
        {
            while(SUCCESS==MQTTYield(&mqttclient,10))
            {
                vTaskDelay(1);
            }
        }


        printf("%s:mqtt yield failed!!restarting!!!\r\n",TAG);

        if(mqttserver.disconnect!=NULL)
        {
            mqttserver.disconnect(&mqttserver);
        }

    }

}

static void mqtt_ping_task(void *arg)
{

    TickType_t last_ping_tick=xTaskGetTickCount();
    while(true)
    {
        if(mqttclient.isconnected && xTaskGetTickCount()-last_ping_tick>pdMS_TO_TICKS(keepalive*1000/2))//10s ping 一次
        {
            last_ping_tick=xTaskGetTickCount();
            bool is_ok=mqtt_ping(&mqttclient);
            printf("%s:ping %s\r\n",TAG,is_ok?"success":"failed");
        }
        vTaskDelay(1000);
    }

}

uint32_t mqtt_receive_task_stack[1024]= {0};
uint32_t mqtt_ping_task_stack[1024]= {0};

extern "C"
{
#include  "wm_osal.h"
}

void MQTT_Init()
{
    /*
    由于套接字超时设置无效,因此需要单独的任务执行ping
    */
    tls_os_task_create(NULL,"mqtt_receive",mqtt_receive_task,NULL,(uint8_t *) mqtt_receive_task_stack,sizeof( mqtt_receive_task_stack),33,0);
    tls_os_task_create(NULL,"mqtt_ping",mqtt_ping_task,NULL,(uint8_t *) mqtt_ping_task_stack,sizeof( mqtt_ping_task_stack),33,0);
}



