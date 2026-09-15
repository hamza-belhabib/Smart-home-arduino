int pirPin = 2;     
int buzzer = 8;     

void setup() {
  pinMode(pirPin, INPUT);
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int motion = digitalRead(pirPin);

  if (motion == HIGH) {
    Serial.println("Motion detected!");
    digitalWrite(buzzer, HIGH); 
  } else {
    Serial.println("No motion");
    digitalWrite(buzzer, LOW); 
  }

  delay(500);
}