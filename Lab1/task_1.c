#include <stdint.h>

#include "inc/tm4c123gh6pm.h"

int main(void) {
    // 声明一个 32 位无符号整数变量，使用 volatile 关键字修饰
    volatile uint32_t ui32Loop;
    // 1. 设置时钟（5分）
    // 启动 GPIOF 时钟，0x20 对应第5位，表示 GPIOF
    SYSCTL_RCGCGPIO_R |= 0x20;
    // 等待 GPIOF 时钟启动
    while ((SYSCTL_PRGPIO_R & 0x20) == 0);
    // 2. 配置端口F的引脚1和引脚2为数字输出模式（5分）
    // 设置 PF1 和 PF2 为输出
    GPIO_PORTF_DIR_R |= 0x06;
    // 设置 PF1 和 PF2 为数字输出
    GPIO_PORTF_DEN_R |= 0x06;
    // 3. 编写程序，使led红蓝闪烁（10分）
    // 无限循环
    while (1) {
        // 设置 PF1 为高电平，PF2 为低电平，即红灯亮
        GPIO_PORTF_DATA_R = 0x02;
        // 计数延时
        for (ui32Loop = 0; ui32Loop < 1000000; ui32Loop++);
        // 设置 PF1 为低电平，PF2 为高电平，即蓝灯亮
        GPIO_PORTF_DATA_R = 0x04;
        // 计数延时
        for (ui32Loop = 0; ui32Loop < 1000000; ui32Loop++);
    }
    return 0;
}