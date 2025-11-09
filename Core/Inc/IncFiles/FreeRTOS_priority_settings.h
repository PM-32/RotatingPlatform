/**
 * @file 	FreeRTOS_priority_settings.h
 *
 * @brief 	используется для настройки приоритетов\n
 * прерываний для корректной работы FreeRTOS.\n
 *
 * @attention 	Приоритет прерывания, в котором используется
 * API FreeRTOS (например, xSemaphoreGiveFromISR),\n
 * должен быть ниже, чем configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY\n
 * (из файла FreeRTOSConfig.h) по смыслу (не численно!).\n
 * Приоритеты прерываний численно должны быть больше\n
 * configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY и\n
 * меньше или равно configLIBRARY_LOWEST_INTERRUPT_PRIORITY.\n
 * Это справедливо для Cortex-M3, где приоритет прерывания тем выше,\n
 * чем меньше численное значение приоритета (значение 0 = максимальный\n
 * приоритет прерывания), на других мк может быть иначе.\n
 * В данном случае имеется 16 уровней приоритетов, прерываниям\n
 * можно установить численные значения от 6 до 15.
 *
 * @date 	03.11.2025
 * @author 	Prokopyev
 */

#ifndef INC_INCFILES_FREERTOS_PRIORITY_SETTINGS_H_
#define INC_INCFILES_FREERTOS_PRIORITY_SETTINGS_H_

#include "FreeRTOS_project.h"

// Приоритеты прерываний
#define DMA1_Channel1_INTERRUPT_PRIORITY (configLIBRARY_LOWEST_INTERRUPT_PRIORITY - 5)

// Прототипы функций
void InterruptsSetPriority(void);

#endif /* INC_INCFILES_FREERTOS_PRIORITY_SETTINGS_H_ */
