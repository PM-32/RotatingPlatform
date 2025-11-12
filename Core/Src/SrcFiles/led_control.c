/**
 * @file 	led_control.c
 *
 * @brief 	описание в led_control.h
 * @date 	12.11.2025
 * @author 	Prokopyev
 */

#include "led_control.h"

/**
 * @brief Функция управления светодиодами
 * @param permission_flag флаг_разрешения_работы_светодиодов
 * @param motor_state статус_электродвигателя
 */
void LED_Control(uint8_t permission_flag, uint8_t motor_state)
{
	// Включение светодиодов, если их работа разрешена
	if (permission_flag)
	{
		if (motor_state & 0x01)
			HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
		else
			HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);

		if (motor_state & 0x02)
			HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET);
		else
			HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET);

		if (motor_state & 0x04)
			HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_SET);
		else
			HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_RESET);
	}

	// Выключение светодиодов, если их работа запрещена
	else
	{
		HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_RESET);
	}
}
