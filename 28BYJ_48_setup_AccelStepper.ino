#include <AccelStepper.h>


// FULL4WIRE means the motor has 4 control wires
AccelStepper stepper(AccelStepper::FULL4WIRE, 2, 4, 3, 5);

void setup() {
  // Set maximum speed and acceleration
  stepper.setMaxSpeed(1000); // Max speed in steps per second
  stepper.setAcceleration(500); // Acceleration in steps per second^2
}

void loop() {
  // Move the motor to the next position
  stepper.moveTo(2048); // Move one full revolution (2048 steps)
  while (stepper.distanceToGo() != 0) {
    stepper.run(); // Non-blocking control
  }

  delay(1000); // Wait for 1 second

  // Move the motor back to the starting position
  stepper.moveTo(0); // Move back to the starting position
  while (stepper.distanceToGo() != 0) {
    stepper.run(); // Non-blocking control
  }

  delay(1000); // Wait for 1 second
}