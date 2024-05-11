#include <Servo.h>

#define TRIG_PIN 7
#define ECHO_PIN 6
#define IR_SENSOR_PIN 8
#define WATER_BOTTLE_THRESHOLD 20

// Create a Servo object
Servo servoMotor;

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Attach the servo to pin 9
  servoMotor.attach(9);

  // Set the trigger pin as an output
  pinMode(TRIG_PIN, OUTPUT);
  // Set the echo pin as an input
  pinMode(ECHO_PIN, INPUT);
  // Set the IR sensor pin as input
  pinMode(IR_SENSOR_PIN, INPUT);
}

void loop() {
  long duration, distance;

  // Check IR sensor first (adjust logic based on sensor output)
  int irSensorValue = digitalRead(IR_SENSOR_PIN);
  if (irSensorValue == LOW) { // Modify logic based on sensor (LOW for object detected)
    Serial.println("Object detected by IR sensor!");
    servoMotor.write(100); // Move servo (replace with your desired action)
    delay(200);
    servoMotor.write(0); // Move servo back to original position (optional)
    // Since IR sensor detected something, skip ultrasonic check this loop
    return; // Exit the loop to avoid unnecessary ultrasonic measurement
  }

  // If IR sensor didn't detect anything, proceed with ultrasonic check
  // ... (existing ultrasonic sensor code to measure distance)
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = duration * 0.034 / 2;

  // Check if ultrasonic sensor detects an object
  if (distance <= WATER_BOTTLE_THRESHOLD) {
    Serial.println("Object detected by Ultrasonic sensor!");
    servoMotor.write(100); // Move servo (replace with your desired action)
    delay(200);
    servoMotor.write(0); // Move servo back to original position (optional)
  } else {
    // No object detected by either sensor, do nothing or display a message
    Serial.println("No object detected by sensors");
  }

  // ... (rest of your existing code, if any)

  // Wait for a short delay before taking the next measurement
  delay(50); // Reduce this delay for faster response
}
