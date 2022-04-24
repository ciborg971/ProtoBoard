#pragma once

class LED {
 public:
  enum State : int {
    OFF,
    ON,
    BLINK_STEADY, // Blink steadily
    BLINK_TWICE, // Blink twice then rest
    BLINK_TRIPPLE, // Blink three times then rest
    BLINK_QUAD // Blink four times then rest
  };

  LED(int pin) : pin(pin), state(LOW), last_update(0){}

  void setup() {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, state = LOW);
  };

  void setState(int new_state) {
    switch (static_cast<State>(new_state)) {
      case OFF:
        digitalWrite(pin, state = LOW);
        break;
      case ON:
        digitalWrite(pin, state = HIGH);
        break;
      case BLINK_STEADY:
        if (millis() > last_update + 500) {
          // Every 1 second or so invert the state of the LED.
          digitalWrite(pin, state = !state);
          last_update = millis();
        }
        break;
      default:
        digitalWrite(pin, state = LOW);
        break;

    // Not supported yet.
    //   case BLINK_TWICE:
    //     break;
    //   case BLINK_TRIPPLE:
    //     break;
    //   case BLINK_QUAD:
    //     break;
    }
  }

 protected:
  int pin;
  bool state;
  int last_update;
};
