#include <Servo.h>
Servo xservo;  // xaxis servo object
Servo yservo;  // yaxis servo object

int xcount = 0;    // variable to store the x increment
int ycount = 0;    // variable to store the y increment
int xpos = 0;    // variable to store the x servo position
int ypos = 0;    // variable to store the y servo position
int xoffset = 85;  // variable stores x servo offset position
int yoffset = 100;  // variable stores y servo offset position

//int arr[] = {};

int x;
int y;

void setup() {
  Serial.begin(9600); // initialize serial COM at 9600 baudrate

  xservo.attach(9);
  yservo.attach(10);

  Serial.println("Starting...");
  Serial.println(xoffset);
  Serial.println(yoffset);
}

void loop() {
  while (Serial.available()) {
    x = Serial.read();
    Serial.println(x);
  }
}
