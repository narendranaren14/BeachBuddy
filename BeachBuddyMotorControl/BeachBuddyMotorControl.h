#ifndef BeachBuddyMotorControl_h
#define BeachBuddyMotorControl_h

#include "Arduino.h"

#define S1 5
#define S2 6
#define M1 4
#define M2 7

class MotorControl {
public:
	MotorControl();
	void MotorProcessRxData(unsigned long Command, unsigned char d1, unsigned char d2, unsigned char a,unsigned char b);
private:
	void advance(unsigned char a,unsigned char b);
	void back_off (unsigned char a,unsigned char b);
	void turn_L (unsigned char a,unsigned char b);
	void turn_R (unsigned char a,unsigned char b);
	void stop ();
};
typedef enum MotorCommands {
	MOTOR_CMD_DIR_FORWARD 		= 0x0000,
	MOTOR_CMD_DIR_RIGHT 		= 0x0001,
	MOTOR_CMD_DIR_LEFT 			= 0x0002,
	MOTOR_CMD_DIR_BACKWARD		= 0x0003,
	MOTOR_CMD_MOV_STOP			= 0x0004,
	MOTOR_CMD_ACC_LIGHT			= 0x0005,
	MOTOR_CMD_ACC_HORN			= 0x0006,
}_MotorCommands;
#endif