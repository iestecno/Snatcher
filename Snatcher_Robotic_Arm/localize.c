#pragma config(Sensor, S1,     armTouch,       sensorTouch)
#pragma config(Sensor, S3,     colorSensor,    sensorI2CCustom)
#pragma config(Sensor, S4,     sonarSensor,    sensorSONAR)
#pragma config(Motor,  motorA,          armMotor,      tmotorNXT, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

// Motor B --> Right Motor
// Motor C --> Left Motor



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


void Localize()
{
	int distance = 0;
	int closest = 255;
	int direction = 0;

	while (true)
	{
		nMotorEncoder[motorB]=0;
	  nMotorEncoderTarget[motorB] = 800;
	  motor[motorB] = 25;
	  motor[motorC] = -25;
	  while(nMotorRunState[motorB] != runStateIdle)
	  {
	    // do nothing
	  }
		motor[motorB]= 0;
		motor[motorC]= 0;


	  nMotorEncoder[motorC]= 0;
	  nMotorEncoderTarget [motorC]= 800;

	  while (nMotorEncoder[motorC] < 800)
	  {
	  	distance = SensorValue[sonarSensor];
			//int closest = 256;
			//int direction = 0;
			//int heading = nMotorEncoder[motorC];

			motor[motorB] = -25;
	  	motor[motorC] = 25;

	  	if (distance < closest)
	  	{
	  		closest = distance;
	  		direction = nMotorEncoder[motorC];
	  		nxtDisplayTextLine(4,"direction: %d", direction);
	  		nxtDisplayTextLine(2,"Closest: %d", closest);
	  	}

			//nxtDisplayTextLine(4,"direction: %d", closest);
	  }
	  motor[motorB]= 0;
		motor[motorC]= 0;
	  wait10Msec(500);
	}

}

task main()
{
  //RaiseArm();
  Localize();


}