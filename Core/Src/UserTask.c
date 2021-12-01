/*!
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * @file AppTasks.c
 * @brief Implementation of common task primitives
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * @author            Vasil Milev
 * @version           1.0.0
 * @date              2018.07.04
 *
 * @copyright         (C) Copyright Endurosat
 *
 *                    Contents and presentations are protected world-wide.
 *                    Any kind of using, copying etc. is prohibited without prior permission.
 *                    All rights - incl. industrial property rights - are reserved.
 *
 * @history
 * @revision{         1.0.0  , 2018.07.04, author Vasil Milev, Initial revision }
 * @revision{         1.0.1  , 2020.01.16, author Georgi Georgiev, Moved everything, except StartDefaultTask() to DefTasks.c }
 * @endhistory
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

/*
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * INCLUDES
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

#include  "UserTask.h"
#include "stdio.h"
#include "groundStationComm.h"


/*
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * INTERNAL DEFINES
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
#define APP_TASK_CALL_PERIOD        (500)                              /* given time in ms */
#define SEVENHUNDREDMILLISECONDS 	(700)
#define HUNDREDMILLISECONDS 		(100)
#define TENMILLISECONDS 			(10)
#define ONESECOND					(1000)
#define UART_RX_BUF_SIZE			255

/*
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * INTERNAL TYPES DEFINITION
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

/*
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * EXTERNAL VARIABLES DEFINITION
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
uint32_t u32_SevenHundredMillisecondLoop = 0;
uint32_t u32_HundredMilliSecondLoop_ms = 0;
uint32_t u32_SecondLoop_ms = 0;
/*
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * INTERNAL (STATIC) VARIABLES DEFINITION/DECLARATION
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
uint8_t uart_rx_buf[UART_RX_BUF_SIZE];
uint8_t gsMessage[255];
uint8_t uartBuff[200];
uint16_t printSize;
/*
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * INTERNAL (STATIC) ROUTINES DECLARATION
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

/*
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * EXTERNAL (NONE STATIC) ROUTINES DEFINITION
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
/*!
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * @brief That is a task used as example to configure all sensors and actuators and blinks the green LED.
 * That can be changed freely as needed depending on the project.
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * @param[input]      argument - not used
 * @param[output]     none
 * @return            none
 * @note              none
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
void UserTaskInit(void const *argument) {
	/*
	 * Initialise Device Here
	 */
	HAL_UARTEx_ReceiveToIdle_DMA(&huart3, uart_rx_buf, UART_RX_BUF_SIZE);

	gsMessage[0] = 0x7F;
	gsMessage[1] = 4;
	gsMessage[2] = 0;
	gsMessage[3] = 1;
	gsMessage[4] = 2;
	gsMessage[5] = 1;
	gsMessage[6] = 2;
	gsMessage[7] = 3;
	gsMessage[8] = 4;
	gsMessage[9] = 0x32;
	gsMessage[10] = 0x73;

	UserTaskLoop();

}

/*!
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * @brief This task is the main task loop used by QMSat cubesat
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * @param[input]      argument - not used
 * @param[output]     none
 * @return            none
 * @note              none
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
void UserTaskLoop(void const *argument) {
	/* blink the Amber LED for 50ms to indicate the OBC is running */
	//__HAL_DMA_DISABLE_IT(&huart3, DMA_IT_HT);
	for (;;) {
		if (HAL_GetTick() - u32_SevenHundredMillisecondLoop > SEVENHUNDREDMILLISECONDS) {
			HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
			u32_SevenHundredMillisecondLoop = HAL_GetTick();
		}

		if (HAL_GetTick() - u32_HundredMilliSecondLoop_ms > HUNDREDMILLISECONDS) {
			HAL_GPIO_TogglePin(LD1_GPIO_Port, LD1_Pin);
			u32_HundredMilliSecondLoop_ms = HAL_GetTick();
		}

		if(HAL_GetTick() - u32_SecondLoop_ms > ONESECOND){
			//HAL_UART_Transmit(&huart3, (uint8_t*)"Hello from UserTaskLoop\r\n", 25, 20);
			for (int i = 0; i < sizeof(gsMessage) ;i++){
				uint8_t response = gsCommManagerProcessBuffer(gsMessage[i]);
				if (response == 1){
					printSize = snprintf(uartBuff, sizeof(uartBuff),"**Received from GS**\r\nPayload Length: %d\r\nSquence: %d\r\nFlag: %d\r\nCommand: %d\r\nPayload: %d %d %d %d\r\nCRC16: %x%x\r\n\n", gsCommPacket.data[0], gsCommPacket.data[1], gsCommPacket.data[2], gsCommPacket.data[3], gsCommPacket.data[4], gsCommPacket.data[5], gsCommPacket.data[6], gsCommPacket.data[7], gsCommPacket.data[8], gsCommPacket.data[9]);
					HAL_UART_Transmit(&huart3, uartBuff, printSize, 20);
				}else if (response == 2){
					HAL_UART_Transmit(&huart3, (uint8_t*)"BAD CRC\r\n", 9, 20);
				}
			}
			u32_SecondLoop_ms = HAL_GetTick();
		}
		osDelay(5);
	}
}

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size){
	HAL_UART_Transmit(&huart3, (uint8_t*)"Received\r\n", 10, 20);
	HAL_UARTEx_ReceiveToIdle_DMA(&huart3, (uint8_t*) uart_rx_buf, UART_RX_BUF_SIZE);
    __HAL_DMA_DISABLE_IT(&hdma_usart3_rx, DMA_IT_HT);
}

/*
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * INTERNAL (STATIC) ROUTINES DEFINITION
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
