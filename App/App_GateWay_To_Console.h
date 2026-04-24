#ifndef __APP_GATEWAY_TO_CONSOLE_H__
#define __APP_GATEWAY_TO_CONSOLE_H__

#include "Int_MQTT.h"
#include "FreeRTOS.h"
#include "task.h"
#include "usart.h"
#include "stdint.h"
#include "semphr.h"
#include "App_Console_To_GateWay.h"
#include "Int_ModBus.h"
#include "string.h"

void task_T_net(void* pram);
#endif /* __APP_GATEWAY_TO_CONSOLE_H__ */
