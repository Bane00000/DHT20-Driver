/*
 * dht20_driver_i2c_test.c
 *
 *  Created on: Mar 8, 2025
 *      Author: Bane
 */

#include "stm32f4xx_hal.h"
#include "dht20.h"

/*
 * TODO: Test the code. Check if registers for GPIO and I2C are correctly configured. If they are,
 * implement the send_data function.
 */

/*
 * PB6-> SCL
 * PB7 -> SDA
 */

void gpio_config(void)
{
	/*
	* Activate clock for GPIOB
	*/
	__HAL_RCC_GPIOB_CLK_ENABLE();

	/*
	* GPIO configuration
	*/
	GPIO_InitTypeDef i2c_scl;
	i2c_scl.Mode = GPIO_MODE_AF_OD;
	i2c_scl.Pin = GPIO_PIN_6;
	i2c_scl.Pull = GPIO_NOPULL;
	i2c_scl.Speed = GPIO_SPEED_FREQ_HIGH;
	i2c_scl.Alternate = GPIO_AF4_I2C1;

	HAL_GPIO_Init(GPIOB, &i2c_scl);

	GPIO_InitTypeDef i2c_sda;
	i2c_sda.Mode = GPIO_MODE_AF_OD;
	i2c_sda.Pin = GPIO_PIN_7;
	i2c_sda.Pull = GPIO_NOPULL;
	i2c_sda.Speed = GPIO_SPEED_FREQ_HIGH;
	i2c_sda.Alternate = GPIO_AF4_I2C1;

	HAL_GPIO_Init(GPIOB, &i2c_sda);
}

I2C_HandleTypeDef i2c_config(void)
{
	/*
	* Activate clock for I2C1
	*/
	__HAL_RCC_I2C1_CLK_ENABLE();

	/*
	* I2C configuration
	*/
	I2C_HandleTypeDef hi2c;

	hi2c.Instance = I2C1;
	hi2c.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	hi2c.Init.OwnAddress1 = DHT20_DEVICE_ADDRESS;
	// hi2c.Init.OwnAddress2 = 0;
	hi2c.Init.DutyCycle = I2C_DUTYCYCLE_2;
	hi2c.Init.ClockSpeed = 100000;
	hi2c.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
	hi2c.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	hi2c.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;

	HAL_I2C_Init(&hi2c);

	return hi2c;
}

int main(void)
{
	HAL_Init();

	gpio_config();

	//i2c_config();

	/*
	* Activate clock for I2C1
	*/
	__HAL_RCC_I2C1_CLK_ENABLE();

	/*
	* I2C configuration
	*/
	I2C_HandleTypeDef hi2c;

	hi2c.Instance = I2C1;
	hi2c.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	hi2c.Init.OwnAddress1 = DHT20_DEVICE_ADDRESS;
	// hi2c.Init.OwnAddress2 = 0;
	hi2c.Init.DutyCycle = I2C_DUTYCYCLE_2;
	hi2c.Init.ClockSpeed = 100000;
	hi2c.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
	hi2c.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	hi2c.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;

	HAL_I2C_Init(&hi2c);

	// Sending dummy data
	uint8_t TX_Buffer[] = "A";

	HAL_I2C_Master_Transmit(&hi2c, DHT20_DEVICE_ADDRESS, TX_Buffer, 1, 1000);
	HAL_Delay(100);


	while(1);
}
