#ifndef __INT_MQTT_H__
#define __INT_MQTT_H__

#include "Int_W5500.h"
#include "MQTTClient.h"
#include "socket.h"
#include "Com_Debug.h"
#include "Com_Delay.h"

#define CONSOLE_TO_GATEWAY "console_to_gateway"
#define GATEWAY_TO_CONSOLE "gateway_to_console"

//注册回调函数
typedef void (*console_callback)(char* r_msg);
//初始化MQTT客户端(需要依赖以太网)
void Int_MQTT_Init(void);


//处理网络消息
void Int_MQTT_Refsh(void);
//发布消息
void Int_MQTT_SendMessage(char* topicName, uint8_t* data);
//注册回调函数
void Int_MQTT_ConsoleGetData(console_callback cb);

#endif /* __INT_MQTT_H__ */
