#include <Servo.h>

// Motor control pins
#define ENA 9
#define IN1 4
#define IN2 5
#define IN3 6
#define IN4 7
#define ENB 10

// Ultrasonic sensor pins
#define TRIG 2
#define ECHO 3

// Color sensor pins
#define S0 8
#define S1 9
#define S2 10
#define S3 11
#define COLOR_OUT 12

Servo flagServo; // Servo for dropping the flag

void setup() {
    Serial.begin(9600);

    // Motor setup
    pinMode(ENA, OUTPUT);
    pinMode(ENB, OUTPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);

    // Ultrasonic sensor setup
    pinMode(TRIG, OUTPUT);
    pinMode(ECHO, INPUT);

    // Color sensor setup
    pinMode(S0, OUTPUT);
    pinMode(S1, OUTPUT);
    pinMode(S2, OUTPUT);
    pinMode(S3, OUTPUT);
    pinMode(COLOR_OUT, INPUT);

    digitalWrite(S0, HIGH);
    digitalWrite(S1, LOW);
    
    flagServo.attach(13); // Servo connected to pin 13
    flagServo.write(0); // Start position
}

// Function to measure distance using HC-SR04
int getDistance() {
    digitalWrite(TRIG, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG, LOW);
    int duration = pulseIn(ECHO, HIGH);
    return duration * 0.034 / 2; // Convert to cm
}

// Function to get color from TCS230
String detectColor() {
    digitalWrite(S2, LOW);
    digitalWrite(S3, LOW);
    int red = pulseIn(COLOR_OUT, LOW);

    digitalWrite(S2, HIGH);
    digitalWrite(S3, HIGH);
    int green = pulseIn(COLOR_OUT, LOW);

    digitalWrite(S2, LOW);
    digitalWrite(S3, HIGH);
    int blue = pulseIn(COLOR_OUT, LOW);

    if (red < green && red < blue) return "Red";
    if (green < red && green < blue) return "Green";
    if (blue < red && blue < green) return "Blue";

    return "Unknown";
}

// Move forward
void moveBackward() {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    analogWrite(ENA, 200);
    analogWrite(ENB, 200);
}

// Move forward
void moveForward() {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(ENA, 200);
    analogWrite(ENB, 200);
}

// Stop the motors
void stopMotors() {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
}

// Rotate servo to drop flag
void dropFlag() {
    flagServo.write(90);
    delay(1000);
    flagServo.write(0);
}

void loop() {
    moveBackward();
    delay(1000);
    moveForward();
    delay(1000);
}
