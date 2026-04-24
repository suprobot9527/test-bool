#ifndef __APP_CONSOLE_TO_GATEWAY_H__
#define __APP_CONSOLE_TO_GATEWAY_H__

#include "Com_Debug.h"
#include "Int_MQTT.h"
#include "Int_ModBus.h"
#include "FreeRTOS.h"
#include "task.h"
#include "cJSON.h"
#include "string.h"
#include "stdint.h"
#include "semphr.h"
#include "Com_Delay.h"
void task_T(void* pram);

#endif /* __APP_CONSOLE_TO_GATEWAY_H__ */
