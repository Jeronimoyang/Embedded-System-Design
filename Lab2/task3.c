// 接实验1的硬件配置和初始化代码
#include "driverlib/uart.h"
#include "utils/uartstdio.h"

// UART初始化
void UART_Init() {
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    UARTConfigSetExpClk(
        UART0_BASE, SysCtlClockGet(), 115200,
        UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE);
    UARTEnable(UART0_BASE);
}

// 主机发送数据
void Master_Send(uint8_t data) {
    I2CMasterDataPut(I2C_BASE, data);
    I2CMasterControl(I2C_BASE, I2C_MASTER_CMD_SINGLE_SEND);
    while (I2CMasterBusy(I2C_BASE));  // 等待传输完成
    UARTprintf("[主机发送] 数据: 0x%02X\n", data);
}

// 从机接收并回送数据
void Slave_Process() {
    if (I2CSlaveStatus(I2C_BASE) & I2C_SLAVE_ACT_RREQ) {
        uint8_t data = I2CSlaveDataGet(I2C_BASE);
        I2CSlaveDataPut(I2C_BASE, data);  // 回送数据
        UARTprintf("[从机接收] 数据: 0x%02X\n", data);
    }
}

int main() {
    I2C_Init();
    UART_Init();

    // 配置为主机或从机（需根据实验连接选择）
    // I2C_Master_Config(0x24);
    // Master_Send(0x55);

    // 或配置为从机
    I2C_Slave_Config(0x24);
    while (1) {
        Slave_Process();
    }
}