#include <Wire.h>
#include <Adafruit_NeoPixel.h>
#include <avr/wdt.h>  

#define SLAVE_ADDRESS 0x07
const int fsrPins[4] = {A0, A1, A2, A3};
bool anyPressed = false;         
const uint16_t PRESS_THRESHOLD = 100;

#define LED_PIN       4
#define LED_COUNT     9
#define BRIGHT_IDLE   10
#define BRIGHT_ACTIVE 60

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

const unsigned long COMM_TIMEOUT = 500;  
volatile unsigned long lastCommTime = 0; 

void setup() {
  analogReference(DEFAULT);

  Wire.begin(SLAVE_ADDRESS);
  Wire.onRequest(sendStatus);

  strip.begin();
  strip.setBrightness(BRIGHT_IDLE);
  setAll(strip.Color(255,0,0));
  strip.show();

  wdt_enable(WDTO_1S);
  lastCommTime = millis();
}

void loop() {
  wdt_reset();   

  bool pressedNow = false;
  for (int i = 0; i < 4; i++) {
    int val = analogRead(fsrPins[i]);
    if (val < PRESS_THRESHOLD) pressedNow = true;
  }

  if (pressedNow && !anyPressed) {
    anyPressed = true;
    strip.setBrightness(BRIGHT_ACTIVE);
    setAll(strip.Color(255,0,0));   
    strip.show();
  } 
  else if (!pressedNow && anyPressed) {
    anyPressed = false;
    strip.setBrightness(BRIGHT_IDLE);
    setAll(strip.Color(255,0,0));   
    strip.show();
  }

  if (millis() - lastCommTime > COMM_TIMEOUT) {
    anyPressed = false;
    strip.setBrightness(BRIGHT_IDLE);
    setAll(strip.Color(255,0,0));
    strip.show();
  }

  delay(20);
}

void sendStatus() {
  lastCommTime = millis();

  uint8_t flag = anyPressed ? 1 : 0;
  Wire.write(flag);
}

void setAll(uint32_t color) {
  for (int i = 0; i < LED_COUNT; i++) {
    strip.setPixelColor(i, color);
  }
}
