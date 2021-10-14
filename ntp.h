#ifndef NTP_H_INCLUDED
#define NTP_H_INCLUDED

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

#include "wm_ntp.h"
#include "appconfig.h"

void ntp_init();

void ntp_loop();

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // NTP_H_INCLUDED
