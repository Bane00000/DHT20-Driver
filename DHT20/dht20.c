/*
 * dht20.c
 *
 *  Created on: Mar 3, 2025
 *      Author: Branislav Galović
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

	if (sensor->status_word != STATUS_WORD)
	{
		uint8_t sendBuffer[3] = {INIT_REG_1, INIT_REG_2, INIT_REG_3};
		dht20_write(sensor, sendBuffer, THREE_BYTES);
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

	uint8_t sendBuffer[3] = {MEASUREMENT_COMMAND, PARAMETER_ONE, PARAMETER_TWO};

	dht20_write(sensor, sendBuffer, THREE_BYTES);

	HAL_Delay(80);
	dht20_read(sensor, sensor->readBuffer, SIX_BYTES);

	if ((sensor->readBuffer[0] & STATUS_WORD_BIT_SEVEN_MASK) == 0)
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
	sensor->data = humidity_calculation(sensor);
	sensor->humidity = humidity_formula(sensor);

	sensor->data = temperature_calculation(sensor);
	sensor->temperature = temperature_formula(sensor);
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

/**
  * @brief  Calculating humidity with raw data
  * @param  sensor DHT20 struct
  * @retval uint32_t
  */
uint32_t humidity_calculation(DHT20_t *sensor)
{
	return ((uint32_t)sensor->readBuffer[3] >> 4)
					| ((uint32_t)sensor->readBuffer[2] << 4)
					| ((uint32_t)sensor->readBuffer[1] << 12);
}

/**
  * @brief  Calculating temperature with raw data
  * @param  sensor DHT20 struct
  * @retval uint32_t
  */
uint32_t temperature_calculation(DHT20_t *sensor)
{
	return (((uint32_t)sensor->readBuffer[3] & 0x0F) << 16)
				| ((uint32_t)sensor->readBuffer[4] << 8)
				| (uint32_t)sensor->readBuffer[5];
}

/**
  * @brief  Returning humidity value with the formula
  * @param  sensor DHT20 struct
  * @retval float
  */
float humidity_formula(DHT20_t *sensor)
{
	return sensor->data * 100.0f / (1 << 20);
}

/**
  * @brief  Returning temperature value with the formula
  * @param  sensor DHT20 struct
  * @retval float
  */
float temperature_formula(DHT20_t *sensor)
{
	return sensor->data * 200.0f / (1 << 20) - 50;
}
