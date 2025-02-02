Servo
#include <Servo.h>
int servoPin = 7;
Servo servo;

// Echo Sensor

int trigPin = 9;
int echoPin = 10;
long duration;
int distance;


// DC Motor
int enaA = 10; // PWM
int in1 = 9;
int in2 = 8;
int enaB = 11; // PWM
int in3 = 12;
int in4 = 13;


// Color Sensor
// frequency scalars
int S0 = 2;
int S1 = 3;
// color array selectors
int S2 = 4;
int S3 = 5;
int sensorOut = 1;
int redPW = 0;
int greenPW = 0;
int bluePW = 0;

void setup()
{
    // put your setup code here, to run once:

    /*
    Servo
    servo.attach(servoPin);

    // Echo Sensor
    pinMode(trigPin, OU/Users/andyliu/Downloads/Hacker's Kit.pdfTPUT);
    pinMode(echoPin, INPUT);
    Serial.begin(9600);

    // DC Motor
    // prepare motor control pins
    pinMode(left_enable, OUTPUT);
    pinMode(left_in1, OUTPUT);
    pinMode(left_in2, OUTPUT);

    // turn off motors
    motor_off(); // turn off motors

    // set motors to max speed
    analogWrite(left_enable, 255);
    */
    // Color Sensor
    pinMode(S0, OUTPUT);
    pinMode(S1, OUTPUT);
    pinMode(S2, OUTPUT);
    pinMode(S3, OUTPUT);

    // set PW scaling to 20%
    digitalWrite(S0, HIGH);
    digitalWrite(S1, LOW);

    // set sensor output as input
    pinMode(sensorOut, INPUT);

    Serial.begin(9600);
}

void loop()
{
    // put your main code here, to run repeatedly:

    // Servo
    /*
    servo.write(0);
    delay(1000);

    for (int i = 0; i <= 180; i++) {
      servo.write(i);
    }
    delay(2000);

    // Echo Sensor
    digitalWrite(trigPin, LOW); // clear pin
    digitalWrite(trigPin, HIGH); // turn on
    delay(2000);
    digitalWrite(trigPin, LOW); // stop
    duration = pulseIn(echoPin, HIGH); // reads echo travel time in ms
    distance = duration * 0.034 / 2; // in centimeters
    //Serial.print("Distance: ");
    //Serial.print(distance);
    */

    // Color Sensor
    redPW = getRedPW();
    delay(200);
    greenPW = getGreenPW();
    delay(200);
    bluePW = getBluePW();
    delay(200);

    Serial.print("Red PW = ");
    Serial.print(redPW);
    Serial.print(" - Green PW = ");
    Serial.print(greenPW);
    Serial.print(" - Blue PW = ");
    Serial.println(bluePW);
    int color = max(redPW, greenPW, bluePW);
    
}

/*
void motor_off() {
  digitalWrite(left_in1, LOW);
    digitalWrite(left_in2, LOW);
}

void move_forward() {
  // turn on motor
  digitalWrite(left_in1, HIGH);
  digitalWrite(left_in2, LOW);
}
*/

// Function to read Red Pulse Widths
int getRedPW()
{
    // Set sensor to read Red only
    digitalWrite(S2, LOW);
    digitalWrite(S3, LOW);
    // Define integer to represent Pulse Width
    int PW;
    // Read the output Pulse Width
    PW = pulseIn(sensorOut, LOW);
    // Return the value
    return PW;
}

// Function to read Green Pulse Widths
int getGreenPW()
{
    // Set sensor to read Green only
    digitalWrite(S2, HIGH);
    digitalWrite(S3, HIGH);
    // Define integer to represent Pulse Width
    int PW;
    // Read the output Pulse Width
    PW = pulseIn(sensorOut, LOW);
    // Return the value
    return PW;
}

// Function to read Blue Pulse Widths
int getBluePW()
{
    // Set sensor to read Blue only
    digitalWrite(S2, LOW);
    digitalWrite(S3, HIGH);
    // Define integer to represent Pulse Width
    int PW;
    // Read the output Pulse Width
    PW = pulseIn(sensorOut, LOW);
    // Return the value
    return PW;
}