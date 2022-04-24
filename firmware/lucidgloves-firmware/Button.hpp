#pragma once

#include "Config.h"
#include "AdcMux.hpp"
#include "DriverProtocol.hpp"

class Button : public EncodedInput {
 public:
  Button(EncodedInput::Type type, int pin, bool invert) :
    type(type), pin(pin), on_state(invert ? HIGH : LOW), value(false) {}

  void setupInput() override {
    if(pin < MIN_MUX_GPIO)
    {
      pinMode(pin, INPUT_PULLUP);
    }
  }

  virtual void readInput() {
    value = (AdcMuxRead(pin) == on_state);
  }

  inline int getEncodedSize() const override {
    // Encode string size = single char
    return 1;
  }

  int encode(char* output) const override {
    if (value) output[0] = type;
    return value ? 1 : 0;
  }

  bool isPressed() const {
    return value;
  }

 private:
  const EncodedInput::Type type;
  const int pin;
  const bool on_state;
  bool value;
};
