/*!
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * @file antennaDriver.h
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

#ifndef INC_ANTENNADRIVER_H_
#define INC_ANTENNADRIVER_H_

#include <stdint.h>
#include <stdbool.h>

//-----------------------Variables-------------------------------
#define A_MICROCONTROLLER_ADDR 0x30
#define B_MICROCONTROLLER_ADDR 0x31
//#define ACTIVE_MICROCONTROLLER 0x30

uint8_t ANTS_ADDR = 0x30;

//-----------------------Command codes---------------------------
// Commands
#define MICROCONTROLLER_RESET 0xAA //10101010
#define ARM_ANTENNA_SYSTEM 0xAD //10101101
#define DISARM_ANTENNA_SYSTEM 0xAC //10101100
#define DEPLOY_ANTENNA_1 0xA1 //10100001
#define DEPLOY_ANTENNA_2 0xA2 //10100010
#define DEPLOY_ANTENNA_3 0xA3 //10100011
#define DEPLOY_ANTENNA_4 0xA4 //10100100
#define AUTOMATED_ANTENNA_DEPLOYMENT 0xA5 //10100101
#define DEPLOY_ANTENNA_1_OVERRIDE 0xBA //10111010
#define DEPLOY_ANTENNA_2_OVERRIDE 0xBB //10111011
#define DEPLOY_ANTENNA_3_OVERRIDE 0xBC //10111100
#define DEPLOY_ANTENNA_4_OVERRIDE 0xBD //10111101
#define CANCEL_DEPLOYMENT_ACTIVATION 0xA9 //10101001

// Telemetry
#define GET_ANTENNA_SYSTEM_TEMPERATURE 0xC0 //11000000
#define GET_DEPLOYMENT_STATUS 0xC3 //11000011
#define GET_ANTENNA_1_DEPLOYMENT_SYSTEM_ACTIVATION_COUNT 0xB0 //10110000
#define GET_ANTENNA_2_DEPLOYMENT_SYSTEM_ACTIVATION_COUNT 0xB1 //10110001
#define GET_ANTENNA_3_DEPLOYMENT_SYSTEM_ACTIVATION_COUNT 0xB2 //10110010
#define GET_ANTENNA_4_DEPLOYMENT_SYSTEM_ACTIVATION_COUNT 0xB3 //10110011
#define GET_ANTENNA_1_DEPLOYMENT_SYSTEM_ACTIVATION_TIME 0xB4 //10110100
#define GET_ANTENNA_2_DEPLOYMENT_SYSTEM_ACTIVATION_TIME 0xB5 //10110101
#define GET_ANTENNA_3_DEPLOYMENT_SYSTEM_ACTIVATION_TIME 0xB6 //10110110
#define GET_ANTENNA_4_DEPLOYMENT_SYSTEM_ACTIVATION_TIME 0xB7 //10110111


//---------------------------------Function Prototypes--------------------------------

bool setActiveMicrocontroller(int microcontrollerIndex);

// Commands
bool microControllerReset();
bool armAntennaSystem();
bool disarmAntennaSystem();
bool deployAntenna1(uint8_t* maxActivationTime);
bool deployAntenna2(uint8_t* maxActivationTime);
bool deployAntenna3(uint8_t* maxActivationTime);
bool deployAntenna4(uint8_t* maxActivationTime);
bool automatedAntennaDeployment(uint8_t* maxActivationTime);
bool deployAntenna1WithOverride(uint8_t* maxActivationTime);
bool deployAntenna2WithOverride(uint8_t* maxActivationTime);
bool deployAntenna3WithOverride(uint8_t* maxActivationTime);
bool deployAntenna4WithOverride(uint8_t* maxActivationTime);
bool cancelDeploymentActivation();

// Telemetry
uint16_t* getAntennaSystemTemperature();
uint16_t* getDeploymentStatus();
uint8_t* getAntenna1DeploymentSystemActivationCount();
uint8_t* getAntenna2DeploymentSystemActivationCount();
uint8_t* getAntenna3DeploymentSystemActivationCount();
uint8_t* getAntenna4DeploymentSystemActivationCount();
uint16_t* getAntenna1DeploymentSystemActivationTime();
uint16_t* getAntenna2DeploymentSystemActivationTime();
uint16_t* getAntenna3DeploymentSystemActivationTime();
uint16_t* getAntenna4DeploymentSystemActivationTime();




#endif /* INC_ANTENNADRIVER_H_ */

