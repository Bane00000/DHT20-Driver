/*
 * gpio_stm32f4xx.c
 *
 *  Created on: Mar 3, 2025
 *      Author: Bane
 */

#include "gpio_stm32f4xx.h"

void gpio_init(GPIO_Handle_TypeDef *GPIOHandle)
{
	// GPIO clock activation
	if (GPIOHandle->GPIOx == GPIOA)
	{
		RCC_AHB1ENR_GPIOAEN();
	}
	else if (GPIOHandle->GPIOx == GPIOD)
	{
		RCC_AHB1ENR_GPIODEN();
	}

	if (GPIOHandle->GPIO_Config->GPIO_PinMode == GPIO_MODE_INPUT)
	{
		GPIOHandle->GPIOx->MODER &= ~(3u << (PinNumber*2));
	}
	else if (GPIOHandle->GPIO_Config->GPIO_PinMode == GPIO_MODE_OUTPUT)
	{
		GPIOHandle->GPIOx->MODER |= (1u << (PinNumber*2));
	}
}

void gpio_deinit(void);

void gpio_read(void);

void gpio_write_pin(GPIO_TypeDef *GPIOx, uint8_t Pin, uint8_t data)
{
	if (data == 1)
	{
		GPIOx->ODR |= (1u << Pin);
	}
	else if (data == 0)
	{
		GPIOx->ODR &= ~(1u << Pin);
	}
}
