#include <Servo.h>
#define Nothing 180
#define Hotel 0
#define Building 45
#define Villa 90
#define Land 135

Servo servo[23];

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(50);
  for(int i = 0; i < 23; i++){
    servo[i].attach(16+i);
    servo[i].write(Nothing);   
  }  
}

void loop() {
  if(Serial.available()){
    short code = Serial.parseInt();
    short build = Serial.parseInt();
    if(0 == build) servo[code-1].write(Nothing);
    else if(1 == build) servo[code-1].write(Land);
    else if(2 == build) servo[code-1].write(Villa);
    else if(3 == build) servo[code-1].write(Building);
    else if(4 == build) servo[code-1].write(Hotel);
    Serial.read();
  }
}
