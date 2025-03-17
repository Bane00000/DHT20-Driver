/*
 * dht20.h
 *
 *  Created on: Mar 3, 2025
 *      Author: Bane
 */

#ifndef DHT20_INC_DHT20_H_
#define DHT20_INC_DHT20_H_

#include "stm32f4xx_hal.h"

#define DHT20_DEVICE_ADDRESS	0x70
#define ONE_BYTE		1
#define THREE_BYTES		3
#define SIX_BYTES		6

extern I2C_HandleTypeDef hI2Cx;

typedef struct
{
	I2C_HandleTypeDef *i2c_handle;
	uint8_t addres;
	uint8_t readBuffer[6];
	uint32_t data;

} DHT20_t;

/*
 * Init
 * Application user is deciding which I2Cx to use. All the other configurations will already be
 * set in place, except some things like speed.
 * Things that should be able to configure: pins and i2cx
 */
void dht20_init();

// These functions are used in other functions, to encapsulate data transmission
void dht20_write(uint8_t *data, uint16_t size);
void dht20_read(uint8_t *rBuffer, uint16_t size);

/*
 * Deinit
 */
void dht20_deinit(void);

/*
 * Status word
 */
void dht20_check_status_word(void);

/*
 * Measurement command
 */
void dht20_start_measure(void);

/*
 * CRC check data
 */
void dht20_crc_check(void);

/*
 * Calculate temperature
 */
void dht20_calculate_temperature(void);

/*
 * Calculate humidity
 */
void dht20_calculate_humidity(void);

void dht20(void);

#endif /* DHT20_INC_DHT20_H_ */
