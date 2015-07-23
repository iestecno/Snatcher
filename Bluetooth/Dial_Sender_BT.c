#pragma config(Sensor, S1,     touchSensor,    sensorTouch)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//Defining the variables
int buttonTest;
int power;
int encoderCount;
//int testMessage = 1;																						// We use this to check if we are sending something


void measureRPM() 																							// Function to measure the rotation speed in rpm
{


	wait1Msec(167);																								// Wait for 0,1 sec to measure the final angle
	encoderCount = nMotorEncoder [motorC];

	power = encoderCount;

	//speed = 6 *(( 60 * encoderCount / 360));											//Converting the units to rpm

	// We add limits to the possible speed values

	if (power > 100)
	{
		power = 100;
	}

	else if (power < -100)
	{
		power = -100;
	}

	//else if (speed == -0)																					// Just in case as this is a reported bug of the NXT
	//{
	//	speed = 0;
	//}

	//nxtDisplayTextLine(1,"Encoder=%d", nMotorEncoder[motorA]); 		//Displaying the result of the angle measured
	nxtDisplayTextLine (2, "Power: %d", power);								//Displaying the result in rpm

}


task main()
{
	nMotorEncoder[motorC] = 0;																			// Initialize the rotation sensor of the servo
	while (true)																					// We want the function to run all the time
	{
		wait1Msec(50);
		if(nNxtButtonPressed == 1)                        	// If we press the Right Arrow
		{
	  	buttonTest = 1;  																	// We send "1"
			nxtDisplayTextLine(4,"Button: %d",buttonTest);		// We present the result on the screen
  	}

  	else if (nNxtButtonPressed == 2)										// If we press the Left Arrow
		{
			buttonTest= 2;																		// We send "2"
			nxtDisplayTextLine(4,"Button: %d",buttonTest);
		}

		else if (nNxtButtonPressed == 3)										// If we press the Orange Square
		{
	  	buttonTest = 3;  																	// We send "3"
	  	nxtDisplayTextLine(4,"Button: %d",buttonTest);
		}

		else if (SensorValue [touchSensor] == 1)           	// If the SensorTouch is pressed
		{
  		buttonTest = 4;  																	// We send "4"
			nMotorEncoder[motorC] = 0;
  		nxtDisplayTextLine(4,"Button: %d",buttonTest);
  		nxtDisplayTextLine(4,"Stop and Reset");
  	}

  	else 																		           	// If Nothing is pressed
		{
  		buttonTest = 0;  																	// We send "0"
			nxtDisplayTextLine(4,"No Button Pressed");
  	}

  	measureRPM();																				// We call the function to measure the speed of dial (motorC)

  	sendMessageWithParm(buttonTest, power);
  	//motor[motorA] = power;														// For debugging purposes
  	wait1Msec(75);
  }


}
