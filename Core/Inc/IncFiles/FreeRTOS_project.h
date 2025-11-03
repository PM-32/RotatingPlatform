/**
 * @file FreeRTOS_project.h
 *
 * @brief используется для работы с FreeRTOS.\n
 * Содержится создание задач/семафоров, а также\n
 * их исходный код (логика задач).
 *
 * @date 03.11.2025
 * @author User
 */

#ifndef INC_FREERTOS_PROJECT_H_
#define INC_FREERTOS_PROJECT_H_

#include "main.h"
#include "string.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "FreeRTOS_priority_settings.h"


// Handle задач, семафоров
extern TaskHandle_t vGetAdcDataTaskHandle;
extern SemaphoreHandle_t xAdcSemaphore;

// Переменная, хранящая значение
// текущего преобразования АЦП
extern volatile uint16_t adc_value;

extern ADC_HandleTypeDef hadc1;

// Прототипы функций
void CreateAll(void);
void TasksCreation(void);
void SemaphoresCreation(void);

void vGetAdcDataTask(void* pvParameters);

#endif /* INC_FREERTOS_PROJECT_H_ */
