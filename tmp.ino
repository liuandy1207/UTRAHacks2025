#include <Servo.h>
const int SERVOPIN = 7;
Servo servo;

// Echo Sensor
const int TRIGPIN = A1;   // Trigger pin (ensure wiring matches)
const int ECHOPIN = A2;   // Echo pin – now we'll set it to INPUT_PULLUP for stability
long duration;
int distance;

// DC Motor
const int ENAA = 10; // PWM
const int IN1 = 9;
const int IN2 = 8;
const int ENAB = 11; // PWM
const int IN3 = 12;
const int IN4 = 13;

// Color Sensor
// Frequency scalars
const int S0 = 2;
const int S1 = 3;
// Color array selectors
const int S2 = 4;
const int S3 = 5;
// Change SENSOROUT from pin 1 (TX) to pin 6
const int SENSOROUT = 6;
int redPW = 0;
int greenPW = 0;
int bluePW = 0;

void setup() {
  Serial.begin(9600);
  servo.attach(SERVOPIN);

  // Setup for Echo Sensor
  pinMode(TRIGPIN, OUTPUT);
  // Use INPUT_PULLUP to improve stability
  pinMode(ECHOPIN, INPUT_PULLUP);

  // Setup for DC Motor control pins
  pinMode(ENAA, OUTPUT);
  pinMode(ENAB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  
  // Setup for Color Sensor
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  // Set frequency scaling (20% duty cycle)
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  // Use a free digital pin for sensor output (pin 6 in this case)
  pinMode(SENSOROUT, INPUT);
}

void loop() {
  // For testing: print sensor values once per second
  distance = getDistance();
  Serial.print("Distance: ");
  Serial.println(distance);
  
  int redValue = getRedPW();
  int greenValue = getGreenPW();
  int blueValue = getBluePW();
  
  Serial.print("Red: ");
  Serial.print(redValue);
  Serial.print("   Green: ");
  Serial.print(greenValue);
  Serial.print("   Blue: ");
  Serial.println(blueValue);
  
  delay(1000);
}

// -------------------- Sensor Functions --------------------

// Ultrasonic Sensor: returns distance in centimeters
int getDistance() {
  digitalWrite(TRIGPIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGPIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGPIN, LOW);
  
  // Read pulse duration with a timeout of 30ms
  duration = pulseIn(ECHOPIN, HIGH, 30000);
  if (duration == 0) {
    Serial.println("Ultrasonic Sensor: No echo detected");
    return 999;  // Use 999 to indicate no reading
  }
  int dist = duration * 0.034 / 2;
  return dist;
}

// Color Sensor: Reads the pulse width for Red
int getRedPW() {
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  delay(10);  // Give sensor time to settle
  int PW = pulseIn(SENSOROUT, LOW, 10000);
  return PW;
}

// Color Sensor: Reads the pulse width for Green
int getGreenPW() {
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  delay(10);
  int PW = pulseIn(SENSOROUT, LOW, 10000);
  return PW;
}

// Color Sensor: Reads the pulse width for Blue
int getBluePW() {
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  delay(10);
  int PW = pulseIn(SENSOROUT, LOW, 10000);
  return PW;
}
