// Doug Carroll
// CST486
// Motor lab

#include <stdio.h>
#include <wiringPi.h>
#include "motor.h"

void setMotor(int x1, int x2, int x3, int x4){
		
  digitalWrite(PIN0, x1);
  digitalWrite(PIN1, x2);
  digitalWrite(PIN2, x3);
  digitalWrite(PIN3, x4);
		
};

// Spin motor counter clockwise
void left(){
	
	setMotor(0,0,0,1);
	delay(SPEED);
	setMotor(0,0,1,1);
	delay(SPEED);
	setMotor(0,0,1,0);
	delay(SPEED);
	setMotor(0,1,1,0);
	delay(SPEED);
	setMotor(0,1,0,0);
	delay(SPEED);
	setMotor(1,1,0,0);
	delay(SPEED);
	setMotor(1,0,0,0);
	delay(SPEED);
	setMotor(1,0,0,1);
	delay(SPEED);
	step = step - 1;
	writeAngle();
}

// Spin motor clockwise
void right(){

	
	setMotor(1,0,0,0);
	delay(SPEED);
	setMotor(1,1,0,0);
	delay(SPEED);
	setMotor(0,1,0,0);
	delay(SPEED);
	setMotor(0,1,1,0);
	delay(SPEED);
	setMotor(0,0,1,0);
	delay(SPEED);
	setMotor(0,0,1,1);
	delay(SPEED);
	setMotor(0,0,0,1);
	delay(SPEED);
	setMotor(1,0,0,1);
	delay(SPEED);
	step = step + 1;
	writeAngle();
}

// Read the last known angle from the file
int readAngle(){
	int angle = 0;
	FILE *file;
	
	// Open the file
	file = fopen(ANGLEFILE, "r");
	
	// If opened, proceed
	if(file != NULL){
		fscanf(file, "%d", &angle);
	}
	else{
		printf("Failed to open the file!\n");
	}
	
	fclose(file);
	
	return angle;
}

// Write the current step angle to the file
void writeAngle(){
	FILE *file;
	
	// Open the file
	file = fopen(ANGLEFILE, "w");
	
	// If opened, proceed
	if(file != NULL){
		fprintf(file, "%d", step);
	}
	else{
		printf("Failed to open the file!\n");
	}
	
	fclose(file);
}

// Move the motor position to home
void center(){

	while(step != HOME){
		printf("<CENTERING> Current angle: %d\n", step);
		if(step < HOME){
			right();
		}
		else if(step > HOME){
			left();
		}
	}
	
	printf("<CENTERING> Solar Panel now at home position.\n");
}

// Go to the requested angle
void moveToAngle(int angle){
	
	while(step != angle){

		if(step < angle){
			right();
		}
		else if(step > angle){
			left();
		}
	}
	
	printf("<MOVING> Solar Panel now at requested position.\n");
}


int safeMove(int dir){
	int result = 1;
	
	// Left
	if(dir < 0 && (step - 1) < MAXLEFT){
		result = 0;
	}
	// Right
	else if(dir > 0 && (step + 1) > MAXRIGHT){
		result = 0;
	}
	
	return result;
}

int getCurrentAngle(){
	return step;
}

void motorSetup()
{
  // Set pin modes
  pinMode(PIN0, OUTPUT);
  pinMode(PIN1, OUTPUT);
  pinMode(PIN2, OUTPUT);
  pinMode(PIN3, OUTPUT);
  
  // Grab the correct starting angle
  step = readAngle();
}
