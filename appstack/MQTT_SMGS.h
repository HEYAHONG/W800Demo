#ifndef MQTT_SMGS_H
#define MQTT_SMGS_H

#include "MQTT.hpp"

#ifdef __cplusplus

/*
下列函数均用于回调函数,请不要手动调用它们。
*/

void MQTT_SMGS_Init(MQTT_Cfg_t &cfg);

void MQTT_SMGS_Connect(MQTT_Cfg_t &cfg);

void MQTT_SMGS_DisConnect(MQTT_Cfg_t &cfg);

void MQTT_SMGS_OnMessage(MQTT_Cfg_t &cfg,MQTT_Message_Ptr_t msg);

#endif // __cplusplus


#endif // MQTT_SMGS_H
