#define  DCSBIOS_DEFAULT_SERIAL
#include "DcsBios.h"
#define LGFX_USE_V1
#include <LovyanGFX.hpp>
class LGFX : public lgfx::LGFX_Device
{
lgfx::Panel_ILI9488     _panel_instance;
lgfx::Bus_SPI           _bus_instance;   
public:

LGFX(void)
  {
    {
      auto cfg = _bus_instance.config();    // バス設定用の構造体を取得します。


      cfg.spi_mode = 0;             // SPI通信モードを設定 (0 ~ 3)
      cfg.spi_3wire  = false;       // 受信をMOSIピンで行う場合はtrueを設定
      cfg.freq_write = 40000000;    // 送信時のSPIクロック (最大80MHz, 80MHzを整数で割った値に丸められます)
      cfg.freq_read  = 16000000;    // 受信時のSPIクロック
      cfg.pin_sclk = 14;            // SPIのSCLKピン番号を設定
      cfg.pin_mosi = 13;            // SPIのMOSIピン番号を設定
      cfg.pin_miso = -1;            // SPIのMISOピン番号を設定 (-1 = disable)
      cfg.pin_dc   =  4;            // SPIのD/Cピン番号を設定  (-1 = disable)
      _bus_instance.config(cfg);    // 設定値をバスに反映します。
      _panel_instance.setBus(&_bus_instance);      // バスをパネルにセットします。
    }

    { 
      auto cfg = _panel_instance.config();    // 表示パネル設定用の構造体を取得します。

      cfg.pin_cs           =    15;  // CSが接続されているピン番号   (-1 = disable)
      cfg.pin_rst          =    16;  // RSTが接続されているピン番号  (-1 = disable)
      cfg.pin_busy         =    -1;  // BUSYが接続されているピン番号 (-1 = disable)
      cfg.memory_width     =   320;  // ドライバICがサポートしている最大の幅
      cfg.memory_height    =   480;  // ドライバICがサポートしている最大の高さ
      cfg.panel_width      =   320;  // 実際に表示可能な幅
      cfg.panel_height     =   480;  // 実際に表示可能な高さ
      cfg.offset_x         =     0;  // パネルのX方向オフセット量
      cfg.offset_y         =     0;  // パネルのY方向オフセット量
      cfg.offset_rotation  =     0;  // 回転方向の値のオフセット 0~7 (4~7は上下反転)
      cfg.dummy_read_pixel =     8;  // ピクセル読出し前のダミーリードのビット数
      cfg.dummy_read_bits  =     1;  // ピクセル以外のデータ読出し前のダミーリードのビット数
      cfg.readable         = false;  // データ読出しが可能な場合 trueに設定
      cfg.invert           = false;  // パネルの明暗が反転してしまう場合 trueに設定
      cfg.rgb_order        = false;  // パネルの赤と青が入れ替わってしまう場合 trueに設定
      cfg.dlen_16bit       = false;  // データ長を16bit単位で送信するパネルの場合 trueに設定
      cfg.bus_shared       = false;  // SDカードとバスを共有している場合 trueに設定(drawJpgFile等でバス制御を行います)

      _panel_instance.config(cfg);
    }
    setPanel(&_panel_instance); // 使用するパネルをセットします。
  }
};
LGFX tft;

void setup(void)
{
  tft.init();
  tft.setRotation(1);
  tft.setFont(&fonts::F16DEDBIG32pt8b);
  /////demo
  tft.setTextColor(TFT_WHITE,TFT_BLACK);
  tft.setCursor(100,60);
  tft.print("F-16C DED plus");
  delay(3000);
  tft.fillRect(0,165,480,2,TFT_WHITE);
  delay(1000);
  tft.setCursor(55,170);
  tft.setTextColor(TFT_WHITE,TFT_BLACK);
  tft.print("BARO  ALT:");
  delay(1000);
  tft.setCursor(55,210);
  tft.setTextColor(TFT_WHITE,TFT_BLACK);
  tft.print("FUEL FLOW:");
  delay(1000);
  tft.setCursor(55,250);
  tft.setTextColor(TFT_WHITE,TFT_BLACK);
  tft.print("TOTAL LBS:");
  delay(1000);
  tft.setCursor(55,290);
  tft.setTextColor(TFT_WHITE,TFT_BLACK);
  tft.print("CH:");
  delay(1000);
  tft.setCursor(215,290);
  tft.setTextColor(TFT_WHITE,TFT_BLACK);
  tft.print("FL:");
  delay(1000);
 
  ////
  tft.drawLine(425,179,409,220,TFT_WHITE);
  tft.drawLine(425,179,441,220,TFT_WHITE);
  tft.drawLine(409,220,374,235,TFT_WHITE);
  tft.drawLine(441,220,476,235,TFT_WHITE);
  tft.drawLine(374,235,374,250,TFT_WHITE);
  tft.drawLine(476,235,476,250,TFT_WHITE);
  tft.drawLine(374,250,409,250,TFT_WHITE);
  tft.drawLine(476,250,441,250,TFT_WHITE);
  tft.drawLine(409,265,409,220,TFT_WHITE);
  tft.drawLine(441,265,441,220,TFT_WHITE);
  tft.drawLine(409,265,390,275,TFT_WHITE);
  tft.drawLine(441,265,460,275,TFT_WHITE);
  tft.drawLine(390,275,390,285,TFT_WHITE);
  tft.drawLine(460,275,460,285,TFT_WHITE);
  tft.drawLine(390,285,412,285,TFT_WHITE);
  tft.drawLine(438,285,460,285,TFT_WHITE);
  tft.drawLine(412,285,417,290,TFT_WHITE);
  tft.drawLine(438,285,433,290,TFT_WHITE);
  tft.drawLine(417,290,433,290,TFT_WHITE);
  tft.fillCircle(446,230,10,0x39C7);
  tft.fillCircle(446,230,5,TFT_BLACK);
  tft.fillCircle(404,230,10,0x39C7);
  tft.fillCircle(404,230,5,TFT_BLACK); 
  tft.fillCircle(425,200,10,0x39C7);
  tft.fillCircle(425,200,5,TFT_BLACK);  
  delay(1000);
  
  //center
  tft.fillCircle(425,200,10,0x0740);
  tft.fillCircle(425,200,5,TFT_GREEN);
  delay(1000);
   //left
  tft.fillCircle(404,230,10,0x0740);
  tft.fillCircle(404,230,5,TFT_GREEN);
  
   //right
  tft.fillCircle(446,230,10,0x0740);
  tft.fillCircle(446,230,5,TFT_GREEN);
  delay(1000);
  tft.setCursor(403,297); 
  tft.setFont(&fonts::Font2);
  tft.print("CLOSED");
  delay(1000);
  tft.fillRect(400,292,70,35, TFT_BLACK);
  tft.fillCircle(405,305,3,TFT_WHITE);
  tft.fillCircle(425,305,3,TFT_WHITE);
  tft.fillCircle(445,305,3,TFT_WHITE);
  tft.fillCircle(405,315,3,TFT_WHITE);
  tft.fillCircle(425,315,3,TFT_WHITE);
  tft.fillCircle(445,315,3,TFT_WHITE);
  tft.fillCircle(405,295,3,TFT_WHITE);
  tft.fillCircle(425,295,3,TFT_WHITE);
  tft.fillCircle(445,295,3,TFT_WHITE);
  delay(1000);
  tft.fillRect(400,292,70,35, TFT_BLACK);
  tft.setCursor(403,297);
  tft.print("CLOSED");
  ///
  delay(1000);
  tft.setFont(&fonts::AOA50pt7b);  
  tft.setCursor(0,220);
  tft.setTextColor(TFT_GREEN,TFT_BLACK);
  tft.print(1);
  delay(1000);
  tft.setCursor(0,220);
  tft.setTextColor(TFT_BLACK,TFT_BLACK);
  tft.print(1); 
  tft.setCursor(0,170);
  tft.setTextColor(TFT_RED,TFT_BLACK);
  tft.print(2);
  delay(1000);
  tft.setCursor(0,170);
  tft.setTextColor(TFT_BLACK,TFT_BLACK);
  tft.print(2); 
  tft.setCursor(0,220);
  tft.setTextColor(TFT_GREEN,TFT_BLACK);
  tft.print(1);
  delay(1000);
  tft.setCursor(0,220);
  tft.setTextColor(TFT_BLACK,TFT_BLACK);
  tft.print(1);    
  tft.setCursor(0,270);
  tft.setTextColor(TFT_YELLOW,TFT_BLACK);
  tft.print(3);
  delay(1000);  
  tft.setCursor(0,220);
  tft.setTextColor(TFT_GREEN,TFT_BLACK);
  tft.print(1);
  delay(1000);
  tft.setCursor(0,170);
  tft.setFont(&fonts::AOA50pt7b);
  tft.setTextColor(TFT_RED,TFT_BLACK);
  tft.print(2);

  DcsBios::setup();
}

void loop(void) {
  DcsBios::loop();
  }

//DED 1 LINE
void onDedLine1Change(char* newValue1) {
   tft.setTextColor(TFT_GREEN,TFT_BLACK);
   tft.setFont(&fonts::F16DEDBIG32pt8b);
   delay(1);
   tft.drawString (newValue1,5 ,0 );
}
DcsBios::StringBuffer<29> dedLine1Buffer(0x4500, onDedLine1Change);

//DED 2 LINE
void onDedLine2Change(char* newValue2) {
  tft.setTextColor(TFT_GREEN,TFT_BLACK);
   tft.setFont(&fonts::F16DEDBIG32pt8b);
   delay(1);
   tft.drawString (newValue2,5 ,32 ); //
}
DcsBios::StringBuffer<29> dedLine2Buffer(0x451e, onDedLine2Change);

//DED 3 LINE
void onDedLine3Change(char* newValue3) {
 tft.setTextColor(TFT_GREEN,TFT_BLACK);
 tft.setFont(&fonts::F16DEDBIG32pt8b);
 delay(1);
 tft.drawString(newValue3,5 ,64 ); //
}
DcsBios::StringBuffer<29> dedLine3Buffer(0x453c, onDedLine3Change);

//DED 4 LINE
void onDedLine4Change(char* newValue4) {
 tft.setTextColor(TFT_GREEN,TFT_BLACK);
 tft.setFont(&fonts::F16DEDBIG32pt8b);
 delay(1);
 tft.drawString(newValue4,5 ,96 ); //
}
DcsBios::StringBuffer<29> dedLine4Buffer(0x455a, onDedLine4Change);

//DED 5 LINE
void onDedLine5Change(char* newValue5) {
 tft.setTextColor(TFT_GREEN,TFT_BLACK);
 tft.setFont(&fonts::F16DEDBIG32pt8b);
 delay(1);
 tft.drawString(newValue5 ,5 ,128 ); //
}
DcsBios::StringBuffer<29> dedLine5Buffer(0x4578, onDedLine5Change);

///////////////////////////////////////////////////////////////////////
///FUEL FLOW
void onFuelflowcounter100Change(unsigned int newValue) {
    tft.setTextColor(TFT_GREEN,TFT_BLACK);
    tft.setFont(&fonts::F16DEDBIG32pt8b);
    unsigned int lEngFuelFlowValue = (newValue & 0xffff) >> 0;
    unsigned int valueL = map(lEngFuelFlowValue, 0, 65535, 0, 99); 
    unsigned int firstDigit;
    unsigned int secondDigit;
    firstDigit = valueL/10;
    secondDigit = valueL%10;
    tft.setCursor(295,205);
    tft.print(firstDigit);
    tft.setCursor(315,205);
    tft.print(secondDigit);
    tft.setCursor(335,205);
    tft.print("0");
}
DcsBios::IntegerBuffer fuelflowcounter100Buffer(0x44de, 0xffff, 0, onFuelflowcounter100Change);

void onFuelflowcounter1kChange(unsigned int newValue) {
    tft.setTextColor(TFT_GREEN,TFT_BLACK);
    tft.setFont(&fonts::F16DEDBIG32pt8b);
    unsigned int lEngFuelFlowValue = (newValue & 0xffff) >> 0;
    unsigned int valueL = map(lEngFuelFlowValue, 0, 65535, 0, 10); 
    tft.setCursor(275,205);
    tft.print(valueL);/* your code here */
}
DcsBios::IntegerBuffer fuelflowcounter1kBuffer(0x44dc, 0xffff, 0, onFuelflowcounter1kChange);

void onFuelflowcounter10kChange(unsigned int newValue) {
        tft.setTextColor(TFT_GREEN,TFT_BLACK);
        tft.setFont(&fonts::F16DEDBIG32pt8b);
        unsigned int lEngFuelFlowValue = (newValue & 0xffff) >> 0;
        unsigned int valueL = map(lEngFuelFlowValue, 0, 65535, 0, 10); 
        tft.setCursor(255,205);
        tft.print(valueL);/* your code here */
}
DcsBios::IntegerBuffer fuelflowcounter10kBuffer(0x44da, 0xffff, 0, onFuelflowcounter10kChange);

///////////////////////////////////////////////////////////////////////
//Remaing fuel counter//
 void onFueltotalizer100Change(unsigned int newValue) {
 tft.setTextColor(TFT_GREEN,TFT_BLACK);
 tft.setFont(&fonts::F16DEDBIG32pt8b);
 unsigned int lEngFuelFlowValue = (newValue & 0xffff) >> 0;
 unsigned int valueL = map(lEngFuelFlowValue, 0, 65535, 0, 99); 
 unsigned int firstDigit;
 unsigned int secondDigit;
 firstDigit = valueL/10;
 secondDigit = valueL%10;
 tft.setCursor(295,240);
 tft.print(firstDigit);
 tft.setCursor(315,240);
 tft.print(secondDigit);
 tft.setCursor(335,240);
 tft.print("0");
}
DcsBios::IntegerBuffer fueltotalizer100Buffer(0x44e8, 0xffff, 0, onFueltotalizer100Change);

void onFueltotalizer1kChange(unsigned int newValue) {
 tft.setTextColor(TFT_GREEN,TFT_BLACK);
 tft.setFont(&fonts::F16DEDBIG32pt8b);
 unsigned int lEngFuelFlowValue = (newValue & 0xffff) >> 0;
 unsigned int valueL = map(lEngFuelFlowValue, 0, 65535, 0, 11); 
  tft.setCursor(275,240);
 tft.print(valueL);
 }
DcsBios::IntegerBuffer fueltotalizer1kBuffer(0x44e6, 0xffff, 0, onFueltotalizer1kChange);

void onFueltotalizer10kChange(unsigned int newValue){
  tft.setFont(&fonts::F16DEDBIG32pt8b);
 tft.setTextColor(TFT_GREEN,TFT_BLACK); 
 unsigned int lEngFuelFlowValue = (newValue & 0xffff) >> 0;
 unsigned int valueL = map(lEngFuelFlowValue, 0, 65535, 0, 11); 
 
 tft.setCursor(255,240);
 tft.print(valueL);
 }
DcsBios::IntegerBuffer fueltotalizer10kBuffer(0x44e4, 0xffff, 0, onFueltotalizer10kChange);

//CMDS

void onCmdsChAmountChange(char* newValueCH) {
  tft.setTextColor(TFT_GREEN,TFT_BLACK);
  tft.setFont(&fonts::F16DEDBIG132pt8b);
  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  tft.drawString(newValueCH , 115 , 290 );
}
DcsBios::StringBuffer<4> cmdsChAmountBuffer(0x459e, onCmdsChAmountChange);

void onCmdsFlAmountChange(char* newValueFL) {
  tft.setFont(&fonts::F16DEDBIG132pt8b);
  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  tft.drawString(newValueFL , 275 , 290 );
}
DcsBios::StringBuffer<4> cmdsFlAmountBuffer(0x45a2, onCmdsFlAmountChange);
//BARO ALTIMETER
void onAlt100FtCntChange(unsigned int newValue100) {
 tft.setTextColor(TFT_GREEN,TFT_BLACK);
 tft.setFont(&fonts::F16DEDBIG32pt8b);
 unsigned int lonAlt100Value = (newValue100 & 0xffff) >> 0;
 unsigned int valueL = map(lonAlt100Value, 0, 65535, 0, 99); 
 unsigned int firstDigit;
 unsigned int secondDigit;
 firstDigit = valueL/10;
 secondDigit = valueL%10;
 tft.setCursor(295,170);
 tft.print(firstDigit);
 tft.setCursor(315,170);
 tft.print(secondDigit);
 tft.setCursor(335,170);
 tft.print("0");
}
DcsBios::IntegerBuffer alt100FtCntBuffer(0x4490, 0xffff, 0, onAlt100FtCntChange);
////
void onAlt1000FtCntChange(unsigned int newValue1000) {
  tft.setTextColor(TFT_GREEN,TFT_BLACK);
  tft.setFont(&fonts::F16DEDBIG32pt8b);
  unsigned int lonAlt1000Value = (newValue1000 & 0xffff) >> 0;
  unsigned int valueL = map(lonAlt1000Value, 0, 65535, 0, 11); 
  tft.setCursor(275,170);
  tft.print(valueL);
}
DcsBios::IntegerBuffer alt1000FtCntBuffer(0x448e, 0xffff, 0, onAlt1000FtCntChange);
////
void onAlt10000FtCntChange(unsigned int newValue10000) {
 tft.setTextColor(TFT_GREEN,TFT_BLACK);
 tft.setFont(&fonts::F16DEDBIG32pt8b); 
 unsigned int lonAlt10000Value = (newValue10000 & 0xffff) >> 0;
 unsigned int valueL = map(lonAlt10000Value, 0, 65535, 0, 11); 
 tft.setCursor(255,170);
 tft.print(valueL);   
}
DcsBios::IntegerBuffer alt10000FtCntBuffer(0x448c, 0xffff, 0, onAlt10000FtCntChange);

///// AOA INDEKSER

void onLightAoaUpChange(unsigned int newValue1) {
    tft.setCursor(0,170);
    tft.setFont(&fonts::AOA50pt7b);
    tft.setTextColor(TFT_RED,TFT_BLACK);
    if (newValue1 > 0 ){    
    tft.print(2);  
    }
    else {
    tft.print(4);  
    }
}

DcsBios::IntegerBuffer lightAoaUpBuffer(0x4478, 0x0004, 2, onLightAoaUpChange);

/////

void onLightAoaMidChange(unsigned int newValue2) {
    tft.setCursor(0,220);
    tft.setFont(&fonts::AOA50pt7b);
    tft.setTextColor(TFT_GREEN,TFT_BLACK);
    if (newValue2 > 0 ){    
    tft.print(1);  
    }
    else {
    tft.print(4);  
    }
   
}
DcsBios::IntegerBuffer lightAoaMidBuffer(0x4478, 0x0008, 3, onLightAoaMidChange);

/////

void onLightAoaDnChange(unsigned int newValue3) {
    tft.setCursor(0,270);
    tft.setFont(&fonts::AOA50pt7b);
    tft.setTextColor(TFT_YELLOW,TFT_BLACK);
    if (newValue3 > 0 ){    
    tft.print(3);  
    }
    else {
    tft.print(4);  
    }
  
}
DcsBios::IntegerBuffer lightAoaDnBuffer(0x4478, 0x0010, 4, onLightAoaDnChange);


/////LANDING GEAR STATUS

//Nose Gear Light
void onLightGearNChange(unsigned int newValueF) {
    if(newValueF > 0){
      tft.fillCircle(425,200,10,0x0740);
      tft.fillCircle(425,200,5,TFT_GREEN);
    }
    else {
      tft.fillCircle(425,200,10,0x39C7);
      tft.fillCircle(425,200,5,TFT_BLACK);
    }
    
}
DcsBios::IntegerBuffer lightGearNBuffer(0x4478, 0x0020, 5, onLightGearNChange);


//Left Gear Light 
void onLightGearLChange(unsigned int newValueL) {
    if(newValueL > 0){
      tft.fillCircle(404,230,10,0x0740);
      tft.fillCircle(404,230,5,TFT_GREEN);
    }
    else {
      tft.fillCircle(404,230,10,0x39C7);
      tft.fillCircle(404,230,5,TFT_BLACK);
    }
    
}
DcsBios::IntegerBuffer lightGearLBuffer(0x4478, 0x0040, 6, onLightGearLChange);


//Right Gear Light
void onLightGearRChange(unsigned int newValueR) {
    if(newValueR > 0){
      tft.fillCircle(446,230,10,0x0740);
      tft.fillCircle(446,230,5,TFT_GREEN);
    }
    else {
      tft.fillCircle(446,230,10,0x39C7);
      tft.fillCircle(446,230,5,TFT_BLACK);
    }
    
}
DcsBios::IntegerBuffer lightGearRBuffer(0x4478, 0x0080, 7, onLightGearRChange);

///SPEED BRAKE

void onSpeedbrakeIndicatorChange(unsigned int newValueS) {
    if(newValueS > 0){
      tft.fillRect(400,292,70,35, TFT_BLACK);
      tft.fillCircle(405,305,3,TFT_WHITE);
      tft.fillCircle(425,305,3,TFT_WHITE);
      tft.fillCircle(445,305,3,TFT_WHITE);
      tft.fillCircle(405,315,3,TFT_WHITE);
      tft.fillCircle(425,315,3,TFT_WHITE);
      tft.fillCircle(445,315,3,TFT_WHITE);
      tft.fillCircle(405,295,3,TFT_WHITE);
      tft.fillCircle(425,295,3,TFT_WHITE);
      tft.fillCircle(445,295,3,TFT_WHITE);
    }
    else {
      tft.fillRect(400,292,70,35, TFT_BLACK);
      tft.setTextColor(TFT_WHITE,TFT_BLACK);
      tft.setCursor(403,297); 
      tft.setFont(&fonts::Font2);
      tft.print("CLOSED"); 
    }
}
DcsBios::IntegerBuffer speedbrakeIndicatorBuffer(0x44ca, 0xffff, 0, onSpeedbrakeIndicatorChange);
