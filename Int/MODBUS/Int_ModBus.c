#include "Int_ModBus.h"

// 发命令
void Int_ModBus_SendCMD(uint8_t *cmd, uint16_t length)
{
    HAL_UART_Transmit(&huart2, cmd, length, 1000);
    // 主设备命令不能发送太频繁，否则会一直占用总线导致从设备无法响应
    Com_Delay_ms(100);
    // 测试发送
    printf("gateway send cmd:");
    for (uint16_t i = 0; i < length; i++)
    {
        printf("%02x ", cmd[i]);
    }
    printf("\n");
}

/**
 * @brief 读线圈
 */
void Int_Modbus_ReadCoil(uint8_t dev_id, uint16_t start_addr, uint16_t num)
{
    // 创建发送的指令
    uint8_t cmd[8] = {0};               //
    cmd[0] = dev_id;                     // 从机地址
    cmd[1] = 0x01;                       // 功能码
    cmd[2] = ((start_addr >> 8) & 0xff); // 读取地址的高位
    cmd[3] = (start_addr & 0xff);        // 读取地址的低位
    cmd[4] = ((num >> 8) & 0xff);        // 读取数量的高位
    cmd[5] = (num & 0xff);               // 读取数量的低位

    uint16_t CRC_Data = usMBCRC16(cmd, 6); // 获取CRC校验码
    cmd[6] = (CRC_Data & 0xff);            // 校验码低位
    cmd[7] = ((CRC_Data >> 8) & 0xff);     // 校验码高位
    // 发送命令
    Int_ModBus_SendCMD(cmd, 8);
}

/**
 * @brief 读离散输入
 */
void Int_Modbus_ReadInputStatus(uint8_t dev_id, uint16_t start_addr, uint16_t num)
{
    // 创建发送的指令
    uint8_t cmd[8] = {0};               //
    cmd[0] = dev_id;                     // 从机地址
    cmd[1] = 0x02;                       // 功能码
    cmd[2] = ((start_addr >> 8) & 0xff); // 读取地址的高位
    cmd[3] = (start_addr & 0xff);        // 读取地址的低位
    cmd[4] = ((num >> 8) & 0xff);        // 读取数量的高位
    cmd[5] = (num & 0xff);               // 读取数量的低位

    uint16_t CRC_Data = usMBCRC16(cmd, 6); // 获取CRC校验码
    cmd[6] = (CRC_Data & 0xff);            // 校验码低位
    cmd[7] = ((CRC_Data >> 8) & 0xff);     // 校验码高位
    // 发送命令
    Int_ModBus_SendCMD(cmd, 8);
}

/**
 * @brief 读保持寄存器
 */
void Int_Modbus_ReadHoldingReg(uint8_t dev_id, uint16_t start_addr, uint16_t num)
{
    // 创建发送的指令
    uint8_t cmd[8] = {0};               //
    cmd[0] = dev_id;                     // 从机地址
    cmd[1] = 0x03;                       // 功能码
    cmd[2] = ((start_addr >> 8) & 0xff); // 读取地址的高位
    cmd[3] = (start_addr & 0xff);        // 读取地址的低位
    cmd[4] = ((num >> 8) & 0xff);        // 读取数量的高位
    cmd[5] = (num & 0xff);               // 读取数量的低位

    uint16_t CRC_Data = usMBCRC16(cmd, 6); // 获取CRC校验码
    cmd[6] = (CRC_Data & 0xff);            // 校验码低位
    cmd[7] = ((CRC_Data >> 8) & 0xff);     // 校验码高位
    // 发送命令
    Int_ModBus_SendCMD(cmd, 8);
}

/**
 * @brief 读输入寄存器
 */
void Int_Modbus_ReadInputReg(uint8_t dev_id, uint16_t start_addr, uint16_t num)
{
    // 创建发送的指令
    uint8_t cmd[8] = {0};               //
    cmd[0] = dev_id;                     // 从机地址
    cmd[1] = 0x04;                       // 功能码
    cmd[2] = ((start_addr >> 8) & 0xff); // 读取地址的高位
    cmd[3] = (start_addr & 0xff);        // 读取地址的低位
    cmd[4] = ((num >> 8) & 0xff);        // 读取数量的高位
    cmd[5] = (num & 0xff);               // 读取数量的低位

    uint16_t CRC_Data = usMBCRC16(cmd, 6); // 获取CRC校验码
    cmd[6] = (CRC_Data & 0xff);            // 校验码低位
    cmd[7] = ((CRC_Data >> 8) & 0xff);     // 校验码高位
    // 发送命令
    Int_ModBus_SendCMD(cmd, 8);
}

/**
 * @brief 写单个线圈
 */
void Int_Modbus_WriteCoil(uint8_t dev_id, uint16_t start_addr, uint8_t value)
{
    // 创建发送的指令
    uint8_t cmd[8] = {0};               //
    cmd[0] = dev_id;                     // 从机地址
    cmd[1] = 0x05;                       // 功能码
    cmd[2] = ((start_addr >> 8) & 0xff); // 写入地址的高位
    cmd[3] = (start_addr & 0xff);        // 写入地址的低位

    cmd[4] = ((value >> 8) & 0xff); // 写入数据的高位
    cmd[5] = (value & 0xff);        // 写入数据的低位

    uint16_t CRC_Data = usMBCRC16(cmd, 6); // 获取CRC校验码
    cmd[6] = (CRC_Data & 0xff);            // 校验码低位
    cmd[7] = ((CRC_Data >> 8) & 0xff);     // 校验码高位
    // 发送命令
    Int_ModBus_SendCMD(cmd, 8);
}

/**
 * @brief 写单个保持寄存器
 */
void Int_Modbus_WriteHoldingReg(uint8_t dev_id, uint16_t start_addr, uint16_t value)
{
    // 创建发送的指令
    uint8_t cmd[8] = {0};               //
    cmd[0] = dev_id;                     // 从机地址
    cmd[1] = 0x06;                       // 功能码
    cmd[2] = ((start_addr >> 8) & 0xff); // 写入地址的高位
    cmd[3] = (start_addr & 0xff);        // 写入地址的低位

    cmd[4] = ((value >> 8) & 0xff); // 写入数据的高位
    cmd[5] = (value & 0xff);        // 写入数据的低位

    uint16_t CRC_Data = usMBCRC16(cmd, 6); // 获取CRC校验码
    cmd[6] = (CRC_Data & 0xff);            // 校验码低位
    cmd[7] = ((CRC_Data >> 8) & 0xff);     // 校验码高位
    // 发送命令
    Int_ModBus_SendCMD(cmd, 8);
}

/**
 * @brief 写多个线圈
 */
void Int_Modbus_WriteCoils(uint8_t dev_id, uint16_t start_addr, uint16_t num, uint8_t *value)
{

    uint8_t data_size = num % 8 ? (num / 8 + 1) : (num / 8); // 计算数据合并后的宽度
    uint8_t size = data_size + 9;                            // 命令的总长度
    uint8_t *cmd = pvPortMalloc(size);                       // 利用FreeRTOS动态管理数组

    cmd[0] = dev_id;                     // 从机地址
    cmd[1] = 0x0F;                       // 功能码
    cmd[2] = ((start_addr >> 8) & 0xff); // 写入地址的高位
    cmd[3] = (start_addr & 0xff);        // 写入地址的低位
    cmd[4] = (num >> 8) & 0xff;          // 数量高位
    cmd[5] = num & 0xff;                 // 数量低位
    cmd[6] = data_size;                  // 字节数

    for (uint8_t i = 0; i < data_size; i++)
    {
        uint8_t byte_data = 0;
        for (uint8_t j = 0; j < 8; j++)
        {
            byte_data |= (value[j + i * 8] << j);
        }
        cmd[7 + i] = byte_data;
    }

    uint16_t CRC_Data = usMBCRC16(cmd, size - 2); // 获取CRC校验码
    cmd[size - 2] = (CRC_Data & 0xff);            // 校验码低位
    cmd[size - 1] = ((CRC_Data >> 8) & 0xff);     // 校验码高位

    // 发送命令
    Int_ModBus_SendCMD(cmd, size);

    vPortFree(cmd); // 释放内存
}
/**
 * @brief 写多个保持寄存器  按寄存器数组写入
 */
void Int_Modbus_WriteHoldingRegs16(uint8_t dev_id, uint16_t start_addr, uint16_t *reg_data, uint16_t reg_len)
{
    uint8_t data_size = reg_len * 2;    // 数据拆分后的长度
    uint8_t size = data_size + 9;        // 命令的总长度
    uint8_t *cmd = pvPortMalloc(size);   // 利用FreeRTOS动态管理数组
    cmd[0] = dev_id;                     // 从机地址
    cmd[1] = 0x10;                       // 功能码
    cmd[2] = ((start_addr >> 8) & 0xff); // 写入地址的高位
    cmd[3] = (start_addr & 0xff);        // 写入地址的低位
    cmd[4] = (reg_len >> 8) & 0xff;      // 数量高位
    cmd[5] = reg_len & 0xff;             // 数量低位
    cmd[6] = data_size;                  // 字节数

    for (uint8_t i = 0; i < reg_len; i++)
    {
        cmd[7 + i * 2] = (reg_data[i] >> 8) & 0xff;
        cmd[8 + i * 2] = reg_data[i] & 0xff;
    }

    uint16_t CRC_Data = usMBCRC16(cmd, size - 2); // 获取CRC校验码
    cmd[size - 2] = (CRC_Data & 0xff);            // 校验码低位
    cmd[size - 1] = ((CRC_Data >> 8) & 0xff);     // 校验码高位

    // 发送命令
    Int_ModBus_SendCMD(cmd, size);

    vPortFree(cmd); // 释放内存
}
