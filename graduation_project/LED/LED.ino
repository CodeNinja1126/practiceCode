struct shift{
  int latchPin;
  int clockPin;
  int dataPin;
  byte leds = 0;
};

struct shift shift[20];

void setup() 
{

  int i;
  for(i = 3;i<18;i++){
    shift[i].latchPin = 3*(i+1)-3;
    shift[i].clockPin = 3*(i+1)-2;
    shift[i].dataPin = 3*(i+1)-1;
  }
  
  shift[0].latchPin = A13;
  shift[0].clockPin = A14;
  shift[0].dataPin =  A15;
  shift[1].latchPin = 3;
  shift[1].clockPin = 4;
  shift[1].dataPin =  5;
  shift[2].latchPin = 6;
  shift[2].clockPin = 1;
  shift[2].dataPin =  2;
  shift[18].latchPin =A0; 
  shift[18].clockPin= A1;
  shift[18].dataPin=  A2;
  shift[19].latchPin =A3; 
  shift[19].clockPin= A4;
  shift[19].dataPin=  A5;
  for(i = 0;i<20;i++){
    pinMode(shift[i].latchPin, OUTPUT);
    pinMode(shift[i].clockPin, OUTPUT);  
    pinMode(shift[i].dataPin, OUTPUT);
    updateShiftRegister(i+1);
  }

  Serial.begin(9600);
  Serial.setTimeout(50);
  Serial.println("Turn on LEDs: A BB");
  Serial.println("Turn off LEDs: -A");
}
 
void loop() 
{
  char value1;
  char value2;
  if(Serial.available()){
    long value1 = Serial.parseInt();
    long value2;
    if(value1 > 0){
      value2 = Serial.parseInt();
    }
  
    if (0 < value1)
    {
      long ch = ((value1 - 1)*40 + value2)-1;
      char led = ch%8;
      bitSet(shift[ch/8].leds, led);
      updateShiftRegister(ch/8+1);
      if(ch<40)
        Serial.print("Turned on 1P's LED ");
      else if(ch<80)
        Serial.print("Turned on 2P's LED ");
      else if(ch<120)
        Serial.print("Turned on 3P's LED ");
      else
        Serial.print("Turned on 4P's LED "); 
      Serial.println(led+1);
    }
    if (0 > value1)
    {
      shift[(-5)*(value1)-5].leds = 0;
      shift[(-5)*(value1)-4].leds = 0;
      shift[(-5)*(value1)-3].leds = 0;
      shift[(-5)*(value1)-2].leds = 0;
      shift[(-5)*(value1)-1].leds = 0;
      updateShiftRegister((-5)*(value1)-4);
      updateShiftRegister((-5)*(value1)-3);
      updateShiftRegister((-5)*(value1)-2);
      updateShiftRegister((-5)*(value1)-1);
      updateShiftRegister((-5)*(value1));
      if(-1 == value1)
        Serial.print("Cleared 1P's all LED");
      else if(-2 == value1)
        Serial.print("Cleared 2P's all LED");
      else if(-3 == value1)
        Serial.print("Cleared 3P's all LED");
      else
        Serial.print("Cleared 4P's all LED"); 
    }
  }
}
 
void updateShiftRegister(char num){  
  digitalWrite(shift[num-1].latchPin, LOW);
  shiftOut(shift[num-1].dataPin, shift[num-1].clockPin, LSBFIRST, shift[num-1].leds);
  digitalWrite(shift[num-1].latchPin, HIGH);
}
