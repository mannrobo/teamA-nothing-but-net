#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, I2C_1,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Sensor, I2C_2,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign)
#pragma config(Motor,  port3,           chain,         tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           drive_frontLeft, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           drive_frontRight, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           drive_backRight, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           fly_left,      tmotorVex393_MC29, openLoop, encoderPort, I2C_1)
#pragma config(Motor,  port8,           fly_right,     tmotorVex393_MC29, openLoop, encoderPort, I2C_2)
#pragma config(Motor,  port9,           drive_backLeft, tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(15)
#pragma userControlDuration(105)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!
#include "robot_constants.h"

int X1, X2, Y1 = 0;
int threshold = 15;

void drive_control() {

    //Create "deadzone" for Y1/Ch3
	if(abs(vexRT[Ch3]) > threshold)
	Y1 = vexRT[Ch3];
	else
	Y1 = 0;
	//Create "deadzone" for X1/Ch4
	if(abs(vexRT[Ch4]) > threshold)
	X1 = vexRT[Ch4];
	else
	X1 = 0;
	//Create "deadzone" for X2/Ch1
	if(abs(vexRT[Ch1]) > threshold)
	X2 = vexRT[Ch1];
	else
	X2 = 0;

	//Remote Control Commands
	motor[drive_frontRight] = Y1 - X1 - X2;
	motor[drive_frontLeft]  = Y1 + X1 + X2;
	motor[drive_backRight]  = Y1 + X1 - X2;
	motor[drive_backLeft]   = Y1 - X1 + X2;

}

void set_flywheel_speed(char speed) {

	motor[fly_left] = speed;
	motor[fly_right] = speed;

}

void flywheel_control() {

	if(vexRT[Btn8U]) {
		FLYWHEEL_SPEED = FLYWHEEL_SPEED + 3;
		wait1Msec(250);
	}
	else if (vexRT[Btn8D]) {
		FLYWHEEL_SPEED = FLYWHEEL_SPEED - 3;
		wait1Msec(250);
	}
	else if (vexRT[Btn7L]) {
		FLYWHEEL_SPEED = FLYWHEEL_DEFAULT;
	}

    if(vexRT[Btn6D])
		set_flywheel_speed(MOTOR_OFF_COAST);
	else if(vexRT[Btn6U])
		set_flywheel_speed(FLYWHEEL_SPEED);

}

void chain_control() {

    if(vexRT[Btn5D])
		motor[chain] = MOTOR_OFF_COAST;
    else if(vexRT[Btn5U])
		motor[chain] = MOTOR_MAX;

}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                          Pre-Autonomous Functions
//
// You may want to perform some actions before the competition starts. Do them in the
// following function.
//
/////////////////////////////////////////////////////////////////////////////////////////

void pre_auton() {

  // Set bStopTasksBetweenModes to false if you want to keep user created tasks running between
  // Autonomous and Tele-Op modes. You will need to manage all user created tasks if set to false.
  bStopTasksBetweenModes = true;

	// All activities that occur before the competition starts
	// Example: clearing encoders, setting servo positions, ...
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 Autonomous Task
//
// This task is used to control your robot during the autonomous phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task autonomous() {

    // Autonomous mode just turns on the chain and
    //   flywheel. Robot should be placed in optimal
    //   position facing the goal at the start of
    //   the match.

	set_flywheel_speed(AUTON_FLYWHEEL_SPEED);

	wait1Msec(5000);

  motor[chain] = MOTOR_MAX;

}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 User Control Task
//
// This task is used to control your robot during the user control phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task usercontrol() {
	// User control code here, inside the loop

	while (true) {
	  // This is the main execution loop for the user control program. Each time through the loop
	  // your program should update motor + servo values based on feedback from the joysticks.

		drive_control();
		flywheel_control();
		chain_control();

	}
}
