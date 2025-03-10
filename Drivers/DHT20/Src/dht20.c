/*
 * dht20.c
 *
 *  Created on: Mar 3, 2025
 *      Author: Bane
 */

#include "dht20.h"

/*
 * Init
 * Application user is deciding which I2Cx to use. All the other configurations will already be
 * set in place, except some things like speed.
 */
void dht20_init()
{
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
	i2c_scl.Pull = GPIO_NOPULL;
	i2c_scl.Speed = GPIO_SPEED_FREQ_HIGH;
	i2c_scl.Alternate = GPIO_AF4_I2C1; // TODO: Change according to the application user's need

	HAL_GPIO_Init(GPIOB, &i2c_scl);

	GPIO_InitTypeDef i2c_sda;
	i2c_sda.Mode = GPIO_MODE_AF_OD;
	i2c_sda.Pin = GPIO_PIN_7; // TODO: Change according to the application user's need
	i2c_sda.Pull = GPIO_NOPULL;
	i2c_sda.Speed = GPIO_SPEED_FREQ_HIGH;
	i2c_sda.Alternate = GPIO_AF4_I2C1; // TODO: Change according to the application user's need

	HAL_GPIO_Init(GPIOB, &i2c_sda);

	/*
	 * I2C handle
	 */
	hI2Cx.Instance = I2C1; // TODO: Change according to the application user's need
	hI2Cx.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	hI2Cx.Init.OwnAddress1 = DHT20_DEVICE_ADDRESS;
	hI2Cx.Init.DutyCycle = I2C_DUTYCYCLE_2;
	hI2Cx.Init.ClockSpeed = 100000;
	hI2Cx.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
	hI2Cx.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	hI2Cx.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;

	HAL_I2C_Init(&hI2Cx);
}

/*
 * Status word
 */
void dht20_check_status_word(void)
{
	uint8_t status_word = 0x71; // DHT20_DEVICE_ADDRESS_READ
}
