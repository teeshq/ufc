#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
//#define  DCSBIOS_IRQ_SERIAL //mega
#define  DCSBIOS_DEFAULT_SERIAL // eps
#include "DcsBios.h"




//U8G2_SH1122_256X64_F_4W_HW_SPI u8g2(U8G2_R2, /* cs=*/ 10, /* dc=*/ 5, /* reset=*/ 4); // mega scl pin52, sda pin 
U8G2_SH1122_256X64_F_4W_HW_SPI u8g2(U8G2_R0, /* cs=*/ 15, /* dc=*/ 5, /* reset=*/ 4);
int count;


void setup() 
{
 count = 0;
  u8g2.begin();
  u8g2.setBusClock(7000000);
  u8g2.setFont(Hornet_UFC);
  u8g2.clearDisplay();
  u8g2.clearBuffer();
  u8g2.drawRFrame(4,2,251,61,4);
  u8g2.drawRFrame(5,3,249,59,4);
  u8g2.drawRFrame(6,4,247,57,4);
  u8g2.setCursor(15, 48);
  u8g2.print("SIM TEES");
  u8g2.sendBuffer();
  delay(3000);
  u8g2.clearDisplay();
  u8g2.clearBuffer();
  u8g2.drawRFrame(4,2,251,61,4);
  u8g2.drawRFrame(5,3,249,59,4);
  u8g2.drawRFrame(6,4,247,57,4);
  u8g2.setCursor(40, 48);
  u8g2.print("HORNET");
  u8g2.sendBuffer();
  delay(3000);
  u8g2.clearDisplay();
  u8g2.clearBuffer();
  u8g2.drawRFrame(4,2,251,61,4);
  u8g2.drawRFrame(5,3,249,59,4);
  u8g2.drawRFrame(6,4,247,57,4);
  u8g2.setCursor(15, 48);
  u8g2.print("SIM TEES");
  u8g2.sendBuffer();
  delay(3000);
  
  DcsBios::setup();

}

void loop()
{   
  DcsBios::loop();
}

String comDisplay[3];
void updateComDisplay(int changed,char* newValue) {
 comDisplay[changed] = cleanUpCom(newValue);

u8g2.clearBuffer();          // clear the internal memory 
u8g2.setCursor(2, 45);
u8g2.print(comDisplay[0]);
u8g2.setCursor(54, 45);
u8g2.print(comDisplay[1]);
u8g2.setCursor(72, 45);
u8g2.print(comDisplay[2]);
u8g2.sendBuffer(); 
}


char* cleanUpCom(char* newValue) {
 switch (newValue[0]) {
   case '`':
     newValue[0]='1';
     break;
   case '~':
     newValue[0]='2';
     break;
       
 }
 return newValue;  
}
void onUfcScratchpadNumberDisplayChange(char* newValue) {
    updateComDisplay(2, newValue);
}
DcsBios::StringBuffer<8> ufcScratchpadNumberDisplayBuffer(0x7446, onUfcScratchpadNumberDisplayChange);/// main

void onUfcScratchpadString2DisplayChange(char* newValue) {
    updateComDisplay(1, newValue);
}
DcsBios::StringBuffer<2> ufcScratchpadString2DisplayBuffer(0x7450, onUfcScratchpadString2DisplayChange);///mid

void onUfcScratchpadString1DisplayChange(char* newValue) {
    updateComDisplay(0, newValue);
}
DcsBios::StringBuffer<2> ufcScratchpadString1DisplayBuffer(0x744e, onUfcScratchpadString1DisplayChange);///left
  //// updateComDisplay(2, newValue);
DcsBios::LED masterCautionLt(0x7408, 0x0200, 16);
