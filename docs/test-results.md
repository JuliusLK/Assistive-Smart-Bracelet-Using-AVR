# Test Results

Results from the course final project report (CPEN6261010 Microcontroller, Binus University, odd semester 2025/2026). All tests were done on the prototype in a small-scale lab setting, using the MAX30102 configuration in `firmware/src/main.cpp` (LED power `0xDF`, averaging 2, 200 Hz sample rate).

## 1. Heart rate vs. Samsung Galaxy Fit 3
The bracelet was compared against a Samsung Galaxy Fit 3 worn at the same time, 10 readings. All readings were above 100 BPM, so the heart rate alarm was triggered every time.

| # | Galaxy Fit 3 (BPM) | Bracelet (BPM) | Difference | Alarm |
|---|--------------------|----------------|------------|-------|
| 1 | 106 | 101 | 5 | On |
| 2 | 107 | 109 | -2 | On |
| 3 | 111 | 110 | 1 | On |
| 4 | 111 | 117 | -6 | On |
| 5 | 114 | 119 | -5 | On |
| 6 | 115 | 120 | -5 | On |
| 7 | 117 | 121 | -4 | On |
| 8 | 120 | 121 | -1 | On |
| 9 | 121 | 122 | -1 | On |
| 10 | 122 | 122 | 0 | On |
| **Mean** | **114.4** | **116.2** | **-1.8** | |

- Difference of the means: **1.57%** (1.8 / 114.4).
- Mean absolute difference (computed from the table): **3.0 BPM**, about 2.6% of the mean reading.
- The bracelet read slightly higher on average. The report attributes this to sensor calibration and signal processing differences.

**Limitations:** the readings only cover an elevated heart rate (106-122 BPM), so the low and normal ranges were not tested, and the reference is a consumer smartband, not a medical-grade device.

## 2. Fall detection
Ten simulated falls. Detection rule (see [`how-it-works.md`](how-it-works.md)): free-fall below 0.6 g, followed within 1 s by an impact above 2.5 g or a jerk above 1.5 g.

| # | ACC min (mg) | ACC max (mg) | Jerk max (mg) | Gyro max (dps) | Possible fall | Awaiting impact | Impact detected | Alarm |
|---|--------------|--------------|---------------|----------------|---------------|-----------------|-----------------|-------|
| 1 | 134 | 3321 | 3150 | 1135 | Yes | Yes | Yes | Yes |
| 2 | 96 | 1605 | 1426 | 375 | Yes | Yes | Yes | Yes |
| 3 | 166 | 2013 | 1418 | 946 | Yes | Yes | Yes | Yes |
| 4 | 182 | 2875 | 1980 | 822 | Yes | Yes | Yes | Yes |
| 5 | 210 | 2654 | 1742 | 610 | Yes | Yes | Yes | Yes |
| 6 | 155 | 3098 | 2214 | 990 | Yes | Yes | Yes | Yes |
| 7 | 243 | 2531 | 1687 | 540 | Yes | Yes | Yes | Yes |
| 8 | 198 | 2794 | 1902 | 734 | Yes | Yes | Yes | Yes |
| 9 | 174 | 2950 | 2140 | 865 | Yes | Yes | Yes | Yes |
| 10 | 221 | 2688 | 1823 | 603 | Yes | Yes | Yes | Yes |

- **10 / 10** simulated falls were detected and triggered the alarm.
- ACC min was 96-243 mg in every trial, below the 600 mg free-fall threshold.
- ACC max ranged 1605-3321 mg, jerk max 1418-3150 mg, and gyro max 375-1135 dps, showing a sharp acceleration spike and a clear orientation change during each fall.

**Notes and limitations:**
- Only simulated falls were recorded. Everyday activities (walking, sitting down quickly, swinging the arm) were not part of this test, so the false-alarm rate is still unknown.
- In trials 2 and 3 the logged peaks (ACC max 1605 / 2013 mg, jerk 1426 / 1418 mg) are below the configured impact thresholds (2500 mg / 1500 mg). Re-check how these peaks were logged if you reuse this table.

## 3. Alarm patterns
The three alarm patterns (heart rate, fall, both) were verified to work as designed. See the table in the [README](../README.md#alert-patterns).
