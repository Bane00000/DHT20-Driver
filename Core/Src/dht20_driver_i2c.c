/*
 * dht20_driver_i2c.c
 *
 *  Created on: Mar 10, 2025
 *      Author: Bane
 */

#include "stm32f4xx_hal.h"
#include "dht20.h"

int main(void)
{
	HAL_Init();
	HAL_Delay(100);

	I2C_HandleTypeDef hI2Cx;

	/*
	* Activate clock for GPIOB
	*/
	__HAL_RCC_GPIOB_CLK_ENABLE(); // TODO: Change according to the application user's need

	/*
	* GPIO configuration
	*/
	GPIO_InitTypeDef i2c_scl;
	i2c_scl.Mode = GPIO_MODE_AF_OD;
	i2c_scl.Pin = GPIO_PIN_6; // TODO: Change according to the application user's need
	i2c_scl.Pull = GPIO_PULLUP;
	i2c_scl.Speed = GPIO_SPEED_FREQ_LOW;
	i2c_scl.Alternate = GPIO_AF4_I2C1; // TODO: Change according to the application user's need

	HAL_GPIO_Init(GPIOB, &i2c_scl);

	GPIO_InitTypeDef i2c_sda;
	i2c_sda.Mode = GPIO_MODE_AF_OD;
	i2c_sda.Pin = GPIO_PIN_7; // TODO: Change according to the application user's need
	i2c_sda.Pull = GPIO_PULLUP;
	i2c_sda.Speed = GPIO_SPEED_FREQ_LOW;
	i2c_sda.Alternate = GPIO_AF4_I2C1; // TODO: Change according to the application user's need

	HAL_GPIO_Init(GPIOB, &i2c_sda);

	/*
	 * I2C handle
	 */
	__HAL_RCC_I2C1_CLK_ENABLE();

	hI2Cx.Instance = I2C1; // TODO: Change according to the application user's need
	hI2Cx.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	hI2Cx.Init.OwnAddress1 = 0x00;
	hI2Cx.Init.DutyCycle = I2C_DUTYCYCLE_2;
	hI2Cx.Init.ClockSpeed = 100000;
	hI2Cx.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
	hI2Cx.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	hI2Cx.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;

	HAL_I2C_Init(&hI2Cx);

	/*
	 * Sending data through I2C
	 */
	uint8_t registers[3] = {0x1B, 0x1C, 0x1E};


	HAL_I2C_Master_Transmit(&hI2Cx, (0x38<<1), registers, 3, 50);

	while(1);
}
