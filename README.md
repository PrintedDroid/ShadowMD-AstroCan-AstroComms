# Shadow_MD AstroCan Standalone

Author: printed-droid.com

> ### Which version do I need?
>
> This repository covers **two different boards**, and which sketch you flash
> depends on your hardware:
>
> - **AstroCan** — uses this sketch (AstroCan Standalone) with Sabertooth (feet)
>   and SyRen (dome) via serial motor controllers. **No BLDC support.**
> - **AstroComms Ultra Shield v1.9 / v2.x** — the older platform with BLDC
>   support. Uses a dedicated sketch. Supports Sabertooth, BLDC PPM/VESC, and
>   BLDC PWM+DIR (Cytron MD-Series, BTS7960, etc.).
>   Repo: **<https://github.com/PrintedDroid/ShadowMD-AstroComms-v1.-v2.x>**
>
> **Important**: BLDC does **not** work with AstroCan — the AstroCan board
> does not route the pins that BLDC mode requires. If you want BLDC, you
> need the AstroComms Ultra Shield and the linked repo above.

## What Is This?

A complete Arduino Mega sketch for controlling astromech droids (R2-D2 etc.)
with two PS3 Move Navigation Controllers via Bluetooth. One controller for
foot drive (Sabertooth), one for dome rotation (SyRen).

This is a **standalone version** — the USB Host Shield Library is bundled
in the `src/` folder with all necessary modifications already applied.
No external library installation required. Just open and upload.

## Recent changes

- **2026-04-21 — RAM / String hardening**: PS3 MAC storage moved from
  Arduino `String` to fixed `char[18]` buffers. MAC helpers take
  caller-provided buffers. `marcDuinoButtonPush()` takes `const String&`
  by reference instead of by value (~50 call sites, one copy saved each).
  `MakeSongCommand()` returns `const char*` from a static buffer.
  `output.reserve(384)` + `output.remove(0)` instead of reassigning `""`.
  `cmdClear` EEPROM-loop ends at the correct MAC boundary (`<` instead of
  `<=`). No user-visible behavior changes — same CLI, same commands,
  same pairing workflow. The hardening reduces heap fragmentation on
  long convention sessions. Details in the upstream `BUGFIXES.md` #9.

### Why a Modified Library?

The original USB Host Shield Library 2.0 has several issues that prevent
reliable operation with two PS3 Navigation Controllers:

- **Critical bug:** An uninitialized variable (`timerHID`) causes the Arduino to hang for ~24 days on the first HID command. The heap on Arduino Mega is not zero-initialized, so `timerHID` contains a random value after `new`, leading to `delay(2.1 billion ms)`.
- **No MAC filtering:** At conventions with dozens of PS3 controllers nearby, any controller could connect to your droid. The modified library rejects unknown controllers at HCI level before they even fully connect.
- **Missing timeout protection:** The original `OutTransfer()` can spin forever if the MAX3421E doesn't respond — the modified version has a 5-second timeout.
- **Dongle compatibility:** Some Bluetooth dongles (CSR4) fail on Remote Name Request. The modified library skips this step for known HID gamepads and uses a non-blocking accept delay instead.
- **Reconnect after power-off:** The original library doesn't properly reset service slots on disconnect, preventing controllers from reconnecting.

## Hardware Requirements

- **Arduino Mega 2560** (or Mega ADK Rev3)
- **USB Host Shield** (MAX3421E-based, directly on top of the Mega)
- **Bluetooth USB Dongle** (see compatible dongles below)
- **2x PS3 Move Navigation Controller**
- **Sabertooth 2x32 or 2x25** (foot drive, Packetized Serial)
- **SyRen 10** (dome drive, Packetized Serial)
- **MarcDuino** dome + body boards (optional, for panel/sound control)

### Compatible Bluetooth Dongles

You need a **CSR8510-based** Bluetooth dongle. Most cheap BT 4.0 dongles use this chip.

| Dongle | Max Controllers | Status |
|--------|-----------------|--------|
| LogiLink BT0015 (BT 4.0) | 2 simultaneous | **Recommended** |
| UGREEN CM748 (BT 5.3) | 2 simultaneous | **Confirmed working** |
| Asus USB-BT500 (BT 5.0) | 2 simultaneous | Confirmed working |
| LogiLink BT0048 (BT 4.0) | 2 simultaneous | Confirmed working |
| CSL Bluetooth 4.0 (Amazon B01N0368AY) | 2 simultaneous | Confirmed working |
| UGREEN USB Bluetooth 4.0 | 2 simultaneous | Confirmed working |
| Sandberg Nano Bluetooth 4.0 | 2 simultaneous | Confirmed working |
| Pearl BT 4.0 Class 1 (EDR+CSR) | 2 simultaneous | Confirmed working |
| APLIC ZSB BT Nano Stick v4.0 (302352) | 2 simultaneous | Confirmed working |
| Gembird BTD-Mini (BT 4.0) | **1 only** | Works, but no dual controller |
| Any generic "CSR8510 BT 4.0" dongle | 1–2 simultaneous | Should work |

### NOT Compatible

- **TP-Link UB400** — V1 uses CSR8510 (works), but V2 uses Realtek RTL8761B (does NOT work). Since you can't tell which version you'll get, avoid this dongle entirely.
- **LogiLink BT0058** (Realtek RTL8761B, BT 5.0) — does NOT work
- **Any Realtek-based dongle** — not compatible with the USB Host Shield Library

**Rule of thumb:** If it says "Bluetooth 5.0" on the package and costs less than 15 EUR, it's almost certainly Realtek-based and won't work. Look for "Bluetooth 4.0" or check for a CSR8510 chip. Exception: The Asus USB-BT500 (BT 5.0) is confirmed working.

### Troubleshooting

**Controller blinks but doesn't connect:**
- Make sure you're using a compatible BT dongle (see list above)
- Try `clear` then `pair` to re-pair from scratch
- Power-cycle the Arduino completely (unplug USB power, not just the reset button)

**Second controller takes a long time to connect:**
- This is normal — the second controller may need more time than the first one
- If it only blinks and doesn't connect, briefly press the PS button on the controller
- If it still doesn't connect, turn the controller off and back on, then try pairing again

**Only one controller connects:**
- Your dongle may only support 1 simultaneous connection (e.g. Gembird BTD-Mini)
- Use a BT0015 (LogiLink), UGREEN CM748, or Asus USB-BT500 — confirmed to support 2 controllers

**Motors don't respond:**
- Check motor controller wiring and settings
- For Sabertooth: DIP switches 1 & 2 Down, all others Up
- Type `status` to verify controllers are connected

## Arduino IDE

- **Arduino IDE 1.8.19** — tested, works
- **Arduino IDE 2.x** — tested, works
- Board: **Arduino Mega 2560** (or Mega ADK)
- No additional libraries need to be installed

## Quick Start

### 1. Upload the Sketch

1. Open `Shadow_MD_AstroCan_Standalone.ino` in Arduino IDE
2. Select Board: **Arduino Mega or Mega 2560**
3. Select the correct COM port
4. Upload

### 2. Pair Your Controllers

Each controller needs to be paired once. The MAC address is stored in EEPROM
and survives reboots and re-uploads.

1. Open **Serial Monitor** (115200 Baud)
2. Type `pair` and press Enter
3. **Unplug** the Bluetooth dongle from the USB Host Shield
4. **Plug in** your first PS3 Navigation Controller via USB cable
5. Wait for the message: `>> Paired [Foot Primary]: XX:XX:XX:XX:XX:XX`
6. **Unplug** the controller
7. **Plug in** the second controller for dome
8. Wait for: `>> Paired [Dome Primary]: XX:XX:XX:XX:XX:XX`
9. **Unplug** the controller, **plug the BT dongle back in**
10. Type `done` and press Enter

The controllers are now paired. Turn them on — they should connect automatically.

### 3. Verify Connection

After pairing, turn on both controllers. You should see in Serial Monitor:

```
Waiting for controller...
Connected: 00:07:04:BA:C9:56
[FOOT onInit] enter MAC=00:07:04:BA:C9:56
[LOOP] Sending Foot LED... OK
Connected: 00:06:F7:3B:52:99
[DOME onInit] enter MAC=00:06:F7:3B:52:99
[LOOP] Sending Dome LED... OK
```

The controller LEDs should stay solid (not blinking).

## Serial CLI Commands

Connect via Serial Monitor at **115200 Baud**:

| Command | Description |
|---------|-------------|
| `pair` | Enter pairing mode (Foot -> Dome -> Foot Spare -> Dome Spare) |
| `done` | Exit pairing mode early |
| `status` | Show stored MAC addresses and connection status |
| `clear` | Clear all stored MACs from EEPROM (reset to factory) |
| `debug` | Toggle verbose Bluetooth debug output on/off |
| `reboot` | Software reset |
| `help` | Show available commands |

## User Settings

All settings are at the top of the `.ino` file. The most important ones:

### Speed

| Variable | Default | Description |
|----------|---------|-------------|
| `drivespeed1` | 70 | Normal drive speed (0-127) |
| `drivespeed2` | 110 | Turbo speed, activated with L3+L1 (0-127) |
| `turnspeed` | 50 | Turning speed in place (0-127) |
| `domespeed` | 100 | Dome rotation speed (0-127) |
| `ramping` | 1 | Acceleration ramp (1 = smooth, higher = more direct) |

### Joystick Dead Zones

| Variable | Default | Description |
|----------|---------|-------------|
| `joystickFootDeadZoneRange` | 15 | Foot joystick dead zone (increase if drifting) |
| `joystickDomeDeadZoneRange` | 10 | Dome joystick dead zone |

### Motor Direction

If your droid drives backwards when you push forward, change these:

| Variable | Default | Options |
|----------|---------|---------|
| `invertTurnDirection` | 1 | 1 or -1 |
| `invertDriveDirection` | -1 | 1 or -1 |
| `invertDomeDirection` | -1 | 1 or -1 |

## Motor Controller Setup

### Sabertooth 2x32/2x25 (Foot Drive)

- DIP Switches: **1 and 2 Down**, all others Up
- Connected to **Serial2** (pins 16/17), 9600 Baud
- Address: 128 (default)

### SyRen 10 (Dome Drive)

- DIP Switches: **1, 2 and 4 Down**, all others Up
- Connected to **Serial2** (pins 16/17), 9600 Baud (shared bus with Sabertooth)
- Address: 129

## Controller Layout (PS3 Navigation)

### Foot Controller

| Button | Function |
|--------|----------|
| Analog Stick | Drive (Y = forward/back, X = turn) |
| L2 held | Stop feet + enable dome control from foot stick |
| L1 held | Stop feet |
| L3 + L1 | Toggle turbo mode |
| D-Pad | MarcDuino commands |
| Cross + D-Pad | MarcDuino command set 2 |
| Circle + D-Pad | MarcDuino command set 3 |
| PS + D-Pad | MarcDuino command set 4 |

### Dome Controller (optional)

| Button | Function |
|--------|----------|
| Analog Stick X | Dome rotation |
| D-Pad | MarcDuino dome commands |

## Troubleshooting

### Controller blinks but doesn't connect
- Make sure you're using a compatible BT dongle (see list above)
- Try `clear` then `pair` again to re-pair
- Power-cycle the Arduino (unplug USB power completely, not just reset button)

### "Invalid data" messages in Serial Monitor
- This is normal for a few seconds after connection — the controller needs time to start sending valid data
- If it persists, try `debug` command to see detailed BT messages

### Only one controller connects
- Your dongle may only support 1 simultaneous connection (e.g. some CSR4 dongles)
- Use a BT0015 (LogiLink) or UGREEN CM748 — confirmed to support 2 controllers

### Motors don't respond
- Check Sabertooth/SyRen DIP switch settings
- Check Serial2 wiring (pins 16/17)
- Try the `status` command to verify controllers are connected

## Folder Structure

```
Shadow_MD_AstroCan_Standalone/
  Shadow_MD_AstroCan_Standalone.ino   <- Main sketch (just open and upload)
  README.md                           <- This file
  ERKENNTNISSE.md                     <- Technical development notes
  src/                                <- Bundled USB Host Shield Library 2.0
                                         (all modifications pre-applied)
```

## Credits

- **Shadow_MD** original by KnightShade / vint43
- **Custom Sequences** by Tim Ebel (Eebel)
- **USB Host Shield Library** by Oleg Mazurov
- **PS3BT Library** by Kristian Lauszus
- **Sabertooth Library** by Dimension Engineering
- **BHD Diamond Mixing** by Declan Shanaghy (JabberBot)
