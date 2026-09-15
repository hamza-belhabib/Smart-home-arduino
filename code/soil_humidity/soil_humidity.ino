#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int humidite = A0;
int led = 9;
int buzzer = 8;

int seuil = 500;

void setup() {
  pinMode(led, OUTPUT);
  pinMode(buzzer, OUTPUT);

  lcd.init();
  lcd.backlight();

  Serial.begin(9600);
}

void loop() {
  int value = analogRead(humidite);
  Serial.println(value);

  lcd.clear();

  if (value > seuil) {
    digitalWrite(led, LOW);
    noTone(buzzer);

    lcd.setCursor(0, 0);
    lcd.print("Humidite OK");
    lcd.setCursor(0, 1);
    lcd.print("Normal");
  } else {
     digitalWrite(led, HIGH);
    tone(buzzer, 1000);

    lcd.setCursor(0, 0);
    lcd.print("Humidite Bas !!!");
    lcd.setCursor(0, 1);
    lcd.print("Danger !!");
  }

  delay(500);
}
