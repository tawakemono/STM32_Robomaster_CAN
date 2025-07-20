/*
 * robomaster.h
 *
 *  Created on: Jul 20, 2025
 *      Author: 2005r
 */

#ifndef INC_ROBOMASTER_H_
#define INC_ROBOMASTER_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifdef STM32F4
#include "stm32f4xx_hal.h"
#elif defined STM32F1
#include "stm32f1xx_hal.h"
#endif
#include "main.h"

typedef struct{
	uint16_t encoder;
	int16_t speed_rpm;
	int16_t current;
	uint8_t temperature;
} MotorState;

extern MotorState motorstate[4];

void parse_motor_feedback(CAN_HandleTypeDef* hcan);
void send_motor_current(CAN_HandleTypeDef *hcan, int16_t m1, int16_t m2, int16_t m3, int16_t m4);

#ifdef __cplusplus
}
#endif

#endif /* INC_ROBOMASTER_H_ */
