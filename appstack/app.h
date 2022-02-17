#ifndef APP_H_INCLUDED
#define APP_H_INCLUDED

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus
#include "FreeRTOS.h"
#include "task.h"
#include "stdint.h"

#define MACADDR_LENGTH 6

extern uint8_t macaddr[];

extern char macaddrstr[];

void app_init();

void app_loop();


#ifdef __cplusplus
}
#endif // __cplusplus


#endif // APP_H_INCLUDED
