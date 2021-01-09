#include "robot.h"

wall3::Robot robot;

void setup() {
  Serial.begin(9600);
  robot.setup();
}

void loop() {
  robot.rotateServo(0);
  delay(1500);
  robot.rotateServo(180);
  delay(1500);
  Serial.println(robot.ping());
}
