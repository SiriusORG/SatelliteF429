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


//---------------------------------Command Function Prototypes--------------------------------
bool microControllerReset(){
	return false;
}


bool armAntennaSystem(){
	return false;
}


bool disarmAntennaSystem(){
	return false;
}


bool deployAntenna1(uint8_t* maxActivationTime){
	return false;
}


bool deployAntenna2(uint8_t* maxActivationTime){
	return false;
}


bool deployAntenna3(uint8_t* maxActivationTime){
	return false;
}


bool deployAntenna4(uint8_t* maxActivationTime){
	return false;
}


bool automatedAntennaDeployment(uint8_t* maxActivationTime){
	return false;
}


bool deployAntenna1WithOverride(uint8_t* maxActivationTime){
	return false;
}


bool deployAntenna2WithOverride(uint8_t* maxActivationTime){
	return false;
}


bool deployAntenna3WithOverride(uint8_t* maxActivationTime){
	return false;
}


bool deployAntenna4WithOverride(uint8_t* maxActivationTime){
	return false;
}


bool cancelDeploymentActivation(){
	return false;
}



///---------------------------------Telemetry Function Prototypes--------------------------------
uint16_t* getAntennaSystemTemperature(){
	return 0x0;
}


uint16_t* getDeploymentStatus(){
	return 0x0;
}


uint8_t* getAntenna1DeploymentSystemActivationCount(){
	return 0x0;
}


uint8_t* getAntenna2DeploymentSystemActivationCount(){
	return 0x0;
}


uint8_t* getAntenna3DeploymentSystemActivationCount(){
	return 0x0;
}


uint8_t* getAntenna4DeploymentSystemActivationCount(){
	return 0x0;
}


uint16_t* getAntenna1DeploymentSystemActivationTime(){
	return 0x0;
}


uint16_t* getAntenna2DeploymentSystemActivationTime(){
	return 0x0;
}


uint16_t* getAntenna3DeploymentSystemActivationTime(){
	return 0x0;
}


uint16_t* getAntenna4DeploymentSystemActivationTime(){
	return 0x0;
}














