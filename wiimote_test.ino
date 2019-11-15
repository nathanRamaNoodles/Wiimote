#include "Wiimote.h"

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  Wiimote::init();
  Wiimote::register_callback(1, wiimote_callback);
}

void loop() {
  Wiimote::handle();
}

void wiimote_callback(uint8_t number, uint8_t* data, size_t len) {
  Serial.printf("wiimote number=%d len=%d ", number, len);
  if (data[1] == 0x32) {
    for (int i = 0; i < 4; i++) {
      //      Serial.printf("%02X ", data[i]);
//      handleInput(i, data[i]);
    }

    // http://wiibrew.org/wiki/Wiimote/Extension_Controllers/Nunchuck
    uint8_t* ext = data + 4;
    Serial.printf(" ... Nunchuk: sx=%3d sy=%3d c=%d z=%d\n",
                  ext[0],
                  ext[1],
                  0 == (ext[5] & 0x02),
                  0 == (ext[5] & 0x01)
                 );
  } else {
    for (int i = 0; i < len; i++) {
            Serial.printf("%02X ", data[i]);
            handleInput(i, data[i]);
    }
    Serial.print("\n");
  }
}

void handleInput(int type, uint8_t a) {
  switch (type) {
    case 3:
      switch (a) {
        case 8:
          digitalWrite(LED_BUILTIN, HIGH);
          break;
        case 0:
          digitalWrite(LED_BUILTIN, LOW);
          break;
      }
      break;
  }
  Serial.printf("%d ", a);
}
