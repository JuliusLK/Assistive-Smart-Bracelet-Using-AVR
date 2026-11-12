# Wiring

Based on the schematic in `hardware/schematic/schematic.png`.

## Power
```
Battery (JST-PH 2-pin) -> MT3608 Vin+/Vin-
MT3608 Vout+ -> Arduino Nano VIN (VCC net) and 5V rail
MT3608 Vout- -> GND
```
Set the MT3608 output to **5V** with a multimeter **before** connecting the Arduino and sensors.

## I2C Bus (A4 = SDA, A5 = SCL)
| Device | VCC | GND | SDA | SCL |
|--------|-----|-----|-----|-----|
| MPU6050 (GY-521) | 5V | GND | A4 | A5 |
| MAX30102 | 5V (VIN) | GND | A4 | A5 |
| OLED | 5V | GND | A4 | A5 |

Pull-ups: two 5k resistors from SDA and SCL to 5V.

Unused MPU6050 pins: XDA, XCL, AD0, INT.
Unused MAX30102 pins: INT, IRD, RD.

## Outputs
| Component | Pin |
|-----------|-----|
| Buzzer | D5 (other side to GND) |
| LED | D7 -> LED -> 1k resistor -> GND |

## Notes
- Make sure your MAX30102 module supports 5V on its VIN pin and 5V I2C logic. Some modules use 3.3V pull-ups, so check yours to avoid damaging the sensor.
- Typical I2C addresses: MPU6050 `0x68`, MAX30102 `0x57`, SSD1306 OLED `0x3C`. Run an I2C scanner if a device is not detected.
