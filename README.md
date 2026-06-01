# RainDropAnimation
Nuvoton N76E003 IC controlling WS2811 Pixel LED

SDCC simple rain drop neopixel for Nuvoton N76E003        
## Connect the MCU to a strip.
>
|    **5V or 3.3V**             |  **VCC**                                             |
|-------------------------------|-------------------------------------------------------
|   **GND**                     |  **GND**                                             |
|   **WSPIN**                   |  **Data In possibly through a resistor 12, PIN 1.2** |



## To Build the project 

```console
make all
```
## To clean the project 

```console
make clean
```

## Setup
1. Download and install SDCC. Check "Add to system path" in the end of installation.
http://sdcc.sourceforge.net/
2. Download and install Nuvoton Nu-Link command tool. Add to system path manually.
https://www.nuvoton.com/tool-and-software/software-development-tool/programmer
3. Download and install make command tool for windows. Add to system path manually.
https://gnuwin32.sourceforge.net/packages/make.htm
4. Restart your computer.
