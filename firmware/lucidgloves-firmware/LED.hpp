#pragma once
#include <Adafruit_NeoPixel.h>

// How many NeoPixels/WS2812 are attached to the Arduino?
#define NUMPIXELS 1

#define COLOR1   100, 100, 100 
#define COLOR2   250, 0, 0
#define COLOR3   0, 0, 250
#define COLOR4   0, 250, 0
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

  LED(int pin) : pin(pin), state(LOW), last_update(0){
    // When setting up the NeoPixel library, we tell it how many pixels,
    // and which pin to use to send signals. Note that for older NeoPixel
    // strips you might need to change the third parameter -- see the
    // strandtest example for more information on possible values.
    pixels = Adafruit_NeoPixel(NUMPIXELS, pin, NEO_GRB + NEO_KHZ800);
  }

  void setup() {
    pixels.begin();
    pixels.clear();
  };

  void setState(int new_state) {
    switch (static_cast<State>(new_state)) {
      case OFF:
        pixels.clear();
        break;
      case ON:
        for(int i = 0; i < NUMPIXELS; i++)
        {
          pixels.setPixelColor(i, pixels.Color(COLOR1));
        }
        pixels.show();
        break;
      case BLINK_STEADY:
        if (millis() > last_update + 500) {
          // Every 1 second or so invert the state of the LED.
          digitalWrite(pin, state = !state);
          if(state)
          {
            for(int i = 0; i < NUMPIXELS; i++)
            {
              pixels.setPixelColor(i, pixels.Color(COLOR2));
            }
          }
          else
          {
            pixels.clear();
          }
          pixels.show();
          last_update = millis();
        }
        break;
      default:
        pixels.clear();
        pixels.show();
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
  Adafruit_NeoPixel pixels;
};
