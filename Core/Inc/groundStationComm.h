/*
 * groundStationComm.h
 *
 *  Created on: 1 déc. 2021
 *      Author: Étienne Larivière
 */

#ifndef INC_GROUNDSTATIONCOMM_H_
#define INC_GROUNDSTATIONCOMM_H_

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
