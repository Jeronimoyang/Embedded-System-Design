// 接实验1的硬件配置和初始化代码

// 主机模式设置
void I2C_Master_Config(uint8_t slave_addr) {
    // 设置从机地址和写模式
    I2CMasterSlaveAddrSet(I2C_BASE, slave_addr, false);
}

// 从机模式设置
void I2C_Slave_Config(uint8_t slave_addr) {
    // 绑定从机地址到I2C模块
    I2CSlaveInit(I2C_BASE, slave_addr);
    // 启用从机响应
    I2CSlaveEnable(I2C_BASE);
}

int main() {
    I2C_Init();  // 初始化I2C

    // 配置为主机模式，从机地址0x24
    I2C_Master_Config(0x24);

    // 或配置为从机模式，地址0x24
    // I2C_Slave_Config(0x24);

    while (1);
}