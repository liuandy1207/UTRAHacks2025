#include <Servo.h>
const int SERVOPIN = 7;
Servo servo;

const int TURNFACTOR = 8;

// Echo Sensor
const int TRIGPIN = A1;
const int ECHOPIN = A2;
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
// frequency scalars
const int S0 = 2;
const int S1 = 3;
// color array selectors
const int S2 = 4;
const int S3 = 5;
const int SENSOROUT = 6;
int redPW = 0;
int greenPW = 0;
int bluePW = 0;

void setup()
{
    Serial.begin(9600);
    // put your setup code here, to run once:
    servo.attach(SERVOPIN);

    // Echo Sensor
    pinMode(TRIGPIN, OUTPUT);
    pinMode(ECHOPIN, INPUT_PULLUP);

    // DC Motor
    // prepare motor control pins
    pinMode(ENAA, OUTPUT);
    pinMode(ENAB, OUTPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
    
    // Color Sensor
    pinMode(S0, OUTPUT);
    pinMode(S1, OUTPUT);
    pinMode(S2, OUTPUT);
    pinMode(S3, OUTPUT);

    // set PW scaling to 20%
    digitalWrite(S0, HIGH);
    digitalWrite(S1, LOW);

    // set sensor output as input
    pinMode(SENSOROUT, INPUT);
    delay(2000);
}

void loop() {
    //challenge2 code
    while (true) {
        distance = getDistance();
        
        // If there's no obstacle, move forward
        if (distance > 14) {
            Serial.println("going forwards");
        } 
        else {
            // Stop and read color
            stopMotors();
            delay(500);

            redPW = getRedPW();
            greenPW = getGreenPW();
            bluePW = getBluePW();

            int maxColor = min(redPW, min(greenPW, bluePW));

            Serial.print("Detected Color: ");
            if (maxColor == redPW) {
                Serial.println("Red - Performing 8-Turn");
                //uTurn();
            } 
            else if (maxColor == greenPW) {
                Serial.println("Green - Turning Right");
                //turnRight();
            } 
            else if (maxColor == bluePW) {
                Serial.println("Blue - Turning Left");
                //turnLeft();
            }
        }
    }
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

// Move forward
void moveBackward() {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    analogWrite(ENAA, 200);
    analogWrite(ENAB, 200);
}

// Move forward
void moveForward() {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(ENAA, 200);
    analogWrite(ENAB, 200);
}

void moveLeft() {
    // Right wheel moves forward (normal speed)
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    analogWrite(ENAA, 200);

    // Left wheel doesn't move
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    analogWrite(ENAB, 120);
}

void moveRight() {
    // Left wheel moves forward (normal speed)
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(ENAB, 200);

    // Right wheel doesn't move
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    analogWrite(ENAA, 120);
}

void turnRight(){
    for (int i = 0; i < TURNFACTOR; i++) {
        moveRight();
        delay(120);
        stopMotors();
        moveBackward();
        delay(100);
        stopMotors();
    }
}

void turnLeft(){
    for (int i = 0; i < TURNFACTOR; i++) {
        moveLeft();
        delay(120);
        stopMotors();
        moveBackward();
        delay(100);
        stopMotors();
    }
}

void uTurn(){
    turnRight();
    turnRight();
}

// Stop the motors
void stopMotors() {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
}

void open_claw() {
    servo.write(0);
    delay(10);
}

void close_claw() {
    servo.write(180);
    delay(10);
}

int getDistance() {
    digitalWrite(TRIGPIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIGPIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIGPIN, LOW);
    
    duration = pulseIn(ECHOPIN, HIGH, 30000);
    if (duration == 0) return 999;
    return duration * 0.034 / 2;
}