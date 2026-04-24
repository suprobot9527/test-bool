#include "Com_Delay.h"

//毫秒级延迟
void Com_Delay_ms(uint16_t ms){
    HAL_Delay(ms);
}
//秒级延迟
void Com_Delay_s(uint16_t s){
    while (s--)
    {
        HAL_Delay(1000);
    }
    
}



