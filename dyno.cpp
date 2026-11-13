#include "dyno.hpp"
#include <HX711.h>
#include <cstdio>
#include <esp32-hal-adc.h>
#include "Arduino.h"

Dyno::Dyno() {
    pinMode(34, INPUT);
  loadcell.begin(DYNO_DT_PIN, DYNO_SCK_PIN);
  Serial.println("initializing dyno...");
}

void Dyno::Calibrate() {
Serial.println("calibrating dyno...");
  loadcell.set_offset(LOADCELL_OFFSET);
  loadcell.set_scale(LOADCELL_SCALEFACTOR);
}

float Dyno::GetInstantForce() { return loadcell.get_value(); }
float Dyno::GetUnitForce(int timestamp, int sampleSize) {
  return static_cast<float>(loadcell.get_units(sampleSize));
}

// NOTE: lin pot uses the 5V pin for power!
float Dyno::GetLinearDisplacement(int timestamp) {
  float vNormalized = Dyno::readLinearVoltage(DYNO_LIN_PIN);
  float vPercent = vNormalized / 3.3;
  return vPercent * DYNO_LIN_MAXD;
}

void Dyno::Poweroff() { loadcell.power_down(); }

float Dyno::readLinearVoltage(int pin) {
  int raw = analogRead(pin);

  // If in the dead zones, mathematically clamp or handle
  if (raw < 50)
    return 0.0;
  if (raw >= 4095)
    return 3.3;

  // Polynomial correction formula for 11dB attenuation
  float voltage = -0.000000000000016 * pow(raw, 4) +
                  0.000000000118171 * pow(raw, 3) -
                  0.000000301211691 * pow(raw, 2) + 0.001109019271794 * raw +
                  0.034143524634089;
  return voltage;
}
