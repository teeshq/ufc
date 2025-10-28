#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#define DCSBIOS_DEFAULT_SERIAL
#include "DcsBios.h"

// Konfiguracja wyświetlacza
U8G2_SH1122_256X64_F_4W_HW_SPI u8g2(U8G2_R0, /* cs=*/ 15, /* dc=*/ 5, /* reset=*/ 4);

// Zmienne globalne
String comDisplay[3] = {"", "", ""};  // Domyślne wartości
char spdSign = '=';                  // Domyślny znak dla prędkości
unsigned int prevIasValue = 0;       // Poprzednia wartość prędkości

// Funkcja setup
void setup() {
    u8g2.begin();
    u8g2.setBusClock(10000000);

    DcsBios::setup();
}

// Funkcja loop
void loop() {
    DcsBios::loop();
}

// Funkcja aktualizacji wyświetlacza
void updateComDisplay(int changed, const String& newValue) {
    comDisplay[changed] = newValue;

    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_10x20_mr); // Czcionka dla nagłówków

    // Wyświetlanie nagłówków
    u8g2.setCursor(12, 18);
    u8g2.print("HDG");
    u8g2.setCursor(110, 18);
    u8g2.print("ALT");

    // Wyświetlanie SPD z odpowiednim znakiem
    if (spdSign == '+') {
        u8g2.setCursor(180, 18); // Znak "+" po lewej stronie SPD
        u8g2.print("+");
        u8g2.setCursor(210, 18);
        u8g2.print("SPD");
    } else if (spdSign == '-') {
        u8g2.setCursor(210, 18);
        u8g2.print("SPD");
        u8g2.setCursor(250, 18); // Znak "-" po prawej stronie SPD
        u8g2.print("-");
    } else if (spdSign == '=') {
        // Filtr dla znaku '='
        u8g2.setCursor(180, 18); // Znak "=" po lewej stronie SPD
        u8g2.print("=");
        u8g2.setCursor(210, 18);
        u8g2.print("SPD");
        u8g2.setCursor(250, 18); // Znak "=" po prawej stronie SPD
        u8g2.print("=");
    }

    // Wyświetlanie wartości
    u8g2.setFont(u8g2_font_logisoso28_tr); // Czcionka dla danych
    u8g2.setCursor(2, 60);
    u8g2.print(comDisplay[0]);
    u8g2.setCursor(80, 60);
    u8g2.print(comDisplay[1]);
    u8g2.setCursor(200, 60);
    u8g2.print(comDisplay[2]);

    u8g2.sendBuffer();
}

// Obsługa zmiany kierunku
void onHdgDegChange(unsigned int newValue) {
    updateComDisplay(0, String(newValue));
}
DcsBios::IntegerBuffer hdgDegBuffer(0x0436, 0x01ff, 0, onHdgDegChange);

// Obsługa zmiany wysokości
void onAltMslFtChange(unsigned int newValue) {
    updateComDisplay(1, String(newValue));
}
DcsBios::IntegerBuffer altMslFtBuffer(0x0434, 0xffff, 0, onAltMslFtChange);

// Obsługa zmiany prędkości
void onIasUsIntChange(unsigned int newValue) {
    // Określenie znaku zmiany prędkości
    if (newValue > prevIasValue) {
        spdSign = '+'; // Prędkość wzrasta
    } else if (newValue < prevIasValue) {
        spdSign = '-'; // Prędkość spada
    } else {
        spdSign = '='; // Prędkość stała
    }
    prevIasValue = newValue; // Aktualizacja poprzedniej wartości prędkości

    updateComDisplay(2, String(newValue));
}
DcsBios::IntegerBuffer iasUsIntBuffer(0x042e, 0xffff, 0, onIasUsIntChange);
