# Firmware

Bare-metal AVR C/C++ for the ATmega328P (Arduino Nano), built with PlatformIO.

```bash
pio run              # build
pio run -t upload    # build and upload
```

## Layout
```
firmware/
├── platformio.ini
├── .vscode/extensions.json  # recommends the PlatformIO IDE extension
├── include/README           # default PlatformIO note (project headers)
├── lib/README               # default PlatformIO note (no private libraries are used)
├── test/README              # default PlatformIO note (unit tests)
└── src/
    ├── main.cpp           # application: sensors, fall detection, alarms, OLED
    ├── heartrate.cpp/.h   # beat detection and BPM
    ├── max30105_avr.cpp/.h# MAX30102 driver
    ├── mpu6050.c/.h       # MPU6050 driver
    ├── lcd.c/.h, font.c/.h# SSD1306 OLED driver
    ├── i2c.c/.h           # TWI (I2C) driver
    └── millis.cpp/.h      # Timer1 millis()
```

## Pins
| Function | Pin |
|----------|-----|
| I2C SDA / SCL | A4 (PC4) / A5 (PC5) |
| Buzzer | D5 (PD5) |
| LED | D7 (PD7) |

See [`docs/how-it-works.md`](../docs/how-it-works.md) for the algorithms and [`docs/setup.md`](../docs/setup.md) for the tunable constants.
