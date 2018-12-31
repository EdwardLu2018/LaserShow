int incomingPts[2];

void setup() {
  Serial.begin(9600);
  
  Serial.println("Starting...");
}

void loop() {
  while(Serial.available() >= 2) {
    for(int i = 0; i < 2; i++) {
      if(i == 0) {
        incomingPts[i] = Serial.read();
        Serial.print(incomingPts[i]);
        Serial.print(", ");
      }
      else {
        incomingPts[i] = Serial.read();
        Serial.println(incomingPts[i]);
      }
    }
  }
}
