#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
//#include <Fonts/FreeSans9pt7b.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

class OLEDConsole {
  private:
    int Zeilen = 0; // Initial number of lines printed (to initiate scrolling when needed)
    String Zeile[4] = {"","","",""}; // line buffer 0..3

// Ausgabe: Clear Display and print full line buffer
void Ausgabe() {
  display.clearDisplay();
  display.setCursor(0,0);
  for (int i=0; i<4; i++) {
    display.setCursor(0,i*8);
    display.println(Zeile[i]);
  }
  display.display();
}

  public:

// init: clear display, set font etc.
void init() {
  display.clearDisplay();
  Zeilen = 0;
  //display.setFont(&FreeSans9pt7b);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
}

// println: add a new line, scroll old text one line up
void println(String t) {
  Zeilen++;
  if (Zeilen < 4) {
    Zeile[Zeilen]=t;
  } else for (int i=0; i<3; i++) {
    Zeile[i] = Zeile[i+1];
  }
  Zeile[3] = t;
  Ausgabe();
}

// Updateln: direct update of line:
void updateln(int z, String t) {
  Zeile[z] = t;
  Ausgabe();
}
};

OLEDConsole Console;

void setup() {
  Serial.begin(115200);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);
  Console.init();
  Console.println("Setup completed"); 
  delay(100);
 
}

void loop() {
  for (int i=0; i<10; i++) {
    Console.println("Zeile " + String(i));
    delay(1000);
  }

}