#pragma once

#define DYNO_DT_PIN 16 // DT
#define DYNO_SCK_PIN 4 // PD_SCK
#define DYNO_LIN_PIN 34 // ADC1
#define LOADCELL_OFFSET 27855 // roughly this amount; with bolt inside
#define LOADCELL_SCALEFACTOR 13.645 // raw_reading / known_weight;
#define DYNO_LIN_MAXD 175 // max displacement (unique to the the lin pot.) in mm

#include "HX711.h"

class Dyno {
private:
  HX711 loadcell;

public:
  Dyno();
  void Calibrate();
  float GetInstantForce();
  float GetUnitForce(int timestamp, int sampleSize = 5);
  float GetLinearDisplacement(int timestamp);
  float GetVelocity(int64_t timestamp1, int64_t timestamp2, float displacement1, float displacement2);
  void Poweroff();
  void Poweron();

private:
  float readLinearVoltage(int pin);
};
