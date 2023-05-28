# ProtoBoard V0.2

A small board (48 x 56 mm) for great gloves !

* Still a work in progress, current version does NOT work * 

<img src="media/P1020643.JPG" width="50%" height="50%">
<img src="media/P1020642.JPG" width="50%" height="50%">
<img src="media/P1020641.JPG" width="50%" height="50%">

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

*This design does NOT work right now, do NOT buy it unless you can debug it by yourself*
You can buy the board via PCBWay using the file ProtoBoard.kicad_pcb.zip and the BOM ProtoBoard.xlsx.

## TODO

- Add pinout


## Sponsors

This project is sponsored by PCBWay, thanks to them for their quality PCB + assembly !