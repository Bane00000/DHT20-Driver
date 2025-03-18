/*
 * dht20.h
 *
 *  Created on: Mar 3, 2025
 *      Author: Branislav Galović
 */

#ifndef DHT20_INC_DHT20_H_
#define DHT20_INC_DHT20_H_

#include "stm32f4xx_hal.h"

#define DHT20_DEVICE_ADDRESS	(0x38 << 1)
#define ONE_BYTE		1
#define THREE_BYTES		3
#define SIX_BYTES		6

typedef struct
{
	I2C_HandleTypeDef *i2c_handle;		/* I2C handle */
	uint8_t addres;				/* Address of DHT20 sensor */
	uint8_t status_word;			/* First byte received to check if it's equal to 0x18 */
	uint8_t readBuffer[6];			/* 6 bytes for temperature and humidity */
	uint32_t data;				/* Raw data for temperature and humidity */
	float temperature;			/* Temperature value */
	float humidity;				/* Humidity value */
} DHT20_t;

void dht20_init(DHT20_t *sensor, I2C_HandleTypeDef *i2c);
void dht20_deinit(void);

static void dht20_write(DHT20_t *sensor, uint8_t *data, uint16_t size);
static void dht20_read(DHT20_t *sensor, uint8_t *rBuffer, uint16_t size);

void dht20_check_status_word(DHT20_t *sensor);
uint8_t dht20_read_measurement(DHT20_t *sensor);
void dht20_parse_data(DHT20_t *sensor);

void dht20_sensor_read(DHT20_t *sensor);

#endif /* DHT20_INC_DHT20_H_ */
