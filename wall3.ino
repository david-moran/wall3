#include <avr/wdt.h>
#include "robot.h"

wall3::Robot robot;

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println(robot.ping());
}
