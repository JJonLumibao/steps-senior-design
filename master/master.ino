#include <Wire.h>
#include <Keyboard.h>

const uint8_t tileAddresses[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09};
const char tileKeys[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
const int NUM_TILES = sizeof(tileAddresses);
const int DEBOUNCE_MS = 30;
const int PWM_PIN = 9;

bool tilePressed[9] = {false};

void setup() {
  Wire.begin();
  Keyboard.begin();
  pinMode(PWM_PIN, OUTPUT);
  digitalWrite(PWM_PIN, HIGH); 
}


void loop() {
  for (int i = 0; i < NUM_TILES; i++) {
    uint8_t addr = tileAddresses[i];
    char key = tileKeys[i];

    Wire.requestFrom(addr, (uint8_t)1);
    uint8_t pressed = 0;

    if (Wire.available()) {
      pressed = Wire.read();
    } else {
      continue;
    }

    if (pressed && !tilePressed[i]) {
      Keyboard.press(key);
      tilePressed[i] = true;
    }
    else if (!pressed && tilePressed[i]) {
      Keyboard.release(key);
      tilePressed[i] = false;
    }

    delay(DEBOUNCE_MS);
  }
}
