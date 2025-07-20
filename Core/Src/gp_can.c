/*
 * gp_can.c
 *
 *  Created on: Jul 20, 2025
 *      Author: 2005r
 */

#include "can.h"

//フィルター設定(全受信)
void set_can_filter_all(CAN_HandleTypeDef *hcan){
  CAN_FilterTypeDef filter;
  filter.FilterIdHigh         = 0x0000;
  filter.FilterIdLow          = 0x0000;
  filter.FilterMaskIdHigh     = 0x0000;
  filter.FilterMaskIdLow      = 0x0000;
  filter.FilterScale          = CAN_FILTERSCALE_16BIT;
  filter.FilterFIFOAssignment = CAN_FILTER_FIFO0;
  filter.FilterBank           = 0;
  filter.FilterMode           = CAN_FILTERMODE_IDMASK;
  filter.FilterActivation     = ENABLE;
  filter.SlaveStartFilterBank = 14;

  HAL_CAN_ConfigFilter(hcan, &filter);
}

void can_send_data(CAN_HandleTypeDef *hcan, uint16_t canID, uint16_t message[]) {
    //送信用インスタンス等
	CAN_TxHeaderTypeDef TxHeader;
	uint32_t TxMailbox;
	uint8_t TxData[8];

    TxHeader.DLC = 8;
    TxHeader.StdId = canID;
    TxHeader.IDE = CAN_ID_STD;
    TxHeader.RTR = CAN_RTR_DATA;
    TxHeader.TransmitGlobalTime = DISABLE;

	if (0 < HAL_CAN_GetTxMailboxesFreeLevel(hcan)) {

		TxData[0] = (message[0] >> 8) & 0xFF;
		TxData[1] = message[0] & 0xFF;
		TxData[2] = (message[1] >> 8) & 0xFF;
		TxData[3] = message[1] & 0xFF;
		TxData[4] = (message[2] >> 8) & 0xFF;
		TxData[5] = message[2] & 0xFF;
		TxData[6] = (message[3] >> 8) & 0xFF;
		TxData[7] = message[3] & 0xFF;
		//CANメッセージを送信
		if (HAL_CAN_AddTxMessage(hcan, &TxHeader, TxData, &TxMailbox) != HAL_OK) {
			Error_Handler();
		}

	}
}

void parse_can_feedback(CAN_HandleTypeDef *hcan, uint16_t canID, uint8_t data[]) {
	CAN_RxHeaderTypeDef RxHeader;//受信メッセージの情報が格納されるインスタンス
	uint8_t RxData[8];//受信したデータを一時保存する配列
	int16_t id;
	if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxHeader, RxData)== HAL_OK) {
		id = RxHeader.StdId; // RxHeaderの中に入っているidを取り出す
		if (id == canID){
			for (int i = 0; i <= 7; i++){
    				data[i] = RxData[i];
			}
			/*USER CODE BEGIN*/

			/*USER CODE END*/
		}
	}
}

void conv_uint8_to_uint16(uint8_t data[8], uint16_t out_data[4]){
	for(int i=0; i < 8; i += 2){
		out_data[i/2] = (data[i] << 8) | data[i+1];
	}
}

