#include "App_Console_To_GateWay.h"
extern QueueHandle_t sem_handler;
uint8_t connect_id;
void GetData(char *msg)
{
    printf("%s", msg);
    // 处理CJSON的字符串
    cJSON *JOSN_DATA = cJSON_Parse(msg);
    // 提取json中的数据
    //{"connection_type":"rs485","device_id":5,"motor_status":"on","target_angle":3600,"max_speed":60}
    char *connect_type = cJSON_GetObjectItem(JOSN_DATA, "connection_type")->valuestring;

    connect_id = cJSON_GetObjectItem(JOSN_DATA, "device_id")->valueint;

    float connect_angle = cJSON_GetObjectItem(JOSN_DATA, "target_angle")->valuedouble;
    float connect_speed = cJSON_GetObjectItem(JOSN_DATA, "max_speed")->valuedouble;
    // 释放内存
    cJSON_Delete(JOSN_DATA);

    if (strcmp(connect_type, "rs485") == 0)
    {
        uint16_t cmd_data[4] = {0};
        memcpy(cmd_data, &connect_angle, 4);
        memcpy(cmd_data + 2, &connect_speed, 4);
        Int_Modbus_WriteHoldingRegs16(connect_id, 0, cmd_data, 4);
        // 延时等待电机启动
        Com_Delay_s(1);
        xSemaphoreGive(sem_handler);
    }
}

void task_T(void *pram)
{
    Int_MQTT_Init();
    // Int_MQTT_SendMessage(GATEWAY_TO_CONSOLE,"hello getway");
    Int_MQTT_ConsoleGetData(GetData);
    // uint8_t read1[8] = {0x05, 0x01, 0x00, 0x02, 0x00, 0x01, 0x5D, 0x8E};
    while (1)
    {

        // Int_ModBus_SendCMD(read1,8);

        Int_MQTT_Refsh();

        vTaskDelay(500);
    }
}
