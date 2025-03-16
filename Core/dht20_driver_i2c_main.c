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
}
