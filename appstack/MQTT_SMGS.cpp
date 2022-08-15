#include "MQTT_SMGS.h"
#include "libSMGS.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

#include "MQTTFreeRTOS_LWIP.h"
#include "MQTTClient.h"
extern void * cpp_malloc(size_t nsize);
extern void cpp_free(void *p);
extern char macaddrstr[];
#include "wm_include.h"
#ifdef __cplusplus
}
#endif // __cplusplus

static const char * TAG="MQTT_SMGS";

extern SMGS_gateway_context_t gateway_context;


void MQTT_SMGS_OnMessage(MQTT_Cfg_t &cfg,MQTT_Message_Ptr_t msg)
{

    size_t buff_len=4096;
    uint8_t *buff=new uint8_t[buff_len];
    memset(buff,0,buff_len);
    SMGS_GateWay_Receive_MQTT_MSG(&gateway_context,msg->topic.c_str(),msg->topic.length(),(uint8_t *)msg->payload.c_str(),msg->payload.length(),msg->qos,msg->retain,buff,buff_len);
    delete [] buff;
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

bool SMGS_Device_Command(SMGS_device_context_t *ctx,SMGS_topic_string_ptr_t plies[],SMGS_payload_cmdid_t *cmdid,uint8_t *cmddata,size_t cmddata_length,uint8_t *retbuff,size_t *retbuff_length,SMGS_payload_retcode_t *ret)
{
    bool _ret=false;
    wm_printf("%s:Device_Command(CmdID=%04X)\r\n",TAG,(uint32_t)(*cmdid));
    return _ret;
}

bool SMGS_Device_ReadRegister(SMGS_device_context_t *ctx,SMGS_topic_string_ptr_t plies[],SMGS_payload_register_address_t addr,uint64_t *dat,SMGS_payload_register_flag_t *flag)
{
    bool ret=false;
    wm_printf("%s:Device_ReadRegister(Addr=%04X)\r\n",TAG,(uint32_t)addr);
    return ret;
}

bool SMGS_Device_WriteRegister(SMGS_device_context_t *ctx,SMGS_topic_string_ptr_t plies[],SMGS_payload_register_address_t addr,uint64_t *dat,SMGS_payload_register_flag_t *flag)
{
    bool ret=false;
    wm_printf("%s:Device_WriteRegister(Addr=%04X,Data=%016llX,Flag=%02X)\r\n",TAG,(uint32_t)addr,(*dat),(uint32_t)(flag->val));
    return ret;
}

bool SMGS_Device_ReadSensor(SMGS_device_context_t *ctx,SMGS_topic_string_ptr_t plies[],SMGS_payload_sensor_address_t addr,uint64_t *dat,SMGS_payload_sensor_flag_t *flag)
{
    bool ret=false;
    wm_printf("%s:Device_ReadSensor(Addr=%04X,Flag=%02X)\r\n",TAG,(uint32_t)addr,(uint32_t)(flag->val));
    return ret;
}


SMGS_gateway_context_t gateway_context;

bool SMGS_GateWay_Command(SMGS_gateway_context_t *ctx,SMGS_topic_string_ptr_t plies[],SMGS_payload_cmdid_t *cmdid,uint8_t *cmddata,size_t cmddata_length,uint8_t *retbuff,size_t *retbuff_length,SMGS_payload_retcode_t *ret)
{
    bool _ret=false;
    wm_printf("%s:GateWay_Command(CmdID=%04X)\r\n",TAG,(uint32_t)(*cmdid));
    return _ret;
}

bool SMGS_GateWay_ReadRegister(SMGS_gateway_context_t *ctx,SMGS_topic_string_ptr_t plies[],SMGS_payload_register_address_t addr,uint64_t *dat,SMGS_payload_register_flag_t *flag)
{
    bool ret=false;
    wm_printf("%s:GateWay_ReadRegister(Addr=%04X)\r\n",TAG,(uint32_t)addr);
    return ret;
}

bool SMGS_GateWay_WriteRegister(SMGS_gateway_context_t *ctx,SMGS_topic_string_ptr_t plies[],SMGS_payload_register_address_t addr,uint64_t *dat,SMGS_payload_register_flag_t *flag)
{
    bool ret=false;
    wm_printf("%s:GateWay_WriteRegister(Addr=%04X,Data=%016llX,Flag=%02X)\r\n",TAG,(uint32_t)addr,(*dat),(uint32_t)(flag->val));
    return ret;
}

bool SMGS_GateWay_ReadSensor(SMGS_gateway_context_t *ctx,SMGS_topic_string_ptr_t plies[],SMGS_payload_sensor_address_t addr,uint64_t *dat,SMGS_payload_sensor_flag_t *flag)
{
    bool ret=false;
    wm_printf("%s:GateWay_ReadSensor(Addr=%04X,Flag=%02X)\r\n",TAG,(uint32_t)addr,(uint32_t)(flag->val));
    return ret;
}


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
    MQTT_Message_Ptr_t ptr=std::make_shared<MQTT_Message_t>();
    ptr->topic=std::string(topic);
    ptr->payload=std::string((char *)payload,payloadlen);
    ptr->qos=qos;
    ptr->retain=retain;
    return MQTT_Publish_Message(ptr);
}

void MQTT_SMGS_Init(MQTT_Cfg_t &cfg)
{
    if(SMGS_Is_GateWay_Context_OK(&gateway_context))
    {
        return;
    }
    {
        //处理序列号
        strcat(GateWaySerialNumber,macaddrstr);
    }

    {
        cfg.keepalive=120;
        cfg.clientid=GateWaySerialNumber;
        cfg.auth.username=GateWaySerialNumber;
        cfg.auth.password=GateWaySerialNumber;
        cfg.cleansession=true;
        cfg.subscribe.subtopic=(std::string(GateWaySerialNumber)+"/#");
        cfg.subscribe.qos=0;

    }

    {
        //初始化设备上下文
        SMGS_Device_Context_Init(&device_context);

        //填写设备上下文
        device_context.DeviceName=GateWayName;
        device_context.DevicePosNumber=1;
        device_context.DeviceSerialNumber=GateWaySerialNumber;//默认序列号同网关
        device_context.IsOnline=SMGS_IsOnline;
        device_context.Command=SMGS_Device_Command;
        device_context.ReadRegister=SMGS_Device_ReadRegister;
        device_context.WriteRegister=SMGS_Device_WriteRegister;
        device_context.ReadSensor=SMGS_Device_ReadSensor;

    }

    {

        //初始化网关上下文
        SMGS_GateWay_Context_Init(&gateway_context,GateWaySerialNumber,SMGS_MessagePublish);

        //填写网关上下文
        gateway_context.GateWayName=GateWayName;
        gateway_context.Command=SMGS_GateWay_Command;
        gateway_context.ReadRegister=SMGS_GateWay_ReadRegister;
        gateway_context.WriteRegister=SMGS_GateWay_WriteRegister;
        gateway_context.ReadSensor=SMGS_GateWay_ReadSensor;
        gateway_context.Device_Next=SMGS_Device_Next;
    }

    {
        //填写will
        uint8_t willbuff[256]= {0};
        SMGS_gateway_will_t will= {0};
        SMGS_GateWay_Will_Encode(&gateway_context,&will,willbuff,sizeof(willbuff));

        cfg.will.will_topic=will.topic;
        cfg.will.will_payload=std::string((char *)will.payload,will.payloadlen);
        cfg.will.will_qos=will.qos;
        cfg.will.will_retain=will.ratain;
    }
}


void MQTT_SMGS_Connect(MQTT_Cfg_t &cfg)
{

    {
        //发送网关上线消息
        uint8_t buff[512]= {0};
        SMGS_GateWay_Online(&gateway_context,buff,sizeof(buff),0,0);
    }

    wm_printf("%s:SimpleMQTTGateWayStack Online\r\n",TAG);


}

void MQTT_SMGS_DisConnect(MQTT_Cfg_t &cfg)
{

}

