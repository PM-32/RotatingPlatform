/**
 * @file FreeRTOS_project.h
 *
 * @brief используется для работы с FreeRTOS.\n
 * Содержится создание задач/семафоров, а также\n
 * их исходный код (логика задач).
 *
 * @date 08.11.2025
 * @author Prokopyev
 */

#ifndef INC_FREERTOS_PROJECT_H_
#define INC_FREERTOS_PROJECT_H_

#include "main.h"
#include "string.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"
#include "FreeRTOS_priority_settings.h"
#include "port_settings.h"


// Handle
extern TaskHandle_t vGetAdcDataTaskHandle;
extern TaskHandle_t vMotorControlTaskHandle;
extern SemaphoreHandle_t xAdcSemaphore;
extern QueueHandle_t xAdcQueue;

extern ADC_HandleTypeDef hadc1;
extern TIM_HandleTypeDef htim3;

// Прототипы функций
void CreateAll(void);
void TasksCreation(void);
void SemaphoresCreation(void);
void QueuesCreation(void);

void vGetAdcDataTask(void* pvParameters);
void vMotorControlTask(void* pvParameters);

#endif /* INC_FREERTOS_PROJECT_H_ */
