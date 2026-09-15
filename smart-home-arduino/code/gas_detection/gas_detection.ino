int gas = A0;
int buzzer = 8;
int led = 9;

int seuil = 500;

void setup() {
  pinMode(buzzer, OUTPUT);
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int value = analogRead(gas);
  Serial.println(value);

  if (value > seuil) {
   
    tone(buzzer, 1000);   
    digitalWrite(led, HIGH);
    delay(200);
    digitalWrite(led, LOW);
    delay(200);
  } else {
    
    noTone(buzzer);
    digitalWrite(led, LOW);
  }
}