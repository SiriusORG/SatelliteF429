/*
 * obtDriver.h
 *
 *  Created on: 2 déc. 2021
 *      Author: Gabriel Quirion
 */

#ifndef INC_OBTDRIVER_H_
#define INC_OBTDRIVER_H_

#include <stdint.h>
#include <stdbool.h>

//Downlink frame and buffer size -> 40 frames with a maximum payload size of 235 bytes
//Uplink frame and buffer size -> 40 frames with a maximum payload size of 200 bytes


//-----------------------Command codes---------------------------
#define WATCHDOG_RESET 0xCC
#define SOFTWARE_RESET 0xAA
#define HARDWARE_RESET 0xAB

//Receiver
#define OBT_ADDR_RX 0x60

#define NUMBER_FRAMES_IN_RECEIVEBUFFER 0x21
#define FRAME_FROM_RECEIVE_BUFFER 0x22
#define REMOVE_FRAME_FROM_RECEIVE_BUFFER 0x24
#define MEASURE_ALL_TELEMETRY_CHANNELS_RX 0x1A
#define REPORT_RECEIVER_UPTIME 0x40

//Transmitter
#define OBT_ADDR_TX 0x61

#define SEND_A_FRAME 0x10
#define SEND_AX25_FRAME_WITH_OVERRIDE_CALL_SIGNS 0x11
#define SET_BEACON 0x14
#define SET_AX25_BEACON_WITH_OVERRIDE_CALL_SIGNS 0x15
#define CLEAR_BEACON 0x1F
#define SET_DEFAULT_AX25_TO_CALL_SIGNS 0x22
#define SET_DEFAULT_AX25_FROM_CALL_SIGNS 0x23
#define SET_TRANSMITTER_IDLE_STATE 0x24
#define MEASURE_ALL_TELEMETRY_CHANNELS_TX 0x25
#define GET_STORED_TELEMETRY_CHANNELS_DURING_LAST_TRANSMISSION 0x26
#define SET_AX25_TRANSMISSION_BITRATE 0x28
#define REPORT_TRANSMISSION_UPTIME 0x40
#define REPORT_TRANSMISSION_STATE 0x41

uint8_t obtBufferTransmitter[255];

//---------------------------------Function Prototypes--------------------------------


//Receiver
bool obtWatchdogResetRx();
bool obtSoftwareResetRx();
bool obtHardwareResetRx();
bool obtGetNumberOfFramesInRxBufferRx(uint8_t* num);
bool obtGetFrameFromRxBufferRx(uint8_t* rxBuffer);
bool obtRemoveFrameFromRxBufferRx();
bool obtMeasureAllTelemetryChannelsRx(uint8_t* values);
bool obtReportReceiverUptimeRx(uint8_t* uptime);

//Transmitter
bool obtWatchdogResetTx();
bool obtSoftwareResetTx();
bool obtHardwareResetTx();
bool obtSendFrameTx(uint8_t* txBuffer, uint8_t size, uint8_t* returnVal);
bool obtSendAX25FrameWithOverrideCallsignsTx(uint8_t* txBuffer, uint8_t size, uint8_t* returnVal);
bool obtSetBeaconTx(uint8_t* txBuffer, uint8_t size);
bool obtSetAX25BeaconWithOverrideCallsignsTx(uint8_t* txBuffer, uint8_t size);
bool obtClearBeaconTx();
bool obtSetDefaultAX25TOCallsign(uint8_t* txBuffer);
bool obtSetDefaultAX25FROMCallsign(uint8_t* txBuffer);
bool obtSetTxIdleState(uint8_t OnOffBit);
bool obtMeasureAllTelemetryChannelsTx(uint8_t* values);
bool obtGetStoredTelemetryChannelsDuringLastTransmissionTx(uint8_t* values);
bool obtSetAX25TransmissionBitrateTx(uint8_t bitrate);
bool obtReportReceiverUptimeTx(uint8_t* uptime);
bool obtReportTransmitterStateTx(uint8_t* state);


#endif /* INC_OBTDRIVER_H_ */

