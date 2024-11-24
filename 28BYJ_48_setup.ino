#include <Stepper.h>

const int stepsPerRevolution = 2048; // Steps for one full revolution

Stepper myStepper(stepsPerRevolution, 2, 3, 4, 5);

void setup() {
  myStepper.setSpeed(10); // Set speed to 10 RPM
}

void loop() {
  // Rotate one full revolution
  myStepper.step(stepsPerRevolution);
  
  // Pause for 2 seconds
  delay(2000);

  // Rotate another full revolution
  myStepper.step(stepsPerRevolution);

  // Pause for 2 seconds
  delay(2000);
}