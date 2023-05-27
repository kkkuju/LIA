//latest 24/04

//manual mode, no SP, output controlled manually directly from input +LCD display
//good for trouble shoot and freedom know limit
//bad nees to be present 

//the resistor used needs to be adjusted from ambient light
// include the library code:
#include <LiquidCrystal.h>// this is the libray for the LCD display
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

int sens = A0;// set int as Ao port
int input = A1;
int actuator= 3;
int pv = 0;
int inVal = 0;
int CO = 0;
/*
//new variables:
int hys = 30; 
int sp = 0;
*/


void setup() {
  // put your setup code here, to run once:
pinMode(actuator, OUTPUT);
Serial.begin(9600);
lcd.begin(16,2); // set up the available space on the LCD display. 16 colums and 2 rows. 

}

void loop() {
  // put your main code here, to run repeatedly:

pv = analogRead(sens);

inVal = analogRead(input);



CO = map  (inVal, 0, 1023 , 0, 255);


//no need to convert the CO to 255 value because it's set in the previous lines
analogWrite(actuator, CO);

lcd.setCursor(0, 0);
lcd.print("CO=  ");
lcd.print(CO);
lcd.print("           ");

lcd.setCursor(0, 1);
lcd.print("PV=");
lcd.print(pv);
lcd.print("           ");


Serial.print("CO=  ");
Serial.print(CO);
Serial.print("           ");
Serial.print("PV=  ");
Serial.println(pv);



}
