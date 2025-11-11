/**
 * @file 	led_control.h
 *
 * @brief 	здесь содержится функция управления светодиодами
 * @date 	11.11.2025
 * @author 	Prokopyev
 */

#ifndef INC_INCFILES_LED_CONTROL_H_
#define INC_INCFILES_LED_CONTROL_H_

#include "main.h"

/**
 * @brief Текущее состояние электродвигателя\n
 * (бит 3 указывает на направление поворота:\n
 * 0 - против часовой, 1 - по часовой)
 */
typedef enum
{
	OFF_MOTOR = 0b000,				///< двигатель выключен
	COUNTERCLOCKWISE_46 = 0b001,	///< двигатель вращается против часовой стрелки со скоростью от 20 до 46 %
	COUNTERCLOCKWISE_72 = 0b011,	///< двигатель вращается против часовой стрелки со скоростью от 47 до 72%
	COUNTERCLOCKWISE_99 = 0b111,	///< двигатель вращается против часовой стрелки со скоростью от 72 до 99%
	CLOCKWISE_46 = 0b1100,			///< двигатель вращается по часовой стрелке со скоростью от 20 до 46 %
	CLOCKWISE_72 = 0b1110,			///< двигатель вращается по часовой стрелке со скоростью от 47 до 72%
	CLOCKWISE_99 = 0b1111			///< двигатель вращается по часовой стрелке со скоростью от 72 до 99%
} motor_status;

extern motor_status motor_cond;

void LED_Control(uint8_t motor_state);

#endif /* INC_INCFILES_LED_CONTROL_H_ */
