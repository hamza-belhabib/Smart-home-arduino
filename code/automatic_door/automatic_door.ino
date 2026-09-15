#include <LiquidCrystal_I2C.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo monServo;

int pinUltrasonic = 7;
int servoPin = 9;

float calculerDistance() {
  pinMode(pinUltrasonic, OUTPUT);
  digitalWrite(pinUltrasonic, LOW);
  delayMicroseconds(2);
  digitalWrite(pinUltrasonic, HIGH);
  delayMicroseconds(10);
  pinMode(pinUltrasonic, INPUT);

  int duree = pulseIn(pinUltrasonic, HIGH);
  float distance = duree * 0.034 / 2;
  return distance;
}


void rgb(bool r, bool v, bool b) {
  digitalWrite(2, r);
  digitalWrite(3, v);
  digitalWrite(4, b);
}

void setup() {
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);

  monServo.attach(servoPin);
  monServo.write(0); 

  lcd.init();
  lcd.backlight();
}

void loop() {
  float distance = calculerDistance();

  if (distance < 140) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Welcome  ");

    rgb(0, 1, 0); 

    monServo.write(90); 
  } 
  else {
  
    lcd.setCursor(0, 0);
    lcd.print("My room :");
    lcd.setCursor(0, 1);
    lcd.print("ME       ");

    rgb(1, 0, 0);

    monServo.write(0); 
  }

  delay(300);
}