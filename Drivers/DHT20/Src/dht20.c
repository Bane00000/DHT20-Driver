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
	I2Cx.OwnAddress1 = DHT20_DEVICE_ADDRESS;
	I2Cx.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
}
