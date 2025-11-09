/**
 * @file 	FreeRTOS_priority_settings.c
 *
 * @brief 	описание в FreeRTOS_priority_settings.h
 * @date 	03.11.2025
 * @author 	Prokopyev
 */

#include "FreeRTOS_priority_settings.h"

/**
 * @brief Настройка приоритетов прерываний\n
 * (прерывания включаются при генерации\n
 * кода STM32CubeIDE, здесь только настройка)
 */
void InterruptsSetPriority(void)
{
	HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);
	HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, DMA1_Channel1_INTERRUPT_PRIORITY, 0);
}
