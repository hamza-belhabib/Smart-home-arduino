#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int tempPin = A0;
int ledGreen = 6;
int ledRed = 7;
int motor = 9;
int ledbleu = 4;

float seuil_haut = 30.0; 
float seuil_bas = 18.0;  
void setup() {
  pinMode(ledGreen, OUTPUT);
  pinMode(ledRed, OUTPUT);
  pinMode(motor, OUTPUT);

  lcd.init();
  lcd.backlight();

  Serial.begin(9600);
}

void loop() {
  int value = analogRead(tempPin);

  float voltage = value * (5.0 / 1023.0);
  float temp = (voltage - 0.5) * 100;

  lcd.clear();

  if (temp > seuil_haut) {
    digitalWrite(ledRed, HIGH);
    digitalWrite(ledGreen, LOW);
    digitalWrite(motor, HIGH);
    digitalWrite(ledbleu, LOW);

    lcd.setCursor(0, 0);
    lcd.print("Temp Haute:");
    lcd.setCursor(0, 1);
    lcd.print(temp, 1);
    lcd.print("C climatisation");

  }
  
  else if (temp < seuil_bas) {
    digitalWrite(ledbleu, HIGH);
    digitalWrite(motor, HIGH);
    digitalWrite(ledGreen, LOW);
    lcd.setCursor(0, 0);
    lcd.print("Temp Basse:");
    lcd.setCursor(0, 1);
    lcd.print(temp, 1);
    lcd.print("C chauffage");
  }
  
  else {
    digitalWrite(ledRed, LOW);
    digitalWrite(ledGreen, HIGH);
    digitalWrite(ledbleu, LOW);
    digitalWrite(motor, LOW);

    lcd.setCursor(0, 0);
    lcd.print("Temp Normale:");
    lcd.setCursor(0, 1);
    lcd.print(temp, 1);
    lcd.print("C OK");
  }

  delay(500);
}