/*
 * gpio_stm32f4xx.h
 *
 *  Created on: Mar 3, 2025
 *      Author: Bane
 */

#ifndef GPIO_INC_GPIO_STM32F4XX_H_
#define GPIO_INC_GPIO_STM32F4XX_H_

#include "stm32f4xx.h"

typedef struct
{
	uint8_t GPIO_PinNumber;
	uint8_t GPIO_PinMode;
	uint8_t GPIO_Speed;
	uint8_t GPIO_PuPd;
	uint8_t GPIO_OType;
	uint8_t GPIO_AltFun;
} GPIO_Config_TypeDef;

typedef struct
{
	GPIO_TypeDef GPIOx;

	GPIO_Config_TypeDef GPIO_Config;

} GPIO_Handle_TypeDef;

void gpio_init(void);

void gpio_deinit(void);

void gpio_read(void);

void gpio_write_pin(GPIO_TypeDef *GPIOx, uint8_t Pin, uint8_t data);


#endif /* GPIO_INC_GPIO_STM32F4XX_H_ */
