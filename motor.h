#ifndef motor_h_
#define motor_h_

#define SPEED 5 // Smaller is faster
#define HOME 0
#define MAXRIGHT 75
#define MAXLEFT -75
#define ANGLEFILE "Motor/angle.txt"
#define PIN0 0
#define PIN1 1
#define PIN2 2
#define PIN3 3
int step;

void left(); 	// Counter-Clockwise rotation -
void right();	// Clockwise rotation +
void writeAngle(); // Write current angle to file
void center();	// Move the motor to the home position
void moveToAngle(int angle); // Move the motor to the requested position
// Return 1 if the next angle is safe, -1 means left, 1 is right
int safeMove(int direction);
int getCurrentAngle();
void motorSetup();

#endif
