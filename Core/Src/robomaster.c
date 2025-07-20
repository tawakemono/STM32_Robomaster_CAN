/*
 * robomaster.c
 *
 *  Created on: Jul 20, 2025
 *      Author: 2005r
 */

#include "robomaster.h"
#include "can.h"

MotorState motorstate[4];

void parse_motor_feedback(CAN_HandleTypeDef *hcan) {
	CAN_RxHeaderTypeDef RxHeader;//受信メッセージの情報が格納されるインスタンス
	uint8_t RxData[8];//受信したデータを一時保存する配列
	uint8_t use_data[8];
	int id;
	if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxHeader, RxData)== HAL_OK) {
		id = RxHeader.StdId; // RxHeaderの中に入っているidを取り出す
		if (id == 0x201){
			for (int i = 0; i <= 7; i++){
    				use_data[i] = RxData[i];
			}
			motorstate[0].encoder = (use_data[0] << 8) | use_data[1];
			motorstate[0].speed_rpm = (use_data[2] << 8) | use_data[3];
			motorstate[0].current = (use_data[4] << 8) | use_data[5];
			motorstate[0].temperature = use_data[6];
		} else if(id == 0x202){
			for (int i = 0; i <= 7; i++){
    				use_data[i] = RxData[i];
			}
			motorstate[1].encoder = (use_data[0] << 8) | use_data[1];
			motorstate[1].speed_rpm = (use_data[2] << 8) | use_data[3];
			motorstate[1].current = (use_data[4] << 8) | use_data[5];
			motorstate[1].temperature = use_data[6];
		} else if(id == 0x203){
			for (int i = 0; i <= 7; i++){
    				use_data[i] = RxData[i];
			}
			motorstate[2].encoder = (use_data[0] << 8) | use_data[1];
			motorstate[2].speed_rpm = (use_data[2] << 8) | use_data[3];
			motorstate[2].current = (use_data[4] << 8) | use_data[5];
			motorstate[2].temperature = use_data[6];
		} else if(id == 0x204){
			for (int i = 0; i <= 7; i++){
    				use_data[i] = RxData[i];
			}
			motorstate[2].encoder = (use_data[0] << 8) | use_data[1];
			motorstate[2].speed_rpm = (use_data[2] << 8) | use_data[3];
			motorstate[2].current = (use_data[4] << 8) | use_data[5];
			motorstate[2].temperature = use_data[6];
		}
	}
}

void send_motor_current(CAN_HandleTypeDef *hcan, int16_t m1, int16_t m2, int16_t m3, int16_t m4) {
    //送信用インスタンス等
	CAN_TxHeaderTypeDef TxHeader;
	uint32_t TxMailbox;
	uint8_t TxData[8];

    TxHeader.DLC = 8;
    TxHeader.StdId = 0x200;
    TxHeader.IDE = CAN_ID_STD;
    TxHeader.RTR = CAN_RTR_DATA;
    TxHeader.TransmitGlobalTime = DISABLE;

	if (0 < HAL_CAN_GetTxMailboxesFreeLevel(hcan)) {

		TxData[0] = (m1 >> 8) & 0xFF;
		TxData[1] = m1 & 0xFF;
		TxData[2] = (m2 >> 8) & 0xFF;
		TxData[3] = m2 & 0xFF;
		TxData[4] = (m3 >> 8) & 0xFF;
		TxData[5] = m3 & 0xFF;
		TxData[6] = (m4 >> 8) & 0xFF;
		TxData[7] = m4 & 0xFF;
		//CANメッセージを送信
		if (HAL_CAN_AddTxMessage(hcan, &TxHeader, TxData, &TxMailbox) != HAL_OK) {
			Error_Handler();
		}

	}
}
