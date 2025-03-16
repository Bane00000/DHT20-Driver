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

I2C_HandleTypeDef hI2Cx;
static uint8_t rBuffer[1] = {0};

void dht20_write(uint8_t *data, uint16_t size)
{
	HAL_I2C_Master_Transmit(&hI2Cx, DHT20_ADDRESS, *data, size, HAL_MAX_DELAY);
}

void dht20_read(uint8_t *rBuffer, uint16_t size)
{
	HAL_I2C_Master_Receive(&hI2Cx, DHT20_ADDRESS, *rBuffer, size, HAL_MAX_DELAY);
}

void dht20_init()
{
	GPIO_InitTypeDef i2c_pins;
	i2c_pins.Pin = GPIO_PIN_6 | GPIO_PIN_9; // Change
	i2c_pins.Mode = GPIO_MODE_AF_OD;
	i2c_pins.Pull = GPIO_PULLUP;
	i2c_pins.Speed = GPIO_SPEED_FREQ_LOW;
	i2c_pins.Alternate = GPIO_AF4_I2C1; // Change
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
}

/*
 * Status word
 * If the status word and 0x18 are not equal to 0x18, initialize registers
 */
void dht20_check_status_word(void)
{
	HAL_Delay(100);

	uint8_t *readBuffer = 0;
	uint8_t sendBuffer[3] = {0x1B, 0x1C, 0x1E};

	dht20_read(*readBuffer, ONE_BYTE);

	if (*readBuffer != 0x18)
	{
		dht20_write(sendBuffer, THREE_BYTES);
	}
}

/*
 * Measurement command
 */
void dht20_start_measure(void)
{
	HAL_Delay(10);

	uint8_t sendBuffer[3] = {0xAC, 0x33, 0x00};
	uint8_t readBuffer[6] = {0};

	dht20_write(sendBuffer, THREE_BYTES);

	HAL_Delay(80);
	dht20_read(readBuffer, SIX_BYTES);

	// Wait for the measurement to be completed
	while ((readBuffer[0] & 0x70) != 0){};
}

/*
 * CRC check data
 */
void dht20_crc_check(void);

/*
 * Calculate humidity
 */
void dht20_calculate_humidity(void)
{
	uint32_t data = 0;
	data = ((uint32_t)rBuffer[3] >> 4)
			+ ((uint32_t)rBuffer[2] << 4)
			+ ((uint32_t)rBuffer[1] << 12);

	float Humidity = data * 100.0f / (1 << 20);
}

void dht20_calculate_temperature(void)
{
	data = (((uint32_t)rBuffer[3] & 0x0F) << 16)
			+ ((uint32_t)rBuffer[4] << 8)
			+ (uint32_t)rBuffer[5];

	float Temperature = data * 200.0f / (1 << 20) - 50;
}

void dht20(void)
{
	dht20_check_status_word();

	dht20_start_measure();

	dht20_calculate_humidity();

	dht20_calculate_temperature();
}
