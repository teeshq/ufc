#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#define DCSBIOS_DEFAULT_SERIAL
#include "DcsBios.h"

// Konfiguracja wyświetlacza SH1122 256x64
U8G2_SH1122_256X64_F_4W_HW_SPI u8g2(U8G2_R0, /* cs=*/ 15, /* dc=*/ 5, /* reset=*/ 4);

// Bufory na dane (globalne, aktualizowane w callbackach)
volatile unsigned int hdgValue = 0;
volatile unsigned int altValue = 0;
volatile unsigned int spdValue = 0;

// Callbacki – tylko zapisują wartości
void onHdgDegChange(unsigned int newValue) {
  hdgValue = newValue % 360; // heading 0–359
}
DcsBios::IntegerBuffer hdgDegBuffer(0x0436, 0x01ff, 0, onHdgDegChange);

void onAltMslFtChange(unsigned int newValue) {
  altValue = newValue; // wysokość w stopach
}
DcsBios::IntegerBuffer altMslFtBuffer(0x0434, 0xffff, 0, onAltMslFtChange);

void onIasUsIntChange(unsigned int newValue) {
  spdValue = newValue; // prędkość IAS
}
DcsBios::IntegerBuffer iasUsIntBuffer(0x042e, 0xffff, 0, onIasUsIntChange);

// Funkcja rysująca ekran
void drawDisplay() {
  u8g2.clearBuffer();

  // Nagłówki
  u8g2.setFont(u8g2_font_10x20_mr);
  u8g2.setCursor(12, 18);
  u8g2.print("HDG");
  u8g2.setCursor(110, 18);
  u8g2.print("ALT");
  u8g2.setCursor(210, 18);
  u8g2.print("SPD");

  // Formatowanie wartości
  char buf[8];

  u8g2.setFont(u8g2_font_logisoso28_tr);

  // HDG – 3 cyfry
  snprintf(buf, sizeof(buf), "%03u", hdgValue);
  u8g2.setCursor(2, 60);
  u8g2.print(buf);

  // ALT – 5 cyfr
  snprintf(buf, sizeof(buf), "%05u", altValue);
  u8g2.setCursor(80, 60);
  u8g2.print(buf);

  // SPD – 3 cyfry
  snprintf(buf, sizeof(buf), "%03u", spdValue);
  u8g2.setCursor(200, 60);
  u8g2.print(buf);

  u8g2.sendBuffer();
}

void setup() {
  u8g2.begin();
  u8g2.setBusClock(10000000);
  DcsBios::setup();
}

void loop() {
  DcsBios::loop();

  // Odświeżanie ekranu co 100 ms
  static unsigned long lastUpdate = 0;
  if (millis() - lastUpdate > 100) {
    lastUpdate = millis();
    drawDisplay();
  }
}





//master caution
DcsBios::LED pltMasterCautionL(AH_64D_PLT_MASTER_CAUTION_L_AM, 16); //AH-64D
DcsBios::LED masterCautionLt(0x7408, 0x0200, 16); //F-18C
DcsBios::LED masterCaution(0x1012, 0x0800, 16); //A-10C
DcsBios::LED pltMasterCaution(0x12d4, 0x0080,16); //F-14B
DcsBios::LED fMasterCautionL(0x959e, 0x4000, 16); //F-15E
DcsBios::LED mcLight(0x7602, 0x0020, 16); //F-5E
DcsBios::LED warnLMaster(0x485a, 0x0008, 16); //JF-17A
//DcsBios::LED mcAmbre(0x72b0, 0x0001, 16); //M-2000C UPPER AMBER MASTER CAUTION LIGHT
//DcsBios::LED mcRouge(0x72b0, 0x0002, 16); //M-2000C LOWER RED MASTER CAUTION LIGHT
//DcsBios::LED pWlMFailLL(0x86b4, 0x0040, 16); //MIRAGE F1 LEFT WING MASTER FAIL LIGHT
//DcsBios::LED pWlMFailRL(0x86b4, 0x0080, 16); //MIRAGE F1 RIGHT WING MASTER FAIL LIGHT
DcsBios::LED pltWcaMasterCaution(0x2af8, 0x0001, 16); //F-4E
