#include <LiquidCrystal_I2C.h>
#include <Wire.h>

struct player{
  char money[8] = {'0','0','0','0','0','0','0','0'};
  char radio = 0;
  char ticket = 0;
  char estList[28][2] = {{0,0},{0,0},{0,0},{0,0},{0,0},
                         {0,0},{0,0},{0,0},{0,0},{0,0},
                         {0,0},{0,0},{0,0},{0,0},{0,0},
                         {0,0},{0,0},{0,0},{0,0},{0,0},
                         {0,0},{0,0},{0,0},{0,0},{0,0},
                         {0,0},{0,0},{0,0}};
  char estLeng = 0;
  char island = 0;
  char islandFlg = 0;
  char statPage = 1;
  char deadFlg = 0;
  char playFlg = 0;
};

struct button{
  int pin;
  int state = 0;
};

struct player* playerList[4];


struct player p1;
struct player p2;
struct player p3;
struct player p4;

struct button Right1;
struct button Left1;
struct button Right2;
struct button Left2; 
struct button Right3;
struct button Left3; 
struct button Right4;
struct button Left4;
struct button Select1;
struct button Select2;
struct button Select3;
struct button Select4; 

LiquidCrystal_I2C lcd0(0x27, 16, 2);
LiquidCrystal_I2C lcd1(0x26, 16, 2);
LiquidCrystal_I2C lcd2(0x25, 16, 2);
LiquidCrystal_I2C lcd3(0x23, 16, 2);


char mainCode[3];

void setup() {
  Left1.pin = 2;
  Right1.pin = 3;
  Select1.pin = 4;
  Left2.pin = 5;
  Right2.pin = 6;
  Select2.pin = 7;
  Left3.pin = 8;
  Right3.pin = 9;
  Select3.pin = 10;
  Left4.pin = 11;
  Right4.pin = 12;
  Select4.pin = 13;

  playerList[0] = &p1;
  playerList[1] = &p2;
  playerList[2] = &p3;
  playerList[3] = &p4;

  
  Serial.begin(9600);
  Serial.setTimeout(50);

  Serial.write('1');
  while(1) if(Serial.available()){
      char a = Serial.read();
      if('\n'==a) break;
    }

  pinMode(Right1.pin, INPUT_PULLUP);
  pinMode(Left1.pin, INPUT_PULLUP);
  pinMode(Select1.pin, INPUT_PULLUP);
  pinMode(Left2.pin, INPUT_PULLUP);
  pinMode(Right2.pin, INPUT_PULLUP);
  pinMode(Select2.pin, INPUT_PULLUP);
  pinMode(Right3.pin, INPUT_PULLUP);
  pinMode(Left3.pin, INPUT_PULLUP);
  pinMode(Select3.pin, INPUT_PULLUP);
  pinMode(Left4.pin, INPUT_PULLUP);
  pinMode(Right4.pin, INPUT_PULLUP);
  pinMode(Select4.pin, INPUT_PULLUP);
  
  lcd0.begin();
  lcd1.begin();
  lcd2.begin();
  lcd3.begin();

  lcd0.backlight();
  lcd1.backlight();
  lcd2.backlight();
  lcd3.backlight();
  
  lcd0.print(F("!!PRESS BUTTON!!"));
  lcd1.print(F("!!PRESS BUTTON!!"));
  lcd2.print(F("!!PRESS BUTTON!!"));
  lcd3.print(F("!!PRESS BUTTON!!"));


   while(1){
    
    if(0 == playerList[0]->playFlg &&( buttonInput(Select1, &Select1.state)==1)){
      playerList[0]->playFlg = 1;
      lcd0.clear();
      lcd0.print(F("!!PARTICIPATED!!"));
      Serial.write('1');  
    }
    if(0 == playerList[1]->playFlg && (buttonInput(Select2, &Select2.state)==1)){
      playerList[1]->playFlg = 1;
      lcd1.clear();
      lcd1.print(F("!!PARTICIPATED!!"));
      Serial.write('2');  
    }
    if(0 == playerList[2]->playFlg && (buttonInput(Select3, &Select3.state)==1)){
      playerList[2]->playFlg = 1;
      lcd2.clear();
      lcd2.print(F("!!PARTICIPATED!!"));
      Serial.write('3');  
    }
    if(0 == playerList[3]->playFlg && (buttonInput(Select4, &Select4.state)==1)){
      playerList[3]->playFlg = 1;
      lcd3.clear();
      lcd3.print(F("!!PARTICIPATED!!"));
      Serial.write('4');  
    }
    if(Serial.available()){
      if('\n' == Serial.read()) break;
    }
   
  }
  lcd0.clear();
  lcd1.clear();
  lcd2.clear();
  lcd3.clear();
  
  lcd0.print(F("!!WAIT PLEASE!!!"));
  lcd1.print(F("!!WAIT PLEASE!!!"));
  lcd2.print(F("!!WAIT PLEASE!!!"));
  lcd3.print(F("!!WAIT PLEASE!!!"));

  
  while(1){
    if(Serial.available()){
      if('\n' == Serial.read()) break;
    }
  }

  statusLcd(lcd0, *playerList[0]);
  statusLcd(lcd1, *playerList[1]);
  statusLcd(lcd2, *playerList[2]);
  statusLcd(lcd3, *playerList[3]);
}

char mainP = '1';
void loop() {
  if(Serial.available()){
    char serBuffer[8];
    int i = 0;
    while(1){
      char ch;
      if(Serial.available()){
        ch = Serial.read();
        if(ch == '\n'){
          break;
        }
        serBuffer[i] = ch;
        i++;
      }
    }
    if(serBuffer[0]=='0'){
      setPlayer(serBuffer, playerList);
      if(mainP == '1'){
        if('2'==serBuffer[1]) statusLcd(lcd1, *playerList[1]);
        else if('3'==serBuffer[1]) statusLcd(lcd2, *playerList[2]);
        else if('4'==serBuffer[1]) statusLcd(lcd3, *playerList[3]);
      }
      else if(mainP == '2'){
        if('1'==serBuffer[1]) statusLcd(lcd0, *playerList[0]);
        else if('3'==serBuffer[1]) statusLcd(lcd2, *playerList[2]);
        else if('4'==serBuffer[1]) statusLcd(lcd3, *playerList[3]);
      }
      else if(mainP == '3'){ 
        if('1'==serBuffer[1]) statusLcd(lcd0, *playerList[0]);
        else if('2'==serBuffer[1]) statusLcd(lcd1, *playerList[1]);
        else if('4'==serBuffer[1]) statusLcd(lcd3, *playerList[3]);
      }
      else if(mainP == '4'){
        if('1'==serBuffer[1]) statusLcd(lcd0, *playerList[0]);
        else if('2'==serBuffer[1]) statusLcd(lcd1, *playerList[1]);
        else if('3'==serBuffer[1]) statusLcd(lcd2, *playerList[2]);
      }
    }
    else if(serBuffer[0]=='1'){
      if(mainP != serBuffer[1]){
        if(mainP == '1') statusLcd(lcd0, *playerList[0]);
        else if(mainP == '2') statusLcd(lcd1, *playerList[1]);
        else if(mainP == '3') statusLcd(lcd2, *playerList[2]);
        else if(mainP == '4') statusLcd(lcd3, *playerList[3]);
      }
      mainP = serBuffer[1];
      mainCode[0] = serBuffer[5];
      mainCode[1] = serBuffer[6];
      mainCode[2] = serBuffer[7];
      if(mainP == '1') mainLcd(lcd0 ,0);
      else if(mainP == '2') mainLcd(lcd1, 0);
      else if(mainP == '3') mainLcd(lcd2, 0);
      else if(mainP == '4') mainLcd(lcd3, 0);
    }
    else if(serBuffer[0]=='2'){
      if(serBuffer[1] == '1') {
        lcd0.clear(); 
        lcd0.print(F("!!!!!YOU WON!!!!"));
        if(playerList[1]->playFlg == 1){
          lcd1.clear(); 
          lcd1.print(F("!!!!YOU LOSE!!!!"));
        }
        if(playerList[2]->playFlg == 1){
          lcd2.clear(); 
          lcd2.print(F("!!!!YOU LOSE!!!!"));
        }
        if(playerList[3]->playFlg == 1){
          lcd3.clear(); 
          lcd3.print(F("!!!!YOU LOSE!!!!"));
        }
        while(1);
      }
      else if(serBuffer[1] == '2') {
        lcd1.clear(); 
        lcd1.print(F("!!!!!YOU WON!!!!"));
        if(playerList[0]->playFlg == 1){
          lcd0.clear(); 
          lcd0.print(F("!!!!YOU LOSE!!!!"));
        }
        if(playerList[2]->playFlg == 1){
          lcd2.clear(); 
          lcd2.print(F("!!!!YOU LOSE!!!!"));
        }
        if(playerList[3]->playFlg == 1){
          lcd3.clear(); 
          lcd3.print(F("!!!!YOU LOSE!!!!"));
        }
        while(1);
      }
      else if(serBuffer[1] == '3') {
        lcd2.clear(); 
        lcd2.print(F("!!!!!YOU WON!!!!"));
        if(playerList[0]->playFlg == 1){
          lcd0.clear(); 
          lcd0.print(F("!!!!YOU LOSE!!!!"));
        }
        if(playerList[1]->playFlg == 1){
          lcd1.clear(); 
          lcd1.print(F("!!!!YOU LOSE!!!!"));
        }
        if(playerList[3]->playFlg == 1){
          lcd3.clear(); 
          lcd3.print(F("!!!!YOU LOSE!!!!"));
        }
        while(1);
      }
      else if(serBuffer[1] == '4') {
        lcd3.clear(); 
        lcd3.print(F("!!!!!YOU WON!!!!"));
        if(playerList[0]->playFlg == 1){
          lcd0.clear(); 
          lcd0.print(F("!!!!YOU LOSE!!!!"));
        }
        if(playerList[1]->playFlg == 1){
          lcd1.clear(); 
          lcd1.print(F("!!!!YOU LOSE!!!!"));
        }
        if(playerList[2]->playFlg == 1){
          lcd2.clear(); 
          lcd2.print(F("!!!!YOU LOSE!!!!"));
        }
        while(1);
      }
    }
  }
  
  if(buttonInput(Left1, &Left1.state)==1){
    if(mainP!='1'){
      statLeft(playerList[0]);
      statusLcd(lcd0, *playerList[0]);
    }
    else{
      mainLcd(lcd0,1);
    }
  }
  if(buttonInput(Right1, &Right1.state)==1){
    if(mainP!='1'){
      statRight(playerList[0]);
      statusLcd(lcd0, *playerList[0]);
    }
    else{
      mainLcd(lcd0,2);
    }
  }
  if(buttonInput(Select1, &Select1.state)==1){
    if(mainP!='1');
    else mainLcd(lcd0,3);
  }
  if(buttonInput(Left2, &Left2.state)==1){
    if(mainP!='2'){
      statLeft(playerList[1]);
      statusLcd(lcd1, *playerList[1]);
    }
    else{
      mainLcd(lcd1,1);
    }
  }
  if(buttonInput(Right2, &Right2.state)==1){
    if(mainP!='2'){
      statRight(playerList[1]);
      statusLcd(lcd1, *playerList[1]);
    }
    else{
      mainLcd(lcd1,2);
    }
  }
  if(buttonInput(Select2, &Select2.state)==1){
    if(mainP!='2');
    else mainLcd(lcd1,3);
  }
  if(buttonInput(Left3, &Left3.state)==1){
    if(mainP!='3'){
      statLeft(playerList[2]);
      statusLcd(lcd2, *playerList[2]);
    }
    else{
      mainLcd(lcd2,1);
    }
  }
  if(buttonInput(Right3, &Right3.state)==1){
    if(mainP!='3'){
      statRight(playerList[2]);
      statusLcd(lcd2, *playerList[2]);
    }
    else{
      mainLcd(lcd2,2);
    }
  }
  if(buttonInput(Select3, &Select3.state)==1){
    if(mainP!='3');
    else mainLcd(lcd2,3);
  }
  if(buttonInput(Left4, &Left4.state)==1){
    if(mainP!='4'){
      statLeft(playerList[3]);
      statusLcd(lcd3, *playerList[3]);
    }
    else{
      mainLcd(lcd3,1);
    }
  }
  if(buttonInput(Right4, &Right4.state)==1){
    if(mainP!='4'){
      statRight(playerList[3]);
      statusLcd(lcd3, *playerList[3]);
    }
    else{
      mainLcd(lcd3,2);
    }
  }
  if(buttonInput(Select4, &Select4.state)==1){
    if(mainP!='4');
    else mainLcd(lcd3,3);
  }
}
void statRight(player* p){
  if(p->statPage==(p->estLeng+2)){
    p->statPage=1;
  }
  else if(p->statPage==(p->estLeng+1)){
    (p->statPage+=1)*(p->islandFlg==0)&&(p->statPage=1);
  }
  else{
    p->statPage++;
  }
}

void statLeft(player* p){
  if(p->statPage == 1){
    (p->statPage=p->estLeng+2)*(p->islandFlg==0)&&(p->statPage=p->estLeng+1);
  }
  else{
    p->statPage--;
  }
}



int buttonInput(button button, int* state){
  if((digitalRead(button.pin) == LOW) && (*state == 0)){
    *state = 1;
    delay(10);
    return 1;
  }
  else if((digitalRead(button.pin) == HIGH) && (*state ==1)){
    *state = 0;
    delay(10);
    return 0;
  }
  else{
    return 0;
  }
}

void statusLcd(LiquidCrystal_I2C lcd, player p){
  lcd.clear();
  if(p.deadFlg == 1) lcd.print(F("*bankruptcy*"));
  else if(p.playFlg == 0) lcd.print(F("NOT PLAYING"));
  else if(p.statPage==1){
    lcd.print("Money:  ");
    int b = 0;
    for(int i = 0;i < 8; i++){
      if(p.money[i] == '0' && b == 0){
        lcd.print(' ');
      }
      else{
        b = 1;
        lcd.print(p.money[i]);
      }
    }
    lcd.setCursor(0,1);
    lcd.print("Radio:");
    if(p.radio == 0){
      lcd.print("0 ");
    }
    else if(p.radio == 1){
      lcd.print("1 ");
    }
    lcd.print("Ticket:");
    if(p.ticket == 0){
      lcd.print("0 ");
    }
    else if(p.ticket == 1){
      lcd.print("1 ");
    }
    else if(p.ticket == 2){
      lcd.print("2 ");
    }
  }
  else if(1<p.statPage&&p.statPage<p.estLeng+2){
    switch (p.estList[p.statPage-2][0]){
      case 1: lcd.print(F("Taipei          ")); break;
      case 2: lcd.print(F("Hong Kong       ")); break;
      case 3: lcd.print(F("Manila          ")); break;
      case 4: lcd.print(F("Jeju island     ")); break;
      case 5: lcd.print(F("Singapore       ")); break;
      case 6: lcd.print(F("Cairo           ")); break;      
      case 7: lcd.print(F("Istanbul        ")); break;
      case 8: lcd.print(F("Athens          ")); break;
      case 9: lcd.print(F("Copenhagen      ")); break;
      case 10: lcd.print(F("Stockholm       ")); break;
      case 11: lcd.print(F("Concord         ")); break;
      case 12: lcd.print(F("Zurich          ")); break;
      case 13: lcd.print(F("Berlin          ")); break;
      case 14: lcd.print(F("Montreal        ")); break;
      case 15: lcd.print(F("Buenos Aires    ")); break;
      case 16: lcd.print(F("Sao paulo       ")); break;
      case 17: lcd.print(F("Sydney          ")); break;
      case 18: lcd.print(F("Busan           ")); break;
      case 19: lcd.print(F("Hawaii          ")); break;
      case 20: lcd.print(F("Lisbon          ")); break;
      case 21: lcd.print(F("Queen Elizabeth ")); break;
      case 22: lcd.print(F("Madrid          ")); break;
      case 23: lcd.print(F("Tokyo           ")); break;
      case 24: lcd.print(F("Colombia        ")); break;
      case 25: lcd.print(F("Paris           ")); break;
      case 26: lcd.print(F("Rome            ")); break;
      case 27: lcd.print(F("London          ")); break;
      case 28: lcd.print(F("New York        ")); break;
      case 29: lcd.print(F("Seoul           ")); break;
    } 
    if((p.estList[p.statPage-2][0]!=4)&&
       (p.estList[p.statPage-2][0]!=11)&&
       (p.estList[p.statPage-2][0]!=18)&&
       (p.estList[p.statPage-2][0]!=21)&&
       (p.estList[p.statPage-2][0]!=24)&&
       (p.estList[p.statPage-2][0]!=29)){
      lcd.setCursor(0,1);
      switch(p.estList[p.statPage-2][1]){
        case 0: lcd.print(F("Land")); break;
        case 1: lcd.print(F("Villa")); break;
        case 2: lcd.print(F("Building")); break;
        case 3: lcd.print(F("Hotel")); break;
      }
    }
  }
  else{
    lcd.print(F("Island turn: "));
    if(p.island == 0){
      lcd.print("0 ");
    }
    else if(p.island == 1){
      lcd.print("1 ");
    }
    else if(p.island == 2){
      lcd.print("2 ");
    }
    else if(p.island == 3){
      lcd.print("3 ");
    }
  }
}


void mainLcd(LiquidCrystal_I2C lcd, char button){
  static char control = 0;
  if(10 == control || 12 == control || 13 == control){
    if(mainCode[1]=='0' && 0 == button){
      if(mainCode[2]=='1'){
        lcd.clear();
        lcd.print(F("<-Taipei      ->"));
        if(13 != control) control = 11;
        else control = 14;
      }else if(mainCode[2]=='2'){
        lcd.clear();
        lcd.print(F("<-Hong Kong   ->"));
        if(13 != control) control = 11;
        else control = 14;
      }else if(mainCode[2]=='3'){
        lcd.clear();
        lcd.print(F("<-Manila      ->"));
        if(13 != control) control = 11;
        else control = 14;
      }else if(mainCode[2]=='4'){
        lcd.clear();
        lcd.print(F("<-Jeju island ->"));
        if(13 != control) control = 11;
        else control = 14;
      }else if(mainCode[2]=='5'){
        lcd.clear();
        lcd.print(F("<-Singapore   ->"));
        if(13 != control) control = 11;
        else control = 14;
      }else if(mainCode[2]=='6'){
        lcd.clear();
        lcd.print(F("<-Cairo       ->"));
        if(13 != control) control = 11;
        else control = 14;
      }else if(mainCode[2]=='7'){
        lcd.clear();
        lcd.print(F("<-Istanbul    ->"));
        if(13 != control) control = 11;
        else control = 14;
      }else if(mainCode[2]=='8'){
        lcd.clear();
        lcd.print(F("<-Athens      ->"));
        if(13 != control) control = 11;
        else control = 14;
      }else if(mainCode[2]=='9'){
        lcd.clear();
        lcd.print(F("<-Copenhagen  ->"));
        if(13 != control) control = 11;
        else control = 14;
      }
    }else if(mainCode[1]=='1' && 0 == button){
      if(mainCode[2]=='0'){
        lcd.clear();
        lcd.print(F("<-Stockhom    ->"));
        if(13 != control) control = 11;
        else control = 14;
      }else if(mainCode[2]=='1'){
        lcd.clear();
        lcd.print(F("<-Concord     ->"));
        if(13 != control) control = 11;
        else control = 14;
      }else if(mainCode[2]=='2'){
        lcd.clear();
        lcd.print(F("<-Zurich      ->"));
        if(13 != control) control = 11;
        else control = 14;
      }else if(mainCode[2]=='3'){
        lcd.clear();
        lcd.print(F("<-Berlin      ->"));
        if(13 != control) control = 11;
        else control = 14;
      }else if(mainCode[2]=='4'){
        lcd.clear();
        lcd.print(F("<-Montreal    ->"));
        if(13 != control) control = 11;
        else control = 14;
      }else if(mainCode[2]=='5'){
        lcd.clear();
        lcd.print(F("<-Buenos Aires->"));
        if(13 != control) control = 11;
        else control = 14;
      }else if(mainCode[2]=='6'){
        lcd.clear();
        lcd.print(F("<-Sao paulo   ->"));
        if(13 != control) control = 11;
        else control = 14;
      }else if(mainCode[2]=='7'){
        lcd.clear();
        lcd.print(F("<-Sydney      ->"));
        if(13 != control) control = 11;
        else control = 14;
      }else if(mainCode[2]=='8'){
        lcd.clear();
        lcd.print(F("<-Busan       ->"));
        if(13 != control) control = 11;
        else control = 14;
      }else if(mainCode[2]=='9'){
        lcd.clear();
        lcd.print(F("<-Hawaii      ->"));
        if(13 != control) control = 11;
        else control = 14;
      }
    }else if(mainCode[1]=='2' && 0 == button){
      if(mainCode[2]=='0'){
        lcd.clear();
        lcd.print(F("<-Lisbon      ->"));
        if(13 != control) control = 11;
        else control = 14;
      }else if(mainCode[2]=='1'){
        lcd.clear();
        lcd.print(F("<-Queen Eliza ->"));
        if(13 != control) control = 11;
        else control = 14;
      }else if(mainCode[2]=='2'){
        lcd.clear();
        lcd.print(F("<-Madrid      ->"));
        if(13 != control) control = 11;
        else control = 14;
      }else if(mainCode[2]=='3'){
        lcd.clear();
        lcd.print(F("<-Tokyo       ->"));
        if(13 != control) control = 11;
        else control = 14;
      }else if(mainCode[2]=='4'){
        lcd.clear();
        lcd.print(F("<-Colombia    ->"));
        if(13 != control) control = 11;
        else control = 14;
      }else if(mainCode[2]=='5'){
        lcd.clear();
        lcd.print(F("<-Paris       ->"));
        if(13 != control) control = 11;
        else control = 14;
      }else if(mainCode[2]=='6'){
        lcd.clear();
        lcd.print(F("<-Rome        ->"));
        if(13 != control) control = 11;
        else control = 14;
      }else if(mainCode[2]=='7'){
        lcd.clear();
        lcd.print(F("<-London      ->"));
        if(13 != control) control = 11;
        else control = 14;
      }else if(mainCode[2]=='8'){
        lcd.clear();
        lcd.print(F("<-New York    ->"));
        if(13 != control) control = 11;
        else control = 14;
      }else if(mainCode[2]=='9'){
        lcd.clear();
        lcd.print(F("<-Seoul       ->"));
        if(13 != control) control = 11;
        else control = 14;
      }
    }else if('3' == mainCode[1] && '8' == mainCode[2] && 0 == button){
      lcd.clear();
      lcd.print(F("You sold it"));
      control = 12;
    }else if('3' == mainCode[1] && '8' == mainCode[2] && 3 == button && 12 == control){
      Serial.write("1");
      control = 12;
    }else if('3' == mainCode[1] && '9' == mainCode[2] && 0 == button){
      lcd.clear();
      lcd.print(F("You have to sell"));
      lcd.setCursor(0,1);
      lcd.print(F("more"));
      control = 12;
    }else if('3' == mainCode[1] && '9' == mainCode[2] && 3 == button && 12 == control){
      Serial.write("1");
      control = 10;
    }else if('4' == mainCode[1] && 0 == button){
      control = 0;
    }
  }else if(11 == control && 0 == button){
    lcd.setCursor(0,1);
    int b = 0;
    for(int i = 0;i < 3; i++){
      if(mainCode[i] == '0' && b == 0){
        lcd.print(' ');
      }
      else{
        b = 1;
        lcd.print(mainCode[i]);
      }
    }
    lcd.print("000Won");
  }else if(((11 == control) || (14 == control))&& (1 == button)){
    Serial.write('1');
    if(14 != control) control = 10;
    else control = 13;
  }else if(((11 == control) || (14 == control)) &&(2 == button)){
    Serial.write('2');
    if(14 != control) control = 10;
    else control = 13;
  }else if(((11 == control) || (14 == control)) && (3 == button)){
    Serial.write('3');
    if(14 != control) control = 10;
    else control = 13;
  }
  else if(mainCode[0]=='1' && control < 10){
    if(0 == control && 0 == button){ 
      lcd.clear();
      lcd.print(F("Roll the dice!"));
      control = 1;
    }else if(1 == control && 3 == button){
      lcd.setCursor(4,1);
      lcd.print(mainCode[1]);
      control = 2;
    }else if(2 == control && 3 == button){
      lcd.setCursor(11,1);
      lcd.print(mainCode[2]);
      control = 3;
    }else if(3 == control && 3 == button){
      Serial.write('1');
      control = 0;
    }
  }else if(mainCode[1] == '0'&& control < 10){
    if('1' == mainCode[2]&& 0 == button){
      lcd.clear();
      lcd.print(F("3 doubles!"));
      lcd.setCursor(0,1);
      lcd.print(F("Go to the island"));
      control = 1;
    }else if('1' == mainCode[2 ]&& 3 == button && 1 == control){
      Serial.write('1');
      control = 0;
    }else if('2' == mainCode[2] && 0 == button){
      lcd.clear();
      lcd.print(F("Want space tour?"));
      lcd.setCursor(4,1);
      lcd.print("Y");
      lcd.setCursor(11,1);
      lcd.print("N");
      lcd.setCursor(4,1);
      lcd.cursor();
      control = 1;
    }else if('2' == mainCode[2] && 0 != control && 2 == button || 1 == button){
      if(1 == control) lcd.setCursor(10 + control++,1);
      else lcd.setCursor(2 + control--,1);
    }else if('2' == mainCode[2] && 3 == button && 0 != control){
      1 == control && Serial.write('1');
      2 == control && Serial.write('2');
      control = 0;
      lcd.noCursor();
    }else if('3' == mainCode[2]&& 0 == button){
      lcd.clear();
      lcd.print(F("Use Radio?"));
      lcd.setCursor(4,1);
      lcd.print("Y");
      lcd.setCursor(11,1);
      lcd.print("N");
      lcd.setCursor(4,1);
      lcd.cursor();
      control = 1;
    }else if('3' == mainCode[2] && 0 != control && 2 == button || 1 == button){
      if(1 == control) lcd.setCursor(10 + control++,1);
      else lcd.setCursor(2 + control--,1);
    }else if('3' == mainCode[2] && 3 == button && 0 != control){
      1 == control && Serial.write('1');
      2 == control && Serial.write('2');
      control = 0;
      lcd.noCursor();
    }else if('4' == mainCode[2]&& 0 == button){
      lcd.clear();
      lcd.print(F("You used radio"));
      control = 1;
    }else if('4' == mainCode[2]&& 3 == button && control == 1){
      Serial.write('1');
      control = 0;
    }else if('5' == mainCode[2]&& 0 == button){
      lcd.clear();
      lcd.print(F("You can go now!"));
      control = 1;
    }else if('5' == mainCode[2]&& 3 == button && 1 == control){
      Serial.write('1');
      control = 0;
    }else if('6' == mainCode[2]&& 0 == button){
      lcd.clear();
      lcd.print(F("Here is deserted"));
      lcd.setCursor(0,1);
      lcd.print(F("island"));
      control = 1;
    }else if('6' == mainCode[2]&& 3 == button && control == 1){
      Serial.write('1');
      control = 0;
    }else if('7' == mainCode[2]&& 0 == button){
      lcd.clear();
      lcd.print(F("Double!!"));
      lcd.setCursor(0,1);
      lcd.print(F("You can go now!"));
      control = 1;
    }else if('7' == mainCode[2]&& 3 == button && control == 1){
      Serial.write('1');
      control = 0;
    }else if('8' == mainCode[2]&& 0 == button){
      lcd.clear();
      lcd.print(F("You can't go now"));
      control = 1;
    }else if('8' == mainCode[2]&& 3 == button && control == 1){
      Serial.write('1');
      control = 0;
    }else if('9' == mainCode[2]&& 0 == button){
      lcd.clear();
      lcd.print(F("You've rested"));
      lcd.setCursor(0,1);
      lcd.print(F("enough"));
      control = 1;
    }else if('9' == mainCode[2]&& 3 == button && control == 1){
      Serial.write('1');
      control = 0;
    }
  }else if('1' == mainCode[1] && control < 10){
    if('0' == mainCode[2]&& 0 == button){
      lcd.clear();
      lcd.print(F("Go on space tour"));
      control = 1;
    }else if('0' == mainCode[2] && 3 == button && control == 1){
      Serial.write('1');
      control = 0;
    }else if('1' == mainCode[2]&& 0 == button){
      lcd.clear();
      lcd.print(F("<-Where do you->"));
      lcd.setCursor(0,1);
      lcd.print(F("want to go?"));
      control = 1;
    }else if('1' == mainCode[2] && 1 == control && 2 == button || 1 == button){
      if(button == 1) Serial.write('1');
      else Serial.write('2');
    }else if('1' == mainCode[2] && 1 == control && 3 == button){
      Serial.write('3');
      control = 0;
    }else if('2' == mainCode[2]&& 0 == button){
      lcd.clear();
      lcd.print(F("You have arrived"));
      control = 1;
    }else if('2' == mainCode[2] && 3 == button && control == 1){
      Serial.write('1');
      control = 0;
    }else if('3' == mainCode[2]&& 0 == button){
      lcd.clear();
      lcd.print(F("You paid"));
      control = 1;
    }else if('3' == mainCode[2] && 3 == button && control == 1){
      Serial.write('1');
      control = 0;
    }else if('4' == mainCode[2]&& 0 == button){
      lcd.clear();
      lcd.print(F("You don't want"));
      lcd.setCursor(0,1);
      lcd.print(F("space tour"));
      control = 1;
    }else if('4' == mainCode[2] && 3 == button && control == 1){
      Serial.write('1');
      control = 0;
    }else if('5' == mainCode[2]&& 0 == button){
      lcd.clear();
      lcd.print(F("Take a Golden"));
      lcd.setCursor(0,1);
      lcd.print(F("Key"));
    }else if('6' == mainCode[2]&& 0 == button){
      lcd.clear();
      lcd.print(F("Deserted island"));
      lcd.setCursor(0,1);
      lcd.print(F("Rest for 3 turns"));
      control = 1;
    }else if('6' == mainCode[2] && 3 == button && control == 1){
      Serial.write('1');
      control = 0;
    }else if('7' == mainCode[2]&& 0 == button){
      lcd.clear();
      lcd.print(F("You can take"));
      lcd.setCursor(0,1);
      lcd.print(F("welfare fund"));
      control = 1;
    }else if('7' == mainCode[2] && 3 == button && control == 1){
      Serial.write('1');
      control = 0;
    }else if('8' == mainCode[2]&& 0 == button){
      lcd.clear();
      lcd.print(F("You took"));
      lcd.setCursor(0,1);
      lcd.print(F("welfare fund"));
      control = 1;
    }else if('8' == mainCode[2] && 3 == button && control == 1){
      Serial.write('1');
      control = 0;
    }else if('9' == mainCode[2]&& 0 == button){
      lcd.clear();
      lcd.print(F("You have arrived"));
      lcd.setCursor(0,1);
      lcd.print(F("space ship"));
      control = 1;
    }else if('9' == mainCode[2] && 3 == button && control == 1){
      Serial.write('1');
      control = 0;
    }
  }else if('2' == mainCode[1] && control < 10){
    if('0' == mainCode[2] && 0 == button){
      lcd.clear();
      lcd.print(F("Next turn, you"));
      lcd.setCursor(0,1);
      lcd.print(F("can go anywhere"));
      control = 1;
    }else if('0' == mainCode[2] && 3 == button && control == 1){
      Serial.write('1');
      control = 0;
    }else if('1' == mainCode[2]&& 0 == button){
      lcd.clear();
      lcd.print(F("Donate money"));
      lcd.setCursor(0,1);
      lcd.print(F("for welfare fund"));
      control = 1;
    }else if('1' == mainCode[2] && 3 == button && control == 1){
      Serial.write('1');
      control = 0;
    }else if('2' == mainCode[2]&& 0 == button){
      lcd.clear();
      lcd.print(F("Donate "));
      lcd.setCursor(0,1);
      lcd.print(F("150000 Won"));
      control = 1;
    }else if('2' == mainCode[2] && 3 == button && control == 1){
      Serial.write('1');
      control = 0;
    }else if('3' == mainCode[2]&& 0 == button){
      lcd.clear();
      lcd.print(F("Not enough money"));
      lcd.setCursor(0,1);
      lcd.print(F("Sell your estate"));
      control = 1;
    }else if('3' == mainCode[2] && 3 == button && control == 1){
      Serial.write('1');
      control = 0;
    }else if('4' == mainCode[2]&& 0 == button){
      lcd.clear();
      lcd.print(F("This is your"));
      lcd.setCursor(0,1);
      lcd.print(F("estate"));
      control = 1;
    }else if('4' == mainCode[2] && 3 == button && control == 1){
      Serial.write('1');
      control = 0;
    }else if('5' == mainCode[2]&& 0 == button){
      lcd.clear();
      lcd.print(F("Buy this tour?"));
      lcd.setCursor(4,1);
      lcd.print("Y");
      lcd.setCursor(11,1);
      lcd.print("N");
      lcd.setCursor(4,1);
      lcd.cursor();
      control = 1;
    }else if('5' == mainCode[2] && 0 != control && 2 == button || 1 == button){
      if(1 == control) lcd.setCursor(10 + control++,1);
      else lcd.setCursor(2 + control--,1);
    }else if('5' == mainCode[2] && 3 == button && 0 != control){
      1 == control && Serial.write('1');
      2 == control && Serial.write('2');
      control = 0;
      lcd.noCursor();
    }else if('6' == mainCode[2]&& 0 == button){
      lcd.clear();
      lcd.print(F("Not enough money"));
      control = 1;
    }else if('6' == mainCode[2] && 3 == button && control == 1){
      Serial.write('1');
      control = 0;
    }else if('7' == mainCode[2]&& 0 == button){
      lcd.clear();
      lcd.print(F("You Buyed"));
      control = 1;
    }else if('7' == mainCode[2] && 3 == button && control == 1){
      Serial.write('1');
      control = 0;
    }else if('8' == mainCode[2]&& 0 == button){
      lcd.clear();
      lcd.print(F("You didn't buyed"));
      control = 1;
    }else if('8' == mainCode[2] && 3 == button && control == 1){
      Serial.write('1');
      control = 0;
    }else if('9' == mainCode[2] && 0 == button){
      lcd.clear();
      lcd.print(F("Buy this land?"));
      lcd.setCursor(4,1);
      lcd.print("Y");
      lcd.setCursor(11,1);
      lcd.print("N");
      lcd.setCursor(4,1);
      lcd.cursor();
      control = 1;
    }else if('9' == mainCode[2] && 0 != control && 2 == button || 1 == button){
      if(1 == control) lcd.setCursor(10 + control++,1);
      else lcd.setCursor(2 + control--,1);
    }else if('9' == mainCode[2] && 3 == button && 0 != control){
      1 == control && Serial.write('1');
      2 == control && Serial.write('2');
      control = 0;
      lcd.noCursor();
    }
  }else if('3' == mainCode[1] && control < 10){
    if('0' == mainCode[2]&& 0 == button){
      lcd.clear();
      lcd.print(F("What do you want"));
      lcd.setCursor(0,1);
      lcd.print(F("to build?"));
      control = 1;
    }else if('0' == mainCode[2] && 3 == button && control == 1){
      Serial.write('1');
      control = 0;
    }else if('1' == mainCode[2] && 0 == button){
      lcd.clear();
      lcd.print(F("1.Nothing2.Villa"));
      lcd.setCursor(0,1);
      lcd.print(F("3.Buildng4.Hotel"));
      lcd.setCursor(0,0);
      lcd.cursor();
      control = 1;
    }else if('1' == mainCode[2] && 0 != control && 1 == button){
      if(1 == control){
        lcd.setCursor(9,1);
        control = 4;
      }else if(2 == control){
        lcd.setCursor(0,0);
        control = 1;
      }else if(3 == control){
        lcd.setCursor(9,0);
        control = 2;
      }else{
        lcd.setCursor(0,1);
        control = 3;
      }
    }else if('1' == mainCode[2] && 0 != control && 2 == button){
      if(1 == control){
        lcd.setCursor(9,0);
        control = 2;
      }else if(2 == control){
        lcd.setCursor(0,1);
        control = 3;
      }else if(3 == control){
        lcd.setCursor(9,1);
        control = 4;
      }else{
        lcd.setCursor(0,0);
        control = 1;
      }
    }else if('1' == mainCode[2] && 0 != control && 3 == button){
      1 == control && Serial.write('1');
      2 == control && Serial.write('2');
      3 == control && Serial.write('3');
      4 == control && Serial.write('4');
      control = 0;
      lcd.noCursor();
    }else if('2' == mainCode[2]&& 0 == button){
      lcd.clear();
      lcd.print(F("You built"));
      lcd.setCursor(0,1);
      lcd.print(F("a villa"));
      control = 1;
    }else if('2' == mainCode[2] && 3 == button && control == 1){
      Serial.write('1');
      control = 0;
    }else if('3' == mainCode[2]&& 0 == button){
      lcd.clear();
      lcd.print(F("You built"));
      lcd.setCursor(0,1);
      lcd.print(F("a building"));
      control = 1;
    }else if('3' == mainCode[2] && 3 == button && control == 1){
      Serial.write('1');
      control = 0;
    }else if('4' == mainCode[2]&& 0 == button){
      lcd.clear();
      lcd.print(F("You built"));
      lcd.setCursor(0,1);
      lcd.print(F("a hotel"));
      control = 1;
    }else if('4' == mainCode[2] && 3 == button && control == 1){
      Serial.write('1');
      control = 0;
    }else if('5' == mainCode[2]&& 0 == button){
      lcd.clear();
      lcd.print(F("You built"));
      lcd.setCursor(0,1);
      lcd.print(F("nothing"));
      control = 1;
    }else if('5' == mainCode[2] && 3 == button && control == 1){
      Serial.write('1');
      control = 0;
    }else if('6' == mainCode[2]&& 0 == button){
      lcd.clear();
      lcd.print(F("YOU ARE BANKRUPT"));
      lcd.setCursor(0,1);
      lcd.print(F("KKKKKKKKKKKKKKKK"));
      control = 1;
    }else if('6' == mainCode[2] && 3 == button && control == 1){
      control = 0;
    }else if('7' == mainCode[2]&& 0 == button){
      control = 10;
    }else if('8' == mainCode[2] && 0 == button){
      lcd.clear();
      lcd.print(F("You sold it"));
      control = 1;
    }else if('8' == mainCode[2] && 3 == button && 1 == control){
      Serial.write("1");
      control = 0;
    }
  }else if('4' == mainCode[1] && control < 10){
    if('1' == mainCode[2] && 0 == button){
      lcd.clear();
      lcd.print(F("Use ticket?"));
      lcd.setCursor(4,1);
      lcd.print("Y");
      lcd.setCursor(11,1);
      lcd.print("N");
      lcd.setCursor(4,1);
      lcd.cursor();
      control = 1;
    }else if('1' == mainCode[2] && 0 != control && 2 == button || 1 == button){
      if(1 == control) lcd.setCursor(10 + control++,1);
      else lcd.setCursor(2 + control--,1);
    }else if('1' == mainCode[2] && 3 == button && 0 != control){
      1 == control && Serial.write('1');
      2 == control && Serial.write('2');
      control = 0;
      lcd.noCursor();
    }else if('2' == mainCode[2]&& 0 == button){
      lcd.clear();
      lcd.print(F("This isn't your"));
      lcd.setCursor(0,1);
      lcd.print(F("estate"));
      control = 1;
    }else if('2' == mainCode[2] && 3 == button && control == 1){
      Serial.write('1');
      control = 0;
    }else if('3' == mainCode[2]&& 0 == button){
      lcd.clear();
      lcd.print(F("Pay your fees"));
      control = 1;
    }else if('3' == mainCode[2] && 3 == button && control == 1){
      Serial.write('1');
      control = 0;
    }else if('4' == mainCode[2]&& 0 == button){
      lcd.clear();
      lcd.print(F("There is not"));
      lcd.setCursor(0,1);
      lcd.print(F("estate for sale"));
      control = 1;
    }else if('4' == mainCode[2] && 3 == button && control == 1){
      Serial.write('1');
      control = 0;
    }else if('5' == mainCode[2] && 0 == button){
      lcd.clear();
      lcd.print(F("Sell Radio?"));
      lcd.setCursor(4,1);
      lcd.print("Y");
      lcd.setCursor(11,1);
      lcd.print("N");
      lcd.setCursor(4,1);
      lcd.cursor();
      control = 1;
    }else if('5' == mainCode[2] && 0 != control && 2 == button || 1 == button){
      if(1 == control) lcd.setCursor(10 + control++,1);
      else lcd.setCursor(2 + control--,1);
    }else if('5' == mainCode[2] && 3 == button && 0 != control){
      1 == control && Serial.write('1');
      2 == control && Serial.write('2');
      control = 0;
      lcd.noCursor();
    }else if('6' == mainCode[2]&& 0 == button){
      lcd.clear();
      lcd.print(F("Start Bonus!!!"));
      control = 1;
    }else if('6' == mainCode[2] && 3 == button && control == 1){
      Serial.write('1');
      control = 0;
    }else if('7' == mainCode[2]&& 0 == button){
      lcd.clear();
      lcd.print(F("You can build"));
      lcd.setCursor(0,1);
      lcd.print(F("anything"));
      control = 1;
    }else if('7' == mainCode[2]&& 3 == button && control == 1){
      lcd.clear();
      lcd.print(F("on one of your"));
      lcd.setCursor(0,1);
      lcd.print(F("lands"));
      control = 2;
    }else if('7' == mainCode[2] && 3 == button && control == 2){
      Serial.write('1');
      control = 0;
    }else if('8' == mainCode[2]&& 0 == button){
      lcd.clear();
      lcd.print(F("You have not any"));
      lcd.setCursor(0,1);
      lcd.print(F("land to build"));
      control = 1;
    }else if('8' == mainCode[2] && 3 == button && control == 1){
      Serial.write('1');
      control = 0;
    }else if('9' == mainCode[2] && 0 == button){
      control = 13;
    }
  }
}


void setPlayer(char* serBuffer, player** playerList){
  char leng;
  char i;
  switch(serBuffer[1]){
    case '1': i = 0; break;
    case '2': i = 1; break;
    case '3': i = 2; break;
    case '4': i = 3; break;
  }
  switch(serBuffer[2]){
    case '0':  // 돈의 경우
        playerList[i]->money[4] = serBuffer[7];
        playerList[i]->money[3] = serBuffer[6];
        playerList[i]->money[2] = serBuffer[5];
        playerList[i]->money[1] = serBuffer[4];
        playerList[i]->money[0] = serBuffer[3];
       break;
    case '1':  // 부동산의 경우
      if(serBuffer[4]=='1'){
        playerList[i]->estLeng++;
        leng = playerList[i]->estLeng;
        playerList[i]->estList[leng-1][0]=10*(serBuffer[5]-48)+(serBuffer[6]-48);
        playerList[i]->estList[leng-1][1]=(serBuffer[7]-48);
      }
      else{
        char j=0;
        leng = playerList[i]->estLeng;
        while(1){
          if(playerList[i]->estList[j][0]==10*(serBuffer[5]-48)+(serBuffer[6]-48))break;
          j++;
        }
        playerList[i]->estList[j][0]=0;
        playerList[i]->estList[j][1]=0;
        if(j!=leng-1){
          playerList[i]->estList[j][0]=playerList[i]->estList[leng-1][0];
          playerList[i]->estList[j][1]=playerList[i]->estList[leng-1][1];
          playerList[i]->estList[leng-1][0]=0;
          playerList[i]->estList[leng-1][1]=0;
        }
        playerList[i]->statPage=1;
        playerList[i]->estLeng--;
      }  break;
    case '2': //황금열쇠의 경우
      if(serBuffer[6]=='0'){
        if(serBuffer[7]=='0'){
          playerList[i]->ticket = playerList[i]->ticket - 1;
        }
        else{
          playerList[i]->ticket = playerList[i]->ticket + 1;
        }
      }
      else if(serBuffer[6]=='1'){
        if(serBuffer[7]=='0'){
          playerList[i]->radio = playerList[i]->radio - 1;
        }
        else{
          playerList[i]->radio = playerList[i]->radio + 1;
        }
      } break;
    case '3': //무인도의 경우
      if(serBuffer[7]=='3'){
        playerList[i]->islandFlg = 1;
        playerList[i]->island = 3;
      }
      else if(serBuffer[7]=='2'){
        playerList[i]->island = 2;
      }
      else if(serBuffer[7]=='1'){
        playerList[i]->island = 1;
      }
      else if(serBuffer[7]=='0'){
        playerList[i]->island = 0;
      }
      else if(serBuffer[7]=='4'){
        playerList[i]->islandFlg = 0;
      }
      playerList[i]->statPage=1;
      break;
    case '4':
      playerList[i]->deadFlg = 1;
      break;
  }
}
