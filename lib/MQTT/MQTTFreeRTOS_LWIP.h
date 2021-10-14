/*******************************************************************************
 * Copyright (c) 2014, 2015 IBM Corp.
 *
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * and Eclipse Distribution License v1.0 which accompany this distribution.
 *
 * The Eclipse Public License is available at
 *    http://www.eclipse.org/legal/epl-v10.html
 * and the Eclipse Distribution License is available at
 *   http://www.eclipse.org/org/documents/edl-v10.php.
 *
 * Contributors:
 *    Allan Stockdill-Mander - initial API and implementation and/or initial documentation
 *******************************************************************************/

#if !defined(MQTTFreeRTOS_H)
#define MQTTFreeRTOS_H

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "lwip/sockets.h"
#include "lwip/netdb.h"
#include "string.h"

#ifndef TickType_t
#define TickType_t portTickType
#endif // TickType_t
#ifndef TimeOut_t
#define TimeOut_t  xTimeOutType
#endif // TimeOut_t
#ifndef SemaphoreHandle_t
#define SemaphoreHandle_t xSemaphoreHandle
#endif // SemaphoreHandle_t
#ifndef TaskHandle_t
#define TaskHandle_t xTaskHandle
#endif // TaskHandle_t
#ifndef pdMS_TO_TICKS
#include "FreeRTOS.h"
#define pdMS_TO_TICKS(x) ((x)/((1000/configTICK_RATE_HZ)))
#endif // pdMS_TO_TICKS
#ifndef UBaseType_t
#define UBaseType_t portBASE_TYPE
#endif // UBaseType_t
#ifndef portTICK_PERIOD_MS
#define portTICK_PERIOD_MS (1000/configTICK_RATE_HZ)
#endif // portTICK_PERIOD_MS


/*
配置PAHO MQTT,是否使用线程
*/
//#define MQTT_TASK


typedef struct Timer
{
	TickType_t xTicksToWait;
	TimeOut_t xTimeOut;
} Timer;

typedef struct Network Network;

struct Network
{
	int my_socket;
	int (*mqttread) (Network*, unsigned char*, int, int);
	int (*mqttwrite) (Network*, unsigned char*, int, int);
	void (*disconnect) (Network*);
};

void TimerInit(Timer*);
char TimerIsExpired(Timer*);
void TimerCountdownMS(Timer*, unsigned int);
void TimerCountdown(Timer*, unsigned int);
int TimerLeftMS(Timer*);

typedef struct Mutex
{
	SemaphoreHandle_t sem;
} Mutex;

void MutexInit(Mutex*);
int MutexLock(Mutex*);
int MutexUnlock(Mutex*);

typedef struct Thread
{
	TaskHandle_t task;
} Thread;

int ThreadStart(Thread*, void (*fn)(void*), void* arg);

int FreeRTOS_read(Network*, unsigned char*, int, int);
int FreeRTOS_write(Network*, unsigned char*, int, int);
void FreeRTOS_disconnect(Network*);

void NetworkInit(Network*);
int NetworkConnect(Network*, char*, int);

#endif
