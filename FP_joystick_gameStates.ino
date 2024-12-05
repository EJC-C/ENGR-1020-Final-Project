#include <Stepper.h>

const int stepsPerRevolution = 2048;  // Steps per full revolution

// Initialize stepper motors
Stepper small_stepper(stepsPerRevolution, 2, 3, 4, 5);      // Motor 1
Stepper small_stepper2(stepsPerRevolution, 6, 7, 8, 9);     // Motor 2
Stepper small_stepper3(stepsPerRevolution, 10, 11, 12, 13); // Motor 3

// Joystick pins
const int xPin = A0;  // X-axis for Motor 1
const int yPin = A4;  // Y-axis for Motor 2
const int zPin = A2;  // Z-button for game start

// Game states
const int IDLE = 0;
const int PLAYING = 1;
const int FINISHED = 2;
int gameState = IDLE;

// Timer variables
unsigned long gameStartTime = 0;
const unsigned long playDuration = 45000; // 45 seconds in milliseconds
unsigned long zButtonStartTime = 0;       // Start time for Z button press
bool zButtonPressed = false;              // Flag for tracking Z button press state

void setup() {
  // Set motor speeds
  small_stepper.setSpeed(5);
  small_stepper2.setSpeed(5);
  small_stepper3.setSpeed(5);

  // Z button configuration
  pinMode(zPin, INPUT_PULLUP);

  // Initialize Serial Monitor
  Serial.begin(9600);
}

void loop() {
  // Read joystick inputs
  int xValue = analogRead(xPin);  // X-axis for Motor 1
  int yValue = analogRead(yPin);  // Y-axis for Motor 2
  int zButton = digitalRead(zPin); // Z-button state

  // Handle game states
  if (gameState == IDLE) {
    // Allow both motors to operate for game practice
    if (xValue < 150) {
      small_stepper.step(stepsPerRevolution / 25);
    } else if (xValue > 600) {
      small_stepper.step(-stepsPerRevolution / 25);
    }

    if (yValue < 150) {
      small_stepper2.step(stepsPerRevolution / 25);
    } else if (yValue > 600) {
      small_stepper2.step(-stepsPerRevolution / 25);
    }

    // Handle Z button press for 3 seconds
    if (zButton == LOW) {
      if (!zButtonPressed) {
        zButtonStartTime = millis();  
        zButtonPressed = true;   
      } else if (millis() - zButtonStartTime >= 3000) {
        // Button has been held for 3 seconds
        gameState = PLAYING;          // Transition to PLAYING state
        gameStartTime = millis();     // Record start time for PLAYING state
        zButtonPressed = false;       // Reset button press flag
      }
    } else {
      zButtonPressed = false;         // Reset if button is released before 3 seconds
    }
  }

  if (gameState == PLAYING) {
    // Rotate Motor 3 for 45 seconds
    if (millis() - gameStartTime < playDuration) {
      small_stepper3.step(stepsPerRevolution / 25); // Rotate Motor 3
    } else {
      // Transition to FINISHED state after 45 seconds
      gameState = FINISHED;
    }

    // Allow Motor 1 and Motor 2 to remain operable
    if (xValue < 150) {
      small_stepper.step(stepsPerRevolution / 25);
    } else if (xValue > 600) {
      small_stepper.step(-stepsPerRevolution / 25);
    }

    if (yValue < 150) {
      small_stepper2.step(stepsPerRevolution / 25);
    } else if (yValue > 600) {
      small_stepper2.step(-stepsPerRevolution / 25);
    }
  }

  if (gameState == FINISHED) {
    // Stop Motor 3 and reset game state
    gameState = IDLE;
  }

  // Debugging: Print joystick and Z button state
  Serial.print("Z: ");
  Serial.print(zButton);
  Serial.print(" | X: ");
  Serial.print(xValue);
  Serial.print(" | Y: ");
  Serial.println(yValue);
}