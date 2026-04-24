#ifndef __APP_MAIN_H__
#define __APP_MAIN_H__

#include "FreeRTOS.h"
#include "task.h"
#include "Com_Debug.h"
#include "Int_MQTT.h"
#include "Int_ModBus.h"
#include "App_Console_To_GateWay.h"
#include "App_GateWay_To_Console.h"
#include "semphr.h"
void App_main_Start(void);

#endif /* __APP_MAIN_H__ */
