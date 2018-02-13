//const int forwardSpeed;
//const int turnSpeed;
//const int forwardTimer;
//const int startSoundDB;

//function that starts the program
void start()
{
	//Defining sensor
	SensorType[S2] = sensorSoundDB;
	
	//getting value for sensor
	int clap = 1;
	
	//Loop listening for sound and completes when a sound above 50 decibles is heard
	while (clap == 1){
		int sound 
		= SensorValue[S2];
		wait1Msec(1);
		if (sound > 30){
			clap = 0;
		}
	}
}

// function that checks bumpers
void checkBumpers()
{
	int bump;
	SensorType[S3] = sensorEV3_Touch;
	SensorType[S4] = sensorEV3_Touch;
	int leftBumper=getTouchValue(S3);
	int rightBumper=getTouchValue(S4);
	
	if ((rightBumper==0) && (leftBumper==0))
	{
		bump=0;
	}
	if ((rightBumper==1) || (leftBumper==1))
	{
		bump=1;
	}
	if (bump==1)
	{	
		setLEDColor(ledRed);
		displayTextLine (1,"Please clear the grid.");
		displayTextLine (3, "place into starting position ");
		displayTextLine (5, "and restart.");
		setMotorSpeed(motorC, 0);
		setMotorSpeed(motorB, 0);
		wait1Msec(2000000);
	}	
}


//define function that checks if it is stopped on a colour
void checkColor(int iterations, int prepix[4][4])
{
	// declare things
	int colourCode=getColorName(S1);
	int yesno;
	int col, row;
	
	// figure out what col its in
	if (iterations<=3)
		col=0;
	else if ((iterations<=7) && (iterations>3))
		col=1;
	else if ((iterations<=11) && (iterations>7))
		col=2;
	else if ((iterations<=15) && (iterations>11))
		col=3;
	
	// figure out what row its in
	if ((iterations==0)||(iterations==7)||(iterations==8)||(iterations==15))
		row=0;
	else if ((iterations==1)||(iterations==6)||(iterations==9)||(iterations==14))
		row=1;
	else if ((iterations==2)||(iterations==5)||(iterations==10)||(iterations==13))
		row=2;
	else if ((iterations==3)||(iterations==4)||(iterations==11)||(iterations==12))
		row=3;
	
	//check the colour
	if (colourCode==colorRed)
	{	displayTextLine(4,"Red");
		setLEDColor(ledRed);
		yesno=1;
	}
	else if (colourCode==colorBlue)
	{	displayTextLine(4,"Blue");
		setLEDColor(ledGreenFlash);
		yesno=1;
	}
	else if (colourCode==colorYellow)
	{	displayTextLine(4,"Yellow");
		setLEDColor(ledOrangeFlash);
		yesno=1;
	}
	else if (colourCode==colorGreen)
	{	displayTextLine(4,"Green");
		setLEDColor(ledGreen);
		yesno=1;
	}
	else
	{	displayTextLine(4,"Floor");
		setLEDColor(ledOff);
		yesno=0;
	}
	wait1Msec(1000);
	
	//register that a square is coloured
	prepix[row][col]=yesno;	
}

task main()

{
	//Define variables
	int colourCode;
	int i=0;
	int j=0;
	int k=0;
	int iterations=0;
	int prepix[4][4];
	int xOffset=80;
	int yOffset=55;
	
	//Sensor type and mode
	SensorType[S1]=sensorEV3_Color;
	SensorMode[S1]=modeEV3Color_Color;
	
	//Beginning robot movement
	//start();
	
	
	//Checking box colour
	//for(i=0;i<=15;i++)
	//{
	//	checkColor(iterations,prepix);
	//	iterations++;
	//}
	
	//navigating the map and giving command to read colour and check bumpers
	for (int m = 0; m < 4; m++)
	{
		checkBumpers();
		if(m == 1 || m == 3)
		{
			setMotorSpeed(motorB, 20);
			wait1Msec(1600);
			checkBumpers();
			setMotorSpeed(motorC, 50);
			setMotorSpeed(motorB, 50);
			wait1Msec(900);
			checkBumpers();		
			setMotorSpeed(motorC, 0);
			setMotorSpeed(motorB, 0);
			wait1Msec(1000);
			checkBumpers();
			checkColor(iterations,prepix);
			iterations++;
			setMotorSpeed(motorB, 20);
			wait1Msec(1800);
			checkBumpers();
			setMotorSpeed(motorC, 0);
			setMotorSpeed(motorB, 0);
			wait1Msec(1190);
			checkBumpers();
			checkColor(iterations,prepix);
			iterations++;
		}
		else if(m == 2)
		{
			setMotorSpeed(motorC, 20);
			wait1Msec(1600);
			checkBumpers();
			setMotorSpeed(motorC, 50);
			setMotorSpeed(motorB, 50);
			wait1Msec(900);
			checkBumpers();
			setMotorSpeed(motorC, 0);
			setMotorSpeed(motorB, 0);
			wait1Msec(1000);
			checkBumpers();
			checkColor(iterations,prepix);
			iterations++;
			setMotorSpeed(motorC, 20);
			wait1Msec(1800);
			checkBumpers();
			setMotorSpeed(motorC, 0);
			setMotorSpeed(motorB, 0);
			checkColor(iterations,prepix);
			iterations++;
		}
		for(int n = 0; n< 3; n++)
		{
			checkBumpers();
			setMotorSpeed(motorC, 50);
			setMotorSpeed(motorB, 50);
			checkBumpers();
			wait1Msec(1220);
			setMotorSpeed(motorC, 0);
			setMotorSpeed(motorB, 0);
			checkColor(iterations,prepix);
			iterations++;
			wait1Msec(1220);
		}
	}
	
	displayTextLine(3,"                            ");
	displayTextLine(4,"                            ");
	displayTextLine(5,"                            ");
	
	
	//looking at pixels recovered during mapping process and creating map image
	int actualpixels[20][20]={{prepix[3][0],prepix[3][0],prepix[3][0],prepix[3][0],prepix[3][0],prepix[3][1],prepix[3][1],prepix[3][1],prepix[3][1],prepix[3][1],prepix[3][2],prepix[3][2],prepix[3][2],prepix[3][2],prepix[3][2],prepix[3][3],prepix[3][3],prepix[3][3],prepix[3][3],prepix[3][3]},
				 {prepix[3][0],prepix[3][0],prepix[3][0],prepix[3][0],prepix[3][0],prepix[3][1],prepix[3][1],prepix[3][1],prepix[3][1],prepix[3][1],prepix[3][2],prepix[3][2],prepix[3][2],prepix[3][2],prepix[3][2],prepix[3][3],prepix[3][3],prepix[3][3],prepix[3][3],prepix[3][3]},
  				 {prepix[3][0],prepix[3][0],prepix[3][0],prepix[3][0],prepix[3][0],prepix[3][1],prepix[3][1],prepix[3][1],prepix[3][1],prepix[3][1],prepix[3][2],prepix[3][2],prepix[3][2],prepix[3][2],prepix[3][2],prepix[3][3],prepix[3][3],prepix[3][3],prepix[3][3],prepix[3][3]},
				 {prepix[3][0],prepix[3][0],prepix[3][0],prepix[3][0],prepix[3][0],prepix[3][1],prepix[3][1],prepix[3][1],prepix[3][1],prepix[3][1],prepix[3][2],prepix[3][2],prepix[3][2],prepix[3][2],prepix[3][2],prepix[3][3],prepix[3][3],prepix[3][3],prepix[3][3],prepix[3][3]},
				 {prepix[3][0],prepix[3][0],prepix[3][0],prepix[3][0],prepix[3][0],prepix[3][1],prepix[3][1],prepix[3][1],prepix[3][1],prepix[3][1],prepix[3][2],prepix[3][2],prepix[3][2],prepix[3][2],prepix[3][2],prepix[3][3],prepix[3][3],prepix[3][3],prepix[3][3],prepix[3][3]},
				 {prepix[2][0],prepix[2][0],prepix[2][0],prepix[2][0],prepix[2][0],prepix[2][1],prepix[2][1],prepix[2][1],prepix[2][1],prepix[2][1],prepix[2][2],prepix[2][2],prepix[2][2],prepix[2][2],prepix[2][2],prepix[2][3],prepix[2][3],prepix[2][3],prepix[2][3],prepix[2][3]},
				 {prepix[2][0],prepix[2][0],prepix[2][0],prepix[2][0],prepix[2][0],prepix[2][1],prepix[2][1],prepix[2][1],prepix[2][1],prepix[2][1],prepix[2][2],prepix[2][2],prepix[2][2],prepix[2][2],prepix[2][2],prepix[2][3],prepix[2][3],prepix[2][3],prepix[2][3],prepix[2][3]},
				 {prepix[2][0],prepix[2][0],prepix[2][0],prepix[2][0],prepix[2][0],prepix[2][1],prepix[2][1],prepix[2][1],prepix[2][1],prepix[2][1],prepix[2][2],prepix[2][2],prepix[2][2],prepix[2][2],prepix[2][2],prepix[2][3],prepix[2][3],prepix[2][3],prepix[2][3],prepix[2][3]},
				 {prepix[2][0],prepix[2][0],prepix[2][0],prepix[2][0],prepix[2][0],prepix[2][1],prepix[2][1],prepix[2][1],prepix[2][1],prepix[2][1],prepix[2][2],prepix[2][2],prepix[2][2],prepix[2][2],prepix[2][2],prepix[2][3],prepix[2][3],prepix[2][3],prepix[2][3],prepix[2][3]},
				 {prepix[2][0],prepix[2][0],prepix[2][0],prepix[2][0],prepix[2][0],prepix[2][1],prepix[2][1],prepix[2][1],prepix[2][1],prepix[2][1],prepix[2][2],prepix[2][2],prepix[2][2],prepix[2][2],prepix[2][2],prepix[2][3],prepix[2][3],prepix[2][3],prepix[2][3],prepix[2][3]},
				 {prepix[1][0],prepix[1][0],prepix[1][0],prepix[1][0],prepix[1][0],prepix[1][1],prepix[1][1],prepix[1][1],prepix[1][1],prepix[1][1],prepix[1][2],prepix[1][2],prepix[1][2],prepix[1][2],prepix[1][2],prepix[1][3],prepix[1][3],prepix[1][3],prepix[1][3],prepix[1][3]},
				 {prepix[1][0],prepix[1][0],prepix[1][0],prepix[1][0],prepix[1][0],prepix[1][1],prepix[1][1],prepix[1][1],prepix[1][1],prepix[1][1],prepix[1][2],prepix[1][2],prepix[1][2],prepix[1][2],prepix[1][2],prepix[1][3],prepix[1][3],prepix[1][3],prepix[1][3],prepix[1][3]},
				 {prepix[1][0],prepix[1][0],prepix[1][0],prepix[1][0],prepix[1][0],prepix[1][1],prepix[1][1],prepix[1][1],prepix[1][1],prepix[1][1],prepix[1][2],prepix[1][2],prepix[1][2],prepix[1][2],prepix[1][2],prepix[1][3],prepix[1][3],prepix[1][3],prepix[1][3],prepix[1][3]},
				 {prepix[1][0],prepix[1][0],prepix[1][0],prepix[1][0],prepix[1][0],prepix[1][1],prepix[1][1],prepix[1][1],prepix[1][1],prepix[1][1],prepix[1][2],prepix[1][2],prepix[1][2],prepix[1][2],prepix[1][2],prepix[1][3],prepix[1][3],prepix[1][3],prepix[1][3],prepix[1][3]},
				 {prepix[1][0],prepix[1][0],prepix[1][0],prepix[1][0],prepix[1][0],prepix[1][1],prepix[1][1],prepix[1][1],prepix[1][1],prepix[1][1],prepix[1][2],prepix[1][2],prepix[1][2],prepix[1][2],prepix[1][2],prepix[1][3],prepix[1][3],prepix[1][3],prepix[1][3],prepix[1][3]},
				 {prepix[0][0],prepix[0][0],prepix[0][0],prepix[0][0],prepix[0][0],prepix[0][1],prepix[0][1],prepix[0][1],prepix[0][1],prepix[0][1],prepix[0][2],prepix[0][2],prepix[0][2],prepix[0][2],prepix[0][2],prepix[0][3],prepix[0][3],prepix[0][3],prepix[0][3],prepix[0][3]},
				 {prepix[0][0],prepix[0][0],prepix[0][0],prepix[0][0],prepix[0][0],prepix[0][1],prepix[0][1],prepix[0][1],prepix[0][1],prepix[0][1],prepix[0][2],prepix[0][2],prepix[0][2],prepix[0][2],prepix[0][2],prepix[0][3],prepix[0][3],prepix[0][3],prepix[0][3],prepix[0][3]},
				 {prepix[0][0],prepix[0][0],prepix[0][0],prepix[0][0],prepix[0][0],prepix[0][1],prepix[0][1],prepix[0][1],prepix[0][1],prepix[0][1],prepix[0][2],prepix[0][2],prepix[0][2],prepix[0][2],prepix[0][2],prepix[0][3],prepix[0][3],prepix[0][3],prepix[0][3],prepix[0][3]},
				 {prepix[0][0],prepix[0][0],prepix[0][0],prepix[0][0],prepix[0][0],prepix[0][1],prepix[0][1],prepix[0][1],prepix[0][1],prepix[0][1],prepix[0][2],prepix[0][2],prepix[0][2],prepix[0][2],prepix[0][2],prepix[0][3],prepix[0][3],prepix[0][3],prepix[0][3],prepix[0][3]},
				 {prepix[0][0],prepix[0][0],prepix[0][0],prepix[0][0],prepix[0][0],prepix[0][1],prepix[0][1],prepix[0][1],prepix[0][1],prepix[0][1],prepix[0][2],prepix[0][2],prepix[0][2],prepix[0][2],prepix[0][2],prepix[0][3],prepix[0][3],prepix[0][3],prepix[0][3],prepix[0][3]}};
	
	
	//draw shape
	for (k=0;k<=19;k++)
	{
		for (j=0;j<=19;j++)
		{
			// get pixel state 			
			int pix=actualpixels[j][k];
			
			// plot the pixel if it is a 1
			if (pix == 1)
			{
				setPixel(j + xOffset, k + yOffset);
				wait1Msec(1);
			}
		}
	}
	
	wait1Msec(10000);
}
}