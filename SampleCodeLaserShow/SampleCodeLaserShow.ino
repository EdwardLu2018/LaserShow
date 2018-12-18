#include <Servo.h>   
Servo xservo;  // xaxis servo object 
Servo yservo;  // yaxis servo object                  
int xcount = 0;    // variable to store the x increment 
int ycount = 0;    // variable to store the y increment   
int xpos = 0;    // variable to store the x servo position 
int ypos = 0;    // variable to store the y servo position  
int xamplitude = 5;  //variable stores the max sweep of the servo - maximum value is 180
int yamplitude = 5;  //variable stores the max sweep of the servo - maximum value is 180 
int xoffset = 90;  // variable stores x servo offset position 
int yoffset = 90;  // variable stores y servo offset position  
int xcentre = 0; //centre of travel for the servo
int ycentre = 0; 
int xwavelength = 300; // number of loops to complete one x cycle
int ywavelength = 100; // number of loops to complete one y cycle 
float xangle = 0; //current x angle goes from 0 to 2 
float yangle = 0; //current x angle goes from 0 to 2  

void setup()  {  
  xservo.attach(9);    // attaches the servo on pin 9  to the servo object   
  yservo.attach(10);   // attaches the servo on pin 10 to the servo object         
  xcentre = xoffset + xamplitude/2;  
  ycentre = yoffset + yamplitude/2;
  Serial.begin(9600);
  Serial.println("online...");
}   
  
void loop() 
{   
  if (xcount == xwavelength) xcount = 0; //reset xpos at the end of cycle  
  if (ycount == ywavelength) ycount = 0; //reset ypos at the end of cycle     
  xcount++; //increment x counter  
  ycount++; //increment y counter     
  xangle = (6.283/float(xwavelength))*xcount; // 2 * Pi rads in a circle  
  yangle = (6.283/float(ywavelength))*ycount; // 2 * Pi rads in a circle     
  xpos = int(xcentre + ((sin(xangle))*xamplitude)/2); 
  ypos = int(ycentre + ((cos(yangle))*yamplitude)/2); 
  //Serial.println(xangle); debug line  
  xservo.write(xpos);    
  yservo.write(ypos);

  Serial.print("(");
  Serial.print(xpos);
  Serial.print(",");
  Serial.print(ypos);
  Serial.print(")\n");
}

