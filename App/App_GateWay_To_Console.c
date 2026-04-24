#include "App_GateWay_To_Console.h"

extern QueueHandle_t sem_handler;
extern QueueHandle_t sem_handler1;

extern uint8_t connect_id;
//数据缓冲区
#define maxsize 50
uint16_t recevice_size =0;
uint8_t recevice_data[maxsize]={0};

uint8_t running=0;
float angle=0;
void App_Set_recevice_data(){

    running=recevice_data[2];
    
    uint16_t tmp=recevice_data[4];
    recevice_data[4]=recevice_data[3];
    recevice_data[3]=tmp;
    tmp=recevice_data[6];
    recevice_data[6]=recevice_data[5];
    recevice_data[5]=tmp;
    
    memcpy(&angle,recevice_data+3,4);
}
void App_SendJsondatatoserver(){
    cJSON *root=cJSON_CreateObject();
    cJSON_AddNumberToObject(root,"device_id",connect_id);
    char str[10]={0};
    sprintf(str,"%.1f",angle);
    cJSON_AddStringToObject(root,"cur_angle",str);
    cJSON_AddStringToObject(root,"motor_status",running?"on" : "off");

    //转换
    char* json=cJSON_PrintUnformatted(root);

    Int_MQTT_SendMessage(GATEWAY_TO_CONSOLE,(uint8_t*)json);
    cJSON_Delete(root);
    cJSON_free(json);
}
void task_T_net(void* pram){
    //检测空闲中断
    HAL_UARTEx_ReceiveToIdle_IT(&huart2,recevice_data,maxsize);
    while (1)
    {
        //等待信号量被释放
        xSemaphoreTake(sem_handler,UINT32_MAX);
        //电机已经启动
        while (1)
        {
            //发送读取指令
            Int_Modbus_ReadInputReg(connect_id,0,3);
            xSemaphoreTake(sem_handler1,2000);
            //调换数组顺序
            App_Set_recevice_data();
            //向服务器上传数据
            App_SendJsondatatoserver();
        }
    }
}
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size){
    HAL_UARTEx_ReceiveToIdle_IT(&huart2,recevice_data,maxsize);

    if (huart->Instance==USART2&&recevice_data[1]==0x04)
    {
        recevice_size=Size;
        //中断信号量的使用
        BaseType_t pxHigherPriorityTaskWoken=pdFALSE;
        xSemaphoreGiveFromISR(sem_handler1,&pxHigherPriorityTaskWoken);
        if (pxHigherPriorityTaskWoken==pdTRUE)
        {
            portYIELD_FROM_ISR(pxHigherPriorityTaskWoken);
        }
    }
}

