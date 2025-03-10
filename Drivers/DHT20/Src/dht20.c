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
 * If the status word and 0x18 are not equal to 0x18, initialize registers
 */
void dht20_check_status_word(void)
{
	static uint8_t *rBuffer = 0;

	HAL_I2C_Master_Receive(&hI2Cx, DHT20_DEVICE_ADDRESS_READ, rBuffer, 1, 1000);
	HAL_Delay(100);

	if (*rBuffer != STATUS_WORD)
	{
		uint8_t init_registers[3] = {0x1B, 0x1C, 0x1E};

		HAL_I2C_Master_Transmit(&hI2Cx, DHT20_DEVICE_ADDRESS_WRITE, init_registers, 3, 1000);
	}
}

/*
 * Measurement command
 */
void dht20_start_measure(void)
{
	HAL_Delay(10);

	*rBuffer = 0;
	uint8_t read_status_word = 0x40;

	HAL_Delay(10);
	uint8_t trigger_measurement[3] = {0xAC, 0x33, 0x00};

	// Send commands to trigger measurement
	HAL_I2C_Master_Transmit(&hI2Cx, DHT20_DEVICE_ADDRESS_WRITE, trigger_measurement, 3, 1000);
	HAL_Delay(80);

	// Check if the measurement is complete, if not then wait
	HAL_I2C_Master_Receive(&hI2Cx, DHT20_DEVICE_ADDRESS_READ, rBuffer, 1, 1000);

	while (rBuffer & (1 << 6) != 0);

	// Receive raw temperature and humidity data
	*rBuffer = 0;
	HAL_I2C_Master_Receive(&hI2Cx, DHT20_DEVICE_ADDRESS_READ, rBuffer, 1, 1000);
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
	uint32_t humidity_raw = 0;
	uint8_t humidity_calculated = 0;

	humidity_raw = ((uint32_t)rBuffer[0] << 12)
			| ((uint32_t)rBuffer[1] << 4)
			| ((rBuffer[2] & 0xF0) >> 4);

	humidity_calculated = (humidity_raw / 1048576) * 100;
}
