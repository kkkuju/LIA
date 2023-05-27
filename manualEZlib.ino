//latest 24/04

//manual mode, no SP, output controlled manually directly from input +LCD display
//good for trouble shoot and freedom know limit
//bad nees to be present 

//the resistor used needs to be adjusted from ambient light
// include the library code:
#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

#include <ezButton.h>
ezButton b1(2);// create ezButton object that attach to pin 2
ezButton b2(3);


int sens = A0;// set int as Ao port
int input = A1;
int actuator= 6;
int pv = 0;
int inval = 0;
int CO = 0;



void setup() {
  // put your setup code here, to run once:
pinMode(actuator, OUTPUT);
Serial.begin(9600);
lcd.begin(16,2); // set up the available space on the LCD display. 16 colums and 2 rows. 

}

void loop() {
  // put your main code here, to run repeatedly:
  b1.loop(); // MUST call the loop() function first
  b2.loop(); // MUST call the loop() function first
pv = analogRead(sens);

if(b1.isPressed())
  inval = inval +100;
    if (inval >= 1023){
   inval = 1023;}

if(b2.isPressed())
  inval = inval -100;
   if (inval <= 0){
   inval = 0;}



CO = map  (inval, 0, 1023 , 0, 255);


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
Serial.print(pv);

Serial.print("           ");
Serial.print("inval=  ");
Serial.println(inval);

}
