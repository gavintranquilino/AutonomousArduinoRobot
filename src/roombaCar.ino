/*
	Gavin's Autonomous Robot Code
    Making a Robot Move with 2 DC Motors L293
    and 
    Ultrasonic Distance Sensor
*/

// Variables

// Sensor
const int trigPin = 3;
const int echoPin = 2;

long duration;
int distance;

// LEDs
const int greenLed = 12;
const int redLed = 13;

// Motors
int motorPins[] = {10, 9, 5, 6}; // Motor pins wiring flipped in irl version 
// 0, 1 -> motorA pins
// 2, 3 -> motorB pins

// Random
int randomChoice;

// Buzzer
int buzzerPin = 11;

void setup() {

  // LED pin modes
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);

  // Serial Stuff
  Serial.begin(9600);
  
  // Randomness
  randomSeed(analogRead(0));
  
  // ultrasonic sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // buzzer
  pinMode(buzzerPin, OUTPUT);
  
  // iterate through motor pins
  for (int i = 0; i < 4; i++) {
	pinMode(motorPins[i], OUTPUT);
  }
  
}

void loop() {
  do {
    greenOnRedOff();
    forward();
    
    digitalWrite(trigPin, LOW); // clear trigPin condition
    delayMicroseconds(2);
    
    // Activate trigPin for 10 microsecs
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    
    // Read what echo pin saw
    duration = pulseIn(echoPin, HIGH);
    distance = duration * 0.034 / 2;

    // Displays the distance on the Serial Monitor
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println("cm");
    
  } while (distance > 15);
  
  redOnGreenOff();
  
  Serial.println("Obstacle");

  // Direction, Turn Speed, Reverse Delay
  avoidObstacle(random(2));
  
  // Displays the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println("cm");
}

void greenOnRedOff() {
  digitalWrite(buzzerPin, LOW);
  digitalWrite(greenLed, HIGH);
  digitalWrite(redLed, LOW);
}

void redOnGreenOff() {
  digitalWrite(buzzerPin, HIGH);
  digitalWrite(greenLed, LOW);
  digitalWrite(redLed, HIGH);
}

void avoidObstacle(bool direction) {
  if (direction == true) { // Left
    Serial.println("LEFT");
    stop();
    delay(500);
    left();
    delay(200);
    reverse();
    delay(100);
  }
  else { // Right
    Serial.println("RIGHT");
    stop();
    delay(500);
    right();
    delay(200);
    reverse();
    delay(100);
  }
}

void forward() {
  for (int i = 0; i < 4; i++) { // Iterate through list of pins
    if (i % 2 == 0) { // Check if even 
      digitalWrite(motorPins[i], LOW);
    }
    else { // ODD
      digitalWrite(motorPins[i], HIGH);
    }
  }
}

void reverse() {
  for (int i = 0; i < 4; i++) { // Iterate through list of pins
    if (i % 2 == 0) { // Check if even 
      digitalWrite(motorPins[i], HIGH);
    }
    else { // ODD
      digitalWrite(motorPins[i], LOW);
    }
  }  
}

void left() {
  digitalWrite(motorPins[0], LOW);
  digitalWrite(motorPins[1], HIGH);
  digitalWrite(motorPins[2], HIGH);
  digitalWrite(motorPins[3], LOW);
}

void right() {
  digitalWrite(motorPins[0], HIGH);
  digitalWrite(motorPins[1], LOW);
  digitalWrite(motorPins[2], LOW);
  digitalWrite(motorPins[3], HIGH);
}

void stop() {
  for (int i = 0; i < 4; i++) { // Iterate through list of pins
	digitalWrite(motorPins[i], LOW);
  }
}