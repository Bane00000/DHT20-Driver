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
void dht20_init(I2C_InitTypeDef I2Cx)
{
	/*
	 * Activate clock
	 */
	/*if (I2Cx == I2C1)
	{
		__HAL_RCC_I2C1_CLK_ENABLE();
	}
	else if (I2Cx == I2C2)
	{
		__HAL_RCC_I2C2_CLK_ENABLE();
	}
	else if (I2Cx == I2C3)
	{
		__HAL_RCC_I2C3_CLK_ENABLE();
	}*/

	/*
	 * I2C configuration
	 */
	I2Cx.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	I2Cx.OwnAddress1 = DHT20_DEVICE_ADDRESS;
	I2Cx.DutyCycle = I2C_DUTYCYCLE_2;
	I2Cx.ClockSpeed = 200;
	I2Cx.NoStretchMode = I2C_NOSTRETCH_DISABLE;
}
