/*
 * dht20_driver_i2c.c
 *
 *  Created on: Mar 10, 2025
 *      Author: Bane
 */

#include "stm32f4xx_hal.h"
//#include "dht20.h"

#define DHT20_ADDRESS 0x70
I2C_HandleTypeDef hI2Cx;

int main(void)
{
    HAL_Init();
    HAL_Delay(100);

    /*
     * Aktivacija clock-a za GPIOB
     */
    __HAL_RCC_GPIOB_CLK_ENABLE();

    /*
     * Konfiguracija GPIO pinova za I2C
     */
    GPIO_InitTypeDef i2c_pins;
    i2c_pins.Pin = GPIO_PIN_6 | GPIO_PIN_9;
    i2c_pins.Mode = GPIO_MODE_AF_OD;
    i2c_pins.Pull = GPIO_PULLUP;
    i2c_pins.Speed = GPIO_SPEED_FREQ_LOW;
    i2c_pins.Alternate = GPIO_AF4_I2C1;
    HAL_GPIO_Init(GPIOB, &i2c_pins);

    /*
     * Inicijalizacija I2C
     */
    __HAL_RCC_I2C1_CLK_ENABLE();

    hI2Cx.Instance = I2C1;
    hI2Cx.Init.ClockSpeed = 100000;
    hI2Cx.Init.DutyCycle = I2C_DUTYCYCLE_2;
    hI2Cx.Init.OwnAddress1 = 0;
    hI2Cx.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    hI2Cx.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    hI2Cx.Init.OwnAddress2 = 0;
    hI2Cx.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    hI2Cx.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
    HAL_I2C_Init(&hI2Cx);

    /*
    * DHT20 CONFIGURATION
    */
    // DHT20_INIT
    uint8_t readBuffer;
    HAL_Delay(40);
    HAL_I2C_Master_Receive(&hI2Cx, DHT20_ADDRESS, &readBuffer, 1, HAL_MAX_DELAY);
    if ((readBuffer & 0x08) == 0x00)
    {
    	uint8_t sendBuffer[3] = {0xBE, 0x08, 0x00};
    	HAL_I2C_Master_Transmit(&hI2Cx, DHT20_ADDRESS, sendBuffer, 3, HAL_MAX_DELAY);
    }
    if (readBuffer != 0x18)
    {
    	uint8_t sendBuffer[3] = {0x1B, 0x1C, 0x1E};
        HAL_I2C_Master_Transmit(&hI2Cx, DHT20_ADDRESS, sendBuffer, 3, HAL_MAX_DELAY);
    }

    // DHT20_READ
    uint8_t sendBuffer[3] = {0xAC, 0x33, 0x00};
    uint8_t rBuffer[6];

    HAL_I2C_Master_Transmit(&hI2Cx, DHT20_ADDRESS, sendBuffer, 3, HAL_MAX_DELAY);
    HAL_Delay(75);
    HAL_I2C_Master_Receive(&hI2Cx, DHT20_ADDRESS, rBuffer, 6, HAL_MAX_DELAY);

    if ((rBuffer[0] & 	0x80) == 0x00)
    {
    	uint32_t data = 0;
    	data = ((uint32_t)rBuffer[3] >> 4)
    			+ ((uint32_t)rBuffer[2] << 4)
				+ ((uint32_t)rBuffer[1] << 12);

    	float Humidity = data * 100.0f / (1 << 20);

    	data = (((uint32_t)rBuffer[3] & 0x0F) << 16)
    			+ ((uint32_t)rBuffer[4] << 8)
				+ (uint32_t)rBuffer[5];

    	float Temperature = data * 200.0f / (1 << 20) - 50;
    }
    HAL_Delay(10000);
}
