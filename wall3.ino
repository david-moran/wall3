#include "robot.h"
#include "wmpu6050.h"

long lastMillis;
long timeCounter;
bool direction = true;

wall3::Robot robot;

void setup() {
  Serial.begin(9600);
  Serial.println("Running robot setup");
  robot.setup();
  robot.turn(50, 1);
  lastMillis = millis();
}

void loop() {
  auto current = millis();
  auto delta = current - lastMillis;
  lastMillis = current;

  robot.loop(delta);

  timeCounter += delta;
  if (timeCounter > 3000) {
    timeCounter = 0;
    direction = !direction;
    if (direction) {
      robot.turn(50, 90);
    } else {
      robot.turn(-50, 90);
    }
  }

}
