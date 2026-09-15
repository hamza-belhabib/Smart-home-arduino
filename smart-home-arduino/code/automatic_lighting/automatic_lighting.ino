int ldr = A0;    
int led = 9;     
int seuil = 500;  

void setup() {
  pinMode(led, OUTPUT);
  Serial.begin(9600); 
}

void loop() {
  int value = analogRead(ldr); 
  Serial.println(value);

  if (value < seuil) {
    digitalWrite(led, HIGH);
  } else {
    digitalWrite(led, LOW); 
  }

  delay(200);
}