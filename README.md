# ProtoBoard

A small board (35 x 50 mm) for great gloves !

![Top](media/3dTop.png)

![Bottom](media/3dBot.png)

![Pcb](media/Pcb.png)

# Features

## Pros :
- ESP32 dual core
- Small (35x50 mm)
- Power from 2S to 4S lipo (accept 6.5 volt up to 20 volt)
- Can use Wifi (doesnt use ADC2)
- 32 ADC input
- 1 extra GPIO (can be used for anything for instance RGB)
- 5V 5A for Servo with current protection
- Support up to 6 LRA (small vibrating motor, also have current protection)
- [QWIIC](https://www.sparkfun.com/qwiic) connector (for extension like display or IMU for SlimeVR or heartbeat sensor...)
- Up to 5 Servo
- Battery level (via voltage divider)
- Cheap to build
- Use JST GH 1.25 connector (cheap and easy to find)

## Cons :
- Compoment on both side => more expensive to produce in small quantity in pcb fab
- No on board USB (Boot0, EN, RX0, TX0 via solder pad)
- Doesnt charge the battery
- PCB is 4 layer (a bit more expensive than 2 layer PCB)

## BOM

|    Reference    | Name | Qty | URL |
|-----------------|------|-----|-----|
|R1, R2, R3, R4, R5, R6, R7, R8, R15| 10K 10% 0402 resistor | 9 | [url](https://www.lcsc.com/product-detail/Chip-Resistor-Surface-Mount_UNI-ROYAL-Uniroyal-Elec-0402WGF1002TCE_C25744.html) | 
|C2, C4| 0.1uF 0402 capacitor | 2 | [url](https://www.lcsc.com/product-detail/Multilayer-Ceramic-Capacitors-MLCC-SMD-SMT_Samsung-Electro-Mechanics-CL05C100JB5NNNC_C32949.html) |
|C3, C7, C9| 22uF 0402 capacitor | 3 | [url](https://www.lcsc.com/product-detail/Multilayer-Ceramic-Capacitors-MLCC-SMD-SMT_Murata-Electronics-GRM155R60J226ME11D_C415703.html) |
|R11, R12| 6.8K 1% 0402 resistor | 2 | [url]() |
|R10| 3.4K 1% 0402 resistor | 1 | [url]() |
|R9| 1.7K 1% 0402 resistor | 3 | [url]() |
|U7, U8, U9, U10| SY6280AAC overcurrent protection | 4 | [url](https://www.lcsc.com/product-detail/Power-Distribution-Switches_Silergy-Corp-SY6280AAC_C55136.html) |
|U1| ESP32-WROOM-32D | 1 | [url](https://www.lcsc.com/product-detail/WiFi-Modules_Espressif-Systems-ESP32-WROOM-32D_C473012.html) |
|J3| QWIIC connector | 1 | [url]() |
|R14| 5M 1% 0402 | 1 | [url]() |
|R13| 1M 1% 0402 | 1 | [url]() |
|U2, U4| CD74HC4067SM analog multiplexer | 2 | [url](https://www.lcsc.com/product-detail/Analog-Switches-Multiplexers_Texas-Instruments-CD74HC4067SM96_C98457.html) |
|U3| LM1084-5.0 5volt 5A regulator | 1 | [url](https://www.lcsc.com/product-detail/Linear-Voltage-Regulators-LDO_HGSEMI-LM1084S-5-0-TR_C259973.html) |
|U6| LM1084-3.3 3.3volt 5A regulator | 1 | [url](https://www.lcsc.com/product-detail/Linear-Voltage-Regulators-LDO_HGSEMI-LM1084S-3-3-TR_C259972.html) |
|C6, C8| 10uF 0402 capacitor | 2 | [url](https://www.lcsc.com/product-detail/Multilayer-Ceramic-Capacitors-MLCC-SMD-SMT_Samsung-Electro-Mechanics-CL05A106MQ5NUNC_C15525.html) |
|IC1, IC2, IC3| L9110S motor controller | 3 | [url]() |
|J4, J7, J9, J11| JST GH 1.25 vertical smd 10 pin | 4 | [url]() |
|J2| JST GH 1.25 vertical smd 8 pin | 1 | [url]() |
|J5, J6, J8| connector 2.54 male header | 3 | [url]() |

## Buy the PCB

*Warning still in alpha, design is not yet validated*

Go on [JLCPCB](https://jlcpcb.com) and select "Instant Quote".
Clic on "Add gerber file" and select [Output.zip](Output.zip)

![JLCPCB1](media/JLCPCB1.png)

Select the same layer stackup (let all other parameters as is).
![JLCPCB2](media/JLCPCB2.png)

You can go crazy with the PCB color (it's a bit more expensive and take a bit more time).

SMT assembly will only work for half of the board (JLCPCB only do the assembly of one side).

Stencil is a good idea if you have a reflow oven or hot plate.

## Multiplexer implementation

The ESP32 with the most gpio have 48 gpio (GPIO0 to GPIO47) to simplify the GPIO logic, I decided that the 32 gpio of the multiplexer are GPIO48 to GPIO79. Related code [here](firmware/lucidgloves-firmware/AdcMux.hpp).

Equivalent fritzing diagram
![Mux diagram](media/Mux1.png)

Pinout :
- S0 is GPIO26
- S1 is GPIO25
- S2 is GPIO32
- S3 is GPIO33
- Two adc pin from the ESP32 are used GPIO35 (multiplexer 1 : GPIO48 to GPIO63) and GPIO34 (multiplexer 2 : GPIO64 to GPIO79)
![Mux diagram](media/Mux2.png)

## TODO

- Add url for bom
- Add battery level information
- Add pinout