#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include "uv.h"


float readUVData(){
	float volts = wiringPiI2CRead(fd);
	float uvIndex;
	volts = volts * 3.3 / 255;
	uvIndex = volts / 0.1;
	return uvIndex;
}

void uvSetup(){
	fd = wiringPiI2CSetup(DEVADDR);
}
