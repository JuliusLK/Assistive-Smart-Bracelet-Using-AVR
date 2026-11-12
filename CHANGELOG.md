# Changelog

## [Unreleased]
- Calibrate MAX30102 and MPU6050
- More compact design

## [0.1.0-prototype] - 2026-11-10
- Initial circuit: Arduino Nano, MPU6050, MAX30102, SSD1306 OLED, buzzer, LED
- Bare-metal drivers: I2C, SSD1306, MPU6050, MAX30102, millis
- Heart rate detection with stabilized BPM
- Fall detection (free-fall + impact) with MPU6050
- Distinct buzzer/LED alert patterns for heart rate, fall, and both
- MAX30102 setup updated to the calibrated values from the final report (LED power `0xDF`, averaging 2, 200 Hz)
- Test results added: heart rate comparison and simulated fall tests (`docs/test-results.md`)
- Firmware licensed under GPL-3.0-or-later (OLED driver derived from Sylaina/oled-display)
- Initial enclosure design (`hardware/enclosure/Casing.stl`)
