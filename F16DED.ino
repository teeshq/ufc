


#include <FlickerFreePrint.h>
#include <SPI.h>
#include <TFT_eSPI.h> // Hardware-specific library
TFT_eSPI tft = TFT_eSPI();       // Invoke custom library
#define  DCSBIOS_DEFAULT_SERIAL
#include "DcsBios.h"
#define GFXFF 1
#define CF_01 &DEDFont16px24pt8b
//#define FF_19 &FreeSans18pt7b
FlickerFreePrint<TFT_eSPI> newValue1(&tft, TFT_BLACK,TFT_BLACK);
FlickerFreePrint<TFT_eSPI> newValue2(&tft, TFT_BLACK,TFT_BLACK);
FlickerFreePrint<TFT_eSPI> newValue3(&tft, TFT_BLACK,TFT_BLACK);
FlickerFreePrint<TFT_eSPI> newValue4(&tft, TFT_BLACK,TFT_BLACK);
FlickerFreePrint<TFT_eSPI> newValue5(&tft, TFT_BLACK,TFT_BLACK);


boolean didMyOneTimeAction = false;




void setup() 
{

  DcsBios::setup();
  SPI.begin();
  tft.begin();  //480*320
  tft.fillScreen (TFT_BLACK);
  tft.setRotation(1);
  
  
 
  
}

void loop() {
  DcsBios::loop();
  if (didMyOneTimeAction == false)
 {tft.fillScreen (TFT_BLACK);
   didMyOneTimeAction = true;
    
  }
 
  tft.drawRect(43,83,398,159,TFT_GREEN);
}


void onDedLine1Change(char* newValue1) {
     tft.setFreeFont(CF_01);
    
     delay(1);  
     tft.drawString(newValue1,50 ,85  ); //
     tft.setTextColor(TFT_GREEN,TFT_BLACK);
     
}
DcsBios::StringBuffer<25> dedLine1Buffer(0x44fc, onDedLine1Change);

void onDedLine2Change(char* newValue2) {
   tft.setFreeFont(CF_01);
  
   delay(1);
   tft.drawString (newValue2,50 ,115 ); //
   tft.setTextColor(TFT_GREEN,TFT_BLACK);
   
}

DcsBios::StringBuffer<25> dedLine2Buffer(0x4516, onDedLine2Change);

void onDedLine3Change(char* newValue3) {
 tft.setFreeFont(CF_01);
 
 delay(1);
 tft.drawString(newValue3,50 ,145 ); //
 tft.setTextColor(TFT_GREEN,TFT_BLACK);
 
}

DcsBios::StringBuffer<25> dedLine3Buffer(0x4530, onDedLine3Change);

void onDedLine4Change(char* newValue4) {
  tft.setFreeFont(CF_01);
  ;
  delay(1);
  tft.drawString(newValue4,50 ,175 ); //
  tft.setTextColor(TFT_GREEN,TFT_BLACK);
  
}

DcsBios::StringBuffer<25> dedLine4Buffer(0x454a, onDedLine4Change);

void onDedLine5Change(char* newValue5) {
 tft.setFreeFont(CF_01);
 
 delay(1);
 tft.drawString(newValue5 ,50 ,215 ); //
 tft.setTextColor(TFT_GREEN,TFT_BLACK);
 
}

DcsBios::StringBuffer<25> dedLine5Buffer(0x4564, onDedLine5Change);
///DcsBios::PotentiometerEWMA<5, 128, 5> priDataDisplayBrtKnb("PRI_DATA_DISPLAY_BRT_KNB", A0);
//void onPilotnameChange(char* newValue) {
//    tft.setFreeFont(FF_19);
//    tft.drawString (newValue ,10 ,20);
//    tft.setTextColor(TFT_GREEN,TFT_BLACK);
//    
//}
//DcsBios::StringBuffer<24> pilotnameBuffer(0x0406, onPilotnameChange);
//
//void onAcftNameChange(char* newValue) {
//    tft.setFreeFont(FF_19); 
//    tft.drawString (newValue ,10 ,70);
//    tft.setTextColor(TFT_GREEN,TFT_BLACK);
//    
//}
//DcsBios::StringBuffer<24> AcftNameBuffer(0x0000, onAcftNameChange);
/////
