# How It Works

## System block diagram
```mermaid
flowchart LR
    subgraph IN["Input"]
        MPU["MPU6050<br/>accelerometer + gyro"]
        HRS["MAX30102<br/>heart rate"]
    end
    subgraph OUT["Output"]
        OLED["OLED 128x64"]
        BUZ["Active buzzer"]
        LED["Red LED"]
    end
    BAT["LiPo 3.7V 1000 mAh"] --> BOOST["MT3608 boost to 5V"] --> MCU
    MPU -->|I2C| MCU["Arduino Nano<br/>ATmega328P"]
    HRS -->|I2C| MCU
    MCU -->|I2C| OLED
    MCU --> BUZ
    MCU --> LED
```

## Main loop flowchart
```mermaid
flowchart TD
    A["Power on"] --> B["Init: pins, millis, I2C, OLED,<br/>MPU6050 + gyro bias, MAX30102, HR algorithm"]
    B --> C["Enable global interrupts and enter main loop"]
    C --> D["Read MAX30102 FIFO"]
    D --> E{"Valid beat detected?"}
    E -- yes --> F["Update instant and stable BPM"]
    F --> F2{"Stable BPM below 60 or above 100?"}
    F2 -- yes --> F3["Start heart rate alarm"]
    F2 -- no --> G
    F3 --> G
    E -- "no / noise" --> G
    G{"50 ms elapsed?"}
    G -- yes --> H["Read MPU6050, compute magnitude and jerk"]
    H --> I{"Free-fall then impact?"}
    I -- yes --> J["Start fall alarm<br/>(both-alarm if HR alarm active)"]
    I -- no --> K
    J --> K
    G -- no --> K
    K{"250 ms elapsed?"}
    K -- yes --> L["Refresh OLED"]
    K -- no --> M
    L --> M["Update alarm: buzzer + LED"]
    M --> D
```

## Main loop (`firmware/src/main.cpp`)
1. **Init:** Timer1 millis, I2C (100 kHz), buzzer/LED pins, OLED, MPU6050, gyro bias calibration (200 samples), MAX30102.
2. **Heart rate:** read the MAX30102 FIFO, feed each IR/Red sample to `hr_process()`. On each detected beat, the stable BPM is checked against the allowed range.
3. **Motion:** every 50 ms, read the accelerometer and run the fall state machine.
4. **Display:** refresh the OLED every 250 ms (and on fall state changes).
5. **Alarm:** a non-blocking alarm state machine toggles the buzzer and LED.

## Heart rate algorithm (`heartrate.cpp`)
- The IR signal is compared with an adaptive baseline (IIR filter) plus a dynamic offset to find rising edges.
- A refractory period (250 ms) and hysteresis prevent double counting.
- Beats are validated by a minimum amplitude and by Red/IR correlation.
- IR below `10000` is treated as "no finger / no contact" and resets the state.
- Beat-to-beat intervals (RR) between 300 and 2000 ms are stored in a window of 5. The **stable BPM** is a trimmed mean (within ±20% of the median); the **instant BPM** is computed from the latest interval. Values outside 30-220 BPM are discarded.

## Fall detection (`main.cpp`)
Accelerometer magnitude (in g) is sampled every 50 ms:

```
IDLE --(mag < 0.6 g)--> POSSIBLE_FALL
POSSIBLE_FALL --(3 consecutive samples < 0.6 g)--> WAIT_IMPACT
POSSIBLE_FALL --(mag >= 0.6 g)--> IDLE
WAIT_IMPACT --(mag > 2.5 g or jerk > 1.5 g)--> ALARM, back to IDLE
WAIT_IMPACT --(no impact within 1000 ms)--> IDLE
```

If the heart rate alarm is already active when a fall is detected, the **both** pattern is used.

## Alarm patterns
| Type | Buzzer on / off | Duration |
|------|-----------------|----------|
| Heart rate | 100 ms / 400 ms | 3 s |
| Fall | 100 ms / 100 ms | 3 s |
| Both | 50 ms / 50 ms | 3 s |

## Sensor configuration
| Sensor | Setting |
|--------|---------|
| MPU6050 | Accelerometer ±2 g, gyroscope ±2000 °/s, sample-rate divider 7, no DLPF |
| MAX30102 | LED power `0xDF`, averaging 2, Red + IR, 200 Hz sample rate, 411 µs pulse width, 16384 ADC range |
