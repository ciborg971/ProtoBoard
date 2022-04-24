#pragma once

#define SEL1 26
#define SEL2 25
#define SEL3 32
#define SEL4 33
#define AdcRead1 35
#define AdcRead2 34

// Maximum number of pin in the ESP32 familly
#define MIN_MUX_GPIO 48

// GPIO from AdcMux is num 49 to 81
// Syntax SEL1, SEL2, SEL3, SEL4, Analog pin to read
int MuxArrRow0[] = {0, 0, 0, 0, AdcRead1};
int MuxArrRow1[] = {0, 0, 0, 0, AdcRead2};
int MuxArrRow2[] = {1, 0, 0, 0, AdcRead1};
int MuxArrRow3[] = {1, 0, 0, 0, AdcRead2};
int MuxArrRow4[] = {0, 1, 0, 0, AdcRead1};
int MuxArrRow5[] = {0, 1, 0, 0, AdcRead2};
int MuxArrRow6[] = {1, 1, 0, 0, AdcRead1};
int MuxArrRow7[] = {1, 1, 0, 0, AdcRead2};
int MuxArrRow8[] = {0, 0, 1, 0, AdcRead1};
int MuxArrRow9[] = {0, 0, 1, 0, AdcRead2};
int MuxArrRow10[] = {1, 0, 1, 0, AdcRead1};
int MuxArrRow11[] = {1, 0, 1, 0, AdcRead2};
int MuxArrRow12[] = {0, 1, 1, 0, AdcRead1};
int MuxArrRow13[] = {0, 1, 1, 0, AdcRead2};
int MuxArrRow14[] = {1, 1, 1, 0, AdcRead1};
int MuxArrRow15[] = {1, 1, 1, 0, AdcRead2};
int MuxArrRow16[] = {0, 0, 0, 1, AdcRead1};
int MuxArrRow17[] = {0, 0, 0, 1, AdcRead2};
int MuxArrRow18[] = {1, 0, 0, 1, AdcRead1};
int MuxArrRow19[] = {1, 0, 0, 1, AdcRead2};
int MuxArrRow20[] = {0, 1, 0, 1, AdcRead1};
int MuxArrRow21[] = {0, 1, 0, 1, AdcRead2};
int MuxArrRow22[] = {1, 1, 0, 1, AdcRead1};
int MuxArrRow23[] = {1, 1, 0, 1, AdcRead2};
int MuxArrRow24[] = {0, 0, 1, 1, AdcRead1};
int MuxArrRow25[] = {0, 0, 1, 1, AdcRead2};
int MuxArrRow26[] = {1, 1, 0, 1, AdcRead1};
int MuxArrRow27[] = {1, 1, 0, 1, AdcRead1};
int MuxArrRow28[] = {0, 0, 1, 1, AdcRead1};
int MuxArrRow29[] = {0, 0, 1, 1, AdcRead2};
int MuxArrRow30[] = {1, 0, 1, 1, AdcRead1};
int MuxArrRow31[] = {1, 0, 1, 1, AdcRead2};
int MuxArrRow32[] = {0, 1, 1, 1, AdcRead1};
int MuxArrRow33[] = {0, 1, 1, 1, AdcRead2};
int MuxArrRow34[] = {1, 1, 1, 1, AdcRead1};
int MuxArrRow35[] = {1, 1, 1, 1, AdcRead2};

int *MuxArr[] = { 
    MuxArrRow0,
    MuxArrRow1,
    MuxArrRow2,
    MuxArrRow3,
    MuxArrRow4,
    MuxArrRow5,
    MuxArrRow6,
    MuxArrRow7,
    MuxArrRow8,
    MuxArrRow9,
    MuxArrRow10,
    MuxArrRow11,
    MuxArrRow12,
    MuxArrRow13,
    MuxArrRow14,
    MuxArrRow15,
    MuxArrRow16,
    MuxArrRow17,
    MuxArrRow18,
    MuxArrRow19,
    MuxArrRow20,
    MuxArrRow21,
    MuxArrRow22,
    MuxArrRow23,
    MuxArrRow24,
    MuxArrRow25,
    MuxArrRow26,
    MuxArrRow27,
    MuxArrRow28,
    MuxArrRow29,
    MuxArrRow30,
    MuxArrRow31,
    MuxArrRow32,
    MuxArrRow33,
    MuxArrRow34,
    MuxArrRow35
};

void SetupAdcMux()
{

  pinMode(SEL1, OUTPUT);
  pinMode(SEL2, OUTPUT);
  pinMode(SEL3, OUTPUT);
  pinMode(SEL4, OUTPUT);
}

int AdcMuxRead(uint8_t pin)
{
    if(pin >= MIN_MUX_GPIO && pin < MIN_MUX_GPIO + 32)
    {
        pin -= MIN_MUX_GPIO;
        digitalWrite(SEL1, MuxArr[pin][0] ? HIGH : LOW);
        digitalWrite(SEL2, MuxArr[pin][1] ? HIGH : LOW);
        digitalWrite(SEL3, MuxArr[pin][2] ? HIGH : LOW);
        digitalWrite(SEL4, MuxArr[pin][3] ? HIGH : LOW);
        delay(1);
        return analogRead(MuxArr[pin][4]);
    }
    else
    {
        return analogRead(pin);
    }
}