#include "Int_W5500.h"
wiz_NetInfo default_net_info = {
    .mac = {0x00, 0x08, 0x9c, 0x12, 0x92, 0x12},
    .ip = {192, 168, 55, 230},
    .gw = {192, 168, 55, 1},
    .sn = {255, 255, 255, 0},
    .dns = {8, 8, 8, 8},
    };

void wizchip_setnetWork(wiz_NetInfo* pnetinfo)
{
   setSHAR(pnetinfo->mac);//mac
   setGAR(pnetinfo->gw);//网关
   setSUBR(pnetinfo->sn);//掩码
   setSIPR(pnetinfo->ip);//IP
}
//打印获取到的网络信息
wiz_NetInfo net_info;
void wizchip_getnetWork(wiz_NetInfo* pnetinfo)
{
    printf("111");
   getSHAR(pnetinfo->mac);
   getGAR(pnetinfo->gw);
   getSUBR(pnetinfo->sn);
   getSIPR(pnetinfo->ip);
}
//初始化
void Int_W5500_Init(void){
    printf("123");
    //注册函数
    user_register_callback();
    //复位
    HAL_GPIO_WritePin(W5500_RST_GPIO_Port,W5500_RST_Pin,GPIO_PIN_RESET);
    Com_Delay_ms(10);
    HAL_GPIO_WritePin(W5500_RST_GPIO_Port,W5500_RST_Pin,GPIO_PIN_SET);
    Com_Delay_ms(10);
    //配置网络信息
    wizchip_setnetWork(&default_net_info);
    HAL_Delay(8000);
    //HAL_Delay(8000);
    // printf("222");
    // wizchip_getnetWork(&net_info);
    // printf("123");
    // printf("please try ping %d.%d.%d.%d\r\n", net_info.ip[0], net_info.ip[1], net_info.ip[2], net_info.ip[3]);

}



