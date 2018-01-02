#include <Wire.h> 

#include <LiquidCrystal_I2C.h>

#include <Keypad.h>

LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {40, 41, 42, 43}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {44, 45, 46, 47}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );


int alarm = 22;
int door = 23;
int toggle = 33;
int var = 1;


void setup() { 
 Serial.begin(9600);  
 lcd.begin(20,4);   

  pinMode(toggle, INPUT);
  pinMode(alarm, OUTPUT);
  digitalWrite(alarm, HIGH);
  pinMode(door, INPUT);  
}


void loop() {
  
  int  key;
  char pin1;
  char pin2;
  char pin3;
  char pin4;
  boolean password = false;
  int act = 1;
  
  lcd.setCursor(0,0);
  lcd.print("Drew's Secure System");
  lcd.setCursor(2,4);
  lcd.print("A = Activate");
  
  key = keypad.waitForKey();
  if (key == 'A'){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Type in the password");
  
  pin1 = keypad.waitForKey();
  lcd.setCursor ( 0, 2 );
  lcd.print(pin1);
  pin2 = keypad.waitForKey();
  lcd.setCursor ( 1, 2 );
  lcd.print(pin2);
  pin3 = keypad.waitForKey();
  lcd.setCursor ( 2, 2 );
  lcd.print(pin3);
  pin4 = keypad.waitForKey();
  lcd.setCursor ( 3, 2 );
  lcd.print(pin4);
  delay(700);
  
  if(pin1=='7'&&pin2=='0'&&pin3=='8'&&pin4=='9') {
    lcd.clear();
    lcd.print("Password is correct");
    delay(1000);
    password = true;
  }
  else {
     lcd.clear();
     lcd.print("Wrong password!");
     delay(1000);
     lcd.clear();
  }

  
 while (password == true) { 
   
   while (act == 1) {
   lcd.clear();
   digitalWrite(alarm, LOW);   
   delay(150);               
   digitalWrite(alarm, HIGH);    
   delay(150);
    digitalWrite(alarm, LOW);   
   delay(150);               
   digitalWrite(alarm, HIGH);    
   lcd.print("Alarm activatted");
   delay(1000);
   lcd.clear();
   act--;
   }
   
   if (digitalRead(door) == HIGH) {
      lcd.setCursor(3,0);
      lcd.print("Front Door Open");
      digitalWrite(alarm, LOW);   
      delay(700);               
      digitalWrite(alarm, HIGH);    
      delay(700);
      var = 0;
    }
    
    if (digitalRead(door) == LOW) {
      while(var==0) { 
        lcd.setCursor(3,0);
        lcd.print("Front Door Closed");
        delay(2000);
        var++;
      }
       lcd.clear();
       digitalWrite(alarm, HIGH);
    }
 }
    if (digitalRead(toggle) == LOW) {
      lcd.setCursor(3,0);
      lcd.clear();
      digitalWrite (alarm, HIGH);
    } 
  }
}
