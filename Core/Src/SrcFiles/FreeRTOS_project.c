/**
 * @file 	FreeRTOS_project.c
 *
 * @brief 	описание в FreeRTOS_project.h
 * @date 	09.11.2025
 * @author 	Prokopyev
 */

#include "FreeRTOS_project.h"


#define adc_buffer_size 10 ///< Размер массива для хранения данных АЦП (потенциометр)

// Хендлы
TaskHandle_t vGetAdcDataTaskHandle; ///< Хендл задачи по сбору данных с АЦП
TaskHandle_t vMotorControlTaskHandle; ///< Хендл задачи управления электродвигателем

SemaphoreHandle_t xAdcSemaphore = NULL; ///< Хендл бинарного семафора для синхронизации с задачей по сбору данных с АЦП

QueueHandle_t xAdcQueue = NULL; ///< Хендл очереди для передачи значений АЦП в задачу для обработки


/**
 * @brief Создание всех задач, семафоров
 */
void CreateAll(void)
{
	// Создание всех задач
	TasksCreation();

	// Создание всех семафоров
	SemaphoresCreation();

	// Создание всех очередей
	QueuesCreation();
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

	// Задача управления электродвигателем
	xTaskCreationResult = xTaskCreate(vMotorControlTask, "Motor control task", 128, NULL, 1, &vMotorControlTaskHandle);

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
 * @brief Создание всех очередей
 */
void QueuesCreation(void)
{
	// Очередь для передачи значений АЦП
	// (потенциометр) в задачу для обработки
	xAdcQueue = xQueueCreate(1, sizeof(uint16_t));

	// Проверка того, что очередь была успешно создана
	while (xAdcQueue == NULL);
}


/**
 * @brief Задача сбора данных,\n
 * полученных от АЦП (DMA), в массив
 */
void vGetAdcDataTask(void* pvParameters)
{
	// Переменная, хранящая значение
	// текущего преобразования АЦП
	uint16_t adc_value = 0;

	// Запуск АЦП
	HAL_ADC_Start_DMA(&hadc1, (uint32_t*) &adc_value, 1);

	for (;;)
	{
		// Ожидание выдачи семафора
		if (xSemaphoreTake(xAdcSemaphore, portMAX_DELAY) == pdTRUE)
		{
			// Остановка АЦП
			HAL_ADC_Stop_DMA(&hadc1);

			// Отправка значения текущего преобразования АЦП в очередь
			xQueueSend(xAdcQueue, &adc_value, pdMS_TO_TICKS(1000));

			// Запуск АЦП
			HAL_ADC_Start_DMA(&hadc1, (uint32_t*) &adc_value, 1);
		}
	}
}


/**
 * @brief Задача управления электродвигателем
 */
void vMotorControlTask(void* pvParameters)
{
	// Коэффициент преобразования
	// значений АЦП в скважность ШИМ
	float coef = 0.0;

	// Флаг того, что массив adc_poten заполнен
	static uint8_t fArrayIsFull = 0;

	// Принятое из очереди значение
	// текущего преобразования АЦП
	static uint16_t value = 0;

	// Усреднённое значение АЦП
	uint16_t adc_mean = 0;

	// Сумма значений АЦП (для расчёта среднего значения)
	uint32_t adc_sum = 0;

	// Значение для установки скважности ШИМ в процентах
	// (допустимые значения от 20 до 99,
	//  при значении меньше 20 возникают просадки по питанию)
	static uint8_t pwm_value = 20;

	// Начальное состояние мотора - выключен
	motor_status motor_cond = OFF_MOTOR;

	// Массив для хранения данных АЦП (потенциометр)
	static uint16_t adc_poten[adc_buffer_size];

	static uint8_t i = 0;
	uint8_t j = 0;


	// Очистка массива
	memset((void*) &adc_poten, 0, sizeof(adc_poten));

	// Установка конфигурации портов
	// для выключения двигателя
	MotorPortsConfig(motor_cond);

	for (;;)
	{
		// Если значение текущего преобразования АЦП успешно получено
		if (xQueueReceive(xAdcQueue, &value, pdMS_TO_TICKS(1000)) == pdPASS)
		{
			// Сохранение значения в массив
			adc_poten[i++] = value;

			if (i == adc_buffer_size)
			{
				i = 0;

				// Однократная установка флага
				// "массив adc_poten заполнен"
				if (!fArrayIsFull)
					fArrayIsFull = 1;
			}
		}

		// Если массив adc_poten заполнен
		if (fArrayIsFull)
		{
			// Сброс значений
			adc_mean = 0;
			adc_sum = 0;

			// Расчёт среднего значения АЦП
			for (j = 0; j < adc_buffer_size; j++)
				adc_sum += adc_poten[j];

			adc_mean = (uint16_t) (adc_sum / adc_buffer_size);

			// Определение требуемого направления вращения электродвигателя
			// и установка соответствующего коэффициента
			if ((adc_mean >= 0) && (adc_mean <= 2047))
			{
				coef = -0.03857;

				// Двигатель вращается
				// по часовой стрелке
				motor_cond = ROTATES_CLOCKWISE;
			}

			else
			if ((adc_mean >= 2048) && (adc_mean <= 4095))
			{
				coef = 0.03857;

				// Двигатель вращается
				// против часовой стрелки
				motor_cond = ROTATES_COUNTERCLOCKWISE;
			}

			// Установка конфигурации портов
			// для управления двигателем и включение ШИМ
			MotorPortsConfig(motor_cond);

			/*
			 	Преобразование среднего значения АЦП (потенциометр)
			 	в процент скважности ШИМ

			 	Расчётные параметры:
			  	0.03857 = 79(99-20)/2048(4095/2) - коэффициент преобразования;
			  	20 - минимально допустимый процент скважности ШИМ;
			  	2048 - смещение для установки нулевого положения,
			  	соответствует центральному положению ручки потенциометра.
			*/
			pwm_value = (uint8_t) (coef * (adc_mean - 2048) + 20);

			// Ограничение процента скважности ШИМ
			if (pwm_value < 20)
				pwm_value = 20;
			else
			if (pwm_value > 99)
				pwm_value = 99;

			// Установка процента скважности ШИМ
			// по соответствующему направлению вращения
			// каналу таймера 3
			if (motor_cond == ROTATES_CLOCKWISE)
				TIM3->CCR2 = pwm_value;
			else
			if (motor_cond == ROTATES_COUNTERCLOCKWISE)
				TIM3->CCR1 = pwm_value;
		}
	}
}
