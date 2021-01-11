#include "robot.h"
#include "wmpu6050.h"

wall3::Robot robot;
bool obstacle = false;

void setup() {
  Serial.begin(9600);
  Serial.println("Running robot setup");
  robot.setup();
}

void loop() {
  robot.loop();

  if(!obstacle && robot.forwardUntilObstacle(50)) {
    Serial.println("Obstacle found.");
    obstacle = true;
  }
}
