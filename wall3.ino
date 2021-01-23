#include "wmpu6050.h"

wall3::WMPU6050 mpu;

void setup() {
  Serial.begin(9600);
  mpu.setup();
}

void loop() {
  Serial.println((float)mpu.gyroZ() / 131.0);
}
