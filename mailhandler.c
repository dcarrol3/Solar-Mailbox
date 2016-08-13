#include <stdio.h>
#include <wiringPi.h>
#include <pthread.h>
#include <unistd.h>
#include "mailhandler.h"
#include "mail.h" // Definitions for mail server functions

int ready = 1;

// Wait before accepting anymore opening triggers
void* waitForMailman(){
	// Wait 30 seconds before allowing another message
	// Low for demo purposes
	sleep(WAITTIME);
	
	printf("Wait time of %d seconds has passed.\n", WAITTIME);
	ready = 1;
	
	return NULL;
}

// Interrupt to be triggered when mail is detected
void handler(){
	
	int result = 0;
	
	// Check if handler was not recently run
	// And if the door is in the open state.
	if(ready == 1 && digitalRead(PIN) == LOW){
		
		ready = 0;
		
		result = haveMail();
		
		if(result == 1){
			printf("\nMessage sent.\n");
			printf("Waiting %d seconds before allowing another trigger.\n", WAITTIME);	
		}
		else{
			printf("Message sending Error.\n");
		}
		
		// Create thread that handles waiting
		pthread_create(&pid, NULL, &waitForMailman, NULL);
	
	}
}

// Start the mail program
void* mailStart()
{
    char c;
    
    pinMode(PIN, INPUT);
    
    // Set interuppt for mailbox opening
    wiringPiISR(PIN, INT_EDGE_FALLING, handler);
    
    // Keep program alive
    while(1){
		sleep(2);
	}
	
	return NULL;

}
