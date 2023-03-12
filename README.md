# ProtoBoard V0.2

A small board (48 x 56 mm) for great gloves !

![Top](media/3dTop.png)

![Bottom](media/3dBot.png)

![Pcb](media/Pcb.png)

# Features

## Pros :
- ESP32S3 dual core
- Small (48x56 mm)
- Power from 2S to 4S lipo (accept 6.5 volt up to 20 volt)
- Can use Wifi (doesnt use ADC2)
- 16 ADC input
- RGB Header
- 5V 5A for Servo for up to 5 Servo
- Support up to 7 LRA
- Battery protection (integrated BMS : overcharge, overdischarge and overcurrent protection)
- Battery level (via voltage divider)
- Cheap to build
- Use 2.54 mm header
- USB C for programming (The board CANNOT be powered via USB)

## Cons :
- Compoment on both side => more expensive to produce in small quantity in pcb fab (bottom side have easy to solder components)
- Doesnt charge the battery
- PCB is 4 layer (a bit more expensive than 2 layer PCB)

## Buy the PCB

*Warning still in alpha, design is not yet validated*

## TODO

- Add url for bom
- Add battery level information
- Add pinout