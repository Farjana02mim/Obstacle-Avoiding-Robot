#include <LiquidCrystal.h>

// Ultrasonic Sensor Pins
#define echoPin 7
#define trigPin 6

// Motor Pins (L293D)
#define FwdRot_LeftMotor 2
#define BckRot_LeftMotor 3
#define FwdRot_RgtMotor 4
#define BckRot_RgtMotor 5

// LCD Pins
LiquidCrystal lcd(13, 12, 8, 9, 10, 11);

long duration;
int distance;

// Setup
void setup() {
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);

  pinMode(FwdRot_LeftMotor, OUTPUT);
  pinMode(BckRot_LeftMotor, OUTPUT);
  pinMode(FwdRot_RgtMotor, OUTPUT);
  pinMode(BckRot_RgtMotor, OUTPUT);

  lcd.begin(16, 2);

  lcd.setCursor(0, 0);
  lcd.print("Obstacle Robot");
  lcd.setCursor(0, 1);
  lcd.print("System Ready");
  delay(2000);
}

// Main Loop
void loop() {

  // Measure Distance
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH, 30000);

  distance = duration * 0.034 / 2;

  if (duration == 0) {
    distance = 400;
  }

  // Display Distance
  lcd.setCursor(0, 0);
  lcd.print("Distance: ");
  lcd.print(distance);
  lcd.print(" cm   ");

  // Obstacle Detection
  if (distance > 20) {

    // Move Forward
    digitalWrite(FwdRot_LeftMotor, HIGH);
    digitalWrite(BckRot_LeftMotor, LOW);
    digitalWrite(FwdRot_RgtMotor, HIGH);
    digitalWrite(BckRot_RgtMotor, LOW);

    lcd.setCursor(0, 1);
    lcd.print("Moving Forward  ");
  }

  else {

    // Stop Robot
    digitalWrite(FwdRot_LeftMotor, LOW);
    digitalWrite(BckRot_LeftMotor, LOW);
    digitalWrite(FwdRot_RgtMotor, LOW);
    digitalWrite(BckRot_RgtMotor, LOW);

    lcd.setCursor(0, 1);
    lcd.print("Obstacle Found  ");
    delay(500);

    // Move Backward
    digitalWrite(FwdRot_LeftMotor, LOW);
    digitalWrite(BckRot_LeftMotor, HIGH);
    digitalWrite(FwdRot_RgtMotor, LOW);
    digitalWrite(BckRot_RgtMotor, HIGH);

    lcd.setCursor(0, 1);
    lcd.print("Moving Backward ");
    delay(500);

    // Turn Right
    digitalWrite(FwdRot_LeftMotor, HIGH);
    digitalWrite(BckRot_LeftMotor, LOW);
    digitalWrite(FwdRot_RgtMotor, LOW);
    digitalWrite(BckRot_RgtMotor, HIGH);

    lcd.setCursor(0, 1);
    lcd.print("Turning Right   ");
    delay(600);

    // Stop Motors
    digitalWrite(FwdRot_LeftMotor, LOW);
    digitalWrite(BckRot_LeftMotor, LOW);
    digitalWrite(FwdRot_RgtMotor, LOW);
    digitalWrite(BckRot_RgtMotor, LOW);
    delay(200);
  }
}