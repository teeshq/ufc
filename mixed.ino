#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#define DCSBIOS_DEFAULT_SERIAL
#include "DcsBios.h"


// Wyświetlacz SH1122 256x64
U8G2_SH1122_256X64_F_4W_HW_SPI u8g2(U8G2_R0, /* cs=*/15, /* dc=*/5, /* reset=*/4);

// Bufory Common Data
volatile unsigned int hdgValue = 0;
volatile unsigned int altValue = 0;
volatile unsigned int spdValue = 0;

// Nazwa samolotu
String currentAircraft = "";

// --- CALLBACKI ---
void onAcftNameChange(char* newValue) {
  currentAircraft = String(newValue);
  Serial.print("Aircraft: ");
  Serial.println(currentAircraft);
}
DcsBios::StringBuffer<24> AcftNameBuffer(0x0000, onAcftNameChange);

// Common Data
void onHdgDegChange(unsigned int newValue) { hdgValue = newValue % 360; }
DcsBios::IntegerBuffer hdgDegBuffer(0x0436, 0x01ff, 0, onHdgDegChange);

void onAltMslFtChange(unsigned int newValue) { altValue = newValue; }
DcsBios::IntegerBuffer altMslFtBuffer(0x0434, 0xffff, 0, onAltMslFtChange);

void onIasUsIntChange(unsigned int newValue) { spdValue = newValue; }
DcsBios::IntegerBuffer iasUsIntBuffer(0x042e, 0xffff, 0, onIasUsIntChange);

// UFC Horneta
String comDisplay[3];
void updateComDisplay(int changed, char* newValue) {
  comDisplay[changed] = String(newValue);
  u8g2.clearBuffer();
  u8g2.setFont(Hornet_UFC);
  u8g2.setCursor(2, 45);
  u8g2.print(comDisplay[0]);
  u8g2.setCursor(54, 45);
  u8g2.print(comDisplay[1]);
  u8g2.setCursor(72, 45);
  u8g2.print(comDisplay[2]);
  u8g2.sendBuffer();
}
void onUfcScratchpadNumberDisplayChange(char* newValue) { updateComDisplay(2, newValue); }
DcsBios::StringBuffer<8> ufcScratchpadNumberDisplayBuffer(0x7446, onUfcScratchpadNumberDisplayChange);
void onUfcScratchpadString2DisplayChange(char* newValue) { updateComDisplay(1, newValue); }
DcsBios::StringBuffer<2> ufcScratchpadString2DisplayBuffer(0x7450, onUfcScratchpadString2DisplayChange);
void onUfcScratchpadString1DisplayChange(char* newValue) { updateComDisplay(0, newValue); }
DcsBios::StringBuffer<2> ufcScratchpadString1DisplayBuffer(0x744e, onUfcScratchpadString1DisplayChange);

// --- RYSOWANIE Common Data ---
void drawCommonData() {
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_10x20_mr);
  u8g2.setCursor(12, 18); u8g2.print("HDG");
  u8g2.setCursor(110, 18); u8g2.print("ALT");
  u8g2.setCursor(210, 18); u8g2.print("SPD");

  char buf[8];
  u8g2.setFont(u8g2_font_logisoso28_tr);
  snprintf(buf, sizeof(buf), "%03u", hdgValue);   u8g2.setCursor(2, 60);   u8g2.print(buf);
  snprintf(buf, sizeof(buf), "%05u", altValue);  u8g2.setCursor(80, 60);  u8g2.print(buf);
  snprintf(buf, sizeof(buf), "%03u", spdValue);  u8g2.setCursor(200, 60); u8g2.print(buf);
  u8g2.sendBuffer();
}

// --- RYSOWANIE EKRANU OCZEKIWANIA ---
void drawWaitingScreen() {
  u8g2.setFont(Hornet_UFC);
  u8g2.clearBuffer();
  u8g2.drawRFrame(4,2,251,61,4);
  u8g2.drawRFrame(5,3,249,59,4);
  u8g2.drawRFrame(6,4,247,57,4);
int textWidth = u8g2.getStrWidth("SIM TEES");
int fontHeight = u8g2.getMaxCharHeight();

int x = (256 - textWidth) / 2;
int y = (64 + fontHeight) / 2;

u8g2.setCursor(x, y);
u8g2.print("SIM TEES");
  u8g2.sendBuffer();
}

// --- MASTER CAUTION LED (pin 16) dla różnych samolotów ---
DcsBios::LED pltMasterCautionL(0x0000, 0x0000, 16); // AH-64D
DcsBios::LED masterCautionLt(0x7408, 0x0200, 16);   // F-18C
DcsBios::LED masterCaution(0x1012, 0x0800, 16);     // A-10C
DcsBios::LED pltMasterCaution(0x12d4, 0x0080, 16);  // F-14B
DcsBios::LED fMasterCautionL(0x959e, 0x4000, 16);   // F-15E
DcsBios::LED mcLight(0x7602, 0x0020, 16);           // F-5E
DcsBios::LED warnLMaster(0x485a, 0x0008, 16);       // JF-17A
DcsBios::LED pltWcaMasterCaution(0x2af8, 0x0001, 16); // F-4E
DcsBios::LED lightMasterCaution(0x447a, 0x0001, 16); // F-16C

// --- SETUP/LOOP ---
void setup() {
  Serial.begin(115200);
  u8g2.begin();
  u8g2.setBusClock(10000000);
  DcsBios::setup();
}

void loop() {
  DcsBios::loop();

  static unsigned long lastUpdate = 0;
  if (millis() - lastUpdate > 100) {
    lastUpdate = millis();

    if (currentAircraft == "") {
      drawWaitingScreen();
    } else if (currentAircraft == "FA-18C_hornet") {
      // Tryb UFC Horneta – rysowanie odbywa się w updateComDisplay()
    } else {
      drawCommonData();
    }
  }
}
