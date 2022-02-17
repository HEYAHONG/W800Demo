#include "MQTT.hpp"
#include "string.h"
#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

#include "MQTTFreeRTOS_LWIP.h"
#include "MQTTClient.h"
extern void * cpp_malloc(size_t nsize);
extern void cpp_free(void *p);
extern char macaddrstr[];
#ifdef __cplusplus
}
#endif // __cplusplus
static const char * TAG="MQTT";






/*
MQTT相关
*/
struct Network mqttserver= {0};
struct MQTTClient mqttclient= {0};
uint8_t mqtttxbuff[1024]= {0};
uint8_t mqttrxbuff[1024]= {0};

const int keepalive=120;


extern SMGS_gateway_context_t gateway_context;
static void mqttmessageHandler(MessageData*msg)
{
    uint8_t buff[4096]= {0};
    SMGS_GateWay_Receive_MQTT_MSG(&gateway_context,msg->topicName->lenstring.data,msg->topicName->lenstring.len,(uint8_t *)msg->message->payload,msg->message->payloadlen,msg->message->qos,msg->message->retained,buff,sizeof(buff));

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


/*
协议栈相关
*/
const char *GateWayName="W800Demo";
char GateWaySerialNumber[32]="W800";
SMGS_device_context_t device_context;

bool SMGS_IsOnline(struct __SMGS_device_context_t *ctx)
{
    //默认返回真
    return true;
}

SMGS_gateway_context_t gateway_context;


//设备查询函数
SMGS_device_context_t * SMGS_Device_Next(struct __SMGS_gateway_context_t *ctx,SMGS_device_context_t * devctx)
{
    if(devctx==NULL)
    {
        return &device_context;//返回第一个设备
    }

    //由于只有一个设备，直接返回NULL

    return NULL;
}


static bool SMGS_MessagePublish(struct __SMGS_gateway_context_t *ctx,const char * topic,void * payload,size_t payloadlen,uint8_t qos,int retain)
{
    if(MQTTIsConnected(&mqttclient)==0)
    {
        return false;
    }

    QoS Qos=QOS0;
    switch(qos)
    {
    default:
        break;
    case 0:
        Qos=QOS0;
        break;
    case 1:
        Qos=QOS1;
        break;
    case 2:
        Qos=QOS2;
        break;

    }

    MQTTMessage msg;
    memset(&msg,0,sizeof(msg));
    msg.payload=payload;
    msg.payloadlen=payloadlen;
    msg.qos=Qos;
    msg.retained=retain;
    return MQTTPublish(&mqttclient,topic,&msg)==0;
}


static void mqtt_receive_task(void *arg)
{
    printf("%s:mqtt task start!!\r\n",TAG);

    strcat(GateWaySerialNumber,macaddrstr);

    {
        //初始化设备上下文
        SMGS_Device_Context_Init(&device_context);

        //填写设备上下文
        device_context.DeviceName=TAG;
        device_context.DevicePosNumber=1;
        device_context.DeviceSerialNumber=GateWaySerialNumber;//默认序列号同网关
        device_context.IsOnline=SMGS_IsOnline;

    }

    {

        //初始化网关上下文
        SMGS_GateWay_Context_Init(&gateway_context,GateWaySerialNumber,SMGS_MessagePublish);

        //填写网关上下文
        gateway_context.GateWayName=TAG;
        gateway_context.Device_Next=SMGS_Device_Next;
    }


    while(true)
    {
        //测试MQTT连接
        printf("%s:mqtt start!!\r\n",TAG);


        NetworkInit(&mqttserver);
        while(0!=NetworkConnect(&mqttserver,(char *)"didiyun.hyhsystem.cn",1883))
        {
            printf("%s:connect mqtt server!\r\n",TAG);
            vTaskDelay(3000);
        }

        MQTTClientInit(&mqttclient,&mqttserver,3000,mqtttxbuff,sizeof(mqtttxbuff),mqttrxbuff,sizeof(mqttrxbuff));

        {

            MQTTPacket_connectData cfg=MQTTPacket_connectData_initializer;

            //使用keepalive选项
            cfg.keepAliveInterval=keepalive;

            //填写clientID
            cfg.clientID.cstring=(char *)GateWaySerialNumber;

            //填写cleansession
            cfg.cleansession=1;

            //填写用户名与密码
            cfg.username.cstring=(char *)GateWaySerialNumber;
            cfg.password.cstring=(char *)GateWaySerialNumber;

            //填写will
            uint8_t willbuff[256]= {0};
            SMGS_gateway_will_t will= {0};
            SMGS_GateWay_Will_Encode(&gateway_context,&will,willbuff,sizeof(willbuff));

            cfg.will.topicName.cstring=(char *)will.topic;
            cfg.will.qos=will.qos;
            cfg.will.message.lenstring.data=(char *)will.payload;
            cfg.will.message.lenstring.len=will.payloadlen;
            cfg.will.retained=will.ratain;
            cfg.willFlag=1;


            if(SUCCESS!=MQTTConnect(&mqttclient,&cfg))
            {
                printf("%s:mqtt connect failed!!\r\n",TAG);
                continue;
            }
        }
        {
            char subscribestr[64]= {0};
            strcat(subscribestr,GateWaySerialNumber);
            strcat(subscribestr,"/#");
            if(SUCCESS!=MQTTSubscribe(&mqttclient,subscribestr,QOS0,mqttmessageHandler))
            {
                printf("%s:mqtt subscribe failed!!\r\n",TAG);
                continue;
            }
        }

        {
            //发送网关上线消息
            uint8_t buff[512]= {0};
            SMGS_GateWay_Online(&gateway_context,buff,sizeof(buff),0,0);
        }

        printf("%s:SimpleMQTTGateWayStack Online\r\n",TAG);

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

uint32_t mqtt_receive_task_stack[4096]= {0};
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



