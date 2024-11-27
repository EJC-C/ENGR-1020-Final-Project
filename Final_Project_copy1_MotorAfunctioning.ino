//Final Project: Fishing game

//Evan Corcoran


//Include AccelStepper library
#include <AccelStepper.h>

//Define Motors
AccelStepper MotorA(AccelStepper::FULL4WIRE, 2,3,4,5);      //Fishing line motor 
AccelStepper MotorB(AccelStepper::FULL4WIRE, 6,7,8,9);      // Crane arm motor
AccelStepper MotorC(AccelStepper::FULL4WIRE, 10,11,12,13);  //Fish base

//Define Buttons
const int buttonAleft = A0;       //Fishing reel in
const int buttonAright = A1;      //Fishing reel out
const int buttonBleft = A2;       //Move arm left
const int buttonBright = A3;      //Move arm right
const int buttonC = A4;           //Move fishing base

//Button state
int lastAleftState = 0;
int lastArightState = 0;





void setup() {
  //Set speed and acceleration
  MotorA.setMaxSpeed(800);            //Optimum: 200-800, Min: 1-50, Max: 1000
  MotorA.setAcceleration(350);        //Optimum: 100-400, Min: 10-50, Max: 600
  MotorB.setMaxSpeed(800);            //""
  MotorB.setAcceleration(350);        //"
  MotorC.setMaxSpeed(800);            //""
  MotorC.setAcceleration(350);        //"

  //Set button I/O's
  pinMode(buttonAleft, INPUT);
  pinMode(buttonAright, INPUT);
  pinMode(buttonBleft, INPUT);
  pinMode(buttonBright, INPUT);
  pinMode(buttonC, INPUT);

  //Serial monitor setup
  Serial.begin(9600);

}

void loop() {

  // Read button states
  int buttonAleftState = analogRead(buttonAleft);
  int buttonArightState = analogRead(buttonAright);

  // Motor control logic
  if (buttonAleftState > 500) {
    MotorA.setSpeed(700);  // Reel in
    MotorA.runSpeed();
  } else if (buttonArightState > 500) {
    MotorA.setSpeed(-700); // Reel out
    MotorA.runSpeed();
  } else {
    MotorA.setSpeed(0);
    MotorA.runSpeed();
  }
}