// This is a skeleton for what the esp32 side of the wifi and collection should
// be When compiling, it is necessary to have both AsyncTCP and AsyncWebServer
// by ESP32 Async the string described below is how the app understands and
// interprets data it is required that the calculations are handled on the esp32
// side

#include "board_backend.hpp"
#include <esp32-hal.h>

static const char *ssid = "esp32Wifi";
static const char *password = "MBRdatacollect";
static BoardBackend *backend = nullptr;

void setup() {
  Serial.begin(9600);
  delay(1000);
  Serial.println("[boot] setup entered");

  pinMode(32, INPUT_PULLDOWN);
  pinMode(33, INPUT_PULLDOWN);
  Serial.println("[boot] pins set");

  backend = new BoardBackend(ssid, password);
  backend->Initialize();
  Serial.println("[boot] backend initalized");
}

void loop() { backend->Run(); }
