#pragma once

#include "DriverProtocol.hpp"

// The base Haptic Motor class uses a transister to spin an ERM haptic
// motor.
class HapticMotor : public DecodedOuput {
 public:
  HapticMotor(DecodedOuput::Type frequency_key, DecodedOuput::Type duration_key, DecodedOuput::Type amplitude_key, int motor_pin) :
    frequency_key(frequency_key), duration_key(duration_key), amplitude_key(amplitude_key), motor_pin(motor_pin),
    frequency(0), duration(0), amplitude(0), haptic_start(0) {}

  void setupOutput() override {
    pinMode(motor_pin, OUTPUT);
    digitalWrite(motor_pin, LOW);
  }

  void decodeToOuput(const char* input) override {
    char* start = strchr(input, frequency_key);
    if (start != NULL) {
      frequency = atoi(start + 1);
    }

    start = strchr(input, duration_key);
    if (start != NULL) {
      duration = atoi(start + 1);
    }

    start = strchr(input, amplitude_key);
    if (start != NULL) {
      amplitude = atoi(start + 1);
    }

    haptic_start = millis();
  }

  void updateOutput() override {
    if (duration > 0 && millis() < haptic_start + duration) {
      // If there is duration remaining, keep the motor on.
      digitalWrite(motor_pin, HIGH);
    } else {
      // Duration has expired, keep the motor off.
      digitalWrite(motor_pin, LOW);
      duration = 0;
    }
  }

 protected:
  DecodedOuput::Type frequency_key;
  DecodedOuput::Type duration_key;
  DecodedOuput::Type amplitude_key;
  int motor_pin;
  int frequency;
  int duration;
  int amplitude;
  int haptic_start;
};
