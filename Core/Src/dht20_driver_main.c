/*
 * dht20_driver_main.c
 *
 *  Created on: Mar 3, 2025
 *      Author: Bane
 */

#include "stm32f4xx_hal.h"

int main(void)
{
	HAL_Init();

	/* GPIO configuration for button */
	GPIO_InitTypeDef Button;

	__HAL_RCC_GPIOA_CLK_ENABLE();

	Button.Pin = GPIO_PIN_0;
	Button.Mode = GPIO_MODE_INPUT;
	Button.Pull = GPIO_PULLDOWN;

	HAL_GPIO_Init(GPIOA, &Button);

	/* GPIO configuration for LED */
	GPIO_InitTypeDef LED;

	__HAL_RCC_GPIOD_CLK_ENABLE();

	LED.Pin = GPIO_PIN_12;
	LED.Mode = GPIO_MODE_OUTPUT_PP;
	LED.Pull = GPIO_NOPULL;
	LED.Speed = GPIO_SPEED_FAST;

	HAL_GPIO_Init(GPIOD, &LED);

	while(1)
	{
		if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0))
		{
			HAL_Delay(100);
			HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_12);
			HAL_Delay(100);
		}
	}
}
