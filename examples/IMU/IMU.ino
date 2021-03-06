/*
 Name:		IMU.ino
 Created:	5/28/2018 12:48:29 PM
 Author:	M.J
*/
#include <I2C.h>
#include "MPU9250.h"
#define DEBUG

#define SerialPort Serial

MPU9250 myIMU;

void setup() {
	I2c.begin();
	I2c.pullup(0); // Disable internal pullup
	I2c.timeOut(200); // 200 milliseconds time out to avoid i2c freezing
#ifdef DEBUG
	SerialPort.begin(115200);
	myIMU.setSerial(&SerialPort);
	SerialPort.println("Hello");
#endif

	myIMU.init();

	myIMU.update();
}

void loop() {
	myIMU.update();

#ifdef DEBUG
	myIMU.delt_t = millis() - myIMU.count;
	if (myIMU.delt_t > 20) {
		SerialPort.println(String(myIMU.roll) + " " + String(myIMU.pitch) + " " + String(myIMU.yaw));
		SerialPort.println();
		myIMU.count = millis();
	}
#endif
	delay(5); // otherwise imu becomes bouncy
}

