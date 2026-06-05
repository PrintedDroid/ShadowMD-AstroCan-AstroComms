# Shadow_MD AstroCan BLDC Standalone v2

Author: printed-droid.com
Original Base: Shadow_MD by KnightShade / vint43

> ### Which board is this for?
>
> This sketch targets the **AstroComms Ultra Shield v1.9 / v2.x** — the
> platform with BLDC support. Three foot-drive modes are supported:
> Sabertooth (classic), BLDC PPM/VESC, and BLDC PWM+DIR (Cytron MD-Series,
> BTS7960, etc.).
>
> **Repository for this sketch (AstroComms with BLDC)**:
> <https://github.com/PrintedDroid/ShadowMD-AstroComms-v1.-v2.x>
>
> If you have a classic **AstroCan** board **without BLDC**, use the
> other repository instead — it contains the non-BLDC Standalone sketch:
> <https://github.com/PrintedDroid/ShadowMD-AstroCan-AstroComms>
>
> BLDC does **not** work with AstroCan — the AstroCan board does not
> route the pins that BLDC mode requires.

## What Is This?

A complete Arduino Mega sketch for controlling astromech droids (R2-D2 etc.)
with two PS3 Move Navigation Controllers via Bluetooth. Supports three
different foot drive modes: **Sabertooth**, **BLDC PPM/Servo** (VESC, RC
ESCs), and **BLDC PWM+DIR** (Cytron MD-Series, BTS7960, other H-bridge
drivers).

This is a **standalone version** — the USB Host Shield Library is bundled
in the `src/` folder with all necessary modifications already applied.
No external library installation required. Just open and upload.

Features added by printed-droid.com over the original Shadow_MD:

- Three foot drive modes (Sabertooth, BLDC PPM, BLDC PWM+DIR) selectable
  at compile time via `#define FOOT_CONTROLLER`
- EEPROM-based PS3 controller pairing (no hardcoded MAC addresses)
- Serial CLI for runtime configuration (`pair`, `status`, `clear`,
  `invert`, `debug`, `reboot`, `help`)
- Sequential pairing mode: Foot -> Dome -> Foot Spare -> Dome Spare
- HCI-level MAC filtering (convention-safe: rejects unknown controllers)
- Deferred LED mechanism (prevents USB callback chain deadlocks)
- Runtime debug toggle (`debug` CLI command)
- **Runtime motor inversion** with EEPROM persistence (`invert left on/off`,
  `invert save`)
- **Shield revision selector** (`ASTROCOMMS_SHIELD_V2` / `_V19`) —
  one sketch fits both board revisions
- Bundled USB Host Shield Library with all necessary fixes in `src/`

## Recent changes (2026-04-21)

- **Shield revision selector**: `#define ASTROCOMMS_SHIELD_V2` or
  `ASTROCOMMS_SHIELD_V19` at the top of the sketch switches BLDC pin
  assignments between the two board revisions. A compile-time `#error`
  guards against missing or double definition.
- **Runtime motor inversion with CLI**: `invertLeft` and `invertRight`
  are now runtime variables (not compile-time defines). Settable via
  `invert left on/off`, `invert right on/off`, persisted via
  `invert save`, factory-reset via `invert reset`. EEPROM bytes 25/26.
- **writeBLDCMotors() safety clamps**: Mode 1 `constrain(us, 1000, 2000)`
  protects ESC/VESC from out-of-range values. Mode 2 splits magnitude
  and direction to avoid `uint8_t` wrap on `analogWrite()`.
- **External mixing respects invert flags**: the external-mixing code
  path now honors `invertLeft` / `invertRight` like the internal path.
- **drivespeed globals preserved**: `drivespeed1` / `drivespeed2` are
  no longer overwritten in `setup()`. Internal mixing caches its own
  runtime-scaled values.
- **RAM / String hardening**: PS3 MAC storage moved from Arduino `String`
  to fixed `char[18]` buffers. MAC helpers take caller-provided buffers.
  `marcDuinoButtonPush(const String&)` by reference. `MakeSongCommand()`
  returns `const char*` from a static buffer. `output.reserve(384)` and
  `output.remove(0)` instead of reassigning `""`.
- **cmdClear EEPROM loop** uses `<` instead of `<=` so the invert bytes
  at 25/26 are not touched. Use `invert reset` to clear them separately.

Compile footprint after these changes: **Flash 70056 B (27%),
RAM 4845 B (59%)** on `arduino:avr:mega`.

Details: see `../BUGFIXES.md` in the repo root.

## Hardware Requirements

- **Arduino Mega 2560** (or Mega ADK Rev3)
- **USB Host Shield** (MAX3421E-based, directly on top of the Mega)
- **Bluetooth USB Dongle** (see compatible list below)
- **2× PS3 Move Navigation Controller**
- **Foot motor controller** — one of:
  - Sabertooth 2x32 / 2x25 (Mode 0)
  - VESC or RC ESC (Mode 1, PPM signal)
  - BTS7960, Cytron MD-Series, or similar H-bridge (Mode 2, PWM+DIR)
- **SyRen 10** for dome drive — always required, regardless of foot drive mode
- **MarcDuino** dome + body boards (optional, for panel/sound control)

### Compatible Bluetooth Dongles

You need a **CSR8510-based** Bluetooth dongle. Most cheap BT 4.0 dongles use this chip.

| Dongle | Max Controllers | Status |
|---|---|---|
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

**NOT compatible**:

- **TP-Link UB400** — V1 uses CSR8510 (works), but V2 uses Realtek RTL8761B (does NOT work). Since you can't tell which version you'll get, avoid this dongle entirely.
- **LogiLink BT0058** (Realtek RTL8761B, BT 5.0) — does NOT work
- **Any Realtek-based dongle** — not compatible with the USB Host Shield Library

Rule of thumb: if it says "Bluetooth 5.0" on the package and costs less than 15 EUR, it's almost certainly Realtek-based and won't work. Look for "Bluetooth 4.0" or check for a CSR8510 chip. Exception: the Asus USB-BT500 (BT 5.0) is confirmed working.

### Why a Modified USB Host Shield Library?

The upstream USB Host Shield Library 2.0 has several issues that prevent
reliable operation with two PS3 Navigation Controllers on a convention
floor:

- **Critical bug**: an uninitialized variable (`timerHID`) causes the
  Arduino to hang for ~24 days on the first HID command. The heap on
  Arduino Mega is not zero-initialized, so `timerHID` contains a random
  value after `new`, leading to `delay(2.1 billion ms)`.
- **No MAC filtering**: at conventions with dozens of PS3 controllers
  nearby, any controller could connect to your droid. The modified
  library rejects unknown controllers at HCI level before they even
  fully connect.
- **Missing timeout protection**: the original `OutTransfer()` can spin
  forever if the MAX3421E doesn't respond — the modified version has a
  5-second timeout.
- **Dongle compatibility**: some Bluetooth dongles (CSR4) fail on Remote
  Name Request. The modified library skips this step for known HID
  gamepads and uses a non-blocking accept delay instead.
- **Reconnect after power-off**: the original library doesn't properly
  reset service slots on disconnect, preventing controllers from
  reconnecting.

All fixes are documented in detail in [ERKENNTNISSE.md](ERKENNTNISSE.md).

## Arduino IDE

- **Arduino IDE 1.8.19** — tested, works
- **Arduino IDE 2.x** — tested, works
- Board: **Arduino Mega 2560** (or Mega ADK)
- No additional libraries need to be installed (USB Host Shield 2.0
  comes bundled in `src/`)

## Quick Start

### 1. Select Shield Revision

Open `Shadow_MD_AstroCan_BLDC_Standalone_v2.ino` and set exactly one of:

```cpp
#define ASTROCOMMS_SHIELD_V2       // current board (default)
//#define ASTROCOMMS_SHIELD_V19    // older board (v1.9)
```

If unsure: look at your board's silkscreen. "ASTROCOMMS ULTRA SHIELD v1.9+"
means use `ASTROCOMMS_SHIELD_V19`. Otherwise keep the default.

### 2. Select Your Foot Drive Mode

Also at the top of the sketch:

```cpp
#define FOOT_CONTROLLER 0
// 0 = Sabertooth Serial (default)
// 1 = BLDC PPM/Servo   (VESC, RC ESC)
// 2 = BLDC PWM+DIR     (Cytron MD-Series, BTS7960, H-bridge)
```

### 3. Upload the Sketch

1. Open the `.ino` in Arduino IDE.
2. Board: **Arduino Mega or Mega 2560**.
3. Port: select the correct COM port.
4. Upload (Ctrl-U).

> ⚠️ **Dry-test before first drive**: block up the droid (wheels in
> the air) before the first power-on. Wrong motor direction, wrong
> pin mapping or unexpected ramping values can otherwise cause the
> droid to take off uncontrolled.

### 4. Pair Your Controllers

Each controller needs to be paired once. The MAC address is stored in EEPROM and survives reboots and re-uploads.

1. Open **Serial Monitor** (115200 Baud).
2. Type `pair` and press Enter.
3. **Unplug** the Bluetooth dongle from the USB Host Shield.
4. **Plug in** your first PS3 Navigation Controller via USB cable.
5. Wait for: `>> Paired [Foot Primary]: XX:XX:XX:XX:XX:XX`.
6. **Unplug** the controller, **plug in** the second controller (for dome).
7. Wait for: `>> Paired [Dome Primary]: XX:XX:XX:XX:XX:XX`.
8. **Unplug** the controller, **plug the BT dongle back in**.
9. Type `done` and press Enter.

The controllers are now paired. Turn them on — they connect automatically
after ~5 seconds (the second controller may take longer than the first).

### 5. Verify Connection

Serial Monitor should show:

```
Waiting for controller...
Connected: 00:07:04:BA:C9:56
[FOOT onInit] enter MAC=00:07:04:BA:C9:56
[LOOP] Sending Foot LED... OK
Connected: 00:06:F7:3B:52:99
[DOME onInit] enter MAC=00:06:F7:3B:52:99
[LOOP] Sending Dome LED... OK
```

The controller LEDs should be solid (not blinking). If you're still
aufgebockt (dry-test), try gentle stick movements and verify direction
with `status`. If a side turns wrong: `invert left on` / `invert right on`
/ `invert save`. Then put the droid on the floor.

## Drive Modes

The drive mode is selected via `#define FOOT_CONTROLLER` at the top of
the sketch:

| Mode | `FOOT_CONTROLLER` | Controller Type | Use Case |
|---|---|---|---|
| 0 | Sabertooth Serial | Sabertooth 2x32/2x25 | Classic brushed DC drive |
| 1 | BLDC PPM/Servo | VESC, RC ESC | Brushless with PPM signal |
| 2 | BLDC PWM+DIR | BTS7960, Cytron MD | H-bridge with PWM + direction |

### Mode 0 — Sabertooth Serial (Default)

- Communication via Serial2 (Packetized Serial, 9600 Baud)
- Internal mixing in the Sabertooth
- DIP switches on Sabertooth: 1 & 2 Down, all others Up

### Mode 1 — BLDC PPM / Servo

- Servo signal (1000–2000 µs) per motor
- 1500 µs = stop, <1500 µs = reverse, >1500 µs = forward
- Internal BHD Diamond mixing
- Ideal for VESC or standard RC ESCs
- `writeBLDCMotors()` clamps output to 1000–2000 µs so invalid inputs
  can't harm your ESC

### Mode 2 — BLDC PWM+DIR

- PWM signal (0–255) for speed, per motor
- Digital direction pin (HIGH/LOW) per motor
- Optional shared brake pin (active LOW)
- For H-bridge drivers like BTS7960 or Cytron MD-Series
- Magnitude and direction are split in software so the direction
  indication never wraps

## Pin Assignment

### Mode 1 — PPM/Servo Pins

| Board revision | Left ESC | Right ESC |
|---|---|---|
| `ASTROCOMMS_SHIELD_V2` | D44 | D45 |
| `ASTROCOMMS_SHIELD_V19` | D6 (Timer4 OC4A) | D7 (Timer4 OC4B) |

### Mode 2 — PWM+DIR Pins

| Signal | `V2` | `V19` |
|---|---|---|
| `leftFootPwmPin`  | D44 | D6 |
| `leftFootDirPin`  | D42 | D32 |
| `rightFootPwmPin` | D45 | D7 |
| `rightFootDirPin` | D43 | D8 |
| `footBrakePin`    | D40 | D5 |

On the v1.9 the 8-pin BLDC header also exposes D11 (reserve), D17, and
D19. D17 and D19 are silkscreened `RX2` / `RX1` — originally intended
for two Sbus / iBus RC receivers (not implemented in this firmware yet).

### Serial Ports (Arduino Mega)

| Serial | Pins | Function | Baud Rate |
|---|---|---|---|
| Serial0 | 0, 1 | Debug / USB | 115200 |
| Serial1 | 19, 18 | MarcDuino Dome | 9600 |
| Serial2 | 17, 16 | Motor controller (Sabertooth/SyRen) | 9600 |
| Serial3 | 15, 14 | MarcDuino Body (optional) | 9600 |

### Dome Drive

The dome is always controlled via a **SyRen** (address 129) on Serial2 —
regardless of the selected foot drive mode. DIP switches on SyRen:
1, 2 and 4 Down, all others Up.

## Serial CLI Commands

Connect via Serial Monitor at **115200 Baud**:

| Command | Description |
|---|---|
| `pair` | Enter pairing mode (Foot -> Dome -> Foot Spare -> Dome Spare) |
| `done` | Exit pairing mode early |
| `status` | Show stored MAC addresses, connection state, invert state |
| `clear` | Clear all stored MACs from EEPROM (factory reset) |
| `invert` | Show runtime motor inversion state |
| `invert left on`/`off` | Invert / normalize left motor |
| `invert right on`/`off` | Invert / normalize right motor |
| `invert save` | Persist current invert settings to EEPROM |
| `invert reset` | Factory-reset invert to 0/0 and save |
| `debug` | Toggle verbose Bluetooth debug output |
| `reboot` | Software reset |
| `help` | Show all commands |

## User Settings

All settings are at the top of the `.ino` file.

### Speed

| Variable | Default | Range | Description |
|---|---|---|---|
| `drivespeed1` | 70 | 0–127 | Normal drive speed |
| `drivespeed2` | 110 | 0–127 | Turbo speed (L3+L1) |
| `turnspeed` | 50 | 0–127 | Turning speed in place |
| `domespeed` | 100 | 0–127 | Dome rotation speed |
| `ramping` | 1 | 1–10 | Acceleration ramp (1 = smooth, 10 = direct) |

### Joystick

| Variable | Default | Description |
|---|---|---|
| `joystickFootDeadZoneRange` | 15 | Foot joystick dead zone |
| `joystickDomeDeadZoneRange` | 10 | Dome joystick dead zone |
| `driveDeadBandRange` | 10 | Sabertooth deadband (Mode 0) |

### Motor Direction

If your droid drives backwards when you push forward, or turns the
wrong way, change these:

| Variable | Default | Options | Scope |
|---|---|---|---|
| `invertTurnDirection` | 1 | 1 or -1 | all modes |
| `invertDriveDirection` | -1 | 1 or -1 | all modes |
| `invertDomeDirection` | -1 | 1 or -1 | all modes |
| `invertLeft` (runtime) | 0 | 0 or 1 | BLDC modes (CLI-controllable) |
| `invertRight` (runtime) | 0 | 0 or 1 | BLDC modes (CLI-controllable) |

`invertLeft` and `invertRight` are **runtime settings**: change them
live with `invert left on`/`invert right on`, persist with `invert save`.
Settings survive reboot. In Sabertooth mode these two flags are ignored
(use `invertDriveDirection` / `invertTurnDirection` instead).

### Dome Automation

| Variable | Default | Description |
|---|---|---|
| `domeAutomation` | false | Automatic dome movement |
| `domeAutoSpeed` | 70 | Automation speed (50–100) |
| `time360DomeTurn` | 2500 | Milliseconds for 360° turn |

## Controller Layout (PS3 Navigation)

### Foot Controller

| Button | Function |
|---|---|
| Analog Stick Y | Forward / Reverse |
| Analog Stick X | Turn left / right |
| L2 held | Deadman (stop feet) + dome control from foot stick |
| L1 held | Deadman (stop feet) |
| L3 + L1 | Toggle turbo mode |
| D-Pad | MarcDuino commands |
| Cross + D-Pad | MarcDuino Set 2 |
| Circle + D-Pad | MarcDuino Set 3 |
| PS + D-Pad | MarcDuino Set 4 |

### Dome Controller (optional)

| Button | Function |
|---|---|
| Analog Stick X | Dome rotation |
| D-Pad | MarcDuino dome commands |

## Mixing / Steering

### BHD Diamond Mixing (Internal)

Enabled with `#define INTERNAL_MIXING` (default). Converts joystick X/Y
into left/right motor values via a diamond coordinate system. Prevents
the sum of drive + steering from exceeding the maximum. Result: smooth,
proportional curve driving.

Reference: [Diamond Coordinates PDF](https://github.com/declanshanaghy/JabberBot/raw/master/Docs/Using%20Diamond%20Coordinates%20to%20Power%20a%20Differential%20Drive.pdf)

### External Mixing

Comment out `INTERNAL_MIXING` — the motor controller (e.g. Roboteq)
handles mixing itself. Raw X/Y values are passed through directly.
External mixing now honors `invertLeft` / `invertRight` like the
internal path.

## Safety Features

### Deadman Switch

- **L2 or L1 pressed**: foot drive stopped immediately.
- L2 also activates dome control from the foot controller.

### Speed Ramping

Smooth acceleration/deceleration. Adjustable via `ramping` (1 = very
smooth, higher = more direct).

### Controller Timeout

| Timeout | Action |
|---|---|
| 300 ms no signal | Motors stop |
| 10 s no signal | Controller disconnect |
| Sabertooth timeout | 10 ms units (hardware failsafe) |
| SyRen timeout | 20 ms units (hardware failsafe) |

### MAC Address Validation

Unknown controllers are immediately disconnected and all motors
stopped. At conventions, HCI-level rejection prevents unknown
controllers from even connecting.

### Brake Pin (Mode 2)

```cpp
#define ENABLE_BRAKE    // Enable brake function
```

- `LOW` = brake engaged
- `HIGH` = brake released

## Troubleshooting

### Sketch won't compile

- `#error "No shield revision defined"` — uncomment exactly one of
  `ASTROCOMMS_SHIELD_V2` / `ASTROCOMMS_SHIELD_V19`.
- `#error "Define only ONE shield revision"` — you have both; comment
  one out.
- Missing `.h` file — don't replace the bundled `src/` folder with an
  Arduino Library Manager version. The bundled one has critical fixes.

### Controller blinks but doesn't connect

- Check the BT dongle (see list above).
- Try `clear` and then `pair` again.
- Power-cycle the Arduino (unplug USB, not just reset button).

### Only one controller connects

- Some CSR4 dongles only support one simultaneous connection.
- Use a BT0015 (LogiLink), UGREEN CM748 or Asus USB-BT500.

### Second controller takes a long time

- Normal behavior — the second is slower than the first.
- If it still doesn't connect after ~15 s: briefly press PS, or turn
  the controller off and on again.

### Motors don't respond

- Mode 0: check Sabertooth DIP (1 & 2 Down) and Serial2 wiring.
- Mode 1 / 2: check shield revision selector matches your board, check
  motor power supply, check pin wiring against the tables above.
- Use `status` to verify controllers are connected.

### Drive direction wrong

- Use the runtime invert commands: `invert left on` / `invert right on`,
  test, then `invert save`.

### MAC shows as "XX" after flashing

- EEPROM magic byte mismatch (normal after `clear` or on a fresh Mega).
- Run `pair` again.

## Repository contents

This repository contains three sketches that together form the complete
AstroComms-BLDC system. The main Shadow sketch lives in its own folder
because the sound controller and the WiFi bridge are shipped alongside:

```
ShadowMD-AstroComms-v1.-v2.x/                 <- Repo root
|
|-- Shadow_MD_AstroCan_BLDC_Standalone_v2/    <- *** MAIN SKETCH (this folder) ***
|   |-- Shadow_MD_AstroCan_BLDC_Standalone_v2.ino   (open and upload to Mega)
|   |-- README.md                                   (this file)
|   |-- ERKENNTNISSE.md                             (technical dev notes on
|   |                                                the bundled USB Host Shield fixes)
|   `-- src/                                        (bundled USB Host Shield Library 2.0,
|                                                    all modifications pre-applied)
|
|-- DFPlayer_Sound_control_v1.2/              <- Sound controller sketch (Pro Mini)
|   `-- DFPlayer_Sound_control_v1.2.ino             (MarcDuino-compatible sound
|                                                    firmware using DFPlayer 0x14
|                                                    command, mp3/NNNN_*.mp3 SD layout)
|
`-- esp32_esp8266_as_xbee_v2.0/               <- WiFi-to-Serial bridge (ESP)
    `-- esp32_esp8266_as_xbee_v2.0.ino               (TCP server on port 9750,
                                                     works on ESP32, ESP8266, ESP32-C3)
```

The three sketches are flashed to three different microcontrollers:

| Sketch | Target | Role |
|---|---|---|
| `Shadow_MD_AstroCan_BLDC_Standalone_v2` | Arduino Mega 2560 | Main droid controller: PS3 input, motor drive, dome, MarcDuino output |
| `DFPlayer_Sound_control_v1.2` | Arduino Pro Mini (ATmega328P) | Sound controller — receives `$...` commands, drives the DFPlayer Mini |
| `esp32_esp8266_as_xbee_v2.0` | ESP32 / ESP8266 / ESP32-C3 | WiFi bridge — makes the droid controllable via TCP app |

## Credits

- **Shadow_MD** original by KnightShade / vint43
- **Custom Sequences** by Tim Ebel (Eebel)
- **USB Host Shield Library** by Oleg Mazurov
- **PS3BT Library** by Kristian Lauszus
- **Sabertooth Library** by Dimension Engineering
- **BHD Diamond Mixing** by Declan Shanaghy (JabberBot)
- **printed-droid.com extensions**: EEPROM pairing, Serial CLI,
  BLDC modes, shield revision selector, runtime motor inversion, RAM
  hardening, bundled USB Host Shield fixes
