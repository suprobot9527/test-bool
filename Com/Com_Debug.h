#ifndef __COM_DEBUG_H__
#define __COM_DEBUG_H__

#include "stdio.h"
#include "usart.h"
#include "string.h"


// 由于调试的printf开发阶段使用较多耗时长，产品上线又不需要存在，所以使用预处理指令实现调试的开关
// 预处理指令：
// development(开发),
// 第一个#表示把前一个逗号去掉（没有可变参数的情况下有效）
// “...”使用可变参数应对printf使用过程中传参的不确定性,在函数中用#__VA_ARGS__
// printf内多个字符串可以直接拼接，中间不需要任何符号
// 代码的裁剪
// strrchr在某一个字符串中找某一个字符（倒着找）
#define DEVELOPMENT

#ifdef DEVELOPMENT

#define FILENAME strrchr(__FILE__, '/') ? (strrchr(__FILE__, '/') + 1) : __FILE__
#define COM_DEBUG(format, ...) printf("[%s:%d]" format, FILENAME, __LINE__, ##__VA_ARGS__)
#define COM_DEBUG_LN(format, ...) printf("[%s:%d]" format "\r\n", FILENAME, __LINE__, ##__VA_ARGS__)
#else
#define COM_DEBUG(format, ...)
#define COM_DEBUG_LN(format, ...)
#endif

#endif /* __COM_DEBUG_H__ */
