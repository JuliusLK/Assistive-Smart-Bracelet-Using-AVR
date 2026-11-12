# Calibration and Improvement Plan

## Current state
- **MPU6050:** gyro bias is measured at startup (200 samples) but not yet used. There is no accelerometer offset calibration, and fall detection only uses the accelerometer magnitude.
- **MAX30102:** LED power, averaging, and detection constants (e.g. IR cutoff `10000`, refractory 250 ms) are fixed values in the source.

## 1. Heart rate sensor calibration (MAX30102)
Common issue: BPM values fluctuate due to motion, pressure, or ambient light.

Things to try:
- Tune **LED power** (currently `0xDF`), **averaging**, and **pulse width** so the IR signal does not saturate.
- Tune `IR_CUTOFF_MIN`, `MIN_AMPLITUDE`, `REFRACTORY_MS`, and the hysteresis constants in `heartrate.cpp` for wrist placement.
- Reset the alarm state when contact is lost (IR below cutoff).
- Compare against a pulse oximeter or manual pulse count on several people and record the error.
- Confirm the normal BPM range (`HR_MIN` / `HR_MAX`) with the target users.
- Measured so far: the bracelet reads about 1.8 BPM higher than a Samsung Galaxy Fit 3 on average (n = 10, all above 100 BPM). See [`test-results.md`](test-results.md).

## 2. MPU6050 calibration
- Compute **accelerometer offsets** while the module is still and level; store as constants or in EEPROM.
- Apply the already-computed **gyro bias** and consider adding orientation/stillness checks after impact to reduce false positives.
- Consider enabling the MPU6050 digital low-pass filter (`CONFIG` register) to reduce noise.
- Simulated falls are already tested (10 / 10 detected, see [`test-results.md`](test-results.md)). The next step is testing everyday activities (walking, sitting down quickly, swinging the arm) to measure the false-alarm rate.

## 3. Making it more compact
- Replace the Arduino Nano with a bare SMD ATmega328P or a smaller board.
- Design a **custom PCB** that integrates the sensors and regulator.
- Consider a thin LiPo battery and a charger module (TP4056) inside the enclosure.
- Reshape the enclosure into a bracelet with the MAX30102 facing the skin.
