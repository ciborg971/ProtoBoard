#pragma once

#include "config.h"

struct AnalogPin {
  virtual inline int read() const = 0;
};

template<int PIN>
struct DirectPin : public AnalogPin {
  inline int read() const override {
    return analogRead(PIN);
  }

  constexpr operator int() {
    return PIN;
  }
};

enum Mask {
  M0  = 0b00000,
  M1  = 0b00001,
  M2  = 0b00010,
  M3  = 0b00011,
  M4  = 0b00100,
  M5  = 0b00101,
  M6  = 0b00110,
  M7  = 0b00111,
  M8  = 0b01000,
  M9  = 0b01001,
  M10 = 0b01010,
  M11 = 0b01011,
  M12 = 0b01100,
  M13 = 0b01101,
  M14 = 0b01110,
  M15 = 0b01111,
  M16 = 0b10000,
  M17 = 0b10001,
  M18 = 0b10010,
  M19 = 0b10011,
  M20 = 0b10100,
  M21 = 0b10101,
  M22 = 0b10110,
  M23 = 0b10111,
  M24 = 0b11000,
  M25 = 0b11001,
  M26 = 0b11010,
  M27 = 0b11011,
  M28 = 0b11100,
  M29 = 0b11101,
  M30 = 0b11110,
  M31 = 0b11111
};

template<Mask PIN_MASK>
struct MultiplexedPin : public AnalogPin {

  inline int read() const override {
    digitalWrite(MUX_SEL_0, PIN_MASK & 0b01000);
    digitalWrite(MUX_SEL_1, PIN_MASK & 0b00100);
    digitalWrite(MUX_SEL_2, PIN_MASK & 0b00010);
    digitalWrite(MUX_SEL_3, PIN_MASK & 0b00001);
    // Max switching delay for the mux choosen should be around 400ns.
    // Delaying for 1 microsecond is 1000ns, so we should be safe to
    // read after that.
    delayMicroseconds(2);
    return analogRead(PIN_MASK & 0b10000 ? MUX_INPUT_A : MUX_INPUT_B);
  }

};
