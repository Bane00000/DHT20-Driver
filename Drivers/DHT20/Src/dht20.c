/*
 * dht20.c
 *
 *  Created on: Mar 3, 2025
 *      Author: Bane
 */

#include "dht20.h"

/**
  * @brief  Initialize DHT20 struct
  * @param  sensor DHT20 struct
  * @param	i2c Pointer to I2C handle struct
  * @retval void
  */
void dht20_init(DHT20_t *sensor, I2C_HandleTypeDef *i2c)
{
	sensor->i2c_handle = i2c;
	sensor->addres = DHT20_DEVICE_ADDRESS;
}

/**
  * @brief  Transmits in master mode an amount of data in blocking mode.
  * @param  data Pointer to data buffer
  * @param	size Amount of data to be sent
  * @retval void
  */
static void dht20_write(DHT20_t *sensor, uint8_t *data, uint16_t size)
{
	HAL_I2C_Master_Transmit(sensor->i2c_handle, sensor->addres, data, size, HAL_MAX_DELAY);
}

/**
  * @brief  Receives in master mode an amount of data in blocking mode.
  * @param  data Pointer to data buffer
  * @param	size Amount of data to be received
  * @retval void
  */
static void dht20_read(DHT20_t *sensor, uint8_t *rBuffer, uint16_t size)
{
	HAL_I2C_Master_Receive(sensor->i2c_handle, sensor->addres, rBuffer, size, HAL_MAX_DELAY);
}

/**
  * @brief  Get a byte of status word and check if it's correct
  * @param  sensor DHT20 struct
  * @retval void
  */
void dht20_check_status_word(DHT20_t *sensor)
{
	HAL_Delay(100);

	dht20_read(sensor, &sensor->status_word, ONE_BYTE);

	if (sensor->status_word != 0x18)
	{
		uint8_t sendBuffer[3] = {0x1B, 0x1C, 0x1E};
		dht20_write(sensor, sendBuffer, 3);
	}
}

/**
  * @brief  Sensor starts measuring
  * @param  sensor DHT20 struct
  * @retval void
  */
uint8_t dht20_read_measurement(DHT20_t *sensor)
{
	HAL_Delay(10);

	uint8_t sendBuffer[3] = {0xAC, 0x33, 0x00};

	dht20_write(sensor, sendBuffer, THREE_BYTES);

	HAL_Delay(80);
	dht20_read(sensor, sensor->readBuffer, SIX_BYTES);

	// Wait for the measurement to be completed
	if ((sensor->readBuffer[0] & 0x80) == 0)
		return 1;
	return 0;

}

/**
  * @brief  Calculate temperature and humidty based on received buffer
  * @param  sensor DHT20 struct
  * @retval void
  */
void dht20_parse_data(DHT20_t *sensor)
{
	// Humidity calculation
	sensor->data = ((uint32_t)sensor->readBuffer[3] >> 4)
				| ((uint32_t)sensor->readBuffer[2] << 4)
				| ((uint32_t)sensor->readBuffer[1] << 12);

	sensor->humidity = sensor->data * 100.0f / (1 << 20);

	// Temperature calculation
	sensor->data = (((uint32_t)sensor->readBuffer[3] & 0x0F) << 16)
			| ((uint32_t)sensor->readBuffer[4] << 8)
			| (uint32_t)sensor->readBuffer[5];

	sensor->temperature = sensor->data * 200.0f / (1 << 20) - 50;
}

/**
  * @brief  Reading the sensor
  * @param  sensor DHT20 struct
  * @retval void
  */
void dht20_read_sensor(DHT20_t *sensor)
{
	dht20_check_status_word(sensor);

	dht20_read_measurement(sensor);

	dht20_parse_data(sensor);
}
