/*
 * dht20_driver_i2c_main.c
 *
 *  Created on: Mar 16, 2025
 *      Author: Bane
 */

#include "stm32f4xx_hal.h"
#include "dht20.h"

int main(void)
{
	dht20_init();

	dht20();

	while(1);

	/*
	 * 	GPIO_InitTypeDef i2c_pins;
	i2c_pins.Pin = GPIO_PIN_6 | GPIO_PIN_9; // Change
	i2c_pins.Mode = GPIO_MODE_AF_OD;
	i2c_pins.Pull = GPIO_PULLUP;
	i2c_pins.Speed = GPIO_SPEED_FREQ_LOW;
	i2c_pins.Alternate = GPIO_AF4_I2C1; // Change
	HAL_GPIO_Init(GPIOB, &i2c_pins);
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
	*/
}
