//p control, lcd with buttons, need to change gain for the ambient

int sens = A1;// set int as Ao port for the LDR sensor
int actuator= 6;// set the pin 6 as actuator
int pv = 0; // set the pv as a int 
int CO = 0;// set the CO as a int 
int sp = 0;// set the sp as a int 
int error = 0;// set the error as a int 

float gain =20 ;


int select = 0;// set select as int


//button variables:
#include <ezButton.h>//this adds the button debounce library 
ezButton b1(2);// create ezButton object that attach to pin 2
ezButton b2(3);// create ezButton object that attach to pin 3
ezButton b3(4);// create ezButton object that attach to pin 4
ezButton b4(5);// create ezButton object that attach to pin 5

// include the library code:
#include <LiquidCrystal.h>// this is the libray for the LCD display
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);// setup for the LCD pins

const long interval = 300;//setup the time interval for the delay 
unsigned long previousMillis = 0; //set previousMillis as unsigned long

void setup() {
Serial.begin(9600);// begin the serial monitor
pinMode(actuator, OUTPUT);// set the actuator pin declared previously as output
lcd.begin(16,2); // set up the available space on the LCD display. 16 colums and 2 rows. 


}

void loop() {
  b1.loop(); // MUST call the loop() function first
  b2.loop(); // MUST call the loop() function first
  b3.loop(); // MUST call the loop() function first
  b4.loop(); // MUST call the loop() function first




    if(b3.isPressed()) //library command for when b3 is pressed
     select = select +1;//add 1 to the variable select

    if(b4.isPressed()) //library command for when b4 is pressed
     select = select -1;//minus 1 to the variable select

if(select >=1){//condition for when select is bigger than the number
               //this is important to set the number of the parameteres being controlled
  select = 1;//= the number if it passes it
}
if(select <=0){//the same goes for the other way around, the number for the pages is limited to 0

  select = 0;//= the number if it goes below it
}


if (select == 0){//if select is 0, this is he first page/parameter

    unsigned long currentMillis = millis();//this is a delay function without using delay
    if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;//this allows the LCD to print the live value of the pv and CO once every amount of time set

lcd.setCursor(0, 0);//setup the position for the text x=0 y=0
lcd.print("PV=");//print the text
lcd.print(pv);//print the value of pv
lcd.print("           ");//print spaces to avoid visual bugs

lcd.setCursor(8, 0);//setup the position for the text x=8 y=0
lcd.print("error=");//print the text
lcd.print(error);//print the value of CO
lcd.print("           ");//print spaces to avoid visual bugs
    }

if(b1.isPressed())//library command for when b1 is pressed
  sp = sp +100;//sp + 100
    if (sp >= 1030)//sp capped at 1030
   sp = 1030;

if(b2.isPressed())//library command for when b2 is pressed
  sp = sp -100;//sp -100
   if (sp <= 0)//sp capped at 0
   sp = 0;



lcd.setCursor(0, 1);//setup the position for the text x=0 y=1
lcd.print("SP=  ");//print the text
lcd.print(sp);//print the value of sp
lcd.print("           ");//print spaces to avoid visual bugs
}


if (select == 1){
  unsigned long currentMillis = millis();//serves the same funtion as the part on top, to delay the LCD print
    if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

lcd.setCursor(0, 0);//setup the position for the text x=0 y=0
lcd.print("PV=");//print the text
lcd.print(pv);//print the value of pv
lcd.print("           ");//print spaces to avoid visual bugs

lcd.setCursor(8, 0);//setup the position for the text x=8 y=0
lcd.print("error=");//print the text
lcd.print(error);//print the value of CO
lcd.print("           ");//print spaces to avoid visual bugs
    }

if(b1.isPressed())//library command for when b1 is pressed
  gain = gain +2;//hys+15
    if (gain >= 500.0)//hys capped at 155
   gain = 500.0;

if(b2.isPressed())//library command for when b2 is pressed
  gain = gain -2;//hys -15
   if (gain <= 0.0)//hys capped at 0
   gain = 0.0;

lcd.setCursor(0, 1);//setup the position for the text x=0 y=1
lcd.print("gain=  ");//print the text
lcd.print(gain);//print the value of sp
lcd.print("           ");//print spaces to avoid visual bugs



}


//*************************OUTPUT
pv = analogRead(sens);//pv = the value read from analog pin "sens"
error = (sp-pv);
CO = (gain*error)/100;

if (CO >= 255){//if the pv is lower than sp plus hys, the CO turns on
  CO= 255;
}
 else if (CO <= 0){//if the pv is higher than sp plus hys, the CO turns off

   CO= 0;
 }
analogWrite(actuator, CO);//write the value of CO to the actuator pin 



//****************Serial prints values
/*
Serial.print("select=  "); //prints select
Serial.print(select);
Serial.print("       ");

Serial.print("    gain=  ");//prints value of hys
Serial.print(gain);
Serial.print("       ");

Serial.print("    CO=  ");//prints sp
Serial.print(CO);
Serial.print("       ");
*/
Serial.print("    sp=  ");//prints sp
Serial.print(sp);
Serial.print("       ");

Serial.print("    pv=  ");// prints pv
Serial.print(pv);
Serial.print("       ");

Serial.print("    error=  ");// prints pv
Serial.print(error);
Serial.println("       ");

}