#include <SoftwareSerial.h>

int in1 = 6;
int in2 = 7;
int in3 = 8;
int in4 = 9;
int distance = 0;
int trigPin = 10;  // Trig pin of HC-SR04
int echoPin = 11;  // Echo pin of HC-SR04

SoftwareSerial bluetooth(2, 3);  // RX, TX

void setup() {
  Serial.begin(9600);
  bluetooth.begin(9600);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void moveForward() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void backForward() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void Left() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void Right() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void stop() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void loop() {
  while (Serial.available() > 0) {
    char command = Serial.read();
    
    if (command == 'F') {
      moveForward();
    } else if (command == 'R') {
      Right();
    } else if (command == 'L') {
      Left();
    } else if (command == 'B') {
      backForward();
    } else if (command == 'S') {
      stop();
    }
  }

  // Ultrasonic sensor code
  unsigned long duration;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration / 58.2; // Calculate the distance in centimeters

  // Check if an object is too close (e.g., 10 cm) and stop the robot
  if (distance < 10) {
    stop(); // Stop if an obstacle is detected
    // Move backward for a fixed duration (adjust as needed)
    backForward();
    delay(500); // Delay for 0.5 seconds to move backward (5cm)
    stop(); // Stop after moving backward
  }
}