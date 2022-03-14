/*!
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * @file antennaDriver.c
 * @brief Implementation of common commands
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * @author            Etienne Lariviere
 * @version           1.0.0
 * @date              2022.03.12
 *
 * @copyright         (C) Copyright Endurosat
 *
 *                    Contents and presentations are protected world-wide.
 *                    Any kind of using, copying etc. is prohibited without prior permission.
 *                    All rights - incl. industrial property rights - are reserved.
 *
 * @history
 * @revision{         1.0.0  , 2022.03.12, author Etienne Lariviere, Initial revision }
 * @endhistory
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */


/******************
 * TO BE TESTED
 ******************/


#include "antennaDriver.h"
#include "i2c.h"


bool setActiveMicrocontroller(int microcontrollerIndex){
	if (microcontrollerIndex == 0)
		ANTS_ADDR = A_MICROCONTROLLER_ADDR;
	else if (microcontrollerIndex == 1)
		ANTS_ADDR = B_MICROCONTROLLER_ADDR;
	else
		return false;

	return true;
}



//---------------------------------Command Function Prototypes--------------------------------
bool microControllerReset(){
	uint8_t command = MICROCONTROLLER_RESET;

	// testing
	return false;
}


bool armAntennaSystem(){
	uint8_t command = ARM_ANTENNA_SYSTEM;
	return false;
}


bool disarmAntennaSystem(){
	uint8_t command = DISARM_ANTENNA_SYSTEM;
	return false;
}


bool deployAntenna1(uint8_t* maxActivationTime){
	uint8_t command = DEPLOY_ANTENNA_1;
	return false;
}


bool deployAntenna2(uint8_t* maxActivationTime){
	uint8_t command = DEPLOY_ANTENNA_2;
	return false;
}


bool deployAntenna3(uint8_t* maxActivationTime){
	uint8_t command = DEPLOY_ANTENNA_3;
	return false;
}


bool deployAntenna4(uint8_t* maxActivationTime){
	uint8_t command = DEPLOY_ANTENNA_4;
	return false;
}


bool automatedAntennaDeployment(uint8_t* maxActivationTime){
	uint8_t command = AUTOMATED_ANTENNA_DEPLOYMENT;
	return false;
}


bool deployAntenna1WithOverride(uint8_t* maxActivationTime){
	uint8_t command = DEPLOY_ANTENNA_1_OVERRIDE;
	return false;
}


bool deployAntenna2WithOverride(uint8_t* maxActivationTime){
	uint8_t command = DEPLOY_ANTENNA_2_OVERRIDE;
	return false;
}


bool deployAntenna3WithOverride(uint8_t* maxActivationTime){
	uint8_t command = DEPLOY_ANTENNA_3_OVERRIDE;
	return false;
}


bool deployAntenna4WithOverride(uint8_t* maxActivationTime){
	uint8_t command = DEPLOY_ANTENNA_4_OVERRIDE;
	return false;
}


bool cancelDeploymentActivation(){
	uint8_t command = CANCEL_DEPLOYMENT_ACTIVATION;
	return false;
}



///---------------------------------Telemetry Function Prototypes--------------------------------
uint16_t* getAntennaSystemTemperature(){
	uint8_t command = GET_ANTENNA_SYSTEM_TEMPERATURE;
	return 0x0;
}


uint16_t* getDeploymentStatus(){
	uint8_t command = GET_DEPLOYMENT_STATUS;
	return 0x0;
}


uint8_t* getAntenna1DeploymentSystemActivationCount(){
	uint8_t command = GET_ANTENNA_1_DEPLOYMENT_SYSTEM_ACTIVATION_COUNT;
	return 0x0;
}


uint8_t* getAntenna2DeploymentSystemActivationCount(){
	uint8_t command = GET_ANTENNA_2_DEPLOYMENT_SYSTEM_ACTIVATION_COUNT;
	return 0x0;
}


uint8_t* getAntenna3DeploymentSystemActivationCount(){
	uint8_t command = GET_ANTENNA_3_DEPLOYMENT_SYSTEM_ACTIVATION_COUNT;
	return 0x0;
}


uint8_t* getAntenna4DeploymentSystemActivationCount(){
	uint8_t command = GET_ANTENNA_4_DEPLOYMENT_SYSTEM_ACTIVATION_COUNT;
	return 0x0;
}


uint16_t* getAntenna1DeploymentSystemActivationTime(){
	uint8_t command = GET_ANTENNA_1_DEPLOYMENT_SYSTEM_ACTIVATION_TIME;
	return 0x0;
}


uint16_t* getAntenna2DeploymentSystemActivationTime(){
	uint8_t command = GET_ANTENNA_2_DEPLOYMENT_SYSTEM_ACTIVATION_TIME;
	return 0x0;
}


uint16_t* getAntenna3DeploymentSystemActivationTime(){
	uint8_t command = GET_ANTENNA_3_DEPLOYMENT_SYSTEM_ACTIVATION_TIME;
	return 0x0;
}


uint16_t* getAntenna4DeploymentSystemActivationTime(){
	uint8_t command = GET_ANTENNA_4_DEPLOYMENT_SYSTEM_ACTIVATION_TIME;
	return 0x0;
}














