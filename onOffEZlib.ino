//onOff mode, the CO will try to match the SP by turning on and off
//the resistor used needs to be adjusted from ambient light

/*
The on off control mode:
The sp will be set by 2 push buttons along with the hysteresis with the 2 same buttons. 
Once the sp is more than 0, the CO will be activated fully to 255 to attempt to match the sp. 
Because it will activates fully, it can never attend the sp and stay there. 
When the pv surpasses the sp plus the (hysteresis if configured), 
the CO will turn off to match the sp again. 

A library for the button is used to automatically configure the debounce function. 
There are 4 buttons in total. 2 of which configures the hysteresis and the sp as previously mentioned. 
The 2 others change the 2 variables that are currently being configured on the LCD. This is made possible by 
using a counter function. When the configured button (b3 or b4) is pressed, the variable “select” goes up or 
down by one and its value is limited to the configurable variables. So if the current value of select is 0, 
the variable hys will be displayed on the LCD and able to be configured by the button (b1 and b2). Then if 
the button that adds 1 to the select is pressed, select will now be at 1. The LCD will display the value of 
sp and its value will be able to be changes by the buttons (b1 and b2). 

On the LCD display, the number of PV and CO changes too fast where it becomes hard to read. 
So a delay function is used to slow down the print of the LCD for those 2 variables without
actually delaying the program using the millis function. 

*/
int sens = A0;// set int as Ao port for the LDR sensor
int actuator= 6;// set the pin 6 as actuator
int pv = 0; // set the pv as a int 
int CO = 0;// set the CO as a int 
int sp = 0;// set the sp as a int 
int hys = 0;// set the hys as a int 
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

const long interval = 100;//setup the time interval for the delay 
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
lcd.print("CO=");//print the text
lcd.print(CO);//print the value of CO
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
lcd.print("CO=");//print the text
lcd.print(CO);//print the value of CO
lcd.print("           ");//print spaces to avoid visual bugs
    }

if(b1.isPressed())//library command for when b1 is pressed
  hys = hys +15;//hys+15
    if (hys >= 155)//hys capped at 155
   hys = 155;

if(b2.isPressed())//library command for when b2 is pressed
  hys = hys -15;//hys -15
   if (hys <= 0)//hys capped at 0
   hys = 0;

lcd.setCursor(0, 1);//setup the position for the text x=0 y=1
lcd.print("hys=  ");//print the text
lcd.print(hys);//print the value of sp
lcd.print("           ");//print spaces to avoid visual bugs



}


//*************************OUTPUT
pv = analogRead(sens);//pv = the value read from analog pin "sens"
if (pv <= (sp - hys)){//if the pv is lower than sp plus hys, the CO turns on
  CO= 255;
}
 else if (pv >= (sp + hys)){//if the pv is higher than sp plus hys, the CO turns off

   CO= 0;
 }
analogWrite(actuator, CO);//write the value of CO to the actuator pin 



//****************Serial prints values
Serial.print("select=  "); //prints select
Serial.print(select);
Serial.print("       ");

Serial.print("    hys=  ");//prints value of hys
Serial.print(hys);
Serial.print("       ");

Serial.print("    sp=  ");//prints sp
Serial.print(sp);
Serial.print("       ");

Serial.print("    pv=  ");// prints pv
Serial.print(pv);
Serial.println("       ");

}