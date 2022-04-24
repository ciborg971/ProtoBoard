#include "Config.h"

#include "HardwareConfig.hpp"

#include "ICommunication.hpp"
#if COMMUNICATION == COMM_SERIAL
  #include "SerialCommunication.hpp"
#elif COMMUNICATION == COMM_BTSERIAL
  #include "SerialBTCommunication.hpp"
#endif

#include "AdcMux.hpp"

#define ALWAYS_CALIBRATING CALIBRATION_LOOPS == -1

ICommunication* comm;
int calibration_count = 0;

// These are composite lists of the hardware defined in the header above.
EncodedInput* inputs[MAX_INPUT_COUNT];
DecodedOuput* outputs[MAX_OUTPUT_COUNT];
Calibrated* calibrators[MAX_CALIBRATED_COUNT];

char* encoded_output_string;
size_t input_count;
size_t output_count;
size_t calibrated_count;

// Common pattern for registering inputs and outputs
#define register(source, destination, new_count, existing) \
do {                                                       \
  for (size_t i = 0; i < new_count; existing++, i++) {     \
    destination[existing] = source[i];                     \
  }                                                        \
} while(false)

void setup() {
  #if COMMUNICATION == COMM_SERIAL
    comm = new SerialCommunication();
  #elif COMMUNICATION == COMM_BTSERIAL
    comm = new BTSerialCommunication();
  #endif

  comm->start();

  // Register the inputs.
  input_count = 0;
  register(buttons, inputs, BUTTON_COUNT, input_count);
  register(fingers, inputs, FINGER_COUNT, input_count);
  register(joysticks, inputs, JOYSTICK_COUNT, input_count);
  register(gestures, inputs, GESTURE_COUNT, input_count);

  // Register the calibrated inputs
  calibrated_count = 0;
  register(fingers, calibrators, FINGER_COUNT, calibrated_count);

  // Register the outputs.
  output_count = 0;
  register(force_feedbacks, outputs, FORCE_FEEDBACK_COUNT, output_count);
  register(haptics, outputs, HAPTIC_COUNT, output_count);

  // Figure out needed size for the output string.
  int string_size = 0;
  for(size_t i = 0; i < input_count; i++) {
    string_size += inputs[i]->getEncodedSize();
  }

  // Add 1 new line and 1 for the null terminator.
  encoded_output_string = new char[string_size + 1 + 1];

  // Setup all the inputs.
  for (size_t i = 0; i < input_count; i++) {
    inputs[i]->setupInput();
  }

  // Setup all the outputs.
  for (size_t i = 0; i < output_count; i++) {
    outputs[i]->setupOutput();
  }

  // Setup the LED.
  led.setup();

  // Setup Multiplexer
  SetupAdcMux();

  if (ALWAYS_CALIBRATING) {
    for (size_t i = 0; i < calibrated_count; i++) {
      calibrators[i]->enableCalibration();
    }
  }
}

void loop() {
  if (!comm->isOpen()){
    // Connection to Driver not ready, blink the LED to indicate no connection.
    led.setState(LED::State::BLINK_STEADY);
  } else {
    // All is good, LED on to indicate a good connection.
    led.setState(LED::State::ON);
  }

  // Notify the calibrators to turn on.
  if (calibration_button.isPressed()) {
    calibration_count = 0;
    for (size_t i = 0; i < calibrated_count; i++) {
      calibrators[i]->resetCalibration();
      calibrators[i]->enableCalibration();
    }
  }

  if (calibration_count < CALIBRATION_LOOPS || ALWAYS_CALIBRATING) {
    // Keep calibrating for one at least one more loop.
    calibration_count++;
  } else {
    // Calibration is done, notify the calibrators
    for (size_t i = 0; i < calibrated_count; i++) {
      calibrators[i]->disableCalibration();
    }
  }

  // Update all the inputs
  for (int i = 0; i < input_count; i++) {
    inputs[i]->readInput();
  }

  // Encode all of the outputs to a single string.
  encodeAll(encoded_output_string, inputs, input_count);

  // Send the string to the communication handler.
  comm->output(encoded_output_string);

  char received_bytes[100];
  if (comm->hasData() && comm->readData(received_bytes, 100)) {
    for (size_t i = 0; i < output_count; i++) {
      // Decode the update and write it to the output.
      outputs[i]->decodeToOuput(received_bytes);
    }
  }

  // Allow all the outputs to update their state.
  for (size_t i = 0; i < output_count; i++) {
    outputs[i]->updateOutput();
  }

  delay(LOOP_TIME);
}
