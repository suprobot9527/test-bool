#include "Int_MQTT.h"

// 通道参数
Network network;
#define SN 0

// 会话结构体
MQTTClient client;
// 数据缓冲区
#define MAXSIZE 512
uint8_t send_buffers[MAXSIZE];
uint8_t receice_buffers[MAXSIZE];
// 会话主题


//注册回调函数
console_callback msg_cb;


uint8_t server_ip[4] = {192, 168, 55, 31};

static void Int_MQTT_CreateSocketAndConnentServer(void);
static void Int_MQTT_CreateSocketAndConnentServer(void)
{
    // 初始化通道，没有返回值不知道是否成功
    NewNetwork(&network, SN);
    // 链接服务器
    int result = ConnectNetwork(&network, server_ip, 1883);
    if (result == SOCK_OK)
    {
        COM_DEBUG_LN("connect MQTT is ok");
    }else{
        COM_DEBUG_LN("connect MQTT is no ok");
    }
}

void MQTTreceviceHandler(MessageData* messagedata)
{
    //COM_DEBUG_LN("MQTTdata is :%s",(char*)(messagedata->message->payload));
    msg_cb((char*)(messagedata->message->payload));
}
// 创建MQTT客户端
void Int_MQTT_CreateClent(void)
{
    // 创建MQTT客户端
    MQTTClientInit(&client, &network, 1000, send_buffers, MAXSIZE, receice_buffers, MAXSIZE);
    // 配置；链接的服务器
    MQTTPacket_connectData connect_options=MQTTPacket_connectData_initializer;
    int result = MQTTConnect(&client, &connect_options);
    if (result == SUCCESS)
    {
        COM_DEBUG_LN("MQTT connect Server is ok");
    }
    else
    {
        COM_DEBUG_LN("MQTT connect Server is no ok");
    }

    // 已经成为MQTT客户端，订阅消息:参数MQTT客户端结构体，会话主题，会话等级
    MQTTSubscribe(&client, CONSOLE_TO_GATEWAY, QOS0, MQTTreceviceHandler);
}
// 初始化MQTT客户端(需要依赖以太网)
void Int_MQTT_Init(void)
{
    Int_W5500_Init();

    // 创建通信通道，且需要链接到服务器
    Int_MQTT_CreateSocketAndConnentServer();

    // 创建MQTT客户端
    Int_MQTT_CreateClent();
}

//处理网络数据
void Int_MQTT_Refsh(void){
    MQTTYield(&client,1000);
}
//发布消息
void Int_MQTT_SendMessage(char* topicName, uint8_t* data)   
{
    MQTTMessage msg;
    msg.qos=QOS0;
    msg.payload=data;
    msg.payloadlen=strlen((char*)data);
    MQTTPublish(&client,GATEWAY_TO_CONSOLE,&msg);
}

//注册回调函数
void Int_MQTT_ConsoleGetData(console_callback cb){
    msg_cb=cb;
}


