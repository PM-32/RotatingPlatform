/**
 * @file 	FreeRTOS_project.c
 *
 * @brief 	описание в FreeRTOS_project.h
 * @date 	03.11.2025
 * @author 	User
 */

#include "FreeRTOS_project.h"


#define adc_buffer_size 10 ///< Размер массива для хранения данных АЦП (потенциометр)

volatile uint16_t adc_value = 0; ///< Переменная, хранящая значение текущего преобразования АЦП

// Хендлы задач, семафоров
TaskHandle_t vGetAdcDataTaskHandle; ///< Хендл задачи по сбору данных с АЦП
SemaphoreHandle_t xAdcSemaphore = NULL; ///< Хендл бинарного семафора для синхронизации с задачей по сбору данных с АЦП


/**
 * @brief Создание всех задач, семафоров
 */
void CreateAll(void)
{
	// Создание всех задач
	TasksCreation();

	// Создание всех семафоров
	SemaphoresCreation();
}


/**
 * @brief Создание всех задач
 */
void TasksCreation(void)
{
	BaseType_t xTaskCreationResult;

	// Задача для сбора данных с АЦП (DMA)
	xTaskCreationResult = xTaskCreate(vGetAdcDataTask, "Get ADC data task", 128, NULL, 1, &vGetAdcDataTaskHandle);

	// Проверка того, что задача успешно создана
	while (xTaskCreationResult != pdPASS);
}


/**
 * @brief Создание всех семафоров
 */
void SemaphoresCreation(void)
{
	// Бинарный семафор для синхронизации
	// прерывания DMA и задачи по сбору данных с АЦП (DMA)
	xAdcSemaphore = xSemaphoreCreateBinary();

	// Проверка того, что семафор был успешно создан
	while (xAdcSemaphore == NULL);
}


/**
 * @brief Задача сбора данных,\n
 * полученных от АЦП (DMA), в массив
 */
void vGetAdcDataTask(void* pvParameters)
{
	// Массив для хранения данных АЦП (потенциометр)
	static uint16_t adc_poten[adc_buffer_size];
	static uint8_t i = 0;

	// Очистка массива
	memset((void*) &adc_poten, 0, sizeof(adc_poten));

	for (;;)
	{
		// Ожидание выдачи семафора
		if (xSemaphoreTake(xAdcSemaphore, portMAX_DELAY) == pdTRUE)
		{
			// Остановка АЦП
			HAL_ADC_Stop_DMA(&hadc1);

			// Получение данных от DMA
			adc_poten[i++] = adc_value;

			if (i == adc_buffer_size)
				i = 0;

			// Запуск АЦП
			HAL_ADC_Start_DMA(&hadc1, (uint32_t*) &adc_value, 1);
		}
	}
}
