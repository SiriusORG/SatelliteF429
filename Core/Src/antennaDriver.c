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

// Va falloir valider la manière dont on ajoute les paramètres aux commandes. (Bit shift de 8 de la commande et un "ou" logique avec le paramètre)

bool microControllerReset(){
	uint8_t command = MICROCONTROLLER_RESET;

	return HAL_I2C_Master_Transmit(&hi2c1, (ANTS_ADDR << 1) & 0xFF,
					(uint8_t*) command, 1, 100) == HAL_OK;
}


bool armAntennaSystem(){
	uint8_t command = ARM_ANTENNA_SYSTEM;
	return HAL_I2C_Master_Transmit(&hi2c1, (ANTS_ADDR << 1) & 0xFF,
					(uint8_t*) command, 1, 100) == HAL_OK;
}


bool disarmAntennaSystem(){
	uint8_t command = DISARM_ANTENNA_SYSTEM;
	return HAL_I2C_Master_Transmit(&hi2c1, (ANTS_ADDR << 1) & 0xFF,
					(uint8_t*) command, 1, 100) == HAL_OK;
}


bool deployAntenna1(uint8_t* maxActivationTime){
	uint8_t command = DEPLOY_ANTENNA_1;

	return HAL_I2C_Master_Transmit(&hi2c1, (ANTS_ADDR << 1) & 0xFF,
					(uint16_t*) command << 8 | maxActivationTime, 1, 100) == HAL_OK;
}


bool deployAntenna2(uint8_t* maxActivationTime){
	uint8_t command = DEPLOY_ANTENNA_2;

	return HAL_I2C_Master_Transmit(&hi2c1, (ANTS_ADDR << 1) & 0xFF,
			(uint16_t*) command << 8 | maxActivationTime, 1, 100) == HAL_OK;
}


bool deployAntenna3(uint8_t* maxActivationTime){
	uint8_t command = DEPLOY_ANTENNA_3;

	return HAL_I2C_Master_Transmit(&hi2c1, (ANTS_ADDR << 1) & 0xFF,
			(uint16_t*) command << 8 | maxActivationTime, 1, 100) == HAL_OK;
}


bool deployAntenna4(uint8_t* maxActivationTime){
	uint8_t command = DEPLOY_ANTENNA_4;

	return HAL_I2C_Master_Transmit(&hi2c1, (ANTS_ADDR << 1) & 0xFF,
			(uint16_t*) command << 8 | maxActivationTime, 1, 100) == HAL_OK;
}


bool automatedAntennaDeployment(uint8_t* maxActivationTime){
	uint8_t command = AUTOMATED_ANTENNA_DEPLOYMENT;

	return HAL_I2C_Master_Transmit(&hi2c1, (ANTS_ADDR << 1) & 0xFF,
			(uint16_t*) command << 8 | maxActivationTime, 1, 100) == HAL_OK;
}


bool deployAntenna1WithOverride(uint8_t* maxActivationTime){
	uint8_t command = DEPLOY_ANTENNA_1_OVERRIDE;

	return HAL_I2C_Master_Transmit(&hi2c1, (ANTS_ADDR << 1) & 0xFF,
			(uint16_t*) command << 8 | maxActivationTime, 1, 100) == HAL_OK;
}


bool deployAntenna2WithOverride(uint8_t* maxActivationTime){
	uint8_t command = DEPLOY_ANTENNA_2_OVERRIDE;

	return HAL_I2C_Master_Transmit(&hi2c1, (ANTS_ADDR << 1) & 0xFF,
			(uint16_t*) command << 8 | maxActivationTime, 1, 100) == HAL_OK;
}


bool deployAntenna3WithOverride(uint8_t* maxActivationTime){
	uint8_t command = DEPLOY_ANTENNA_3_OVERRIDE;

	return HAL_I2C_Master_Transmit(&hi2c1, (ANTS_ADDR << 1) & 0xFF,
			(uint16_t*) command << 8 | maxActivationTime, 1, 100) == HAL_OK;
}


bool deployAntenna4WithOverride(uint8_t* maxActivationTime){
	uint8_t command = DEPLOY_ANTENNA_4_OVERRIDE;

	return HAL_I2C_Master_Transmit(&hi2c1, (ANTS_ADDR << 1) & 0xFF,
			(uint16_t*) command << 8 | maxActivationTime, 1, 100) == HAL_OK;
}


bool cancelDeploymentActivation(){
	uint8_t command = CANCEL_DEPLOYMENT_ACTIVATION;
	return HAL_I2C_Master_Transmit(&hi2c1, (ANTS_ADDR << 1) & 0xFF,
					(uint8_t*) command, 1, 100) == HAL_OK;
}



///---------------------------------Telemetry Function Prototypes--------------------------------

uint16_t* getAntennaSystemTemperature(){
	uint8_t command = GET_ANTENNA_SYSTEM_TEMPERATURE;
	uint16_t* telemetry;


	// Envoyer la commande
	if (HAL_I2C_Master_Transmit(&hi2c1, (ANTS_ADDR << 1) & 0xFF, (uint8_t*) command, 1, 100) == HAL_OK){
		// Aller lire valeur de retour
		if (HAL_I2C_Master_Receive(&hi2c1, (ANTS_ADDR << 1) & 0xFF | 0x01, 1, telemetry, 2, 100) == HAL_OK)
			return telemetry;
		else
			return 0x0; // Some Error code?
	}else{
		return 0x0; // Another Error code??????
	}
}

//***CODE FÉLIX START HERE (Étienne tu peux valider si tu veux)***


uint16_t* getDeploymentStatus()
/*
 À titre de validation, je vais écrire ici le raisonnement de mes démarche et d'interprétation
 Ainsi, pour cette fonction, la réponse en deux bite correspond au tableau, le MSB étant le premier byte (Most Significatif Byte) et se LSB étant le second byte (Less Significatif Byte)
 Alors, on commence par envoyer la commande par la fonction HAL
 */
{
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














