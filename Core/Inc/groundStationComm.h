/*!
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* @file groundStationComm.h
* @brief Header of groundStationComm.c
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* @author            Étienne Larivière
* @version           1.0.0
* @date              2021.12.01
*
* @copyright         (C) Copyright QMSat
*
*                    Contents and presentations are protected world-wide.
*                    Any kind of using, copying etc. is prohibited without prior permission.
*                    All rights - incl. industrial property rights - are reserved.
*
* @history
* @revision{         1.0.0  , 2021.12.0, author Étienne Larivière, Initial revision }
* @endhistory
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
#ifndef INC_GROUNDSTATIONCOMM_H_
#define INC_GROUNDSTATIONCOMM_H_

/*
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* INCLUDES
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
#include "stdint.h"

#define START 0x7F

typedef enum {
	STX,
	PLL,
	SEQ,
	FLG,
	CMD,
	PL,
	CRC16
} GS_STATES;


/*uint8_t STX;
uint8_t PLL;
uint8_t NACK;
uint8_t SEQ;
uint8_t CMD;
uint8_t FLG;
uint8_t PL[247];
uint16_t CRC16;*/
typedef struct __attribute__((__packed__)) {
	uint8_t data[254];
	GS_STATES state;
	uint8_t counterPL;
	uint8_t counterCRC16;
} gsCommPacket_t, *pgsCommPacket_t;


extern gsCommPacket_t gsCommPacket;


uint16_t CommManagerCRC16(uint8_t* pu8Data, uint16_t u16Length);
uint8_t gsCommManagerProcessBuffer(uint8_t u8Incomming);
void gsCommManagerInit();


#endif /* INC_GROUNDSTATIONCOMM_H_ */
