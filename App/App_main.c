#include "App_main.h"
QueueHandle_t sem_handler;
QueueHandle_t sem_handler1;
// TaskHandle_t task_T_Handle_t;
void App_main_Start(void)
{
    sem_handler = xSemaphoreCreateBinary();
    sem_handler1 = xSemaphoreCreateBinary();
    BaseType_t ret1 = xTaskCreate(task_T, "task_T", 1024, NULL, 5, NULL);
    BaseType_t ret2 = xTaskCreate(task_T_net, "task_T_net", 1024, NULL, 5, NULL);
    if (ret1 != pdPASS )
    {
        printf("task_T creation failed!\n");
    }
    if (ret2 != pdPASS)
    {
        printf("task_T_net creation failed!\n");
    }
    vTaskStartScheduler();
}
