int incoming[3];

void setup() {
  Serial.begin(9600);
  
  Serial.println("Starting...");
}

void loop() {
  while(Serial.available()){
    for (int i = 0; i < 3; i++){
      incoming[i] = Serial.parseInt();
      delay(1000);
    }
  }
  for (int i = 0; i < 3; i++){
    Serial.println(incoming[i]);
  }
}
