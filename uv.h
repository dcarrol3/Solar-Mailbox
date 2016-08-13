#ifndef uv_h_
#define uv_h_

#define DEVADDR 0x48
int fd;      // I2C setup return value

float readUVData(); // Read data from UV sensor
void uvSetup();  // Set up the UV sensor for reading

#endif
