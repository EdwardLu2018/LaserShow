void setup() {
  Serial.begin(9600);
  
  Serial.println("Starting...");
}

void loop() {
  while(Serial.available() > 0){
    delay(1000);
    int incomingX = Serial.parseInt();
    Serial.print(incomingX);
    Serial.print(" ");
    delay(1000);
    int incomingY = Serial.parseInt();
    Serial.println(incomingY);
  }
}
