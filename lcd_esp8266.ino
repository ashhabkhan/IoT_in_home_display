#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 OLED(-1);
int x = 0;
void setup() {
  OLED.begin(SSD1306_SWITCHCAPVCC, 0x3C);
}

void loop() {
  OLED.clearDisplay();
  OLED.setTextColor(WHITE);
  OLED.setCursor(0,0);
  OLED.setTextSize(3);
  OLED.println("COUNT");
  OLED.setCursor(0,27);
  OLED.println(x,DEC);
  OLED.display();
  delay(300);
  x++;
}
