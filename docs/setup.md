# Setup Guide

## Prerequisites
- [PlatformIO](https://platformio.org/) (VS Code extension or CLI). VS Code will suggest the extension automatically thanks to `firmware/.vscode/extensions.json`.
- Arduino Nano (ATmega328P, new bootloader) and a USB cable

The project is configured in `firmware/platformio.ini`:

```ini
[env:nanoatmega328new]
platform = atmelavr
board = nanoatmega328new
framework = arduino
```

> If uploading fails, your Nano may use the old bootloader. Change `board` to `nanoatmega328`.

## Libraries
None. All drivers are included in `firmware/src/`:

| File | Purpose |
|------|---------|
| `i2c.c/.h` | Bare-metal TWI (I2C) driver |
| `lcd.c/.h`, `font.c/.h` | SSD1306 128x64 OLED driver (graphic mode) |
| `mpu6050.c/.h` | MPU6050 driver |
| `max30105_avr.cpp/.h` | MAX30102 driver |
| `heartrate.cpp/.h` | Beat detection and BPM calculation |
| `millis.cpp/.h` | Timer1-based `millis()` |
| `main.cpp` | Application logic and alarms |

## Steps
1. Assemble the circuit following [`wiring.md`](wiring.md).
2. Open the `firmware/` folder in PlatformIO.
3. Build and upload:
   ```bash
   cd firmware
   pio run -t upload
   ```
4. The OLED should show "Initializing..." and then the status screen.

## Initial Tests
1. If the OLED shows `MAX30105 ERROR`, check the MAX30102 wiring and power (the sensor was not detected on I2C `0x57`).
2. Place a finger on the MAX30102 and confirm BPM appears on the display.
3. Shake or safely drop the module (onto a pillow) to test fall detection.
4. Verify the three alert patterns (heart rate, fall, both).

## Changing Thresholds
Edit the constants in `firmware/src/main.cpp`:

| Constant | Default | Meaning |
|----------|---------|---------|
| `HR_MIN` / `HR_MAX` | 60 / 100 | Allowed BPM range |
| `FREEFALL_G` | 0.6 | Free-fall threshold (g) |
| `IMPACT_G` | 2.5 | Impact threshold (g) |
| `JERK_THRESHOLD_G` | 1.5 | Sudden change threshold (g) |
| `FREEFALL_SAMPLES` | 3 | Samples needed to confirm free-fall |
| `IMPACT_WINDOW_MS` | 1000 | Time to wait for an impact |
| `ALARM_DURATION_MS` | 3000 | Alert duration |
