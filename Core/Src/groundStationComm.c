/*!
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * @file AppTasks.c
 * @brief Implementation of common task primitives
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * @author            Étienne Larivière
 * @version           1.0.0
 * @date              2021.12.01
 *
 * @copyright         (C) Copyright Endurosat
 *
 *                    Contents and presentations are protected world-wide.
 *                    Any kind of using, copying etc. is prohibited without prior permission.
 *                    All rights - incl. industrial property rights - are reserved.
 *
 * @history
 * @revision{         1.0.0  , 2021.12.01, author Étienne Larivière, Initial revision }
 * @endhistory
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

/*
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * INCLUDES
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

#include "groundStationComm.h"
#include "stdio.h"

gsCommPacket_t gsCommPacket;

void gsCommManagerInit(){
	gsCommPacket.state = STX;
}

uint16_t CommManagerCRC16(uint8_t* pu8Data, uint16_t u16Length) {
    uint8_t i;
    uint16_t u16crc = 0xffff;

    while (u16Length--) {
    u16crc ^= *(unsigned char *)pu8Data++ << 8;
        for (i=0; i < 8; i++)
        u16crc = u16crc & 0x8000 ? (u16crc << 1) ^ 0x1021 : u16crc << 1;
    }
    return u16crc & 0xffff;
}

uint8_t gsCommManagerProcessBuffer(uint8_t u8Incomming){

	uint8_t returnValue = 0;
	uint16_t calculatedCRC16 = 0;
	uint16_t receivedCRC16 = 0;

	switch(gsCommPacket.state){
		case STX:
			if (u8Incomming == START){
				gsCommPacket.counterPL = 0;
				gsCommPacket.counterCRC16 = 0;
				gsCommPacket.state = PLL;
			}
			break;
		case PLL:
			gsCommPacket.data[0] = u8Incomming;
			gsCommPacket.state = SEQ;
			break;
		case SEQ:
			gsCommPacket.data[1] = u8Incomming;
			gsCommPacket.state = FLG;
			break;
		case FLG:
			gsCommPacket.data[2] = u8Incomming;
			gsCommPacket.state = CMD;
			break;
		case CMD:
			gsCommPacket.data[3] = u8Incomming;
			gsCommPacket.state = PL;
			break;
		case PL:

			gsCommPacket.data[4 + gsCommPacket.counterPL++] = u8Incomming;

			if (gsCommPacket.counterPL >= gsCommPacket.data[0])
				gsCommPacket.state = CRC16;

			break;
		case CRC16:
			gsCommPacket.data[4 + gsCommPacket.counterPL + gsCommPacket.counterCRC16++] = u8Incomming;

			if (gsCommPacket.counterCRC16 == 2){
				calculatedCRC16 = CommManagerCRC16(gsCommPacket.data, 4 + gsCommPacket.counterPL);
				receivedCRC16 = (gsCommPacket.data[4 + gsCommPacket.counterPL] << 8) + gsCommPacket.data[5 + gsCommPacket.counterPL];

				if (calculatedCRC16 == receivedCRC16){
					gsCommPacket.state = STX;
					returnValue = 1;
				}else{
					returnValue = 2;
				}
			}

			break;
	}
	return returnValue;
}



