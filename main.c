#include <stdio.h>
#include <wiringPi.h>
#include <pthread.h>
#include <unistd.h>
#include "uv.h"
#include "motor.h"
#include "mailhandler.h"

#define LEFT -1 // Motor movement counter clockwise
#define RIGHT 1 // Motor movement clockwise
pthread_t pidMail;

void printInfo(float uv, float maxUV){
	printf("\e[1;1H\e[2J"); // Clear terminal  	
	printf("UV Index (current): %f\n", uv);
	printf("Max UV index: %f\n", maxUV);
	printf("<MOVING> Current angle: %d\n", getCurrentAngle());
}

// Search for the most sun
void search(){
	float uv = 0.0;
	float tempUV = 0.0;
	int startStep = getCurrentAngle(); // The starting angle when the search started
	int maxStep = 0; // The motor angle with the max UV light
	
	// Clear garbage reads
	readUVData();
	readUVData();
	readUVData();

	// Search left
	while(safeMove(LEFT)){
		left(); // Move motor left one step
		tempUV = readUVData();
		printInfo(tempUV, uv);
		if(tempUV > uv){
			uv = tempUV;
			maxStep = getCurrentAngle();
		}
	}
	

	// Search right
	while(safeMove(RIGHT)){
		right(); // Move motor right one step
		tempUV = readUVData();
		printInfo(tempUV, uv);
		if(tempUV > uv){
			uv = tempUV;
			maxStep = getCurrentAngle();
		}
	}
	
	// Move to the position with the highest UV index
	moveToAngle(maxStep);
	printInfo(tempUV, uv);
	printf("\n");
}

void* startMailBoxAlert(){
	mailStart();
	return NULL;	
}

// User menu
void displayMenu(){
	printf("Demo Menu: \n"
	"Search again - s\n"
	"Quit - q\n"
	"\n");
}

// Gets user input
char grabInput(){
	char in;
	int valid = 0;
	
	displayMenu();
	
	while(!valid){
		printf("Choice: ");
		in = getchar();
		getchar(); // Consume new line
		
		if(in != 's' && in != 'q'){
			printf("\n Invalid input, try again.\n");
		}
		else{
			valid = 1;
		}
	}
	
	return in;
		
}

int main(){
	char input;
	wiringPiSetup();
	uvSetup();
	motorSetup();
	
	// Create thread for mailbox sensor
	pthread_create(&pidMail, NULL, &startMailBoxAlert, NULL);
	
	// Keep program running
	while(input != 'q'){
		input = grabInput();
		
		if(input == 's'){
			search();
		}
	}

	return 1;	
}
