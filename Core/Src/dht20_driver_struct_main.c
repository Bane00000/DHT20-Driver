/*
 * dht20_driver_struct_main.c
 *
 *  Created on: Mar 17, 2025
 *      Author: Bane
 */

#include "dht20.h"
#include "stm32f4xx_hal.h"

void button_conf(void);
void gpio_conf(void);
void i2c_conf(void);

I2C_HandleTypeDef hI2Cx;

int main(void)
{
	HAL_Init();
	HAL_Delay(1000);

	// Initializing button, gpio pins for i2c and i2c
	gpio_conf();
	i2c_conf();

	// Initializing sensor
	DHT20_t sensor = {0};
	sensor.addres = DHT20_DEVICE_ADDRESS;
	sensor.i2c_handle = &hI2Cx;

	dht20_init(&sensor, &hI2Cx);

	dht20_read_sensor(&sensor);

	while(1)
	{
		HAL_Delay(20000);
	}
}

void button_conf(void)
{
	__HAL_RCC_GPIOA_CLK_ENABLE();

	GPIO_InitTypeDef GPIOBtn;
	GPIOBtn.Mode = GPIO_MODE_INPUT;
	GPIOBtn.Pin = GPIO_PIN_0;
	GPIOBtn.Pull = GPIO_PULLUP;
	GPIOBtn.Speed = GPIO_SPEED_FREQ_LOW;

	HAL_GPIO_Init(GPIOA, &GPIOBtn);
}

void gpio_conf(void)
{
	GPIO_InitTypeDef i2c_pins;
	i2c_pins.Pin = GPIO_PIN_6 | GPIO_PIN_9; // Change
	i2c_pins.Mode = GPIO_MODE_AF_OD;
	i2c_pins.Pull = GPIO_PULLUP;
	i2c_pins.Speed = GPIO_SPEED_FREQ_LOW;
	i2c_pins.Alternate = GPIO_AF4_I2C1; // Change
	HAL_GPIO_Init(GPIOB, &i2c_pins);
	__HAL_RCC_I2C1_CLK_ENABLE();
}

void i2c_conf(void)
{
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
}
