/*
 * LucidGloves Firmware Version 5
 * Author: Lucas_VRTech - LucidVR
 *         John Thomas  - Exia
 * lucidvrtech.com
 * github.com/JohnRThomas/FlexiaGloves/
 */

// This is the main configuration file. Tweak settings here to fit your hardware.

// Which communication protocol to use
#define COMM_SERIAL 0
#define COMM_BTSERIAL 1
#define COMMUNICATION COMM_BTSERIAL

// Serial over USB
#define SERIAL_BAUD_RATE 115200

// Serial over Bluetooth
#define BTSERIAL_DEVICE_NAME "lucidgloves-left"

// Button Settings
// If a button registers as pressed when not and vice versa (eg. using normally-closed switches),
// you can invert their behaviour here by setting their line to true.
// If unsure, set to false
#define INVERT_A        false
#define INVERT_B        false
#define INVERT_JOY      false // Does nothing if joystick is not enabled
#define INVERT_MENU     false
#define INVERT_CALIB    false
#define INVERT_TRIGGER  false // Does nothing if gesture is enabled
#define INVERT_GRAB     false // Does nothing if gesture is enabled
#define INVERT_PINCH    false // Does nothing if gesture is enabled

// Joystick configuration
#define ENABLE_JOYSTICK  true // make false if not using the joystick
#define INVERT_JOY_X     false
#define INVERT_JOY_Y     false
#define JOYSTICK_DEADZONE 0.1 //deadzone in the joystick to prevent drift. Value out of 1.0.

// Finger settings
#define ENABLE_THUMB   true  // If for some reason you don't want to track the thumb
#define ENABLE_SPLAY   true // Track the side to side motion of fingers
#define INVERT_FLEXION false
#define INVERT_SPLAY   false

// Gesture enables, make false to use button override
#define TRIGGER_GESTURE true
#define GRAB_GESTURE    true
#define PINCH_GESTURE   (true && ENABLE_THUMB) // Cannot be enabled if there is no thumb

// Force Feedback and haptic settings
// Force feedback allows you to feel the solid objects you hold
// Haptics provide vibration.
#define ENABLE_FORCE_FEEDBACK true
#define ENABLE_HAPTICS        true

#define FORCE_FEEDBACK_FINGER_SCALING  false // Experimental: Determine servo range of motion based on calibration data.
#define FORCE_FEEDBACK_SMOOTH_STEPPING false // Experimental: Use servo microsecond pulses instead of degrees.

#define FORCE_FEEDBACK_STYLE_SERVO       0
#define FORCE_FEEDBACK_STYLE_CLAMP       1
#define FORCE_FEEDBACK_STYLE_SERVO_CLAMP 2
#define FORCE_FEEDBACK_STYLE             FORCE_FEEDBACK_STYLE_SERVO

#define FORCE_FEEDBACK_CLAMP_UNLOCK       LOW
#define FORCE_FEEDBACK_CLAMP_LOCK         HIGH
#define FORCE_FEEDBACK_SERVO_CLAMP_UNLOCK 0
#define FORCE_FEEDBACK_SERVO_CLAMP_LOCK   20

#define FORCE_FEEDBACK_MIN      0 // Value of 0 means no limit.
#define FORCE_FEEDBACK_MAX   1000 // Value of 1000 means maximum limit.
#define FORCE_FEEDBACK_RELEASE 50 // To prevent hardware damage, value passed the limit for when to release FFB. (Set to FORCE_FEEDBACK_MAX to disable)

// Counts of objects in the system used for looping
// Inputs
#define GESTURE_COUNT        (TRIGGER_GESTURE + GRAB_GESTURE + PINCH_GESTURE)
#define FINGER_COUNT         (ENABLE_THUMB ? 5 : 4)
#define JOYSTICK_COUNT       (ENABLE_JOYSTICK ? 2 : 0)
#define BUTTON_COUNT         (4 + ENABLE_JOYSTICK + !TRIGGER_GESTURE + !GRAB_GESTURE + !PINCH_GESTURE)
// Ouputs
#define HAPTIC_COUNT         (ENABLE_HAPTICS ? 1 : 0)
#define FORCE_FEEDBACK_COUNT (ENABLE_FORCE_FEEDBACK ? FINGER_COUNT : 0)
// Used for array allocations. These may need to be increased if more inputs are added.
#define MAX_INPUT_COUNT      32
#define MAX_CALIBRATED_COUNT 8
#define MAX_OUTPUT_COUNT     11

//PINS CONFIGURATION
//(This configuration is for ESP32 DOIT V1 so make sure to change if you're on another board)
#define PIN_PINKY           48
#define PIN_RING            49
#define PIN_MIDDLE          50
#define PIN_INDEX           51
#define PIN_THUMB           52
#define PIN_JOY_X           64
#define PIN_JOY_Y           65
#define PIN_JOY_BTN         66
#define PIN_A_BTN           70
#define PIN_B_BTN           68
#define PIN_MENU_BTN        69
#define PIN_TRIG_BTN        12 //unused if gesture set
#define PIN_GRAB_BTN        13 //unused if gesture set
#define PIN_PNCH_BTN        23 //unused if gesture set
#define PIN_CALIB           67 //button for recalibration
#define PIN_LED             23 // WS2812
#define PIN_PINKY_FFB       27 //used for force feedback
#define PIN_RING_FFB        14 //^
#define PIN_MIDDLE_FFB      12 //^
#define PIN_INDEX_FFB       13 //^
#define PIN_THUMB_FFB       15 //^
#define PIN_HAPTIC          18
#define PIN_PINKY_SPLAY     59
#define PIN_RING_SPLAY      60
#define PIN_MIDDLE_SPLAY    61
#define PIN_INDEX_SPLAY     62
#define PIN_THUMB_SPLAY     63
#define PIN_BAT             71          

// Advanced Config. Don't touch this unless you know what you are doing. Only for the pros XD
#define LOOP_TIME          4 //How much time between data sends (ms), set to 0 for a good time :)
#define CALIBRATION_LOOPS -1 //How many loops should be calibrated. Set to -1 to always be calibrated.

//Automatically set ANALOG_MAX depending on the microcontroller
#define ANALOG_MAX 4095

//Filtering and clamping analog inputs
#define CLAMP_ANALOG_MAP true //clamp the mapped analog values from 0 to ANALOG_MAX

// Enable and set min and max to match your sensor's expected raw value range
// This discards any spurious values outside of the useful range
#define CLAMP_FLEXION false       // Clamp the raw flexion values
#define CLAMP_MIN     0           // Minimum value from the flexion sensors
#define CLAMP_MAX     ANALOG_MAX  // Maximum value from the flexion sensors

// You must install RunningMedian library to use this feature
// https://www.arduino.cc/reference/en/libraries/runningmedian/
#define ENABLE_MEDIAN_FILTER false //use the median of the previous values, helps reduce noise
#define MEDIAN_SAMPLES 20
