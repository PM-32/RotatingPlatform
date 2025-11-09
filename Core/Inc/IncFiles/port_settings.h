/**
 * @file 	port_settings.h
 *
 * @brief 	в процессе работы программы может понадобиться\n
 * поменять настройки портов, отвечающих за управление\n
 * электродвигателем. Здесь содержится функция, которая\n
 * меняет настройки данных портов.
 *
 * @date 	09.11.2025
 * @author 	Prokopyev
 */

#ifndef INC_INCFILES_PORT_SETTINGS_H_
#define INC_INCFILES_PORT_SETTINGS_H_

#include "main.h"

// Текущее состояние электродвигателя
typedef enum
{
	OFF_MOTOR = 1,				// электродвигатель выключен
	ROTATES_CLOCKWISE,			// электродвигатель вращается по часовой стрелке
	ROTATES_COUNTERCLOCKWISE	// электродвигатель вращается против часовой стрелки
} motor_status;

extern motor_status motor_cond;

void MotorPortsConfig(uint8_t num_config);

#endif /* INC_INCFILES_PORT_SETTINGS_H_ */
