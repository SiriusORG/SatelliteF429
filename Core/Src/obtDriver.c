/*
 * obtDriver.c
 *
 * TO BE TESTED
 *
 *  Created on: 2 déc. 2021
 *      Author: Gabriel Quirion
 */

#include "obtDriver.h"
#include "i2c.h"

//OBT Responses -> The least significant byte is transmitted first (little endian).

//Receiver

bool obtRxWatchdogResetRx() {
	uint8_t command = WATCHDOG_RESET;
	return HAL_I2C_Master_Transmit(&hi2c1, (OBT_ADDR_RX << 1) & 0xFF,
			(uint8_t*) WATCHDOG_RESET, 1, 100) == HAL_OK;
}

bool obtSoftwareResetRx() {
	uint8_t command = SOFTWARE_RESET;
	return HAL_I2C_Master_Transmit(&hi2c1, (OBT_ADDR_RX << 1) & 0xFF, &command,
			1, 100) == HAL_OK;
}

bool obtHardwareResetRx() {
	uint8_t command = HARDWARE_RESET;
	return HAL_I2C_Master_Transmit(&hi2c1, (OBT_ADDR_RX << 1) & 0xFF, &command,
			1, 100) == HAL_OK;
}

bool obtGetNumberOfFramesInRxBufferRx(uint8_t *num) {
	uint8_t command = NUMBER_FRAMES_IN_RECEIVEBUFFER;

	return HAL_I2C_Master_Transmit(&hi2c1, (OBT_ADDR_RX << 1) & 0xFF, &command,
			1, 100) == HAL_OK ?
			HAL_I2C_Master_Receive(&hi2c1, ((OBT_ADDR_RX << 1) & 0xFF) | 0x01,
					num, 2, 100) == HAL_OK :
			false;
}

/**
 * Retrieves the contents of the oldest frame in the receive buffer.
 * The contents of the frame are preceded by two bytes that indicate the frame
 * size in number of bytes. This size can be used by the OBC to terminate the
 * transmission after all the relevant bytes have been received
 * (when the actual size is less than the maximum size).
 * It can also be used for easier processing of the frame contents by the OBC's
 * command processor. If there are 0 frames in the receive buffer the response
 * is undefined.
 */
bool obtGetFrameFromRxBufferRx(uint8_t *rxBuffer) {
	uint8_t command = FRAME_FROM_RECEIVE_BUFFER;
	HAL_I2C_Master_Transmit(&hi2c1, (OBT_ADDR_RX << 1) & 0xFF, &command, 1,
			100);

	//-------------A TESTER (recevoir le frame en deux shots pour savoir le size-------------)
	HAL_I2C_Master_Receive(&hi2c1, ((OBT_ADDR_RX << 1) & 0xFF) | 0x01, rxBuffer,
			6, 100);
	HAL_I2C_Master_Receive(&hi2c1, ((OBT_ADDR_RX << 1) & 0xFF) | 0x01,
			&(rxBuffer[6]), rxBuffer[1] >> 8 | rxBuffer[0], 100);
	return HAL_I2C_Master_Receive(&hi2c1, ((OBT_ADDR_RX << 1) & 0xFF) | 0x01,
			&(rxBuffer[6]), rxBuffer[1] >> 8 | rxBuffer[0], 100) == HAL_OK;
}

bool obtRemoveFrameFromRxBufferRx() {
	uint8_t command = REMOVE_FRAME_FROM_RECEIVE_BUFFER;

	return HAL_I2C_Master_Transmit(&hi2c1, (OBT_ADDR_RX << 1) & 0xFF, &command,
			1, 100) == HAL_OK;
}

bool obtMeasureAllTelemetryChannelsRx(uint8_t *values) {
	uint8_t command = MEASURE_ALL_TELEMETRY_CHANNELS_RX;

	return HAL_I2C_Master_Transmit(&hi2c1, (OBT_ADDR_RX << 1) & 0xFF, &command,
			1, 100) == HAL_OK ?
			HAL_I2C_Master_Receive(&hi2c1, ((OBT_ADDR_RX << 1) & 0xFF) | 0x01,
					values, 17, 100) == HAL_OK :
			false;
}

bool obtReportReceiverUptimeRx(uint8_t *uptime) {
	uint8_t command = REPORT_RECEIVER_UPTIME;

	return HAL_I2C_Master_Transmit(&hi2c1, (OBT_ADDR_RX << 1) & 0xFF, &command,
			1, 100) == HAL_OK ?
			HAL_I2C_Master_Receive(&hi2c1, ((OBT_ADDR_RX << 1) & 0xFF) | 0x01,
					uptime, 4, 100) == HAL_OK :
			false;
}

//Transmitter

bool obtRxWatchdogResetTx() {
	uint8_t command = WATCHDOG_RESET;
	return HAL_I2C_Master_Transmit(&hi2c1, (OBT_ADDR_TX << 1) & 0xFF,
			(uint8_t*) WATCHDOG_RESET, 1, 100) == HAL_OK;
}

bool obtSoftwareResetTx() {
	uint8_t command = SOFTWARE_RESET;
	return HAL_I2C_Master_Transmit(&hi2c1, (OBT_ADDR_TX << 1) & 0xFF, &command,
			1, 100) == HAL_OK;
}
bool obtHardwareResetTx() {
	uint8_t command = HARDWARE_RESET;
	return HAL_I2C_Master_Transmit(&hi2c1, (OBT_ADDR_TX << 1) & 0xFF, &command,
			1, 100) == HAL_OK;
}

/**
 * Adds a frame (AX.25 UI or HDLC frame) to the frame buffer of the transmitter.
 * If the radio mode is AX.25, the AX.25 frame will contain the default callsigns
 * as they are set in the controller at the time this command is received. This command
 * will disable any beacon that is currently being transmitted by the transceiver.
 * The frame will not be added to the frame buffer if:
 	 •	The frame buffer is full
 	 •	The content size is 0 bytes
 	 •	The content size is larger than the maximum size
 Parameters
 [001 - N] n/a, binary
 Contents of the AX.25 frame's INFO field or HDLC payload field.
 The contents have a minimum size of 1 byte and a maximum size specified
 (default value is 235 bytes).

 Response
 [000 - 000] xxxxxxxx
 Number of remaining available 'slots' in the transmission buffer of the
  transmitter after this frame has been added. The minimum value of this
  response is 0 (meaning the buffer is full) and the maximum value of
  this response is the transmission frame buffer size as specified in the
  device configuration (This configuration is defined in the Test Report
  document delivered with this manual). If the response has a value of 255
  (or 0xFF in hexadecimal) then the frame was not added to the buffer.
 *
 */
bool obtSendFrameTx(uint8_t *txBuffer, uint8_t size, uint8_t *returnVal) {
	memset(obtBufferTransmitter, 0, sizeof(obtBufferTransmitter));
	memcpy(obtBufferTransmitter, SEND_A_FRAME, 1);
	memcpy(&(obtBufferTransmitter[1]), txBuffer, size);

	return HAL_I2C_Master_Transmit(&hi2c1, (OBT_ADDR_TX << 1) & 0xFF,
			obtBufferTransmitter, size + 1, 100) == HAL_OK ?
			HAL_I2C_Master_Receive(&hi2c1, ((OBT_ADDR_RX << 1) & 0xFF) | 0x01,
					returnVal, 1, 100) == HAL_OK :
			false;
}

/**
 * Adds an AX.25 UI frame to the frame buffer of the transmitter.
 * This AX.25 frame will contain the callsigns as specified in the command,
 *  ignoring the default callsigns set in the transmitter. This command will
 *  disable any beacon that is currently being transmitted by the transceiver.
 *  The AX.25 frame will not be added to the frame buffer if:
	•	The frame buffer is full
	•	The content size is 0 bytes
	•	The content size is larger than the maximum size.
This command is only available if the radio is set in AX.25 mode.

Parameters
[001 - 007] n/a, ASCII & binary
AX.25 TO callsign to be used when transmitting this AX.25 frame.
The first 6 bytes should be ASCII characters, while the 7th byte should
be a number (binary encoded between 0 and 15, usually 0).

[008 - 014] n/a, ASCII & binary
AX.25 FROM callsign to be used when transmitting this AX.25 frame.
The first 6 bytes should be ASCII characters, while the 7th byte should
 be a number (binary encoded between 0 and 15, usually 0).

[015 - N] n/a, binary
Contents of the AX.25 frame's INFO field. The contents have a minimum
size of 1 byte and a maximum size specified (default value is 235 bytes).

Response
[000 - 000] xxxxxxxx
Number of remaining available 'slots' in the transmission buffer of the
transmitter controller after this frame has been added. The minimum value
of this response is 0 (meaning the buffer is full) and the maximum value of
 this response is the transmission frame buffer size as specified in the
 device configuration (This configuration is defined in the Test Report document
 delivered with this manual). If the response has a value of 255 (or 0xFF in hexadecimal)
  then the frame was not added to the buffer.
 *
 */
bool obtSendAX25FrameWithOverrideCallsignsTx(uint8_t *txBuffer, uint8_t size, uint8_t *returnVal) {
	memset(obtBufferTransmitter, 0, sizeof(obtBufferTransmitter));
	memcpy(obtBufferTransmitter, SEND_AX25_FRAME_WITH_OVERRIDE_CALL_SIGNS, 1);
	memcpy(&(obtBufferTransmitter[1]), txBuffer, size);

	return HAL_I2C_Master_Transmit(&hi2c1, (OBT_ADDR_TX << 1) & 0xFF,
			obtBufferTransmitter, size + 1, 100) == HAL_OK ?
			HAL_I2C_Master_Receive(&hi2c1, ((OBT_ADDR_RX << 1) & 0xFF) | 0x01,
					returnVal, 1, 100) == HAL_OK : false;
}

bool obtSetBeaconTx(uint8_t *txBuffer, uint8_t size){
	memset(obtBufferTransmitter, 0, sizeof(obtBufferTransmitter));
	memcpy(obtBufferTransmitter, SET_BEACON, 1);
	memcpy(&(obtBufferTransmitter[1]), txBuffer, size);

	return HAL_I2C_Master_Transmit(&hi2c1, (OBT_ADDR_TX << 1) & 0xFF,
			obtBufferTransmitter, size + 1, 100) == HAL_OK;
}

bool obtSetAX25BeaconWithOverrideCallsignsTx(uint8_t *txBuffer, uint8_t size){
	memset(obtBufferTransmitter, 0, sizeof(obtBufferTransmitter));
	memcpy(obtBufferTransmitter, SET_AX25_BEACON_WITH_OVERRIDE_CALL_SIGNS, 1);
	memcpy(&(obtBufferTransmitter[1]), txBuffer, size);

	return HAL_I2C_Master_Transmit(&hi2c1, (OBT_ADDR_TX << 1) & 0xFF,
			obtBufferTransmitter, size + 1, 100) == HAL_OK;
}

bool obtClearBeaconTx(){
	return HAL_I2C_Master_Transmit(&hi2c1, (OBT_ADDR_TX << 1) & 0xFF,
			CLEAR_BEACON, 1, 100) == HAL_OK;
}


bool obtSetDefaultAX25TOCallsign(uint8_t *txBuffer){
	memset(obtBufferTransmitter, 0, sizeof(obtBufferTransmitter));
	memcpy(obtBufferTransmitter, SET_AX25_BEACON_WITH_OVERRIDE_CALL_SIGNS, 1);
	memcpy(&(obtBufferTransmitter[1]), txBuffer, 7);
	return HAL_I2C_Master_Transmit(&hi2c1, (OBT_ADDR_TX << 1) & 0xFF,
			obtBufferTransmitter, 8, 100) == HAL_OK;
}

bool obtSetDefaultAX25FROMCallsign(uint8_t *txBuffer){
	memset(obtBufferTransmitter, 0, sizeof(obtBufferTransmitter));
	memcpy(obtBufferTransmitter, SET_DEFAULT_AX25_FROM_CALL_SIGNS, 1);
	memcpy(&(obtBufferTransmitter[1]), txBuffer, 7);
	return HAL_I2C_Master_Transmit(&hi2c1, (OBT_ADDR_TX << 1) & 0xFF,
			obtBufferTransmitter, 8, 100) == HAL_OK;
}

/**
 * 00000000 - transmitter is turned off when idle
 * 00000001 - transmitter remains on when idle
 */
bool obtSetTxIdleState(uint8_t OnOffBit){
	memset(obtBufferTransmitter, 0, sizeof(obtBufferTransmitter));
	memcpy(obtBufferTransmitter, SET_TRANSMITTER_IDLE_STATE, 1);
	memcpy(&(obtBufferTransmitter[1]), OnOffBit, 1);
	return HAL_I2C_Master_Transmit(&hi2c1, (OBT_ADDR_TX << 1) & 0xFF,
			obtBufferTransmitter, 2, 100) == HAL_OK;
}

bool obtMeasureAllTelemetryChannelsTx(uint8_t *values){
	uint8_t command = MEASURE_ALL_TELEMETRY_CHANNELS_TX;

	return HAL_I2C_Master_Transmit(&hi2c1, (OBT_ADDR_RX << 1) & 0xFF, &command,
			1, 100) == HAL_OK ?
			HAL_I2C_Master_Receive(&hi2c1, ((OBT_ADDR_RX << 1) & 0xFF) | 0x01,
					values, 17, 100) == HAL_OK : false;
}

bool obtGetStoredTelemetryChannelsDuringLastTransmissionTx(uint8_t *values){
	uint8_t command = GET_STORED_TELEMETRY_CHANNELS_DURING_LAST_TRANSMISSION;

	return HAL_I2C_Master_Transmit(&hi2c1, (OBT_ADDR_RX << 1) & 0xFF, &command,
			1, 100) == HAL_OK ?
			HAL_I2C_Master_Receive(&hi2c1, ((OBT_ADDR_RX << 1) & 0xFF) | 0x01,
					values, 17, 100) == HAL_OK :
			false;
}

bool obtSetAX25TransmissionBitrateTx(uint8_t bitrate){
	memset(obtBufferTransmitter, 0, sizeof(obtBufferTransmitter));
	memcpy(obtBufferTransmitter, SET_AX25_TRANSMISSION_BITRATE, 1);
	memcpy(&(obtBufferTransmitter[1]), bitrate, 1);
	return HAL_I2C_Master_Transmit(&hi2c1, (OBT_ADDR_TX << 1) & 0xFF,
			obtBufferTransmitter, 2, 100) == HAL_OK;
}

bool obtReportReceiverUptimeTx(uint8_t *uptime){
	uint8_t command = REPORT_TRANSMISSION_UPTIME;

	return HAL_I2C_Master_Transmit(&hi2c1, (OBT_ADDR_RX << 1) & 0xFF, &command,
			1, 100) == HAL_OK ?
			HAL_I2C_Master_Receive(&hi2c1, ((OBT_ADDR_RX << 1) & 0xFF) | 0x01,
					uptime, 4, 100) == HAL_OK :
			false;
}

bool obtReportTransmitterStateTx(uint8_t *state){
	uint8_t command = REPORT_TRANSMISSION_STATE;

	return HAL_I2C_Master_Transmit(&hi2c1, (OBT_ADDR_RX << 1) & 0xFF, &command,
			1, 100) == HAL_OK ?
			HAL_I2C_Master_Receive(&hi2c1, ((OBT_ADDR_RX << 1) & 0xFF) | 0x01,
					state, 1, 100) == HAL_OK :
			false;
}
