#include <stdint.h>

#include "inc/tm4c123gh6pm.h"

int main(void) {
    // 定义 ui32Loop 为按键按下的时间计数
    volatile uint32_t ui32Loop = 0;
    // 定义 ui8flag 为 LED 的状态，0为熄灭，1为点亮
    uint8_t ui8flag = 0;
    // 使能GPIO端口F的时钟（5分）
    // 开启 GPIOF 时钟
    SYSCTL_RCGCGPIO_R |= 0x20;
    // 等待 GPIOF 时钟启动
    while ((SYSCTL_PRGPIO_R & 0x20) == 0);
    // 配置PF2为输出（连接到LED）（5分）
    GPIO_PORTF_DIR_R |= 0x04;    // 设置 PF2 为输出
    GPIO_PORTF_DEN_R |= 0x04;    // 设置 PF2 为数字输出
    GPIO_PORTF_DATA_R &= ~0x04;  // 确保 PF2 为低电平，初始状态 LED 熄灭
    // 配置PF4为输入（连接到按钮）（5分）
    GPIO_PORTF_DIR_R &= ~0x10;  // 设置 PF4 为输入
    GPIO_PORTF_PUR_R |= 0x10;   // 设置 PF4 为上拉电阻
    GPIO_PORTF_DEN_R |= 0x10;   // 设置 PF4 为数字输入
    // 编写程序，完成按键控制led的亮灭任务（10分）
    volatile uint32_t j;  // 定义计数变量
    while (1) {
        // 检测按键是否按下
        if ((GPIO_PORTF_DATA_R & 0x10) == 0) {
            // 每次按键按下时清零计数
            ui32Loop = 0;
            // 持续检测按键是否保持按下
            while ((GPIO_PORTF_DATA_R & 0x10) == 0) {
                // 按键按下计时
                ui32Loop++;
                // 每次按键按下计时延时
                for (j = 0; j < 1000; j++);
                // 如果按键按下时间超过 1 秒，跳出循环
                if (ui32Loop >= 1000) break;
            }
            // 如果按键按下时间超过 1 秒
            if (ui32Loop >= 1000) {
                // 切换 LED 状态
                ui8flag ^= 1;
                // 根据 LED 状态点亮或熄灭 LED
                if (ui8flag) {
                    // 点亮LED
                    GPIO_PORTF_DATA_R |= 0x04;
                } else {
                    // 熄灭LED
                    GPIO_PORTF_DATA_R &= ~0x04;
                }
                // 等待按键释放
                while ((GPIO_PORTF_DATA_R & 0x10) == 0);
            }
        }
    }
}
