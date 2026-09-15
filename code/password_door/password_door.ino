#include <Keypad.h>
#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

Servo myServo;
int servoPin = 11;
int buzzer = 12;
int alert = 0;

String correctCode = "777";
String inputCode = "";

bool accessGranted = false;   
bool changeMode = false;    

const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {2, 3, 4, 5};
byte colPins[COLS] = {6, 7, 8, 9};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  lcd.init();
  lcd.backlight();

  myServo.attach(servoPin);
  myServo.write(0);

  pinMode(buzzer, OUTPUT);

  lcd.setCursor(0,0);
  lcd.print("Enter Code:");
}

void loop() {
  char key = keypad.getKey();

  if (key) {

   
    if (key == 'A') {
      if (accessGranted) {
        changeMode = true;
        inputCode = "";

        lcd.clear();
        lcd.print("New Code:");
      } else {
        lcd.clear();
        lcd.print("Denied");
        delay(1000);
        lcd.clear();
        lcd.print("Enter Code:");
      }
    }

    
    else if (key == '#') {
      lcd.clear();

      
      if (changeMode) {
        correctCode = inputCode;
        lcd.print("Code Changed!");
        delay(1000);

        changeMode = false;
        accessGranted = false;
      }

     
      else {
        if (inputCode == correctCode) {
          lcd.print("Correct!");
          myServo.write(90);
          delay(600);
          myServo.write(0);

          accessGranted = true;
        } else {
          lcd.print("Wrong!");
          alert++;
          accessGranted = false;

          if (alert >= 3) {
            tone(buzzer, 1000);
            delay(1000);
            noTone(buzzer);
            alert = 0;
          }
        }
      }

      delay(500);
      lcd.clear();
      lcd.print("Enter Code:");
      inputCode = "";
    }

    
    else if (key == '*') {
      inputCode = "";
      lcd.clear();
      lcd.print("Cleared");
      delay(500);
      lcd.clear();
      lcd.print("Enter Code:");
    }

    else {
      inputCode += key;

      lcd.setCursor(0,1);
      lcd.print(inputCode);
    }
  }
}