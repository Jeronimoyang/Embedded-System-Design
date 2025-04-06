#include <stdbool.h>
#include <stdint.h>

#include "driverlib/gpio.h"
#include "driverlib/i2c.h"
#include "driverlib/sysctl.h"
#include "inc/hw_i2c.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"

// 硬件配置（以TM4C123G为例）
#define I2C_PERIPHERAL SYSCTL_PERIPH_I2C0
#define GPIO_PERIPHERAL SYSCTL_PERIPH_GPIOB
#define SDA_PIN GPIO_PIN_3
#define SCL_PIN GPIO_PIN_2
#define I2C_BASE I2C0_BASE

void I2C_Init() {
    // 1. 使能I2C和GPIO模块时钟
    SysCtlPeripheralEnable(I2C_PERIPHERAL);
    SysCtlPeripheralEnable(GPIO_PERIPHERAL);

    // 2. 配置GPIO引脚复用功能
    GPIOPinConfigure(GPIO_PB2_I2C0SCL);
    GPIOPinConfigure(GPIO_PB3_I2C0SDA);
    GPIOPinTypeI2CSCL(GPIO_PORTB_BASE, SCL_PIN);
    GPIOPinTypeI2C(GPIO_PORTB_BASE, SDA_PIN);

    // 3. 配置I2C主模式，时钟速率100kbps
    I2CMasterInitExpClk(I2C_BASE, SysCtlClockGet(), false);

    // 4. 启用I2C模块
    I2CMasterEnable(I2C_BASE);
}