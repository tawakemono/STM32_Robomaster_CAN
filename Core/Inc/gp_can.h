/*
 * gp_can.h
 *
 *  Created on: Jul 20, 2025
 *      Author: 2005r
 */

#ifndef INC_GP_CAN_H_
#define INC_GP_CAN_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifdef STM32F4
#include "stm32f4xx_hal.h"
#elif defined STM32F1
#include "stm32f1xx_hal.h"
#endif
#include "main.h"

void set_can_filter_all(CAN_HandleTypeDef *hcan);
void can_send_data(CAN_HandleTypeDef *hcan, int16_t canID, int16_t message[]);
void parse_can_feedback(CAN_HandleTypeDef *hcan, uint16_t canID, uint8_t data[]);
void conv_uint8_to_uint16(uint8_t data[8], uint16_t out_data[4]);

#ifdef __cplusplus
}
#endif

#endif /* INC_GP_CAN_H_ */
