/*
 * dht20.h
 *
 *  Created on: Mar 3, 2025
 *      Author: Bane
 */

#ifndef DHT20_INC_DHT20_H_
#define DHT20_INC_DHT20_H_

#include "stm32f4xx_hal.h"

#define DHT20_DEVICE_ADDRESS	0x38
#define DHT20_DEVICE_ADDRESS_WRITE		(DHT20_DEVICE_ADDRESS << 1)
#define DHT20_DEVICE_ADDRESS_READ		(DHT20_DEVICE_ADDRESS_WRITE | 1)
#define STATUS_WORD				0x18

extern I2C_HandleTypeDef hI2Cx;

/*
 * Init
 * Application user is deciding which I2Cx to use. All the other configurations will already be
 * set in place, except some things like speed.
 */
void dht20_init();

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

/*
 * Get temperature
 */
void dht20_get_temperature(void);

/*
 * Get humidity
 */
void dht20_get_humidity(void);

#endif /* DHT20_INC_DHT20_H_ */
