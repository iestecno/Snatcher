#pragma config(Sensor, S1,     armTouch,       sensorTouch)
#pragma config(Sensor, S3,     colorSensor,    sensorI2CCustom)
#pragma config(Sensor, S4,     sonarSensor,    sensorSONAR)
#pragma config(Motor,  motorA,          armMotor,      tmotorNXT, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

// Motor B --> Right Motor
// Motor C --> Left Motor

//INITIALIZING THE VARIABLES

int distance;														//Variable used to store the value of the sound sensor
int closest = 255;											//Variable used



// FUNTION USED TO GRAB OBJECTS
// WE NEED TO EXECUTE THIS FOR THE SOUND SENSOR TO WORK

void RaiseArm ()
{
  nMotorEncoder[motorA] = 0;
  while (SensorValue(armTouch) == 0)
  {
    motor[motorA] = 35;
  }
  motor[motorA] = 0;
  wait1Msec(100);
}


// FUNCTION USED TO RELEASE OBJECTS
// IN ORDER FOR IT TO WORK WE MUST HAVE EXECUTED RaiseArm FIRST
void LowerArm ()
{
  while(nMotorEncoder[motorA] > 0)
  {
    motor[motorA] = -30;
  }
  motor[motorA] = 0;
  wait1Msec(100);
}


// FUNCTION THAT MOVES THE ROBOT TOWARDS THE CLOSEST DETECTED OBJECT
// DEPENDING ON THE SOUND SENSOR VALUES

void Move_Closer_Sound (int speed1, int speed2, int range)
{

	while (SensorValue [sonarSensor] > range)
  {
   	motor[motorB] = speed1;
	  motor[motorC] = speed2;
  }
	  motor[motorB] = 0;
	  motor[motorC] = 0;
}


// FUNCTION THAT MOVES THE ROBOT TOWARDS THE CLOSEST DETECTED OBJECT
// ONCE YOU KNOW HOW FAR YOU ARE FROM IT

void Move (int speed1, int speed2, int centimeters)
{

	nSyncedMotors = synchCB;															//Syncronizing the motors
	nSyncedTurnRatio = 100; 															//We want to follow a Straight line

	nMotorEncoder[motorB]=0;															//Initialize the encoder
  nMotorEncoderTarget[motorB] = (34 * centimeters);  		//We use 34 as is the number of degress used per cm

  while(nMotorEncoder[motorB] < (34 * centimeters))			//Until you haven't reached your target keep going
  {
   	motor[motorB] = speed1;
	  motor[motorC] = speed2;
  }
	  motor[motorB] = 0;																		//Stop once you are done
	  motor[motorC] = 0;
}



/*FUNCTION THAT ALIGN THE SNATCHER WIHT ITS GOAL*/

int Localize(int degrees_left, int search_range, int search_speed )
{
	//distance = 0;
	//int closest = 255;
	//int direction = 0;


	// Moving the snatcher to the left to start searching
	nMotorEncoder[motorB]=0;																//Initializing the encoder
  nMotorEncoderTarget[motorB] = degrees_left;							//Setting target

  motor[motorB] = search_speed;														//Setting motor power
  motor[motorC] = -search_speed;													//The sing (+) (-) are used to spin to the right or left
  while(nMotorRunState[motorB] != runStateIdle)						//Wait till we are done
  {
    // do nothing
  }
	motor[motorB]= 0;
	motor[motorC]= 0;
	wait10Msec(10);

	// Starting the search now
  nMotorEncoder[motorC]= 0;																//Using motor
  nMotorEncoderTarget [motorC]= search_range;

  while (nMotorEncoder[motorC] < search_range)
  {
  	distance = SensorValue[sonarSensor];
		motor[motorB] = -search_speed;
  	motor[motorC] = search_speed;

  	if (distance < closest)
  	{
  		closest = distance;
  		direction = nMotorEncoder[motorC];
  		nxtDisplayTextLine(4,"direction: %d", direction);
  		nxtDisplayTextLine(2,"Closest: %d", closest);
  	}

	}

	motor[motorB]= 0;
	motor[motorC]= 0;
  wait10Msec(100);

  while (nMotorEncoder[motorC]> direction)
  {
  	motor[motorB]= search_speed;
		motor[motorC]= -search_speed;
  }

  motor[motorB]= 0;
	motor[motorC]= 0;
  wait10Msec(100);
  return closest;
}


task main()
{
  bFloatDuringInactiveMotorPWM = false; 						// This is on by default

	RaiseArm();
  Localize(400, 800, 25);

  if (closest< 30)
  {
  	Localize (100, 200, 20);
  }
	Move_Closer_Sound(15, 15, 25);
	Localize(100, 200, 10);
	LowerArm();
  Move(25, 25, 15);
  RaiseArm();
  Move(-25, -25,-20);
  Move(25, -25, 15);
  LowerArm();

}
