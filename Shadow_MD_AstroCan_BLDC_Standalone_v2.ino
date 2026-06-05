// ╔═══════════════════════════════════════════════════════════════════════════════════════╗
// ║                                                                                       ║
// ║     ███████╗██╗  ██╗ █████╗ ██████╗  ██████╗ ██╗    ██╗    ███╗   ███╗██████╗         ║
// ║     ██╔════╝██║  ██║██╔══██╗██╔══██╗██╔═══██╗██║    ██║    ████╗ ████║██╔══██╗        ║
// ║     ███████╗███████║███████║██║  ██║██║   ██║██║ █╗ ██║    ██╔████╔██║██║  ██║        ║
// ║     ╚════██║██╔══██║██╔══██║██║  ██║██║   ██║██║███╗██║    ██║╚██╔╝██║██║  ██║        ║
// ║     ███████║██║  ██║██║  ██║██████╔╝╚██████╔╝╚███╔███╔╝    ██║ ╚═╝ ██║██████╔╝        ║
// ║     ╚══════╝╚═╝  ╚═╝╚═╝  ╚═╝╚═════╝  ╚═════╝  ╚══╝╚══╝     ╚═╝     ╚═╝╚═════╝         ║
// ║                                                                                       ║
// ║          Small Handheld Arduino Droid Operating Wand + MarcDuino + AstroCan           ║
// ║                      BLDC Motor Support Edition                                       ║
// ║                                                                                       ║
// ╠═══════════════════════════════════════════════════════════════════════════════════════╣
// ║  Current Version:  www.printed-droid.com                                              ║
// ║  Original Base:    SHADOW_MD by vint43 (08/23/2015)                                   ║
// ║  Inspired by:      PADAWAN / KnightShade SHADOW effort                                ║
// ╠═══════════════════════════════════════════════════════════════════════════════════════╣
// ║                                                                                       ║
// ║  Supported Foot Drive Modes (named by control signal, not motor type):                ║
// ║    Mode 0 - Brushed DC, packet-serial   (Sabertooth 2x32 / 2x25)                      ║
// ║    Mode 1 - Brushless ESC, PPM/Servo    (VESC / FSESC, standard RC ESC)               ║
// ║    Mode 2 - Brushed DC, PWM+DIR+Brake   (BTS7960, Cytron MD13S, H-Bridge)             ║
// ║                                                                                       ║
// ║  Dome Drive:   SyRen 10 (Packetized Serial, always active)                            ║ 
// ║  Controller:   PS3 Move Navigation (Bluetooth)                                        ║ 
// ║  Board:        Arduino Mega ADK Rev3                                                  ║ 
// ║                                                                                       ║
// ╠═══════════════════════════════════════════════════════════════════════════════════════╣
// ║                                                                                       ║
// ║  This program is free software: you can redistribute it and/or modify it for          ║
// ║  your personal use and the personal use of other astromech club members.              ║
// ║                                                                                       ║
// ║  IT IS OFFERED WITHOUT ANY WARRANTY; without even the implied warranty of             ║
// ║  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                                 ║
// ║                                                                                       ║
// ║  You are using this software at your own risk. It is completely up to you to          ║
// ║  ensure the safe operation of your droid and to validate and test all aspects         ║
// ║  of your droid control system.                                                        ║
// ║                                                                                       ║
// ╠═══════════════════════════════════════════════════════════════════════════════════════╣
// ║                                                                                       ║
// ║  PS3 Bluetooth library by Kristian Lauszus (kristianl@tkjelectronics.com)             ║
// ║  Sabertooth library by Dimension Engineering                                          ║
// ║  BHD Diamond Mixing by Declan Shanaghy (JabberBot)                                    ║
// ║                                                                                       ║
// ║  Sabertooth (Foot Drive):                                                             ║
// ║    Set Sabertooth 2x32 or 2x25 Dip Switches: 1 and 2 Down, All Others Up              ║
// ║                                                                                       ║
// ║  SyRen 10 (Dome Drive):                                                               ║
// ║    Packetized Serial — Set Switches: 1, 2 and 4 Down, All Others Up                   ║
// ║    NOTE: SyRen Simple Serial support removed. Contact DimensionEngineering for        ║
// ║    firmware update if needed. Some place a 10K resistor between S1 & GND.             ║
// ║                                                                                       ║
// ╚═══════════════════════════════════════════════════════════════════════════════════════╝
//
// ---------------------------------------------------------------------------------------
//                        General User Settings
// ---------------------------------------------------------------------------------------

// MAC addresses are now loaded from EEPROM at boot. Use 'pair' command via Serial to set them.
// Defaults to "XX" (accept any controller) until paired.
#define MAC_STRING_LEN 18
#define MAC_TEXT_NONE "XX"
char PS3ControllerFootMac[MAC_STRING_LEN] = MAC_TEXT_NONE;
char PS3ControllerDomeMAC[MAC_STRING_LEN] = MAC_TEXT_NONE;
char PS3ControllerBackupFootMac[MAC_STRING_LEN] = MAC_TEXT_NONE;
char PS3ControllerBackupDomeMAC[MAC_STRING_LEN] = MAC_TEXT_NONE;

byte drivespeed1 = 70;   //For Speed Setting (Normal): set this to whatever speeds works for you. 0-stop, 127-full speed.
byte drivespeed2 = 110;  //For Speed Setting (Over Throttle): set this for when needing extra power. 0-stop, 127-full speed.

byte turnspeed = 50;      // the higher this number the faster it will spin in place, lower - the easier to control.
                         // Recommend beginner: 40 to 50, experienced: 50+, I like 75

byte domespeed = 100;    // If using a speed controller for the dome, sets the top speed
                         // Use a number up to 127

byte ramping = 1;        // Ramping- the lower this number the longer R2 will take to speedup or slow down,
                         // change this by increments of 1

byte joystickFootDeadZoneRange = 15;  // For controllers that centering problems, use the lowest number with no drift
byte joystickDomeDeadZoneRange = 10;  // For controllers that centering problems, use the lowest number with no drift

byte driveDeadBandRange = 10;     // Used to set the Sabertooth DeadZone for foot motors

// ---------------------------------------------------------------------------------------
//                 AstroComms Shield Hardware Revision Selector
// ---------------------------------------------------------------------------------------
// Uncomment EXACTLY ONE of the following defines to match your AstroComms shield.
// Only the BLDC pin layout depends on this; all other pins are identical across
// shield revisions. If neither is defined below, the sketch will fail to compile
// (with a clear #error) — set one intentionally.
//
//   ASTROCOMMS_SHIELD_V2  — current revision (5-pin BLDC terminal 44/42/45/43/40)
//   ASTROCOMMS_SHIELD_V19 — legacy revision (8-pin BLDC header 5/6/7/8/11/32
//                           + Cytron-MD13S 3-pin terminal on D3/D4)
// ---------------------------------------------------------------------------------------
//#define ASTROCOMMS_SHIELD_V2
#define ASTROCOMMS_SHIELD_V19

#if defined(ASTROCOMMS_SHIELD_V2) && defined(ASTROCOMMS_SHIELD_V19)
  #error "Define only ONE shield revision (ASTROCOMMS_SHIELD_V2 or ASTROCOMMS_SHIELD_V19), not both."
#endif
#if !defined(ASTROCOMMS_SHIELD_V2) && !defined(ASTROCOMMS_SHIELD_V19)
  #error "No shield revision defined. Uncomment ASTROCOMMS_SHIELD_V2 or ASTROCOMMS_SHIELD_V19."
#endif

// ---------------------------------------------------------------------------------------
//                        Foot Motor Controller Selection
// ---------------------------------------------------------------------------------------
// Modes are named by the control SIGNAL they emit, not by the motor type.
// Pick by your motor first, then by your controller:
//   - Brushless motor (3 phases)  -> needs an ESC/VESC          -> Mode 1
//   - Brushed motor   (2 wires)   -> Sabertooth serial          -> Mode 0
//                                 -> or H-bridge (PWM+DIR)      -> Mode 2
//
//   FOOT_CONTROLLER 0 = Brushed DC, packet-serial. Sabertooth 2x32/2x25 (default, original behavior)
//   FOOT_CONTROLLER 1 = Brushless ESC, PPM/Servo. VESC/FSESC or standard RC ESC - 1 signal pin per motor
//   FOOT_CONTROLLER 2 = Brushed DC, PWM+DIR(+Brake). H-bridge: BTS7960, Cytron MD13S - PWM, Direction, Brake pins
//   NOTE: Mode 2 is NOT brushless - an H-bridge cannot commutate a 3-phase BLDC motor.
// ---------------------------------------------------------------------------------------
#define FOOT_CONTROLLER 0

#if FOOT_CONTROLLER == 1
// --- BLDC PPM/Servo Mode Settings ---
// Each VESC/ESC gets a single servo-style PPM signal.
// 1500us = stop, 1000us = full reverse, 2000us = full forward
#if defined(ASTROCOMMS_SHIELD_V2)
  // Shield v2: 2-pin PPM header on Mega pins 44 + 45
  #define leftFootPin 44          // PPM signal pin for left foot ESC (Timer5 OC5C, PWM-capable)
  #define rightFootPin 45         // PPM signal pin for right foot ESC (Timer5 OC5B, PWM-capable)
#elif defined(ASTROCOMMS_SHIELD_V19)
  // Shield v1.9: choose two free pins from the 8-pin BLDC header (5, 6, 7, 8, 11, 32).
  // Pins 17 and 19 on the v1.9 header are RX2/RX1 — do NOT use them (Serial2/Serial1).
  #define leftFootPin 6           // PPM signal pin for left foot ESC (Timer4 OC4A)
  #define rightFootPin 7          // PPM signal pin for right foot ESC (Timer4 OC4B)
#endif
// Motor inversion is now a RUNTIME setting (invertLeft / invertRight globals,
// CLI-controllable via 'invert ...' commands, persisted in EEPROM). The old
// compile-time #define invertLeft/invertRight has been removed — see BUGFIXES #6.
#define INTERNAL_MIXING         // Use BHD Diamond mixing (comment out for external mixing)
#endif

#if FOOT_CONTROLLER == 2
// --- BLDC PWM+DIR Mode Settings ---
// Each motor uses a PWM pin (speed) and a DIR pin (direction).
// An optional shared BRAKE pin stops both motors.
#if defined(ASTROCOMMS_SHIELD_V2)
  // Shield v2: 5-pin terminal 44 PWM-L / 42 DIR-L / 45 PWM-R / 43 DIR-R / 40 BRK
  #define leftFootPwmPin 44       // PWM speed pin for left motor  (Timer5 OC5C)
  #define leftFootDirPin 42       // Direction pin for left motor  (digital)
  #define rightFootPwmPin 45      // PWM speed pin for right motor (Timer5 OC5B)
  #define rightFootDirPin 43      // Direction pin for right motor (digital)
  #define footBrakePin 40         // Shared brake pin (active LOW = brake engaged)
#elif defined(ASTROCOMMS_SHIELD_V19)
  // Shield v1.9: recommended mapping using 5 of the 8 header pins.
  // PWM pins 6 and 7 share Timer4 -> identical PWM frequency on both motors.
  // Pin 11 is kept free as reserve. Pins 17/19 are Serial-RX, unusable.
  #define leftFootPwmPin 6        // PWM speed pin for left motor  (Timer4 OC4A)
  #define leftFootDirPin 32       // Direction pin for left motor  (digital only)
  #define rightFootPwmPin 7       // PWM speed pin for right motor (Timer4 OC4B)
  #define rightFootDirPin 8       // Direction pin for right motor (digital; pin also Timer4 OC4C but unused as PWM here)
  #define footBrakePin 5          // Shared brake pin (digital; pin also Timer3 OC3A but unused as PWM here)
#endif
#define ENABLE_BRAKE            // Comment out if no brake pin is used
// Motor inversion is a RUNTIME setting — see Mode 1 block above.
#define INTERNAL_MIXING         // Use BHD Diamond mixing (comment out for external mixing)
#endif

// ---------------------------------------------------------------------------------------
//                  Motor Inversion Runtime Flags (CLI + EEPROM)
// ---------------------------------------------------------------------------------------
// These were compile-time #defines inside the FOOT_CONTROLLER blocks. They are now
// runtime-settable via the 'invert ...' CLI commands and persisted in EEPROM
// bytes EEPROM_INVERT_LEFT_ADDR / EEPROM_INVERT_RIGHT_ADDR. Values: 0 = normal,
// 1 = inverted (swap motor direction on that side). Mode 0 (Sabertooth) ignores
// these — it has invertDriveDirection / invertTurnDirection instead.
byte invertLeft  = 0;
byte invertRight = 0;

int invertTurnDirection = 1;    // This may need to be set to 1 for some configurations
int invertDriveDirection = -1;  // This may need to be set to 1 for some configurations
int invertDomeDirection = -1;   // This may need to be set to 1 for some configurations

byte domeAutoSpeed = 70;     // Speed used when dome automation is active - Valid Values: 50 - 100
int time360DomeTurn = 2500;  // milliseconds for dome to complete 360 turn at domeAutoSpeed - Valid Values: 2000 - 8000 (2000 = 2 seconds)
//Eebel START
bool DPLOpen = false;  //Global variable to toggle Data Panel Door so I can use one button to open and close
bool HoloOn = false;  //Global Variable to toggle Holos On/Off with one button
bool TopUArmOpen = false;
bool BotUArmOpen = false;
bool LeftDoorOpen = false;
bool RightDoorOpen = false;
int CurrentSongNum = 0; //First of 5 Custom Song MP3 Files stats at zero, the first increment will make it 1.
int CustomSongMax = 8; //Total Number of Custom Songs
//Eebel END

#define SHADOW_DEBUG        // uncomment this for console DEBUG output
#define SHADOW_VERBOSE      // uncomment this for console VERBOSE output
#define MRBADDELEY          // setup marcduino eeprom for MrBaddeley printed droid

// ---------------------------------------------------------------------------------------
//                          MarcDuino Button Settings
// ---------------------------------------------------------------------------------------
// Std MarcDuino Function Codes:
//     1 = Close All Panels
//     2 = Scream - all panels open
//     3 = Wave, One Panel at a time
//     4 = Fast (smirk) back and forth wave
//     5 = Wave 2, Open progressively all panels, then close one by one
//     6 = Beep cantina - w/ marching ants panel action
//     7 = Faint / Short Circuit
//     8 = Cantina Dance - orchestral, rhythmic panel dance
//     9 = Leia message
//    10 = Disco
//    11 = Quite mode reset (panel close, stop holos, stop sounds)
//    12 = Full Awake mode reset (panel close, rnd sound, holo move,holo lights off)
//    13 = Mid Awake mode reset (panel close, rnd sound, stop holos)
//    14 = Full Awake+ reset (panel close, rnd sound, holo move, holo lights on)
//    15 = Scream, with all panels open (NO SOUND)
//    16 = Wave, one panel at a time (NO SOUND)
//    17 = Fast (smirk) back and forth (NO SOUND)
//    18 = Wave 2 (Open progressively, then close one by one) (NO SOUND)
//    19 = Marching Ants (NO SOUND)
//    20 = Faint/Short Circuit (NO SOUND)
//    21 = Rhythmic cantina dance (NO SOUND)
//    22 = Random Holo Movement On (All) - No other actions
//    23 = Holo Lights On (All)
//    24 = Holo Lights Off (All)
//    25 = Holo reset (motion off, lights off)
//    26 = Volume Up
//    27 = Volume Down
//    28 = Volume Max
//    29 = Volume Mid
//    30 = Open All Dome Panels
//    31 = Open Top Dome Panels
//    32 = Open Bottom Dome Panels
//    33 = Close All Dome Panels
//    34 = Open Dome Panel #1
//    35 = Close Dome Panel #1
//    36 = Open Dome Panel #2
//    37 = Close Dome Panel #2
//    38 = Open Dome Panel #3
//    39 = Close Dome Panel #3
//    40 = Open Dome Panel #4
//    41 = Close Dome Panel #4
//    42 = Open Dome Panel #5
//    43 = Close Dome Panel #5
//    44 = Open Dome Panel #6
//    45 = Close Dome Panel #6
//    46 = Open Dome Panel #7
//    47 = Close Dome Panel #7
//    48 = Open Dome Panel #8
//    49 = Close Dome Panel #8
//    50 = Open Dome Panel #9
//    51 = Close Dome Panel #9
//    52 = Open Dome Panel #10
//    53 = Close Dome Panel #10
//   *** BODY PANEL OPTIONS ASSUME SECOND MARCDUINO MASTER BOARD ON MEGA ADK SERIAL #3 ***
//    54 = Open All Body Panels
//    55 = Close All Body Panels
//    56 = Open Body Panel #1
//    57 = Close Body Panel #1
//    58 = Open Body Panel #2
//    59 = Close Body Panel #2
//    60 = Open Body Panel #3
//    61 = Close Body Panel #3
//    62 = Open Body Panel #4
//    63 = Close Body Panel #4
//    64 = Open Body Panel #5
//    65 = Close Body Panel #5
//    66 = Open Body Panel #6
//    67 = Close Body Panel #6
//    68 = Open Body Panel #7
//    69 = Close Body Panel #7
//    70 = Open Body Panel #8
//    71 = Close Body Panel #8
//    72 = Open Body Panel #9
//    73 = Close Body Panel #9
//    74 = Open Body Panel #10
//    75 = Close Body Panel #10
//   *** MAGIC PANEL LIGHTING COMMANDS
//    76 = Magic Panel ON
//    77 = Magic Panel OFF
//    78 = Magic Panel Flicker (10 seconds)
//   ***  Tim Ebel addons
//    79 = Eebel Sppok Wave Dome and body
//    80 = Eebel Wave Bye and WaveByeSound
//    81 = Eebel Utility Arms Open and then Close
//    82 = Eebel Open all Body Doors, raise arms, operate tools, lower arms close all doors
//    83 = Eebel Use Gripper
//    84 = Eebel Use INterface Tool
//    85 = Eebel Ping Pong Body Doors
//    86 = Eebel Star Wars Disco Dance
//    87 = Eebel Star Trek Disco Dance (Wrong franchise! I know, right?)
//    88 = Eebel Play Next Song
//    89 = Eebel Play Previous Song
//
// Std MarcDuino Logic Display Functions (For custom functions)
//     1 = Display normal random sequence
//     2 = Short circuit (10 second display sequence)
//     3 = Scream (flashing light display sequence)
//     4 = Leia (34 second light sequence)
//     5 = Display “Star Wars”
//     6 = March light sequence
//     7 = Spectrum, bar graph display sequence
//     8 = Display custom text
//
// Std MarcDuino Panel Functions (For custom functions)
//     1 = Panels stay closed (normal position)
//     2 = Scream sequence, all panels open
//     3 = Wave panel sequence
//     4 = Fast (smirk) back and forth panel sequence
//     5 = Wave 2 panel sequence, open progressively all panels, then close one by one)
//     6 = Marching ants panel sequence
//     7 = Faint / short circuit panel sequence
//     8 = Rhythmic cantina panel sequence
//     9 = Custom Panel Sequence


//----------------------------------------------------
// CONFIGURE: The FOOT Navigation Controller Buttons
//----------------------------------------------------

//---------------------------------
// CONFIGURE: Arrow Up
//---------------------------------
//1 = Std MarcDuino Function, 2 = Custom Function
int btnUP_type = 1;    

// IF Std MarcDuino Function (type=1) 
// Enter MarcDuino Function Code (1 - 78) (See Above)
//Eebel START
//int btnUP_MD_func = 12; //Full Awake/Holo Lights Off 
int btnUP_MD_func = 80; //Wave Bye 
//Eebel END

// IF Custom Function (type=2)
// CUSTOM SOUND SETTING: Enter the file # prefix on the MP3 trigger card of the sound to play (0 = NO SOUND)
// Valid values: 0 or 182 - 200  
int btnUP_cust_MP3_num = 0;  

// CUSTOM LOGIC DISPLAY SETTING: Pick from the Std MD Logic Display Functions (See Above)
// Valid values: 0, 1 to 8  (0 - Not used)
int btnUP_cust_LD_type = 0;

// IF Custom Logic Display = 8 (custom text), enter custom display text here
String btnUP_cust_LD_text = "";

// CUSTOM PANEL SETTING: Pick from the Std MD Panel Functions or Custom (See Above)
// Valid Values: 0, 1 to 9 (0 = Not used)
int btnUP_cust_panel = 0;

// IF Custom Panel Setting = 9 (custom panel sequence)
// Dome Panel #1
boolean btnUP_use_DP1 = false;
int btnUP_DP1_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_DP1_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #2
boolean btnUP_use_DP2 = false;
int btnUP_DP2_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_DP2_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #3
boolean btnUP_use_DP3 = false;
int btnUP_DP3_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_DP3_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #4
boolean btnUP_use_DP4 = false;
int btnUP_DP4_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_DP4_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #5
boolean btnUP_use_DP5 = false;
int btnUP_DP5_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_DP5_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #6
boolean btnUP_use_DP6 = false;
int btnUP_DP6_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_DP6_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #7
boolean btnUP_use_DP7 = false;
int btnUP_DP7_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_DP7_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #8
boolean btnUP_use_DP8 = false;
int btnUP_DP8_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_DP8_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #9
boolean btnUP_use_DP9 = false;
int btnUP_DP9_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_DP9_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #10
boolean btnUP_use_DP10 = false;
int btnUP_DP10_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_DP10_stay_open_time = 5; // in seconds (1 to 30)

//---------------------------------
// CONFIGURE: Arrow Left
//---------------------------------
//1 = Std MarcDuino Function, 2 = Custom Function
int btnLeft_type = 1;    

// IF Std MarcDuino Function (type=1) 
// Enter MarcDuino Function Code (1 - 78) (See Above)
// Mid Awake
int btnLeft_MD_func = 13;

// IF Custom Function (type=2)
// CUSTOM SOUND SETTING: Enter the file # prefix on the MP3 trigger card of the sound to play (0 = NO SOUND)
// Valid values: 0 or 182 - 200  
int btnLeft_cust_MP3_num = 0;  

// CUSTOM LOGIC DISPLAY SETTING: Pick from the Std MD Logic Display Functions (See Above)
// Valid values: 0, 1 to 8  (0 - Not used)
int btnLeft_cust_LD_type = 0;

// IF Custom Logic Display = 8 (custom text), enter custom display text here
String btnLeft_cust_LD_text = "";

// CUSTOM PANEL SETTING: Pick from the Std MD Panel Functions or Custom (See Above)
// Valid Values: 0, 1 to 9 (0 = Not used)
int btnLeft_cust_panel = 0;

// IF Custom Panel Setting = 9 (custom panel sequence)
// Dome Panel #1
boolean btnLeft_use_DP1 = false;
int btnLeft_DP1_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_DP1_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #2
boolean btnLeft_use_DP2 = false;
int btnLeft_DP2_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_DP2_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #3
boolean btnLeft_use_DP3 = false;
int btnLeft_DP3_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_DP3_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #4
boolean btnLeft_use_DP4 = false;
int btnLeft_DP4_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_DP4_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #5
boolean btnLeft_use_DP5 = false;
int btnLeft_DP5_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_DP5_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #6
boolean btnLeft_use_DP6 = false;
int btnLeft_DP6_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_DP6_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #7
boolean btnLeft_use_DP7 = false;
int btnLeft_DP7_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_DP7_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #8
boolean btnLeft_use_DP8 = false;
int btnLeft_DP8_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_DP8_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #9
boolean btnLeft_use_DP9 = false;
int btnLeft_DP9_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_DP9_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #10
boolean btnLeft_use_DP10 = false;
int btnLeft_DP10_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_DP10_stay_open_time = 5; // in seconds (1 to 30)

//---------------------------------
// CONFIGURE: Arrow Right
//---------------------------------
//1 = Std MarcDuino Function, 2 = Custom Function
int btnRight_type = 1;    

// IF Std MarcDuino Function (type=1) 
// Enter MarcDuino Function Code (1 - 78) (See Above)
// Full Awake + reset
int btnRight_MD_func = 14;

// IF Custom Function (type=2)
// CUSTOM SOUND SETTING: Enter the file # prefix on the MP3 trigger card of the sound to play (0 = NO SOUND)
// Valid values: 0 or 182 - 200  
int btnRight_cust_MP3_num = 0;  

// CUSTOM LOGIC DISPLAY SETTING: Pick from the Std MD Logic Display Functions (See Above)
// Valid values: 0, 1 to 8  (0 - Not used)
int btnRight_cust_LD_type = 0;

// IF Custom Logic Display = 8 (custom text), enter custom display text here
String btnRight_cust_LD_text = "";

// CUSTOM PANEL SETTING: Pick from the Std MD Panel Functions or Custom (See Above)
// Valid Values: 0, 1 to 9 (0 = Not used)
int btnRight_cust_panel = 0;

// IF Custom Panel Setting = 9 (custom panel sequence)
// Dome Panel #1
boolean btnRight_use_DP1 = false;
int btnRight_DP1_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_DP1_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #2
boolean btnRight_use_DP2 = false;
int btnRight_DP2_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_DP2_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #3
boolean btnRight_use_DP3 = false;
int btnRight_DP3_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_DP3_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #4
boolean btnRight_use_DP4 = false;
int btnRight_DP4_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_DP4_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #5
boolean btnRight_use_DP5 = false;
int btnRight_DP5_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_DP5_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #6
boolean btnRight_use_DP6 = false;
int btnRight_DP6_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_DP6_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #7
boolean btnRight_use_DP7 = false;
int btnRight_DP7_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_DP7_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #8
boolean btnRight_use_DP8 = false;
int btnRight_DP8_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_DP8_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #9
boolean btnRight_use_DP9 = false;
int btnRight_DP9_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_DP9_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #10
boolean btnRight_use_DP10 = false;
int btnRight_DP10_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_DP10_stay_open_time = 5; // in seconds (1 to 30)

//---------------------------------
// CONFIGURE: Arrow Down
//---------------------------------
//1 = Std MarcDuino Function, 2 = Custom Function
int btnDown_type = 1;    

// IF Std MarcDuino Function (type=1) 
// Enter MarcDuino Function Code (1 - 78) (See Above)
//Quiet mode + reset
int btnDown_MD_func = 11;

// IF Custom Function (type=2)
// CUSTOM SOUND SETTING: Enter the file # prefix on the MP3 trigger card of the sound to play (0 = NO SOUND)
// Valid values: 0 or 182 - 200  
int btnDown_cust_MP3_num = 0;  

// CUSTOM LOGIC DISPLAY SETTING: Pick from the Std MD Logic Display Functions (See Above)
// Valid values: 0, 1 to 8  (0 - Not used)
int btnDown_cust_LD_type = 0;

// IF Custom Logic Display = 8 (custom text), enter custom display text here
String btnDown_cust_LD_text = "";

// CUSTOM PANEL SETTING: Pick from the Std MD Panel Functions or Custom (See Above)
// Valid Values: 0, 1 to 9 (0 = Not used)
int btnDown_cust_panel = 0;

// IF Custom Panel Setting = 9 (custom panel sequence)
// Dome Panel #1
boolean btnDown_use_DP1 = false;
int btnDown_DP1_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_DP1_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #2
boolean btnDown_use_DP2 = false;
int btnDown_DP2_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_DP2_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #3
boolean btnDown_use_DP3 = false;
int btnDown_DP3_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_DP3_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #4
boolean btnDown_use_DP4 = false;
int btnDown_DP4_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_DP4_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #5
boolean btnDown_use_DP5 = false;
int btnDown_DP5_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_DP5_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #6
boolean btnDown_use_DP6 = false;
int btnDown_DP6_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_DP6_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #7
boolean btnDown_use_DP7 = false;
int btnDown_DP7_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_DP7_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #8
boolean btnDown_use_DP8 = false;
int btnDown_DP8_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_DP8_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #9
boolean btnDown_use_DP9 = false;
int btnDown_DP9_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_DP9_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #10
boolean btnDown_use_DP10 = false;
int btnDown_DP10_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_DP10_stay_open_time = 5; // in seconds (1 to 30)

//---------------------------------
// CONFIGURE: Arrow UP + CROSS
//---------------------------------
//1 = Std MarcDuino Function, 2 = Custom Function
int btnUP_CROSS_type = 1;    

// IF Std MarcDuino Function (type=1) 
// Enter MarcDuino Function Code (1 - 78) (See Above)
// Volume Up
int btnUP_CROSS_MD_func = 26;

// IF Custom Function (type=2)
// CUSTOM SOUND SETTING: Enter the file # prefix on the MP3 trigger card of the sound to play (0 = NO SOUND)
// Valid values: 0 or 182 - 200  
int btnUP_CROSS_cust_MP3_num = 0;  

// CUSTOM LOGIC DISPLAY SETTING: Pick from the Std MD Logic Display Functions (See Above)
// Valid values: 0, 1 to 8  (0 - Not used)
int btnUP_CROSS_cust_LD_type = 0;

// IF Custom Logic Display = 8 (custom text), enter custom display text here
String btnUP_CROSS_cust_LD_text = "";

// CUSTOM PANEL SETTING: Pick from the Std MD Panel Functions or Custom (See Above)
// Valid Values: 0, 1 to 9 (0 = Not used)
int btnUP_CROSS_cust_panel = 0;

// IF Custom Panel Setting = 9 (custom panel sequence)
// Dome Panel #1
boolean btnUP_CROSS_use_DP1 = false;
int btnUP_CROSS_DP1_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_CROSS_DP1_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #2
boolean btnUP_CROSS_use_DP2 = false;
int btnUP_CROSS_DP2_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_CROSS_DP2_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #3
boolean btnUP_CROSS_use_DP3 = false;
int btnUP_CROSS_DP3_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_CROSS_DP3_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #4
boolean btnUP_CROSS_use_DP4 = false;
int btnUP_CROSS_DP4_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_CROSS_DP4_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #5
boolean btnUP_CROSS_use_DP5 = false;
int btnUP_CROSS_DP5_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_CROSS_DP5_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #6
boolean btnUP_CROSS_use_DP6 = false;
int btnUP_CROSS_DP6_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_CROSS_DP6_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #7
boolean btnUP_CROSS_use_DP7 = false;
int btnUP_CROSS_DP7_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_CROSS_DP7_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #8
boolean btnUP_CROSS_use_DP8 = false;
int btnUP_CROSS_DP8_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_CROSS_DP8_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #9
boolean btnUP_CROSS_use_DP9 = false;
int btnUP_CROSS_DP9_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_CROSS_DP9_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #10
boolean btnUP_CROSS_use_DP10 = false;
int btnUP_CROSS_DP10_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_CROSS_DP10_stay_open_time = 5; // in seconds (1 to 30)

//---------------------------------
// CONFIGURE: Arrow Left + CROSS
//---------------------------------
//1 = Std MarcDuino Function, 2 = Custom Function
int btnLeft_CROSS_type = 1;    

// IF Std MarcDuino Function (type=1) 
// Enter MarcDuino Function Code (1 - 78) (See Above)
// Holo toggle
int btnLeft_CROSS_MD_func = 23;

// IF Custom Function (type=2)
// CUSTOM SOUND SETTING: Enter the file # prefix on the MP3 trigger card of the sound to play (0 = NO SOUND)
// Valid values: 0 or 182 - 200  
int btnLeft_CROSS_cust_MP3_num = 0;  

// CUSTOM LOGIC DISPLAY SETTING: Pick from the Std MD Logic Display Functions (See Above)
// Valid values: 0, 1 to 8  (0 - Not used)
int btnLeft_CROSS_cust_LD_type = 0;

// IF Custom Logic Display = 8 (custom text), enter custom display text here
String btnLeft_CROSS_cust_LD_text = "";

// CUSTOM PANEL SETTING: Pick from the Std MD Panel Functions or Custom (See Above)
// Valid Values: 0, 1 to 9 (0 = Not used)
int btnLeft_CROSS_cust_panel = 0;

// IF Custom Panel Setting = 9 (custom panel sequence)
// Dome Panel #1
boolean btnLeft_CROSS_use_DP1 = false;
int btnLeft_CROSS_DP1_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_CROSS_DP1_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #2
boolean btnLeft_CROSS_use_DP2 = false;
int btnLeft_CROSS_DP2_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_CROSS_DP2_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #3
boolean btnLeft_CROSS_use_DP3 = false;
int btnLeft_CROSS_DP3_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_CROSS_DP3_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #4
boolean btnLeft_CROSS_use_DP4 = false;
int btnLeft_CROSS_DP4_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_CROSS_DP4_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #5
boolean btnLeft_CROSS_use_DP5 = false;
int btnLeft_CROSS_DP5_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_CROSS_DP5_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #6
boolean btnLeft_CROSS_use_DP6 = false;
int btnLeft_CROSS_DP6_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_CROSS_DP6_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #7
boolean btnLeft_CROSS_use_DP7 = false;
int btnLeft_CROSS_DP7_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_CROSS_DP7_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #8
boolean btnLeft_CROSS_use_DP8 = false;
int btnLeft_CROSS_DP8_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_CROSS_DP8_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #9
boolean btnLeft_CROSS_use_DP9 = false;
int btnLeft_CROSS_DP9_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_CROSS_DP9_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #10
boolean btnLeft_CROSS_use_DP10 = false;
int btnLeft_CROSS_DP10_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_CROSS_DP10_stay_open_time = 5; // in seconds (1 to 30)

//---------------------------------
// CONFIGURE: Arrow Right + CROSS
//---------------------------------
//1 = Std MarcDuino Function, 2 = Custom Function
int btnRight_CROSS_type = 1;    

// IF Std MarcDuino Function (type=1) 
// Enter MarcDuino Function Code (1 - 78) (See Above)
// Random Holo Movement
int btnRight_CROSS_MD_func = 22;//was 24 Turn Holos Off

// IF Custom Function (type=2)
// CUSTOM SOUND SETTING: Enter the file # prefix on the MP3 trigger card of the sound to play (0 = NO SOUND)
// Valid values: 0 or 182 - 200  
int btnRight_CROSS_cust_MP3_num = 0;  

// CUSTOM LOGIC DISPLAY SETTING: Pick from the Std MD Logic Display Functions (See Above)
// Valid values: 0, 1 to 8  (0 - Not used)
int btnRight_CROSS_cust_LD_type = 0;

// IF Custom Logic Display = 8 (custom text), enter custom display text here
String btnRight_CROSS_cust_LD_text = "";

// CUSTOM PANEL SETTING: Pick from the Std MD Panel Functions or Custom (See Above)
// Valid Values: 0, 1 to 9 (0 = Not used)
int btnRight_CROSS_cust_panel = 0;

// IF Custom Panel Setting = 9 (custom panel sequence)
// Dome Panel #1
boolean btnRight_CROSS_use_DP1 = false;
int btnRight_CROSS_DP1_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_CROSS_DP1_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #2
boolean btnRight_CROSS_use_DP2 = false;
int btnRight_CROSS_DP2_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_CROSS_DP2_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #3
boolean btnRight_CROSS_use_DP3 = false;
int btnRight_CROSS_DP3_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_CROSS_DP3_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #4
boolean btnRight_CROSS_use_DP4 = false;
int btnRight_CROSS_DP4_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_CROSS_DP4_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #5
boolean btnRight_CROSS_use_DP5 = false;
int btnRight_CROSS_DP5_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_CROSS_DP5_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #6
boolean btnRight_CROSS_use_DP6 = false;
int btnRight_CROSS_DP6_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_CROSS_DP6_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #7
boolean btnRight_CROSS_use_DP7 = false;
int btnRight_CROSS_DP7_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_CROSS_DP7_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #8
boolean btnRight_CROSS_use_DP8 = false;
int btnRight_CROSS_DP8_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_CROSS_DP8_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #9
boolean btnRight_CROSS_use_DP9 = false;
int btnRight_CROSS_DP9_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_CROSS_DP9_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #10
boolean btnRight_CROSS_use_DP10 = false;
int btnRight_CROSS_DP10_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_CROSS_DP10_stay_open_time = 5; // in seconds (1 to 30)

//---------------------------------
// CONFIGURE: Arrow Down + CROSS
//---------------------------------
//1 = Std MarcDuino Function, 2 = Custom Function
int btnDown_CROSS_type = 1;    

// IF Std MarcDuino Function (type=1) 
// Enter MarcDuino Function Code (1 - 78) (See Above)
// Volume Down
int btnDown_CROSS_MD_func = 27;

// IF Custom Function (type=2)
// CUSTOM SOUND SETTING: Enter the file # prefix on the MP3 trigger card of the sound to play (0 = NO SOUND)
// Valid values: 0 or 182 - 200  
int btnDown_CROSS_cust_MP3_num = 0;  

// CUSTOM LOGIC DISPLAY SETTING: Pick from the Std MD Logic Display Functions (See Above)
// Valid values: 0, 1 to 8  (0 - Not used)
int btnDown_CROSS_cust_LD_type = 0;

// IF Custom Logic Display = 8 (custom text), enter custom display text here
String btnDown_CROSS_cust_LD_text = "";

// CUSTOM PANEL SETTING: Pick from the Std MD Panel Functions or Custom (See Above)
// Valid Values: 0, 1 to 9 (0 = Not used)
int btnDown_CROSS_cust_panel = 0;

// IF Custom Panel Setting = 9 (custom panel sequence)
// Dome Panel #1
boolean btnDown_CROSS_use_DP1 = false;
int btnDown_CROSS_DP1_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_CROSS_DP1_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #2
boolean btnDown_CROSS_use_DP2 = false;
int btnDown_CROSS_DP2_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_CROSS_DP2_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #3
boolean btnDown_CROSS_use_DP3 = false;
int btnDown_CROSS_DP3_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_CROSS_DP3_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #4
boolean btnDown_CROSS_use_DP4 = false;
int btnDown_CROSS_DP4_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_CROSS_DP4_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #5
boolean btnDown_CROSS_use_DP5 = false;
int btnDown_CROSS_DP5_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_CROSS_DP5_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #6
boolean btnDown_CROSS_use_DP6 = false;
int btnDown_CROSS_DP6_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_CROSS_DP6_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #7
boolean btnDown_CROSS_use_DP7 = false;
int btnDown_CROSS_DP7_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_CROSS_DP7_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #8
boolean btnDown_CROSS_use_DP8 = false;
int btnDown_CROSS_DP8_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_CROSS_DP8_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #9
boolean btnDown_CROSS_use_DP9 = false;
int btnDown_CROSS_DP9_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_CROSS_DP9_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #10
boolean btnDown_CROSS_use_DP10 = false;
int btnDown_CROSS_DP10_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_CROSS_DP10_stay_open_time = 5; // in seconds (1 to 30)

//---------------------------------
// CONFIGURE: Arrow UP + CIRCLE
//---------------------------------
//1 = Std MarcDuino Function, 2 = Custom Function
int btnUP_CIRCLE_type = 1;    

// IF Std MarcDuino Function (type=1) 
// Enter MarcDuino Function Code (1 - 78) (See Above)
//int btnUP_CIRCLE_MD_func = 2;
// Wave One at a time NO SOUND
int btnUP_CIRCLE_MD_func = 16; 



// IF Custom Function (type=2)
// CUSTOM SOUND SETTING: Enter the file # prefix on the MP3 trigger card of the sound to play (0 = NO SOUND)
// Valid values: 0 or 182 - 200  
int btnUP_CIRCLE_cust_MP3_num = 0;  

// CUSTOM LOGIC DISPLAY SETTING: Pick from the Std MD Logic Display Functions (See Above)
// Valid values: 0, 1 to 8  (0 - Not used)
int btnUP_CIRCLE_cust_LD_type = 0;

// IF Custom Logic Display = 8 (custom text), enter custom display text here
String btnUP_CIRCLE_cust_LD_text = "";

// CUSTOM PANEL SETTING: Pick from the Std MD Panel Functions or Custom (See Above)
// Valid Values: 0, 1 to 9 (0 = Not used)
int btnUP_CIRCLE_cust_panel = 0;

// IF Custom Panel Setting = 9 (custom panel sequence)
// Dome Panel #1
boolean btnUP_CIRCLE_use_DP1 = false;
int btnUP_CIRCLE_DP1_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_CIRCLE_DP1_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #2
boolean btnUP_CIRCLE_use_DP2 = false;
int btnUP_CIRCLE_DP2_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_CIRCLE_DP2_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #3
boolean btnUP_CIRCLE_use_DP3 = false;
int btnUP_CIRCLE_DP3_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_CIRCLE_DP3_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #4
boolean btnUP_CIRCLE_use_DP4 = false;
int btnUP_CIRCLE_DP4_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_CIRCLE_DP4_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #5
boolean btnUP_CIRCLE_use_DP5 = false;
int btnUP_CIRCLE_DP5_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_CIRCLE_DP5_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #6
boolean btnUP_CIRCLE_use_DP6 = false;
int btnUP_CIRCLE_DP6_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_CIRCLE_DP6_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #7
boolean btnUP_CIRCLE_use_DP7 = false;
int btnUP_CIRCLE_DP7_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_CIRCLE_DP7_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #8
boolean btnUP_CIRCLE_use_DP8 = false;
int btnUP_CIRCLE_DP8_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_CIRCLE_DP8_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #9
boolean btnUP_CIRCLE_use_DP9 = false;
int btnUP_CIRCLE_DP9_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_CIRCLE_DP9_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #10
boolean btnUP_CIRCLE_use_DP10 = false;
int btnUP_CIRCLE_DP10_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_CIRCLE_DP10_stay_open_time = 5; // in seconds (1 to 30)

//---------------------------------
// CONFIGURE: Arrow Left + CIRCLE
//---------------------------------
//1 = Std MarcDuino Function, 2 = Custom Function
int btnLeft_CIRCLE_type = 1;    

// IF Std MarcDuino Function (type=1) 
// Enter MarcDuino Function Code (1 - 78) (See Above)
// Smirk Wave NO SOUND
int btnLeft_CIRCLE_MD_func = 17;

// IF Custom Function (type=2)
// CUSTOM SOUND SETTING: Enter the file # prefix on the MP3 trigger card of the sound to play (0 = NO SOUND)
// Valid values: 0 or 182 - 200  
int btnLeft_CIRCLE_cust_MP3_num = 0;  

// CUSTOM LOGIC DISPLAY SETTING: Pick from the Std MD Logic Display Functions (See Above)
// Valid values: 0, 1 to 8  (0 - Not used)
int btnLeft_CIRCLE_cust_LD_type = 0;

// IF Custom Logic Display = 8 (custom text), enter custom display text here
String btnLeft_CIRCLE_cust_LD_text = "";

// CUSTOM PANEL SETTING: Pick from the Std MD Panel Functions or Custom (See Above)
// Valid Values: 0, 1 to 9 (0 = Not used)
int btnLeft_CIRCLE_cust_panel = 0;

// IF Custom Panel Setting = 9 (custom panel sequence)
// Dome Panel #1
boolean btnLeft_CIRCLE_use_DP1 = false;
int btnLeft_CIRCLE_DP1_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_CIRCLE_DP1_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #2
boolean btnLeft_CIRCLE_use_DP2 = false;
int btnLeft_CIRCLE_DP2_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_CIRCLE_DP2_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #3
boolean btnLeft_CIRCLE_use_DP3 = false;
int btnLeft_CIRCLE_DP3_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_CIRCLE_DP3_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #4
boolean btnLeft_CIRCLE_use_DP4 = false;
int btnLeft_CIRCLE_DP4_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_CIRCLE_DP4_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #5
boolean btnLeft_CIRCLE_use_DP5 = false;
int btnLeft_CIRCLE_DP5_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_CIRCLE_DP5_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #6
boolean btnLeft_CIRCLE_use_DP6 = false;
int btnLeft_CIRCLE_DP6_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_CIRCLE_DP6_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #7
boolean btnLeft_CIRCLE_use_DP7 = false;
int btnLeft_CIRCLE_DP7_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_CIRCLE_DP7_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #8
boolean btnLeft_CIRCLE_use_DP8 = false;
int btnLeft_CIRCLE_DP8_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_CIRCLE_DP8_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #9
boolean btnLeft_CIRCLE_use_DP9 = false;
int btnLeft_CIRCLE_DP9_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_CIRCLE_DP9_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #10
boolean btnLeft_CIRCLE_use_DP10 = false;
int btnLeft_CIRCLE_DP10_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_CIRCLE_DP10_stay_open_time = 5; // in seconds (1 to 30)

//---------------------------------
// CONFIGURE: Arrow Right + CIRCLE
//---------------------------------
//1 = Std MarcDuino Function, 2 = Custom Function
int btnRight_CIRCLE_type = 1;    

// IF Std MarcDuino Function (type=1) 
// Enter MarcDuino Function Code (1 - 78) (See Above)
//Marching Ants NO SOUND
int btnRight_CIRCLE_MD_func = 19;

// IF Custom Function (type=2)
// CUSTOM SOUND SETTING: Enter the file # prefix on the MP3 trigger card of the sound to play (0 = NO SOUND)
// Valid values: 0 or 182 - 200  
int btnRight_CIRCLE_cust_MP3_num = 0;  

// CUSTOM LOGIC DISPLAY SETTING: Pick from the Std MD Logic Display Functions (See Above)
// Valid values: 0, 1 to 8  (0 - Not used)
int btnRight_CIRCLE_cust_LD_type = 0;

// IF Custom Logic Display = 8 (custom text), enter custom display text here
String btnRight_CIRCLE_cust_LD_text = "";

// CUSTOM PANEL SETTING: Pick from the Std MD Panel Functions or Custom (See Above)
// Valid Values: 0, 1 to 9 (0 = Not used)
int btnRight_CIRCLE_cust_panel = 0;

// IF Custom Panel Setting = 9 (custom panel sequence)
// Dome Panel #1
boolean btnRight_CIRCLE_use_DP1 = false;
int btnRight_CIRCLE_DP1_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_CIRCLE_DP1_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #2
boolean btnRight_CIRCLE_use_DP2 = false;
int btnRight_CIRCLE_DP2_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_CIRCLE_DP2_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #3
boolean btnRight_CIRCLE_use_DP3 = false;
int btnRight_CIRCLE_DP3_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_CIRCLE_DP3_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #4
boolean btnRight_CIRCLE_use_DP4 = false;
int btnRight_CIRCLE_DP4_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_CIRCLE_DP4_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #5
boolean btnRight_CIRCLE_use_DP5 = false;
int btnRight_CIRCLE_DP5_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_CIRCLE_DP5_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #6
boolean btnRight_CIRCLE_use_DP6 = false;
int btnRight_CIRCLE_DP6_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_CIRCLE_DP6_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #7
boolean btnRight_CIRCLE_use_DP7 = false;
int btnRight_CIRCLE_DP7_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_CIRCLE_DP7_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #8
boolean btnRight_CIRCLE_use_DP8 = false;
int btnRight_CIRCLE_DP8_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_CIRCLE_DP8_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #9
boolean btnRight_CIRCLE_use_DP9 = false;
int btnRight_CIRCLE_DP9_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_CIRCLE_DP9_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #10
boolean btnRight_CIRCLE_use_DP10 = false;
int btnRight_CIRCLE_DP10_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_CIRCLE_DP10_stay_open_time = 5; // in seconds (1 to 30)

//---------------------------------
// CONFIGURE: Arrow Down + CIRCLE
//---------------------------------
//1 = Std MarcDuino Function, 2 = Custom Function
int btnDown_CIRCLE_type = 1;    

// IF Std MarcDuino Function (type=1) 
// Enter MarcDuino Function Code (1 - 78) (See Above)
// Cantina Dance NO SOUND
int btnDown_CIRCLE_MD_func = 21;

// IF Custom Function (type=2)
// CUSTOM SOUND SETTING: Enter the file # prefix on the MP3 trigger card of the sound to play (0 = NO SOUND)
// Valid values: 0 or 182 - 200  
int btnDown_CIRCLE_cust_MP3_num = 0;  

// CUSTOM LOGIC DISPLAY SETTING: Pick from the Std MD Logic Display Functions (See Above)
// Valid values: 0, 1 to 8  (0 - Not used)
int btnDown_CIRCLE_cust_LD_type = 0;

// IF Custom Logic Display = 8 (custom text), enter custom display text here
String btnDown_CIRCLE_cust_LD_text = "";

// CUSTOM PANEL SETTING: Pick from the Std MD Panel Functions or Custom (See Above)
// Valid Values: 0, 1 to 9 (0 = Not used)
int btnDown_CIRCLE_cust_panel = 0;

// IF Custom Panel Setting = 9 (custom panel sequence)
// Dome Panel #1
boolean btnDown_CIRCLE_use_DP1 = false;
int btnDown_CIRCLE_DP1_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_CIRCLE_DP1_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #2
boolean btnDown_CIRCLE_use_DP2 = false;
int btnDown_CIRCLE_DP2_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_CIRCLE_DP2_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #3
boolean btnDown_CIRCLE_use_DP3 = false;
int btnDown_CIRCLE_DP3_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_CIRCLE_DP3_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #4
boolean btnDown_CIRCLE_use_DP4 = false;
int btnDown_CIRCLE_DP4_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_CIRCLE_DP4_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #5
boolean btnDown_CIRCLE_use_DP5 = false;
int btnDown_CIRCLE_DP5_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_CIRCLE_DP5_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #6
boolean btnDown_CIRCLE_use_DP6 = false;
int btnDown_CIRCLE_DP6_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_CIRCLE_DP6_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #7
boolean btnDown_CIRCLE_use_DP7 = false;
int btnDown_CIRCLE_DP7_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_CIRCLE_DP7_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #8
boolean btnDown_CIRCLE_use_DP8 = false;
int btnDown_CIRCLE_DP8_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_CIRCLE_DP8_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #9
boolean btnDown_CIRCLE_use_DP9 = false;
int btnDown_CIRCLE_DP9_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_CIRCLE_DP9_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #10
boolean btnDown_CIRCLE_use_DP10 = false;
int btnDown_CIRCLE_DP10_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_CIRCLE_DP10_stay_open_time = 5; // in seconds (1 to 30)

//---------------------------------
// CONFIGURE: Arrow UP + PS
//---------------------------------
//1 = Std MarcDuino Function, 2 = Custom Function
int btnUP_PS_type = 2;    

// IF Std MarcDuino Function (type=1) 
// Enter MarcDuino Function Code (1 - 78) (See Above)
int btnUP_PS_MD_func = 0;

// IF Custom Function (type=2)
// CUSTOM SOUND SETTING: Enter the file # prefix on the MP3 trigger card of the sound to play (0 = NO SOUND)
// Valid values: 0 or 182 - 200  
//Eebel START
//int btnUp_PS_cust_MP3_num = 183;  
int btnUP_PS_cust_MP3_num = 201;  
//Eebel END
// CUSTOM LOGIC DISPLAY SETTING: Pick from the Std MD Logic Display Functions (See Above)
// Valid values: 0, 1 to 8  (0 - Not used)
int btnUP_PS_cust_LD_type = 5;

// IF Custom Logic Display = 8 (custom text), enter custom display text here
String btnUP_PS_cust_LD_text = "";

// CUSTOM PANEL SETTING: Pick from the Std MD Panel Functions or Custom (See Above)
// Valid Values: 0, 1 to 9 (0 = Not used)
int btnUP_PS_cust_panel = 0;

// IF Custom Panel Setting = 9 (custom panel sequence)
// Dome Panel #1
boolean btnUP_PS_use_DP1 = false;
int btnUP_PS_DP1_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_PS_DP1_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #2
boolean btnUP_PS_use_DP2 = false;
int btnUP_PS_DP2_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_PS_DP2_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #3
boolean btnUP_PS_use_DP3 = false;
int btnUP_PS_DP3_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_PS_DP3_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #4
boolean btnUP_PS_use_DP4 = false;
int btnUP_PS_DP4_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_PS_DP4_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #5
boolean btnUP_PS_use_DP5 = false;
int btnUP_PS_DP5_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_PS_DP5_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #6
boolean btnUP_PS_use_DP6 = false;
int btnUP_PS_DP6_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_PS_DP6_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #7
boolean btnUP_PS_use_DP7 = false;
int btnUP_PS_DP7_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_PS_DP7_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #8
boolean btnUP_PS_use_DP8 = false;
int btnUP_PS_DP8_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_PS_DP8_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #9
boolean btnUP_PS_use_DP9 = false;
int btnUP_PS_DP9_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_PS_DP9_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #10
boolean btnUP_PS_use_DP10 = false;
int btnUP_PS_DP10_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_PS_DP10_stay_open_time = 5; // in seconds (1 to 30)

//---------------------------------
// CONFIGURE: Arrow Left + PS
//---------------------------------
//1 = Std MarcDuino Function, 2 = Custom Function
int btnLeft_PS_type = 1;    

// IF Std MarcDuino Function (type=1) 
// Enter MarcDuino Function Code (1 - 78) (See Above)
//Play previous song
int btnLeft_PS_MD_func = 89;

// IF Custom Function (type=2)
// CUSTOM SOUND SETTING: Enter the file # prefix on the MP3 trigger card of the sound to play (0 = NO SOUND)
// Valid values: 0 or 182 - 200  
int btnLeft_PS_cust_MP3_num = 0; //was 186 

// CUSTOM LOGIC DISPLAY SETTING: Pick from the Std MD Logic Display Functions (See Above)
// Valid values: 0, 1 to 8  (0 - Not used)
int btnLeft_PS_cust_LD_type = 1;

// IF Custom Logic Display = 8 (custom text), enter custom display text here
String btnLeft_PS_cust_LD_text = "";

// CUSTOM PANEL SETTING: Pick from the Std MD Panel Functions or Custom (See Above)
// Valid Values: 0, 1 to 9 (0 = Not used)
int btnLeft_PS_cust_panel = 0;

// IF Custom Panel Setting = 9 (custom panel sequence)
// Dome Panel #1
boolean btnLeft_PS_use_DP1 = false;
int btnLeft_PS_DP1_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_PS_DP1_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #2
boolean btnLeft_PS_use_DP2 = false;
int btnLeft_PS_DP2_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_PS_DP2_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #3
boolean btnLeft_PS_use_DP3 = false;
int btnLeft_PS_DP3_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_PS_DP3_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #4
boolean btnLeft_PS_use_DP4 = false;
int btnLeft_PS_DP4_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_PS_DP4_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #5
boolean btnLeft_PS_use_DP5 = false;
int btnLeft_PS_DP5_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_PS_DP5_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #6
boolean btnLeft_PS_use_DP6 = false;
int btnLeft_PS_DP6_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_PS_DP6_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #7
boolean btnLeft_PS_use_DP7 = false;
int btnLeft_PS_DP7_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_PS_DP7_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #8
boolean btnLeft_PS_use_DP8 = false;
int btnLeft_PS_DP8_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_PS_DP8_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #9
boolean btnLeft_PS_use_DP9 = false;
int btnLeft_PS_DP9_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_PS_DP9_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #10
boolean btnLeft_PS_use_DP10 = false;
int btnLeft_PS_DP10_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_PS_DP10_stay_open_time = 5; // in seconds (1 to 30)

//---------------------------------
// CONFIGURE: Arrow Right + PS
//---------------------------------
//1 = Std MarcDuino Function, 2 = Custom Function
int btnRight_PS_type = 1;  //was 2  

// IF Std MarcDuino Function (type=1) 
// Enter MarcDuino Function Code (1 - 78) (See Above)
// Play Next Song
int btnRight_PS_MD_func = 88;//was 0 - Utility Arms Open, then Close

// IF Custom Function (type=2)
// CUSTOM SOUND SETTING: Enter the file # prefix on the MP3 trigger card of the sound to play (0 = NO SOUND)
// Valid values: 0 or 182 - 200  
// Here They Come MP3
int btnRight_PS_cust_MP3_num = 0;//Was 185  

// CUSTOM LOGIC DISPLAY SETTING: Pick from the Std MD Logic Display Functions (See Above)
// Valid values: 0, 1 to 8  (0 - Not used)
int btnRight_PS_cust_LD_type = 1;

// IF Custom Logic Display = 8 (custom text), enter custom display text here
String btnRight_PS_cust_LD_text = "";

// CUSTOM PANEL SETTING: Pick from the Std MD Panel Functions or Custom (See Above)
// Valid Values: 0, 1 to 9 (0 = Not used)
int btnRight_PS_cust_panel = 0;

// IF Custom Panel Setting = 9 (custom panel sequence)
// Dome Panel #1
boolean btnRight_PS_use_DP1 = false;
int btnRight_PS_DP1_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_PS_DP1_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #2
boolean btnRight_PS_use_DP2 = false;
int btnRight_PS_DP2_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_PS_DP2_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #3
boolean btnRight_PS_use_DP3 = false;
int btnRight_PS_DP3_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_PS_DP3_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #4
boolean btnRight_PS_use_DP4 = false;
int btnRight_PS_DP4_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_PS_DP4_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #5
boolean btnRight_PS_use_DP5 = false;
int btnRight_PS_DP5_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_PS_DP5_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #6
boolean btnRight_PS_use_DP6 = false;
int btnRight_PS_DP6_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_PS_DP6_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #7
boolean btnRight_PS_use_DP7 = false;
int btnRight_PS_DP7_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_PS_DP7_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #8
boolean btnRight_PS_use_DP8 = false;
int btnRight_PS_DP8_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_PS_DP8_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #9
boolean btnRight_PS_use_DP9 = false;
int btnRight_PS_DP9_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_PS_DP9_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #10
boolean btnRight_PS_use_DP10 = false;
int btnRight_PS_DP10_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_PS_DP10_stay_open_time = 5; // in seconds (1 to 30)

//---------------------------------
// CONFIGURE: Arrow Down + PS
//---------------------------------
//1 = Std MarcDuino Function, 2 = Custom Function
int btnDown_PS_type = 2;    

// IF Std MarcDuino Function (type=1) 
// Enter MarcDuino Function Code (1 - 78) (See Above)
int btnDown_PS_MD_func = 0;

// IF Custom Function (type=2)
// CUSTOM SOUND SETTING: Enter the file # prefix on the MP3 trigger card of the sound to play (0 = NO SOUND)
// Valid values: 0 or 182 - 200  
// PLay Darth Vader
//int btnDown_PS_cust_MP3_num = 184;  
int btnDown_PS_cust_MP3_num = 202;  
//Eebel END

// CUSTOM LOGIC DISPLAY SETTING: Pick from the Std MD Logic Display Functions (See Above)
// Valid values: 0, 1 to 8  (0 - Not used)
int btnDown_PS_cust_LD_type = 1;

// IF Custom Logic Display = 8 (custom text), enter custom display text here
String btnDown_PS_cust_LD_text = "";

// CUSTOM PANEL SETTING: Pick from the Std MD Panel Functions or Custom (See Above)
// Valid Values: 0, 1 to 9 (0 = Not used)
int btnDown_PS_cust_panel = 0;

// IF Custom Panel Setting = 9 (custom panel sequence)
// Dome Panel #1
boolean btnDown_PS_use_DP1 = false;
int btnDown_PS_DP1_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_PS_DP1_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #2
boolean btnDown_PS_use_DP2 = false;
int btnDown_PS_DP2_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_PS_DP2_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #3
boolean btnDown_PS_use_DP3 = false;
int btnDown_PS_DP3_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_PS_DP3_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #4
boolean btnDown_PS_use_DP4 = false;
int btnDown_PS_DP4_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_PS_DP4_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #5
boolean btnDown_PS_use_DP5 = false;
int btnDown_PS_DP5_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_PS_DP5_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #6
boolean btnDown_PS_use_DP6 = false;
int btnDown_PS_DP6_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_PS_DP6_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #7
boolean btnDown_PS_use_DP7 = false;
int btnDown_PS_DP7_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_PS_DP7_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #8
boolean btnDown_PS_use_DP8 = false;
int btnDown_PS_DP8_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_PS_DP8_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #9
boolean btnDown_PS_use_DP9 = false;
int btnDown_PS_DP9_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_PS_DP9_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #10
boolean btnDown_PS_use_DP10 = false;
int btnDown_PS_DP10_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_PS_DP10_stay_open_time = 5; // in seconds (1 to 30)

//---------------------------------
// CONFIGURE: Arrow Up + L1
//---------------------------------
//1 = Std MarcDuino Function, 2 = Custom Function
int btnUP_L1_type = 2;    

// IF Std MarcDuino Function (type=1) 
// Enter MarcDuino Function Code (1 - 78) (See Above)
// Meco Darth Vader 
int btnUP_L1_MD_func = 184;

// IF Custom Function (type=2)
// CUSTOM SOUND SETTING: Enter the file # prefix on the MP3 trigger card of the sound to play (0 = NO SOUND)
// Valid values: 0 or 182 - 200  
// Meco Darth Vader 
int btnUP_L1_cust_MP3_num = 184;  

// CUSTOM LOGIC DISPLAY SETTING: Pick from the Std MD Logic Display Functions (See Above)
// Valid values: 0, 1 to 8  (0 - Not used)
int btnUP_L1_cust_LD_type = 0;

// IF Custom Logic Display = 8 (custom text), enter custom display text here
String btnUP_L1_cust_LD_text = "";

// CUSTOM PANEL SETTING: Pick from the Std MD Panel Functions or Custom (See Above)
// Valid Values: 0, 1 to 9 (0 = Not used)
int btnUP_L1_cust_panel = 0;

// IF Custom Panel Setting = 9 (custom panel sequence)
// Dome Panel #1
boolean btnUP_L1_use_DP1 = false;
int btnUP_L1_DP1_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_L1_DP1_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #2
boolean btnUP_L1_use_DP2 = false;
int btnUP_L1_DP2_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_L1_DP2_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #3
boolean btnUP_L1_use_DP3 = false;
int btnUP_L1_DP3_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_L1_DP3_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #4
boolean btnUP_L1_use_DP4 = false;
int btnUP_L1_DP4_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_L1_DP4_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #5
boolean btnUP_L1_use_DP5 = false;
int btnUP_L1_DP5_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_L1_DP5_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #6
boolean btnUP_L1_use_DP6 = false;
int btnUP_L1_DP6_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_L1_DP6_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #7
boolean btnUP_L1_use_DP7 = false;
int btnUP_L1_DP7_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_L1_DP7_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #8
boolean btnUP_L1_use_DP8 = false;
int btnUP_L1_DP8_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_L1_DP8_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #9
boolean btnUP_L1_use_DP9 = false;
int btnUP_L1_DP9_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_L1_DP9_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #10
boolean btnUP_L1_use_DP10 = false;
int btnUP_L1_DP10_open_start_delay = 1; // in seconds (0 to 30)
int btnUP_L1_DP10_stay_open_time = 5; // in seconds (1 to 30)

//---------------------------------
// CONFIGURE: Arrow Left + L1
//---------------------------------
//1 = Std MarcDuino Function, 2 = Custom Function
int btnLeft_L1_type = 1;    

// IF Std MarcDuino Function (type=1) 
// Enter MarcDuino Function Code (1 - 78) (See Above)
// Wave Body and dome panels One at a time
int btnLeft_L1_MD_func = 3;

// IF Custom Function (type=2)
// CUSTOM SOUND SETTING: Enter the file # prefix on the MP3 trigger card of the sound to play (0 = NO SOUND)
// Valid values: 0 or 182 - 200  
int btnLeft_L1_cust_MP3_num = 0;  

// CUSTOM LOGIC DISPLAY SETTING: Pick from the Std MD Logic Display Functions (See Above)
// Valid values: 0, 1 to 8  (0 - Not used)
int btnLeft_L1_cust_LD_type = 0;

// IF Custom Logic Display = 8 (custom text), enter custom display text here
String btnLeft_L1_cust_LD_text = "";

// CUSTOM PANEL SETTING: Pick from the Std MD Panel Functions or Custom (See Above)
// Valid Values: 0, 1 to 9 (0 = Not used)
int btnLeft_L1_cust_panel = 0;

// IF Custom Panel Setting = 9 (custom panel sequence)
// Dome Panel #1
boolean btnLeft_L1_use_DP1 = false;
int btnLeft_L1_DP1_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_L1_DP1_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #2
boolean btnLeft_L1_use_DP2 = false;
int btnLeft_L1_DP2_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_L1_DP2_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #3
boolean btnLeft_L1_use_DP3 = false;
int btnLeft_L1_DP3_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_L1_DP3_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #4
boolean btnLeft_L1_use_DP4 = false;
int btnLeft_L1_DP4_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_L1_DP4_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #5
boolean btnLeft_L1_use_DP5 = false;
int btnLeft_L1_DP5_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_L1_DP5_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #6
boolean btnLeft_L1_use_DP6 = false;
int btnLeft_L1_DP6_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_L1_DP6_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #7
boolean btnLeft_L1_use_DP7 = false;
int btnLeft_L1_DP7_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_L1_DP7_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #8
boolean btnLeft_L1_use_DP8 = false;
int btnLeft_L1_DP8_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_L1_DP8_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #9
boolean btnLeft_L1_use_DP9 = false;
int btnLeft_L1_DP9_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_L1_DP9_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #10
boolean btnLeft_L1_use_DP10 = false;
int btnLeft_L1_DP10_open_start_delay = 1; // in seconds (0 to 30)
int btnLeft_L1_DP10_stay_open_time = 5; // in seconds (1 to 30)

//---------------------------------
// CONFIGURE: Arrow Right + L1
//---------------------------------
//1 = Std MarcDuino Function, 2 = Custom Function
int btnRight_L1_type = 1;    

// IF Std MarcDuino Function (type=1) 
// Enter MarcDuino Function Code (1 - 78) (See Above)
int btnRight_L1_MD_func = 5;

// IF Custom Function (type=2)
// CUSTOM SOUND SETTING: Enter the file # prefix on the MP3 trigger card of the sound to play (0 = NO SOUND)
// Valid values: 0 or 182 - 200  
int btnRight_L1_cust_MP3_num = 0;  

// CUSTOM LOGIC DISPLAY SETTING: Pick from the Std MD Logic Display Functions (See Above)
// Valid values: 0, 1 to 8  (0 - Not used)
int btnRight_L1_cust_LD_type = 0;

// IF Custom Logic Display = 8 (custom text), enter custom display text here
String btnRight_L1_cust_LD_text = "";

// CUSTOM PANEL SETTING: Pick from the Std MD Panel Functions or Custom (See Above)
// Valid Values: 0, 1 to 9 (0 = Not used)
int btnRight_L1_cust_panel = 0;

// IF Custom Panel Setting = 9 (custom panel sequence)
// Dome Panel #1
boolean btnRight_L1_use_DP1 = false;
int btnRight_L1_DP1_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_L1_DP1_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #2
boolean btnRight_L1_use_DP2 = false;
int btnRight_L1_DP2_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_L1_DP2_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #3
boolean btnRight_L1_use_DP3 = false;
int btnRight_L1_DP3_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_L1_DP3_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #4
boolean btnRight_L1_use_DP4 = false;
int btnRight_L1_DP4_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_L1_DP4_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #5
boolean btnRight_L1_use_DP5 = false;
int btnRight_L1_DP5_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_L1_DP5_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #6
boolean btnRight_L1_use_DP6 = false;
int btnRight_L1_DP6_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_L1_DP6_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #7
boolean btnRight_L1_use_DP7 = false;
int btnRight_L1_DP7_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_L1_DP7_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #8
boolean btnRight_L1_use_DP8 = false;
int btnRight_L1_DP8_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_L1_DP8_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #9
boolean btnRight_L1_use_DP9 = false;
int btnRight_L1_DP9_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_L1_DP9_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #10
boolean btnRight_L1_use_DP10 = false;
int btnRight_L1_DP10_open_start_delay = 1; // in seconds (0 to 30)
int btnRight_L1_DP10_stay_open_time = 5; // in seconds (1 to 30)

//---------------------------------
// CONFIGURE: Arrow Down + L1
//---------------------------------
//1 = Std MarcDuino Function, 2 = Custom Function
int btnDown_L1_type = 1;    

// IF Std MarcDuino Function (type=1) 
// Enter MarcDuino Function Code (1 - 78) (See Above)
int btnDown_L1_MD_func = 9;

// IF Custom Function (type=2)
// CUSTOM SOUND SETTING: Enter the file # prefix on the MP3 trigger card of the sound to play (0 = NO SOUND)
// Valid values: 0 or 182 - 200  
int btnDown_L1_cust_MP3_num = 0;  

// CUSTOM LOGIC DISPLAY SETTING: Pick from the Std MD Logic Display Functions (See Above)
// Valid values: 0, 1 to 8  (0 - Not used)
int btnDown_L1_cust_LD_type = 0;

// IF Custom Logic Display = 8 (custom text), enter custom display text here
String btnDown_L1_cust_LD_text = "";

// CUSTOM PANEL SETTING: Pick from the Std MD Panel Functions or Custom (See Above)
// Valid Values: 0, 1 to 9 (0 = Not used)
int btnDown_L1_cust_panel = 0;

// IF Custom Panel Setting = 9 (custom panel sequence)
// Dome Panel #1
boolean btnDown_L1_use_DP1 = false;
int btnDown_L1_DP1_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_L1_DP1_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #2
boolean btnDown_L1_use_DP2 = false;
int btnDown_L1_DP2_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_L1_DP2_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #3
boolean btnDown_L1_use_DP3 = false;
int btnDown_L1_DP3_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_L1_DP3_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #4
boolean btnDown_L1_use_DP4 = false;
int btnDown_L1_DP4_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_L1_DP4_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #5
boolean btnDown_L1_use_DP5 = false;
int btnDown_L1_DP5_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_L1_DP5_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #6
boolean btnDown_L1_use_DP6 = false;
int btnDown_L1_DP6_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_L1_DP6_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #7
boolean btnDown_L1_use_DP7 = false;
int btnDown_L1_DP7_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_L1_DP7_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #8
boolean btnDown_L1_use_DP8 = false;
int btnDown_L1_DP8_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_L1_DP8_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #9
boolean btnDown_L1_use_DP9 = false;
int btnDown_L1_DP9_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_L1_DP9_stay_open_time = 5; // in seconds (1 to 30)
// Dome Panel #10
boolean btnDown_L1_use_DP10 = false;
int btnDown_L1_DP10_open_start_delay = 1; // in seconds (0 to 30)
int btnDown_L1_DP10_stay_open_time = 5; // in seconds (1 to 30)

//----------------------------------------------------
// CONFIGURE: The DOME Navigation Controller Buttons
//----------------------------------------------------

//---------------------------------
// CONFIGURE: Arrow Up
//---------------------------------
// Enter MarcDuino Function Code (1 - 78) (See Above)
// Open Body doors and operate arms and tools, then close
int FTbtnUP_MD_func = 82;  //was 58

//---------------------------------
// CONFIGURE: Arrow Left
//---------------------------------
// Enter MarcDuino Function Code (1 - 78) (See Above)
// Gripper Sequence
    int FTbtnLeft_MD_func = 83;//Open door

//---------------------------------
// CONFIGURE: Arrow Right
//---------------------------------
// Enter MarcDuino Function Code (1 - 78) (See Above)
// Interface Tool Seuence
int FTbtnRight_MD_func = 84; //Was 57

//---------------------------------
// CONFIGURE: Arrow Down
//---------------------------------
// Enter MarcDuino Function Code (1 - 78) (See Above)
//Toggle DPL Door
int FTbtnDown_MD_func = 56;//was 59

//---------------------------------
// CONFIGURE: Arrow UP + CROSS
//---------------------------------
// Enter MarcDuino Function Code (1 - 78) (See Above)
// Faint With Body Panels
int FTbtnUP_CROSS_MD_func = 7;
//int FTbtnUP_CROSS_MD_func = 8;

//---------------------------------
// CONFIGURE: Arrow Left + CROSS
//---------------------------------
// Enter MarcDuino Function Code (1 - 78) (See Above)
// Open Dome and Body Panels
int FTbtnLeft_CROSS_MD_func = 30;//Was close all Dome Panels 33

//---------------------------------
// CONFIGURE: Arrow Right + CROSS
//---------------------------------
// Enter MarcDuino Function Code (1 - 78) (See Above)
// Close all Dome and Body Panels
int FTbtnRight_CROSS_MD_func = 33;//Was Open all Dome 30

//---------------------------------
// CONFIGURE: Arrow Down + CROSS
//---------------------------------
// Enter MarcDuino Function Code (1 - 78) (See Above)
// Scream Wave
int FTbtnDown_CROSS_MD_func = 79;

//---------------------------------
// CONFIGURE: Arrow UP + CIRCLE
//---------------------------------
// Enter MarcDuino Function Code (1 - 78) (See Above)
// Cantina Dance Orchestral
int FTbtnUP_CIRCLE_MD_func = 8;

//---------------------------------
// CONFIGURE: Arrow Left + CIRCLE
//---------------------------------
// Enter MarcDuino Function Code (1 - 78) (See Above)
// Disco Staying Alive
int FTbtnLeft_CIRCLE_MD_func = 10;

//---------------------------------
// CONFIGURE: Arrow Right + CIRCLE
//---------------------------------
// Enter MarcDuino Function Code (1 - 78) (See Above)
// Star Wars Disco
int FTbtnRight_CIRCLE_MD_func = 86;

//---------------------------------
// CONFIGURE: Arrow Down + CIRCLE
//---------------------------------
// Enter MarcDuino Function Code (1 - 78) (See Above)
// Star Trek Disco
int FTbtnDown_CIRCLE_MD_func = 87;

//---------------------------------
// CONFIGURE: Arrow UP + PS
//---------------------------------
// Enter MarcDuino Function Code (1 - 78) (See Above)
// Utility Arms Wiggle
int FTbtnUP_PS_MD_func = 81;

//---------------------------------
// CONFIGURE: Arrow Left + PS
//---------------------------------
// Enter MarcDuino Function Code (1 - 78) (See Above)
// Toggle Top Utility Arm
int FTbtnLeft_PS_MD_func = 58;

//---------------------------------
// CONFIGURE: Arrow Right + PS
//---------------------------------
// Enter MarcDuino Function Code (1 - 78) (See Above)
// Toggle Bottom Utility Arm
int FTbtnRight_PS_MD_func = 60;

//---------------------------------
// CONFIGURE: Arrow Down + PS
//---------------------------------
// Enter MarcDuino Function Code (1 - 78) (See Above)
// Ping Pong Left and Right Bofy Doors
int FTbtnDown_PS_MD_func = 85;

//---------------------------------
// CONFIGURE: Arrow Up + L1
//---------------------------------
// Enter MarcDuino Function Code (1 - 78) (See Above)
// Smirk Wave Fast
int FTbtnUP_L1_MD_func = 4;//was 34

//---------------------------------
// CONFIGURE: Arrow Left + L1
//---------------------------------
// Enter MarcDuino Function Code (1 - 78) (See Above)
//Left Door Toggle
int FTbtnLeft_L1_MD_func = 62; //was 36

//---------------------------------
// CONFIGURE: Arrow Right + L1
//---------------------------------
// Enter MarcDuino Function Code (1 - 78) (See Above)
// Right Door Toggle
int FTbtnRight_L1_MD_func = 68;  //was 37

//---------------------------------
// CONFIGURE: Arrow Down + L1
//---------------------------------
// Enter MarcDuino Function Code (1 - 78) (See Above)
int FTbtnDown_L1_MD_func = 18; //was 35

// ---------------------------------------------------------------------------------------
//               SYSTEM VARIABLES - USER CONFIG SECTION COMPLETED
// ---------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------
//                          Drive Controller Settings
// ---------------------------------------------------------------------------------------

int motorControllerBaudRate = 9600; // Set the baud rate for the Syren motor controller
                                    // for packetized options are: 2400, 9600, 19200 and 38400

int marcDuinoBaudRate = 9600; // Set the baud rate for the Syren motor controller
                                    
#define SYREN_ADDR         129      // Serial Address for Dome Syren
#define SABERTOOTH_ADDR    128      // Serial Address for Foot Sabertooth

#define ENABLE_UHS_DEBUGGING 1

// ---------------------------------------------------------------------------------------
//                          Libraries
// ---------------------------------------------------------------------------------------
#include "src/PS3BT.h"
#include "src/usbhub.h"

// Sabertooth library always included for SyRen dome motor control
#include <Sabertooth.h>
#include <EEPROM.h>
#include <avr/wdt.h>

// Servo library needed for BLDC PPM mode
#if FOOT_CONTROLLER == 1
#include <Servo.h>
#endif

// Free RAM diagnostic - reports bytes between heap and stack
extern unsigned int __heap_start;
extern void *__brkval;
int freeMemory() {
    int v;
    return (int)&v - (__brkval == 0 ? (int)&__heap_start : (int)__brkval);
}

// ---------------------------------------------------------------------------------------
//                    EEPROM Layout for PS3 MAC + Motor-Invert Storage
// ---------------------------------------------------------------------------------------
// EEPROM Map:
//   Byte 0:       Magic signature (0xA5) - indicates EEPROM has been initialized
//   Bytes 1-6:    Slot 0 - Foot Primary MAC (6 bytes)
//   Bytes 7-12:   Slot 1 - Dome Primary MAC (6 bytes)
//   Bytes 13-18:  Slot 2 - Foot Backup MAC (6 bytes)
//   Bytes 19-24:  Slot 3 - Dome Backup MAC (6 bytes)
//   Byte 25:      Motor Invert Left  (0 = normal, 1 = inverted; any other value -> 0)
//   Byte 26:      Motor Invert Right (0 = normal, 1 = inverted; any other value -> 0)
//   Total: 27 bytes used (of 4096 available)

#define EEPROM_MAGIC_BYTE       0xA5
#define EEPROM_MAGIC_ADDR       0
#define EEPROM_MAC_START        1
#define EEPROM_MAC_SIZE         6
#define EEPROM_NUM_SLOTS        4

#define MAC_SLOT_FOOT_PRIMARY   0
#define MAC_SLOT_DOME_PRIMARY   1
#define MAC_SLOT_FOOT_BACKUP    2
#define MAC_SLOT_DOME_BACKUP    3

#define EEPROM_INVERT_LEFT_ADDR   25
#define EEPROM_INVERT_RIGHT_ADDR  26

// ---------------------------------------------------------------------------------------
//                    Panel Management Variables
// ---------------------------------------------------------------------------------------
boolean runningCustRoutine = false;

int DP1_Status = 0;  // 0 = closed, 1 = waiting to open, 2 = open
unsigned long DP1_start = 0;
int DP1_s_delay = 0;
int DP1_o_time = 0;

int DP2_Status = 0;  // 0 = closed, 1 = waiting to open, 2 = open
unsigned long DP2_start = 0;
int DP2_s_delay = 0;
int DP2_o_time = 0;

int DP3_Status = 0;  // 0 = closed, 1 = waiting to open, 2 = open
unsigned long DP3_start = 0;
int DP3_s_delay = 0;
int DP3_o_time = 0;

int DP4_Status = 0;  // 0 = closed, 1 = waiting to open, 2 = open
unsigned long DP4_start = 0;
int DP4_s_delay = 0;
int DP4_o_time = 0;

int DP5_Status = 0;  // 0 = closed, 1 = waiting to open, 2 = open
unsigned long DP5_start = 0;
int DP5_s_delay = 0;
int DP5_o_time = 0;

int DP6_Status = 0;  // 0 = closed, 1 = waiting to open, 2 = open
unsigned long DP6_start = 0;
int DP6_s_delay = 0;
int DP6_o_time = 0;

int DP7_Status = 0;  // 0 = closed, 1 = waiting to open, 2 = open
unsigned long DP7_start = 0;
int DP7_s_delay = 0;
int DP7_o_time = 0;

int DP8_Status = 0;  // 0 = closed, 1 = waiting to open, 2 = open
unsigned long DP8_start = 0;
int DP8_s_delay = 0;
int DP8_o_time = 0;

int DP9_Status = 0;  // 0 = closed, 1 = waiting to open, 2 = open
unsigned long DP9_start = 0;
int DP9_s_delay = 0;
int DP9_o_time = 0;

int DP10_Status = 0;  // 0 = closed, 1 = waiting to open, 2 = open
unsigned long DP10_start = 0;
int DP10_s_delay = 0;
int DP10_o_time = 0;

// ---------------------------------------------------------------------------------------
//                          Variables
// ---------------------------------------------------------------------------------------

long previousDomeMillis = millis();
long previousFootMillis = millis();
long previousMarcDuinoMillis = millis();
long previousDomeToggleMillis = millis();
long previousSpeedToggleMillis = millis();
long currentMillis = millis();

int serialLatency = 25;   //This is a delay factor in ms to prevent queueing of the Serial data.
                          //25ms seems approprate for HardwareSerial, values of 50ms or larger are needed for Softare Emulation
                          
int marcDuinoButtonCounter = 0;
int speedToggleButtonCounter = 0;
int domeToggleButtonCounter = 0;

// Sabertooth foot motor controller - only for mode 0
#if FOOT_CONTROLLER == 0
Sabertooth *ST=new Sabertooth(SABERTOOTH_ADDR, Serial2);
#endif

// SyRen dome motor controller - ALWAYS active
Sabertooth *SyR=new Sabertooth(SYREN_ADDR, Serial2);

// BLDC PPM mode - Servo objects for left/right foot
#if FOOT_CONTROLLER == 1
Servo leftFootSignal;
Servo rightFootSignal;
#endif

///////Setup for USB and Bluetooth Devices////////////////////////////
USB Usb;
BTD Btd(&Usb);
PS3BT *PS3NavFoot=new PS3BT(&Btd);
PS3BT *PS3NavDome=new PS3BT(&Btd);

//Used for PS3 Fault Detection
uint32_t msgLagTime = 0;
uint32_t lastMsgTime = 0;
uint32_t currentTime = 0;
uint32_t lastLoopTime = 0;
int badPS3Data = 0;
int badPS3DataDome = 0;

boolean firstMessage = true;
String output = "";

boolean isFootMotorStopped = true;
boolean isDomeMotorStopped = true;

boolean overSpeedSelected = false;

boolean isPS3NavigatonInitialized = false;
boolean isSecondaryPS3NavigatonInitialized = false;

boolean isStickEnabled = true;

boolean WaitingforReconnect = false;
boolean WaitingforReconnectDome = false;

boolean mainControllerConnected = false;
boolean domeControllerConnected = false;

// Dome Automation Variables
boolean domeAutomation = false;
int domeTurnDirection = 1;  // 1 = positive turn, -1 negative turn
float domeTargetPosition = 0; // (0 - 359) - degrees in a circle, 0 = home
unsigned long domeStopTurnTime = 0;    // millis() when next turn should stop
unsigned long domeStartTurnTime = 0;  // millis() when next turn should start
int domeStatus = 0;  // 0 = stopped, 1 = prepare to turn, 2 = turning

byte action = 0;
unsigned long DriveMillis = 0;

void clearMacText(char* dest) {
  dest[0] = 'X';
  dest[1] = 'X';
  dest[2] = '\0';
}

bool isMacTextUnset(const char* macText) {
  return strcmp(macText, MAC_TEXT_NONE) == 0;
}

void macBytesToString(const byte* mac, char* out) {
  // mac[] is LSB-first (like disc_bdaddr), output MSB-first (like standard MAC format)
  for (int i = 0; i < 6; i++) {
    byte b = mac[5 - i];
    out[i * 3]     = "0123456789ABCDEF"[b >> 4];
    out[i * 3 + 1] = "0123456789ABCDEF"[b & 0x0F];
    if (i < 5) out[i * 3 + 2] = ':';
  }
  out[17] = '\0';
}

int footDriveSpeed = 0;

// BLDC mode variables (used for FOOT_CONTROLLER 1 and 2)
#if FOOT_CONTROLLER == 1 || FOOT_CONTROLLER == 2
int leftFoot, rightFoot;                        // Target foot speed values (-100 to 100)
int prevLeftFoot, prevRightFoot;                 // Previous foot speed values
float LeftSpeed, RightSpeed;                     // Diamond mixing output
int footX, footY;                                // Joystick raw values
int leftFootDriveSpeed = 90;                     // Current ramped left speed (servo midpoint = stop)
int rightFootDriveSpeed = 90;                    // Current ramped right speed (servo midpoint = stop)
int driveSpeed1Internal = 0;                     // Internal-mixing runtime value derived from drivespeed1
int driveSpeed2Internal = 0;                     // Internal-mixing runtime value derived from drivespeed2

int mapDriveSpeedForInternalMixing(int configuredSpeed) {
  configuredSpeed = constrain(configuredSpeed, 0, 127);
  #if FOOT_CONTROLLER == 1
  return map(configuredSpeed, 0, 127, 0, 90);
  #elif FOOT_CONTROLLER == 2
  return map(configuredSpeed, 0, 127, 0, 255);
  #endif
  return 0;
}
#endif

// ---------------------------------------------------------------------------------------
//                    Serial CLI & Pairing Mode Variables
// ---------------------------------------------------------------------------------------
#define CLI_BUFFER_SIZE 16
char cliBuffer[CLI_BUFFER_SIZE];
byte cliBufferIndex = 0;

boolean pairingMode = false;
byte pairingSlot = 0;           // 0=foot, 1=dome, 2=foot spare, 3=dome spare

// Runtime debug control - UsbDEBUGlvl is defined in src/message.cpp
// 0x00 = quiet (only Serial.print messages), 0x80 = verbose (all Notify messages)
extern int UsbDEBUGlvl;

// Deferred LED commands - sent from loop() instead of from onInit callback
// (onInit is called from inside USB callback chain, outTransfer from there can deadlock)
boolean pendingFootLed = false;
boolean pendingDomeLed = false;
unsigned long pairingStartTime = 0;
#define PAIRING_TIMEOUT_MS  120000  // 2 minutes overall timeout for pairing mode
const char slotName0[] PROGMEM = "Foot Primary";
const char slotName1[] PROGMEM = "Dome Primary";
const char slotName2[] PROGMEM = "Foot Backup";
const char slotName3[] PROGMEM = "Dome Backup";
const char* const slotNames[] PROGMEM = { slotName0, slotName1, slotName2, slotName3 };


// =======================================================================================
//                          BLDC Motor Mixing & Control Functions
// =======================================================================================

#if FOOT_CONTROLLER == 1 || FOOT_CONTROLLER == 2
// BHD Diamond Mixing function for differential (tank) style drive using two motor controllers.
// Takes joystick X and Y values (0-255), mixes them, and outputs left/right values.
// Output: leftFoot/rightFoot as servo values (0-180, 90=stop) for PPM mode
//         or speed values (-100 to +100) for PWM+DIR mode
void mixBHD(byte stickX, byte stickY, byte maxSpeed) {

    // Deadzone Handling (128 = joystick center)
    if ( abs(stickX-128) < joystickFootDeadZoneRange ) {
      stickX = 128;
    }
    if ( abs(stickY-128) < joystickFootDeadZoneRange ) {
      stickY = 128;
    }

    if((stickX != 128) || (stickY != 128)) {
      // Map to -100 to +100 range in both axes
      int YDist = 0;
      int XDist = 0;
      if(stickY < 128) {
       YDist = (map(stickY, 0, 128, 100, 1));
      } else if(stickY > 128) {
       YDist = (map(stickY, 128, 255, -1, -100));
      }
      if(stickX < 128) {
       XDist = (map(stickX, 0, 128, -100, -1));
      } else if(stickX > 128) {
       XDist = (map(stickX, 128, 255, 1, 100));
      }

      // Constrain to Diamond values using line intersection math
      // Reference: https://github.com/declanshanaghy/JabberBot/raw/master/Docs/Using%20Diamond%20Coordinates%20to%20Power%20a%20Differential%20Drive.pdf
      float TempYDist = YDist;
      float TempXDist = XDist;
      if (YDist>(XDist+100)) {
        TempXDist = -100/(1-(TempYDist/TempXDist));
        TempYDist = TempXDist+100;
      } else if (YDist>(100-XDist)) {
        TempXDist = -100/(-1-(TempYDist/TempXDist));
        TempYDist = -TempXDist+100;
      } else if (YDist<(-XDist-100)) {
        TempXDist = 100/(-1-(TempYDist/TempXDist));
        TempYDist = -TempXDist-100;
      } else if (YDist<(XDist-100)) {
        TempXDist = 100/(1-(TempYDist/TempXDist));
        TempYDist = TempXDist-100;
      }

      // Translate diamond coordinates to left/right speed (-100 to +100)
      LeftSpeed = ((TempXDist+TempYDist-100)/2)+100;
      LeftSpeed = (LeftSpeed-50)*2;
      RightSpeed = ((TempYDist-TempXDist-100)/2)+100;
      RightSpeed = (RightSpeed-50)*2;

      #if FOOT_CONTROLLER == 1
      // PPM mode: map to servo range (0-180, centered at 90)
      int servoMin = 90 - maxSpeed;
      int servoMax = 90 + maxSpeed;

        if (invertLeft == 0)
          leftFoot=map(LeftSpeed, 100, -100, servoMax, servoMin);
        else
          leftFoot=map(LeftSpeed, 100, -100, servoMin, servoMax);
        if (invertRight == 0)
          rightFoot=map(RightSpeed, 100, -100, servoMax, servoMin);
        else
          rightFoot=map(RightSpeed, 100, -100, servoMin, servoMax);
      #elif FOOT_CONTROLLER == 2
      // PWM+DIR mode: map to -maxSpeed to +maxSpeed range
        if (invertLeft == 0)
          leftFoot=map(LeftSpeed, -100, 100, -maxSpeed, maxSpeed);
        else
          leftFoot=map(LeftSpeed, -100, 100, maxSpeed, -maxSpeed);
        if (invertRight == 0)
          rightFoot=map(RightSpeed, -100, 100, -maxSpeed, maxSpeed);
        else
          rightFoot=map(RightSpeed, -100, 100, maxSpeed, -maxSpeed);
      #endif

    } else {
      #if FOOT_CONTROLLER == 1
      leftFoot=90;
      rightFoot=90;
      #elif FOOT_CONTROLLER == 2
      leftFoot=0;
      rightFoot=0;
      #endif
    }
}
#endif

// =======================================================================================
//   stopFeet() - Universal foot motor stop function for all controller types
// =======================================================================================
void stopFeet() {
  #if FOOT_CONTROLLER == 0
  ST->stop();
  #elif FOOT_CONTROLLER == 1
  leftFoot=90;
  rightFoot=90;
  leftFootDriveSpeed=90;
  rightFootDriveSpeed=90;
  leftFootSignal.writeMicroseconds(1500);
  rightFootSignal.writeMicroseconds(1500);
  #elif FOOT_CONTROLLER == 2
  leftFoot=0;
  rightFoot=0;
  leftFootDriveSpeed=0;   // PWM+DIR: 0 = stop (not 90 like PPM servo center)
  rightFootDriveSpeed=0;
  analogWrite(leftFootPwmPin, 0);
  analogWrite(rightFootPwmPin, 0);
    #ifdef ENABLE_BRAKE
    digitalWrite(footBrakePin, LOW);  // Engage brake (active LOW)
    #endif
  #endif

  #ifdef SHADOW_VERBOSE
   output += "\r\n***Foot Motor STOPPED***\r\n";
  #endif
}

// =======================================================================================
//   writeBLDCMotors() - Write speed values to BLDC motors (mode 1 & 2)
// =======================================================================================
#if FOOT_CONTROLLER == 1
void writeBLDCMotors(int leftVal, int rightVal) {
  // PPM mode: write servo microseconds (1000-2000, center 1500)
  int leftUs = constrain(map(leftVal, 0, 180, 1000, 2000), 1000, 2000);
  int rightUs = constrain(map(rightVal, 0, 180, 1000, 2000), 1000, 2000);
  leftFootSignal.writeMicroseconds(leftUs);
  rightFootSignal.writeMicroseconds(rightUs);
}
#elif FOOT_CONTROLLER == 2
void writeBLDCMotors(int leftVal, int rightVal) {
  // PWM+DIR mode: set direction pin and write PWM speed
  int leftMagnitude = constrain((leftVal >= 0) ? leftVal : -leftVal, 0, 255);
  int rightMagnitude = constrain((rightVal >= 0) ? rightVal : -rightVal, 0, 255);

  #ifdef ENABLE_BRAKE
  digitalWrite(footBrakePin, HIGH);  // Release brake
  #endif

  if (leftVal >= 0) {
    digitalWrite(leftFootDirPin, HIGH);
    analogWrite(leftFootPwmPin, leftMagnitude);
  } else {
    digitalWrite(leftFootDirPin, LOW);
    analogWrite(leftFootPwmPin, leftMagnitude);
  }

  if (rightVal >= 0) {
    digitalWrite(rightFootDirPin, HIGH);
    analogWrite(rightFootPwmPin, rightMagnitude);
  } else {
    digitalWrite(rightFootDirPin, LOW);
    analogWrite(rightFootPwmPin, rightMagnitude);
  }
}
#endif


// =======================================================================================
//                          Main Program
// =======================================================================================


// =======================================================================================
//           EEPROM & CLI Helper Functions
// =======================================================================================

void parseMacString(const char* macStr, byte* mac)
{
    // Input is MSB-first string "XX:XX:XX:XX:XX:XX", store as LSB-first (like disc_bdaddr)
    char hexByte[3];
    hexByte[2] = '\0';
    for (int i = 0; i < 6; i++)
    {
        hexByte[0] = macStr[i * 3];
        hexByte[1] = macStr[i * 3 + 1];
        mac[5 - i] = (byte)strtol(hexByte, NULL, 16);
    }
}

void readMacFromEEPROM(byte slot, byte* mac)
{
    int addr = EEPROM_MAC_START + (slot * EEPROM_MAC_SIZE);
    for (int i = 0; i < EEPROM_MAC_SIZE; i++)
    {
        mac[i] = EEPROM.read(addr + i);
    }
}

void writeMacToEEPROM(byte slot, byte* mac)
{
    int addr = EEPROM_MAC_START + (slot * EEPROM_MAC_SIZE);
    for (int i = 0; i < EEPROM_MAC_SIZE; i++)
    {
        EEPROM.update(addr + i, mac[i]);
    }
    EEPROM.update(EEPROM_MAGIC_ADDR, EEPROM_MAGIC_BYTE);
}

// Load invert flags from EEPROM. Any value other than 0/1 is treated as 0 (safe default).
// Called after MAC-loading in setup() so that EEPROM contents apply at boot.
void loadInvertFromEEPROM()
{
    byte l = EEPROM.read(EEPROM_INVERT_LEFT_ADDR);
    byte r = EEPROM.read(EEPROM_INVERT_RIGHT_ADDR);
    invertLeft  = (l == 1) ? 1 : 0;
    invertRight = (r == 1) ? 1 : 0;
}

// Persist current invert flags to EEPROM and set the magic byte so the slot
// survives the next boot. Call from 'invert save' and 'invert reset' only.
void saveInvertToEEPROM()
{
    EEPROM.update(EEPROM_INVERT_LEFT_ADDR,  invertLeft  ? 1 : 0);
    EEPROM.update(EEPROM_INVERT_RIGHT_ADDR, invertRight ? 1 : 0);
    EEPROM.update(EEPROM_MAGIC_ADDR, EEPROM_MAGIC_BYTE);
}

boolean isEEPROMInitialized()
{
    return (EEPROM.read(EEPROM_MAGIC_ADDR) == EEPROM_MAGIC_BYTE);
}

boolean isMacSlotEmpty(byte slot)
{
    byte mac[6];
    readMacFromEEPROM(slot, mac);
    for (int i = 0; i < 6; i++)
    {
        if (mac[i] != 0xFF) return false;
    }
    return true;
}

void setupMacFilters()
{
    // Set MAC filters so PS3NavFoot only claims foot controllers, PS3NavDome only claims dome controllers
    // If no MAC is stored ("XX"), clear filter so that service accepts any controller
    byte mac[6];
    byte macBackup[6];
    bool hasBackup;

    // Foot filter
    if (!isMacTextUnset(PS3ControllerFootMac))
    {
        parseMacString(PS3ControllerFootMac, mac);
        hasBackup = !isMacTextUnset(PS3ControllerBackupFootMac);
        if (hasBackup)
        {
            parseMacString(PS3ControllerBackupFootMac, macBackup);
            PS3NavFoot->setMacFilter(mac, macBackup);
        }
        else
        {
            PS3NavFoot->setMacFilter(mac);
        }
    }
    else
    {
        PS3NavFoot->clearMacFilter();
    }

    // Dome filter
    if (!isMacTextUnset(PS3ControllerDomeMAC))
    {
        parseMacString(PS3ControllerDomeMAC, mac);
        hasBackup = !isMacTextUnset(PS3ControllerBackupDomeMAC);
        if (hasBackup)
        {
            parseMacString(PS3ControllerBackupDomeMAC, macBackup);
            PS3NavDome->setMacFilter(mac, macBackup);
        }
        else
        {
            PS3NavDome->setMacFilter(mac);
        }
    }
    else
    {
        PS3NavDome->clearMacFilter();
    }
}

void loadMacsFromEEPROM()
{
    if (!isEEPROMInitialized())
    {
        Serial.println(F("\r\nEEPROM not initialized. Send 'pair' to pair controllers."));
        clearMacText(PS3ControllerFootMac);
        clearMacText(PS3ControllerDomeMAC);
        clearMacText(PS3ControllerBackupFootMac);
        clearMacText(PS3ControllerBackupDomeMAC);
        setupMacFilters(); // Clear all filters when no MACs stored
        return;
    }

    byte mac[6];

    readMacFromEEPROM(MAC_SLOT_FOOT_PRIMARY, mac);
    if (isMacSlotEmpty(MAC_SLOT_FOOT_PRIMARY)) clearMacText(PS3ControllerFootMac);
    else macBytesToString(mac, PS3ControllerFootMac);

    readMacFromEEPROM(MAC_SLOT_DOME_PRIMARY, mac);
    if (isMacSlotEmpty(MAC_SLOT_DOME_PRIMARY)) clearMacText(PS3ControllerDomeMAC);
    else macBytesToString(mac, PS3ControllerDomeMAC);

    readMacFromEEPROM(MAC_SLOT_FOOT_BACKUP, mac);
    if (isMacSlotEmpty(MAC_SLOT_FOOT_BACKUP)) clearMacText(PS3ControllerBackupFootMac);
    else macBytesToString(mac, PS3ControllerBackupFootMac);

    readMacFromEEPROM(MAC_SLOT_DOME_BACKUP, mac);
    if (isMacSlotEmpty(MAC_SLOT_DOME_BACKUP)) clearMacText(PS3ControllerBackupDomeMAC);
    else macBytesToString(mac, PS3ControllerBackupDomeMAC);

    Serial.println(F("\r\nMAC addresses loaded from EEPROM."));

    // Setup MAC filters so each PS3BT service only claims its own controller
    setupMacFilters();
}

// =======================================================================================
//           Serial CLI Command Functions
// =======================================================================================

void cmdHelp()
{
    Serial.println(F("\r\n--- Shadow_MD BLDC CLI Commands ---"));
    Serial.println(F("  pair   - Enter pairing mode (Foot -> Dome -> Foot Spare -> Dome Spare)"));
    Serial.println(F("  done   - Exit pairing mode early"));
    Serial.println(F("  status - Show stored MAC addresses and connection status"));
    Serial.println(F("  clear  - Clear all stored MACs from EEPROM"));
    Serial.println(F("  invert - Show/change motor inversion flags (BLDC modes only)"));
    Serial.println(F("           Subcommands: invert | invert left [on|off] |"));
    Serial.println(F("                        invert right [on|off] | invert save | invert reset"));
    Serial.println(F("  debug  - Toggle verbose BT debug output on/off"));
    Serial.println(F("  reboot - Software reset"));
    Serial.println(F("  help   - Show this help message"));
    Serial.println(F("----------------------------------\r\n"));
}

void cmdStatus()
{
    Serial.println(F("\r\n--- Controller Status ---"));
    Serial.print(F("  Foot Primary:  ")); Serial.println(PS3ControllerFootMac);
    Serial.print(F("  Dome Primary:  ")); Serial.println(PS3ControllerDomeMAC);
    Serial.print(F("  Foot Backup:   ")); Serial.println(PS3ControllerBackupFootMac);
    Serial.print(F("  Dome Backup:   ")); Serial.println(PS3ControllerBackupDomeMAC);
    Serial.print(F("  EEPROM Init:   ")); Serial.println(isEEPROMInitialized() ? F("Yes") : F("No"));
    Serial.print(F("  Foot Connected: ")); Serial.println(mainControllerConnected ? F("Yes") : F("No"));
    Serial.print(F("  Dome Connected: ")); Serial.println(domeControllerConnected ? F("Yes") : F("No"));
    Serial.print(F("  Pairing Mode:  ")); Serial.println(pairingMode ? F("Active") : F("Off"));
    Serial.print(F("  Invert Left:   ")); Serial.println(invertLeft  ? F("INVERTED") : F("normal"));
    Serial.print(F("  Invert Right:  ")); Serial.println(invertRight ? F("INVERTED") : F("normal"));
    Serial.print(F("  Free RAM:      ")); Serial.print(freeMemory()); Serial.println(F(" bytes"));
    Serial.println(F("-------------------------\r\n"));
}

void cmdClear()
{
    // Clears the magic byte + all 4 MAC slots (bytes 0..24 inclusive).
    // The invert bytes (25, 26) are intentionally left untouched — use
    // 'invert reset' if you want to clear them separately. Codex review
    // option (a), 2026-04-21 (see BUGFIXES #7).
    for (int i = 0; i <  EEPROM_MAC_START + (EEPROM_NUM_SLOTS * EEPROM_MAC_SIZE); i++)
    {
        EEPROM.update(i, 0xFF);
    }
    clearMacText(PS3ControllerFootMac);
    clearMacText(PS3ControllerDomeMAC);
    clearMacText(PS3ControllerBackupFootMac);
    clearMacText(PS3ControllerBackupDomeMAC);
    Serial.println(F("\r\nAll stored MACs cleared. Send 'pair' to pair new controllers.\r\n"));
}

void cmdPair()
{
    pairingMode = true;
    pairingSlot = 0;
    pairingStartTime = millis();
    stopFeet();
    SyR->stop();
    isFootMotorStopped = true;
    footDriveSpeed = 0;

    if (PS3NavFoot->PS3NavigationConnected || PS3NavFoot->PS3Connected)
    {
        PS3NavFoot->disconnect();
    }
    if (PS3NavDome->PS3NavigationConnected || PS3NavDome->PS3Connected)
    {
        PS3NavDome->disconnect();
    }

    mainControllerConnected = false;
    domeControllerConnected = false;
    isPS3NavigatonInitialized = false;
    isSecondaryPS3NavigatonInitialized = false;

    // Clear MAC filters so pairing accepts any controller
    PS3NavFoot->clearMacFilter();
    PS3NavDome->clearMacFilter();

    // Clear disc_bdaddr so we detect the first hotswap
    memset(Btd.disc_bdaddr, 0, 6);

    Serial.println(F("\r\n=== PAIRING MODE ACTIVE ==="));
    Serial.println(F("For each controller:"));
    Serial.println(F("  1. Unplug BT dongle"));
    Serial.println(F("  2. Plug controller via USB (hotswap)"));
    Serial.println(F("     -> MAC is captured automatically"));
    Serial.println(F("  3. Unplug controller, plug dongle back in"));
    Serial.println(F(""));
    Serial.println(F("Order: Foot -> Dome -> Foot Spare -> Dome Spare"));
    Serial.println(F("Send 'done' to exit early. Timeout: 2 minutes."));
    Serial.println(F("\r\nWaiting for Foot Primary controller...\r\n"));
}

void cmdReboot()
{
    Serial.println(F("\r\nRebooting...\r\n"));
    Serial.flush();
    delay(100);
    wdt_enable(WDTO_15MS);
    while (1) {}
}

// Print current invert state + subcommand usage hint.
void cmdInvertPrint()
{
    Serial.println(F("\r\n--- Motor Inversion ---"));
    Serial.print(F("  Left:  ")); Serial.println(invertLeft  ? F("INVERTED") : F("normal"));
    Serial.print(F("  Right: ")); Serial.println(invertRight ? F("INVERTED") : F("normal"));
    Serial.println(F("  Subcommands: invert left [on|off] | invert right [on|off]"));
    Serial.println(F("               invert save | invert reset"));
    Serial.println(F("  (runtime value -- use 'invert save' to persist to EEPROM)"));
    Serial.println(F("-----------------------\r\n"));
}

// Dispatch 'invert ...' subcommands. Expects the tail AFTER the word "invert"
// (already skipped by the caller). Leading whitespace is tolerated.
void cmdInvertDispatch(const char* args)
{
    while (*args == ' ') args++;

    if (*args == '\0') { cmdInvertPrint(); return; }

    // "invert left [on|off]"
    if (strncmp(args, "left", 4) == 0 && (args[4] == '\0' || args[4] == ' '))
    {
        args += 4;
        while (*args == ' ') args++;
        if (*args == '\0')
        {
            Serial.print(F("invert left = "));
            Serial.println(invertLeft ? F("on (INVERTED)") : F("off (normal)"));
            return;
        }
        if (strcmp(args, "on") == 0)       invertLeft = 1;
        else if (strcmp(args, "off") == 0) invertLeft = 0;
        else { Serial.println(F("Usage: invert left [on|off]")); return; }
        Serial.print(F("invert left = "));
        Serial.println(invertLeft ? F("on (INVERTED)") : F("off (normal)"));
        Serial.println(F("(runtime only -- 'invert save' to persist)"));
        return;
    }

    // "invert right [on|off]"
    if (strncmp(args, "right", 5) == 0 && (args[5] == '\0' || args[5] == ' '))
    {
        args += 5;
        while (*args == ' ') args++;
        if (*args == '\0')
        {
            Serial.print(F("invert right = "));
            Serial.println(invertRight ? F("on (INVERTED)") : F("off (normal)"));
            return;
        }
        if (strcmp(args, "on") == 0)       invertRight = 1;
        else if (strcmp(args, "off") == 0) invertRight = 0;
        else { Serial.println(F("Usage: invert right [on|off]")); return; }
        Serial.print(F("invert right = "));
        Serial.println(invertRight ? F("on (INVERTED)") : F("off (normal)"));
        Serial.println(F("(runtime only -- 'invert save' to persist)"));
        return;
    }

    // "invert save"
    if (strcmp(args, "save") == 0)
    {
        saveInvertToEEPROM();
        Serial.print(F("Invert saved to EEPROM. Left="));
        Serial.print(invertLeft);
        Serial.print(F(" Right="));
        Serial.println(invertRight);
        return;
    }

    // "invert reset"
    if (strcmp(args, "reset") == 0)
    {
        invertLeft = 0;
        invertRight = 0;
        saveInvertToEEPROM();
        Serial.println(F("Invert reset to 0/0 and saved to EEPROM."));
        return;
    }

    Serial.print(F("Unknown invert subcommand: '"));
    Serial.print(args);
    Serial.println(F("'"));
    Serial.println(F("Usage: invert | invert left [on|off] | invert right [on|off] | invert save | invert reset"));
}

void processSerialCommand()
{
    cliBuffer[cliBufferIndex] = '\0';

    for (int i = cliBufferIndex - 1; i >= 0; i--)
    {
        if (cliBuffer[i] == '\r' || cliBuffer[i] == '\n' || cliBuffer[i] == ' ')
            cliBuffer[i] = '\0';
        else
            break;
    }

    if (strcmp(cliBuffer, "help") == 0)
        cmdHelp();
    else if (strcmp(cliBuffer, "pair") == 0)
        cmdPair();
    else if (strcmp(cliBuffer, "done") == 0)
    {
        if (pairingMode)
        {
            pairingMode = false;
            Serial.println(F("\r\nPairing mode exited."));
            loadMacsFromEEPROM();
            cmdStatus();
        }
        else
            Serial.println(F("\r\nNot in pairing mode.\r\n"));
    }
    else if (strcmp(cliBuffer, "status") == 0)
        cmdStatus();
    else if (strcmp(cliBuffer, "clear") == 0)
        cmdClear();
    else if (strcmp(cliBuffer, "reboot") == 0)
        cmdReboot();
    else if (strcmp(cliBuffer, "debug") == 0)
    {
        UsbDEBUGlvl = (UsbDEBUGlvl == 0x80) ? 0x00 : 0x80;
        Serial.print(F("\r\nDebug output: "));
        Serial.println(UsbDEBUGlvl ? F("ON (verbose)") : F("OFF (quiet)"));
    }
    else if (strncmp(cliBuffer, "invert", 6) == 0 && (cliBuffer[6] == '\0' || cliBuffer[6] == ' '))
    {
        cmdInvertDispatch(cliBuffer + 6);
    }
    else if (strlen(cliBuffer) > 0)
    {
        Serial.print(F("\r\nUnknown command: "));
        Serial.println(cliBuffer);
        Serial.println(F("Type 'help' for available commands.\r\n"));
    }

    cliBufferIndex = 0;
}

void checkPairingUSB()
{
    // BTD.cpp now reads the controller's BD address into disc_bdaddr
    // during USB hotswap (via HID report 0xF2). Check if it's set.
    if (!pairingMode) return;

    boolean addrValid = false;
    for (int i = 0; i < 6; i++)
    {
        if (Btd.disc_bdaddr[i] != 0x00)
            addrValid = true;
    }
    if (!addrValid) return;

    // Capture MAC for current slot
    writeMacToEEPROM(pairingSlot, Btd.disc_bdaddr);
    char mac[MAC_STRING_LEN];
    macBytesToString(Btd.disc_bdaddr, mac);

    // Clear disc_bdaddr so next hotswap is detected
    memset(Btd.disc_bdaddr, 0, 6);

    char nameBuf[16];
    strcpy_P(nameBuf, (char*)pgm_read_ptr(&(slotNames[pairingSlot])));

    Serial.print(F("\r\n>> Paired ["));
    Serial.print(nameBuf);
    Serial.print(F("]: "));
    Serial.println(mac);

    pairingSlot++;
    if (pairingSlot >= EEPROM_NUM_SLOTS)
    {
        pairingMode = false;
        Serial.println(F("\r\nAll 4 slots paired! Exiting pairing mode."));
        loadMacsFromEEPROM();
        cmdStatus();
    }
    else
    {
        char nextNameBuf[16];
        strcpy_P(nextNameBuf, (char*)pgm_read_ptr(&(slotNames[pairingSlot])));
        Serial.print(F("Waiting for "));
        Serial.print(nextNameBuf);
        Serial.println(F(" controller..."));
    }
}

void processSerialInput()
{
    while (Serial.available())
    {
        char c = Serial.read();

        if (c == '\n' || c == '\r')
        {
            if (cliBufferIndex > 0)
                processSerialCommand();
        }
        else if (cliBufferIndex < CLI_BUFFER_SIZE - 1)
        {
            if (c >= 'A' && c <= 'Z') c += 32;
            cliBuffer[cliBufferIndex++] = c;
        }
    }
}

// =======================================================================================
//                          Initialize - Setup Function
// =======================================================================================
void setup()
{
    wdt_disable();  // Safety: disable watchdog in case we got here from a watchdog reset

    //Debug Serial for use with USB Debugging
    Serial.begin(115200);
    while (!Serial);

    Serial.print(F("\r\nSystem starting up.\r\n"));

    // Load PS3 controller MACs from EEPROM
    loadMacsFromEEPROM();
    // Load motor invert flags from EEPROM (BLDC modes only; ignored in Mode 0)
    loadInvertFromEEPROM();
    cmdStatus();

    Serial.print(F("\r\n[RAM] After EEPROM load: "));
    Serial.print(freeMemory());
    Serial.println(F(" bytes free"));

    //Setup for Serial1:: MarcDuino Dome Control Board
    Serial.print(F("\r\nMarcduino Dome connecting... "));
    Serial1.begin(marcDuinoBaudRate); 
    while (!Serial1);
    Serial.print(F("done.\r\n"));

    //Setup for Serial2:: Motor Controllers - Sabertooth (Feet) 
    Serial.print(F("\r\nMotor Controller connecting... "));
    Serial2.begin(motorControllerBaudRate);
    while (!Serial2);
    Serial.print(F("done.\r\n"));

    //Setup for Serial3:: Optional MarcDuino Control Board for Body Panels
    Serial.print(F("\r\nMarcduino Body connecting... "));
    Serial3.begin(marcDuinoBaudRate);
    while (!Serial3);
    Serial.print(F("done.\r\n"));

    // Wait for powered up USB-Shield
    Serial.print(F("\r\nStarting USB... "));
    delay(1500);
    if (Usb.Init() == -1)
    {
        Serial.print(F("\r\nOSC did not start! - HALT -"));
        while (1); //halt
    }
    Serial.print(F("USB + Bluetooth Library started.\r\n"));
    
    output.reserve(384); // Keep a reusable buffer to reduce reallocations during debug bursts.

    //Setup for PS3
    Serial.print(F("\r\nRegistering Controller Events... "));
    PS3NavFoot->attachOnInit(onInitPS3NavFoot); // onInitPS3NavFoot is called upon a new connection
    PS3NavDome->attachOnInit(onInitPS3NavDome); 
    Serial.print(F("done.\r\n"));

    //Setup for Foot Motor Controller
    #if FOOT_CONTROLLER == 0
    Serial.print(F("\r\nSetting up Sabertooth (foot drive)..."));
    ST->autobaud();
    ST->setTimeout(10);      //DMB:  How low can we go for safety reasons?  multiples of 100ms
    ST->setDeadband(driveDeadBandRange);
    ST->stop();
    Serial.print(F("done.\r\n"));

    #elif FOOT_CONTROLLER == 1
    Serial.print(F("\r\nSetting up BLDC PPM (foot drive)..."));
    leftFootSignal.attach(leftFootPin);
    rightFootSignal.attach(rightFootPin);
      #ifdef INTERNAL_MIXING
      // Keep configured drive speeds intact and cache mapped runtime values separately.
      driveSpeed1Internal = mapDriveSpeedForInternalMixing(drivespeed1);
      driveSpeed2Internal = mapDriveSpeedForInternalMixing(drivespeed2);
      #endif
    // Send neutral signal to arm ESCs
    leftFootSignal.writeMicroseconds(1500);
    rightFootSignal.writeMicroseconds(1500);
    Serial.print(F("done.\r\n"));

    #elif FOOT_CONTROLLER == 2
    Serial.print(F("\r\nSetting up BLDC PWM+DIR (foot drive)..."));
    pinMode(leftFootPwmPin, OUTPUT);
    pinMode(leftFootDirPin, OUTPUT);
    pinMode(rightFootPwmPin, OUTPUT);
    pinMode(rightFootDirPin, OUTPUT);
      #ifdef ENABLE_BRAKE
      pinMode(footBrakePin, OUTPUT);
      digitalWrite(footBrakePin, LOW);  // Start with brake engaged
      #endif
    analogWrite(leftFootPwmPin, 0);
    analogWrite(rightFootPwmPin, 0);
      #ifdef INTERNAL_MIXING
      // Keep configured drive speeds intact and cache mapped runtime values separately.
      driveSpeed1Internal = mapDriveSpeedForInternalMixing(drivespeed1);
      driveSpeed2Internal = mapDriveSpeedForInternalMixing(drivespeed2);
      #endif
    Serial.print(F("done.\r\n"));
    #endif

    stopFeet();

    // Setup SyRen dome motor - ALWAYS active regardless of foot controller type
    Serial.print(F("\r\nSetting up SyRen (dome drive)..."));
    SyR->autobaud();
    SyR->setTimeout(20);      //DMB:  How low can we go for safety reasons?  multiples of 100ms
    SyR->stop();
    Serial.print(F("done.\r\n"));

#ifdef MRBADDELEY
    // Config Mr. Baddeley printed droid
    // #SRxxy Set individual servo to either forward or reversed xx=servo number y=direction
    // *		Must be a 2 digit Servo number i.e. Servo 4 is 04
    // *		Must be either 0 or 1 to set the direction (0 normal, 1 reversed)
    // *		Use SDxx to globally set the Servo direction, then SRxxy to change individual servos.    
    Serial.print(F("\r\nConfiguring ShadowMD AstroCan/AstroComms... "));
    // Only needed once
    delay(1500);
    Serial3.print("#SD00\r");   // All servos normal
    delay(550);
    Serial3.print("#SR011\r");  // DPL door reverse
    delay(550);
    Serial3.print("#SR021\r");  // Upper Utility Arm reverse
    delay(550);
    Serial3.print("#SR031\r");  // Lower Utility Arm reverse
    delay(550);
    Serial.print(F("done.\r\n"));    
#endif

    // Close all panels
    Serial1.print(":CL00");
    Serial3.print(":CL00");
    delay(550);
    Serial1.print(":ST00\r");
    Serial3.print(":ST00\r");            

    randomSeed(analogRead(0));  // random number seed for dome automation

    Serial.print(F("\r\n[RAM] Before loop: "));
    Serial.print(freeMemory());
    Serial.println(F(" bytes free"));

    Serial.println(F("\r\nType 'help' for Serial CLI commands."));
    Serial.print(F("\r\nEntering Loop."));
}

// =======================================================================================
//           Main Program Loop - This is the recurring check loop for entire sketch
// =======================================================================================

bool LoopMessageSent = false;

void loop()
{
    if (!LoopMessageSent)
    {
      Serial.print(F("\r\nInside Loop.\r\n"));
      LoopMessageSent = true;
    }

    // Process Serial CLI input
    processSerialInput();

    // Check pairing mode timeout
    if (pairingMode && (millis() - pairingStartTime > PAIRING_TIMEOUT_MS))
    {
        pairingMode = false;
        Serial.println(F("\r\nPairing mode timed out."));
        loadMacsFromEEPROM();
        cmdStatus();
    }

    //Useful to enable with serial console when having controller issues.
    #ifdef TEST_CONROLLER
      testPS3Controller();
    #endif

    //LOOP through functions from highest to lowest priority.

    // Send deferred LED commands BEFORE readUSB() - otherwise criticalFaultDetect()
    // returns fault (invalid data) causing early return, and LED never gets sent.
    // The LED command tells the controller to enter active mode and start sending valid data.
    if (pendingFootLed && PS3NavFoot->PS3NavigationConnected) {
        Serial.print(F("\r\n[LOOP] Sending Foot LED..."));
        Serial.flush();
        PS3NavFoot->setLedOn(LED1);
        Serial.println(F(" OK"));
        pendingFootLed = false;
    }
    if (pendingDomeLed && PS3NavDome->PS3NavigationConnected) {
        Serial.print(F("\r\n[LOOP] Sending Dome LED..."));
        Serial.flush();
        PS3NavDome->setLedOn(LED1);
        Serial.println(F(" OK"));
        pendingDomeLed = false;
    }

    if ( !readUSB() )
    {
      //We have a fault condition that we want to ensure that we do NOT process any controller data!!!
      printOutput();
      checkPairingUSB();
      return;
    }

    checkPairingUSB();

    if (!pairingMode)
    {
        footMotorDrive();
        domeDrive();
        marcDuinoDome();
        marcDuinoFoot();
        toggleSettings();
    }
    printOutput();

    // If running a custom MarcDuino Panel Routine - Call Function
    if (runningCustRoutine && !pairingMode)
    {
       custMarcDuinoPanel();
    }

    // If dome automation is enabled - Call function
    if (domeAutomation && !pairingMode && time360DomeTurn > 1999 && time360DomeTurn < 8001 && domeAutoSpeed > 49 && domeAutoSpeed < 101)
    {
       autoDome();
    }
}

// =======================================================================================
//           footDrive Motor Control Section
// =======================================================================================

boolean ps3FootMotorDrive(PS3BT* myPS3 = PS3NavFoot)
{
  int stickSpeed = 0;
  int turnnum = 0;

  if (isPS3NavigatonInitialized)
  {
      // Additional fault control.  Do NOT send additional commands if no controllers have initialized.
      if (!isStickEnabled)
      {
            #ifdef SHADOW_VERBOSE
              if ( abs(myPS3->getAnalogHat(LeftHatY)-128) > joystickFootDeadZoneRange)
              {
                output += "Drive Stick is disabled\r\n";
              }
            #endif

          if (!isFootMotorStopped)
          {
              stopFeet();
              isFootMotorStopped = true;
              footDriveSpeed = 0;
          }

          return false;

      } else if (!myPS3->PS3NavigationConnected)
      {

          if (!isFootMotorStopped)
          {
              stopFeet();
              isFootMotorStopped = true;
              footDriveSpeed = 0;
          }

          return false;


      } else if (myPS3->getButtonPress(L2) || myPS3->getButtonPress(L1))
      {

          if (!isFootMotorStopped)
          {
              stopFeet();
              isFootMotorStopped = true;
              footDriveSpeed = 0;
          }

          return false;

      } else
      {
          // =====================================================================
          //  SABERTOOTH MODE (FOOT_CONTROLLER == 0)
          // =====================================================================
          #if FOOT_CONTROLLER == 0

          int joystickPosition = myPS3->getAnalogHat(LeftHatY);

          if (overSpeedSelected)
          {
            stickSpeed = (map(joystickPosition, 0, 255, -drivespeed2, drivespeed2));
          } else
          {
            stickSpeed = (map(joystickPosition, 0, 255, -drivespeed1, drivespeed1));
          }

          if ( abs(joystickPosition-128) < joystickFootDeadZoneRange)
          {
                // RAMP DOWN when stick is at ZERO but prior FootSpeed > 20
                if (abs(footDriveSpeed) > 50)
                {
                    if (footDriveSpeed > 0) { footDriveSpeed -= 3; }
                    else { footDriveSpeed += 3; }

                    #ifdef SHADOW_VERBOSE
                        output += "ZERO FAST RAMP: footSpeed: ";
                        output += footDriveSpeed;
                        output += "\nStick Speed: ";
                        output += stickSpeed;
                        output += "\n\r";
                    #endif

                } else if (abs(footDriveSpeed) > 20)
                {
                    if (footDriveSpeed > 0) { footDriveSpeed -= 2; }
                    else { footDriveSpeed += 2; }

                    #ifdef SHADOW_VERBOSE
                        output += "ZERO MID RAMP: footSpeed: ";
                        output += footDriveSpeed;
                        output += "\nStick Speed: ";
                        output += stickSpeed;
                        output += "\n\r";
                    #endif

                } else
                {
                    footDriveSpeed = 0;
                }

          } else
          {
              isFootMotorStopped = false;

              if (footDriveSpeed < stickSpeed)
              {
                  if ((stickSpeed-footDriveSpeed)>(ramping+1))
                  {
                    footDriveSpeed+=ramping;
                    #ifdef SHADOW_VERBOSE
                        output += "RAMPING UP: footSpeed: ";
                        output += footDriveSpeed;
                        output += "\nStick Speed: ";
                        output += stickSpeed;
                        output += "\n\r";
                    #endif
                  } else
                      footDriveSpeed = stickSpeed;

              } else if (footDriveSpeed > stickSpeed)
              {
                  if ((footDriveSpeed-stickSpeed)>(ramping+1))
                  {
                    footDriveSpeed-=ramping;
                    #ifdef SHADOW_VERBOSE
                        output += "RAMPING DOWN: footSpeed: ";
                        output += footDriveSpeed;
                        output += "\nStick Speed: ";
                        output += stickSpeed;
                        output += "\n\r";
                    #endif
                  } else
                      footDriveSpeed = stickSpeed;
              } else
              {
                  footDriveSpeed = stickSpeed;
              }
          }

          turnnum = (myPS3->getAnalogHat(LeftHatX));

          if ( abs(footDriveSpeed) > 50)
              turnnum = (map(myPS3->getAnalogHat(LeftHatX), 54, 200, -(turnspeed/4), (turnspeed/4)));
          else if (turnnum <= 200 && turnnum >= 54)
              turnnum = (map(myPS3->getAnalogHat(LeftHatX), 54, 200, -(turnspeed/3), (turnspeed/3)));
          else if (turnnum > 200)
              turnnum = (map(myPS3->getAnalogHat(LeftHatX), 201, 255, turnspeed/3, turnspeed));
          else if (turnnum < 54)
              turnnum = (map(myPS3->getAnalogHat(LeftHatX), 0, 53, -turnspeed, -(turnspeed/3)));

          if (abs(turnnum) > 5)
          {
              isFootMotorStopped = false;
          }

          currentMillis = millis();

          if ( (currentMillis - previousFootMillis) > serialLatency  )
          {
              if (footDriveSpeed != 0 || abs(turnnum) > 5)
              {
                  #ifdef SHADOW_VERBOSE
                    output += "Motor: FootSpeed: ";
                    output += footDriveSpeed;
                    output += "\nTurnnum: ";
                    output += turnnum;
                    output += "\nTime of command: ";
                    output += millis();
                  #endif

                  ST->turn(turnnum * invertTurnDirection);
                  ST->drive(footDriveSpeed * invertDriveDirection);

              } else
              {
                  if (!isFootMotorStopped)
                  {
                      stopFeet();
                      isFootMotorStopped = true;
                      footDriveSpeed = 0;
                  }
              }

              previousFootMillis = currentMillis;
              return true;
          }

          // =====================================================================
          //  BLDC MODE (FOOT_CONTROLLER == 1 PPM or FOOT_CONTROLLER == 2 PWM+DIR)
          // =====================================================================
          #elif FOOT_CONTROLLER == 1 || FOOT_CONTROLLER == 2

          currentMillis = millis();

          if ( (currentMillis - previousFootMillis) > serialLatency )
          {
              isFootMotorStopped = false;
              footX = myPS3->getAnalogHat(LeftHatX);
              footY = myPS3->getAnalogHat(LeftHatY);

              byte maxDriveSpeed;

              #ifdef INTERNAL_MIXING
              // Use BHD Diamond mixing for differential drive
              if (overSpeedSelected) {
                mixBHD(footX, footY, driveSpeed2Internal);
                maxDriveSpeed = driveSpeed2Internal;
              } else {
                mixBHD(footX, footY, driveSpeed1Internal);
                maxDriveSpeed = driveSpeed1Internal;
              }

              #else
              // External mixing (e.g. Roboteq) - pass X and Y directly
              maxDriveSpeed = overSpeedSelected ? drivespeed2 : drivespeed1;

              if ( abs(footX-128) < joystickFootDeadZoneRange ) { footX = 128; }
              if ( abs(footY-128) < joystickFootDeadZoneRange ) { footY = 128; }

                #if FOOT_CONTROLLER == 1
                // PPM: map directly to servo range
                int servoMin = 90 - maxDriveSpeed;
                int servoMax = 90 + maxDriveSpeed;
                if (maxDriveSpeed > 90) { servoMin = 0; servoMax = 180; }
                if (invertLeft == 0)
                  leftFoot = map(footX, 0, 255, servoMin, servoMax);
                else
                  leftFoot = map(footX, 0, 255, servoMax, servoMin);
                if (invertRight == 0)
                  rightFoot = map(footY, 0, 255, servoMin, servoMax);
                else
                  rightFoot = map(footY, 0, 255, servoMax, servoMin);
                #elif FOOT_CONTROLLER == 2
                // PWM+DIR: map to -maxDriveSpeed to +maxDriveSpeed
                if (invertLeft == 0)
                  leftFoot = map(footX, 0, 255, -maxDriveSpeed, maxDriveSpeed);
                else
                  leftFoot = map(footX, 0, 255, maxDriveSpeed, -maxDriveSpeed);
                if (invertRight == 0)
                  rightFoot = map(footY, 0, 255, -maxDriveSpeed, maxDriveSpeed);
                else
                  rightFoot = map(footY, 0, 255, maxDriveSpeed, -maxDriveSpeed);
                #endif
              #endif

              #ifdef SHADOW_VERBOSE
                if (prevLeftFoot != leftFoot || prevRightFoot != rightFoot) {
                  output += "  footX="+String(footX)+", footY="+String(footY);
                  output += "\n  LeftSpeed="+String(LeftSpeed)+", RightSpeed="+String(RightSpeed);
                  if (overSpeedSelected) output += "\ndrivespeed2: ";
                  else output += "\ndrivespeed1: ";
                  output += maxDriveSpeed;
                  output += "  L: ";
                  output += leftFoot;
                  output += "  R: ";
                  output += rightFoot;
                }
              #endif

              // Per-foot ramping (independent left/right)
              // LEFT motor ramp
              if (leftFootDriveSpeed < leftFoot) {
                  if ((leftFoot-leftFootDriveSpeed)>(ramping+1)) {
                    leftFootDriveSpeed+=ramping;
                  } else {
                    leftFootDriveSpeed = leftFoot;
                  }
              } else if (leftFootDriveSpeed > leftFoot) {
                  if ((leftFootDriveSpeed-leftFoot)>(ramping+1)) {
                    leftFootDriveSpeed-=ramping;
                  } else {
                    leftFootDriveSpeed = leftFoot;
                  }
              }
              // RIGHT motor ramp
              if (rightFootDriveSpeed < rightFoot) {
                  if ((rightFoot-rightFootDriveSpeed)>(ramping+1)) {
                    rightFootDriveSpeed+=ramping;
                  } else {
                    rightFootDriveSpeed = rightFoot;
                  }
              } else if (rightFootDriveSpeed > rightFoot) {
                  if ((rightFootDriveSpeed-rightFoot)>(ramping+1)) {
                    rightFootDriveSpeed-=ramping;
                  } else {
                    rightFootDriveSpeed = rightFoot;
                  }
              }

              // Write the motor values
              writeBLDCMotors(leftFootDriveSpeed, rightFootDriveSpeed);

              prevLeftFoot = leftFoot;
              prevRightFoot = rightFoot;
              previousFootMillis = currentMillis;
              return true;
          }
          #endif  // FOOT_CONTROLLER
      }
  }
  return false;
}

void footMotorDrive()
{

  //Flood control prevention
  if ((millis() - previousFootMillis) < serialLatency) return;

  if (PS3NavFoot->PS3NavigationConnected) ps3FootMotorDrive(PS3NavFoot);

}  


// =======================================================================================
//           domeDrive Motor Control Section
// =======================================================================================

int ps3DomeDrive(PS3BT* myPS3 = PS3NavDome)
{
    int domeRotationSpeed = 0;
      
    int joystickPosition = myPS3->getAnalogHat(LeftHatX);
        
    domeRotationSpeed = (map(joystickPosition, 0, 255, -domespeed, domespeed));
        
    if ( abs(joystickPosition-128) < joystickDomeDeadZoneRange ) 
       domeRotationSpeed = 0;
          
    if (domeRotationSpeed != 0 && domeAutomation == true)  // Turn off dome automation if manually moved
    {   
            domeAutomation = false; 
            domeStatus = 0;
            domeTargetPosition = 0; 
            
            #ifdef SHADOW_VERBOSE
              output += "Dome Automation OFF\r\n";
            #endif

    }    
    
    return domeRotationSpeed;
}

void rotateDome(int domeRotationSpeed, String mesg)
{
    //Constantly sending commands to the SyRen (Dome) is causing foot motor delay.
    //Lets reduce that chatter by trying 3 things:
    // 1.) Eliminate a constant stream of "don't spin" messages (isDomeMotorStopped flag)
    // 2.) Add a delay between commands sent to the SyRen (previousDomeMillis timer)
    // 3.) Switch to real UART on the MEGA (Likely the *CORE* issue and solution)
    // 4.) Reduce the timout of the SyRen - just better for safety!
    
    currentMillis = millis();
    if ( (!isDomeMotorStopped || domeRotationSpeed != 0) && ((currentMillis - previousDomeMillis) > (2*serialLatency) )  )
    {
      
          if (domeRotationSpeed != 0)
          {
            
            isDomeMotorStopped = false;
            
            #ifdef SHADOW_VERBOSE      
                output += "Dome rotation speed: ";
                output += domeRotationSpeed;
            #endif
        
            SyR->motor(domeRotationSpeed*(invertDomeDirection));
            
          } else
          {
            isDomeMotorStopped = true; 
            
            #ifdef SHADOW_VERBOSE      
                output += "\n\r***Dome motor is STOPPED***\n\r";
            #endif
            
            SyR->stop();
          }
          
          previousDomeMillis = currentMillis;      
    }
}

void domeDrive()
{
  //Flood control prevention
  //This is intentionally set to double the rate of the Dome Motor Latency
  if ((millis() - previousDomeMillis) < (2*serialLatency) ) return;  
  
  int domeRotationSpeed = 0;
  int ps3NavControlSpeed = 0;
  
  if (PS3NavDome->PS3NavigationConnected) 
  {
    
     ps3NavControlSpeed = ps3DomeDrive(PS3NavDome);

     domeRotationSpeed = ps3NavControlSpeed; 

     rotateDome(domeRotationSpeed,"Controller Move");
    
  } else if (PS3NavFoot->PS3NavigationConnected && PS3NavFoot->getButtonPress(L2))
  {
    
     ps3NavControlSpeed = ps3DomeDrive(PS3NavFoot);

     domeRotationSpeed = ps3NavControlSpeed; 

     rotateDome(domeRotationSpeed,"Controller Move");
    
  } else
  {
     if (!isDomeMotorStopped)
     {
         SyR->stop();
         isDomeMotorStopped = true;
     }
  }  
}  

// =======================================================================================
//                               Toggle Control Section
// =======================================================================================

void ps3ToggleSettings(PS3BT* myPS3 = PS3NavFoot)
{

    // enable / disable drive stick
    if(myPS3->getButtonPress(PS) && myPS3->getButtonClick(CROSS))
    {

        #ifdef SHADOW_DEBUG
          output += "Disabling the DriveStick\r\n";
          output += "Stopping Motors";
        #endif

        stopFeet();
        isFootMotorStopped = true;
        isStickEnabled = false;
        footDriveSpeed = 0;
    }
    
    if(myPS3->getButtonPress(PS) && myPS3->getButtonClick(CIRCLE))
    {
        #ifdef SHADOW_DEBUG
          output += "Enabling the DriveStick\r\n";
        #endif
        isStickEnabled = true;
    }
    
    // Enable and Disable Overspeed
    if (myPS3->getButtonPress(L3) && myPS3->getButtonPress(L1) && isStickEnabled)
    {
      
       if ((millis() - previousSpeedToggleMillis) > 1000)
       {
            speedToggleButtonCounter = 0;
            previousSpeedToggleMillis = millis();
       } 
     
       speedToggleButtonCounter += 1;
       
       if (speedToggleButtonCounter == 1)
       {
       
          if (!overSpeedSelected)
          {
           
                overSpeedSelected = true;
           
                #ifdef SHADOW_VERBOSE      
                  output += "Over Speed is now: ON";
                #endif
                
          } else
          {      
                overSpeedSelected = false;
           
                #ifdef SHADOW_VERBOSE      
                  output += "Over Speed is now: OFF";
                #endif   
          }  
       }
    }
   
    // Enable Disable Dome Automation
    if(myPS3->getButtonPress(L2) && myPS3->getButtonClick(CROSS))
    {
          domeAutomation = false;
          domeStatus = 0;
          domeTargetPosition = 0;
          SyR->stop();
          isDomeMotorStopped = true;
          
          #ifdef SHADOW_DEBUG
            output += "Dome Automation OFF\r\n";
          #endif
    } 

    if(myPS3->getButtonPress(L2) && myPS3->getButtonClick(CIRCLE))
    {
          domeAutomation = true;

          #ifdef SHADOW_DEBUG
            output += "Dome Automation On\r\n";
          #endif
    } 

}

void toggleSettings()
{
   if (PS3NavFoot->PS3NavigationConnected) ps3ToggleSettings(PS3NavFoot);
}  

// =======================================================================================
// This is the main MarcDuino Button Management Function
// =======================================================================================
void marcDuinoButtonPush(int type, int MD_func, int MP3_num, int LD_type, const String& LD_text, int panel_type, 
                         boolean use_DP1,
                         int DP1_str_delay, 
                         int DP1_open_time,
                         boolean use_DP2,
                         int DP2_str_delay, 
                         int DP2_open_time,
                         boolean use_DP3,
                         int DP3_str_delay, 
                         int DP3_open_time,
                         boolean use_DP4,
                         int DP4_str_delay, 
                         int DP4_open_time,
                         boolean use_DP5,
                         int DP5_str_delay, 
                         int DP5_open_time,
                         boolean use_DP6,
                         int DP6_str_delay, 
                         int DP6_open_time,
                         boolean use_DP7,
                         int DP7_str_delay, 
                         int DP7_open_time,
                         boolean use_DP8,
                         int DP8_str_delay, 
                         int DP8_open_time,
                         boolean use_DP9,
                         int DP9_str_delay, 
                         int DP9_open_time,
                         boolean use_DP10,
                         int DP10_str_delay, 
                         int DP10_open_time)
{
  
  if (type == 1)  // Std Marcduino Function Call Configured
  {
//     5 = Wave 2, Open progressively all panels, then close one by one
//     6 = Beep cantina - w/ marching ants panel action
//     7 = Faint / Short Circuit
//     8 = Cantina Dance - orchestral, rhythmic panel dance
//     9 = Leia message
//    10 = Disco
//    11 = Quite mode reset (panel close, stop holos, stop sounds)
//    12 = Full Awake mode reset (panel close, rnd sound, holo move,holo lights off)
//    13 = Mid Awake mode reset (panel close, rnd sound, stop holos)
//    14 = Full Awake+ reset (panel close, rnd sound, holo move, holo lights on)
//    15 = Scream, with all panels open (NO SOUND)
//    16 = Wave, one panel at a time (NO SOUND)
//    17 = Fast (smirk) back and forth (NO SOUND)
//    18 = Wave 2 (Open progressively, then close one by one) (NO SOUND)
//    19 = Marching Ants (NO SOUND)
//    20 = Faint/Short Circuit (NO SOUND)
//    21 = Rhythmic cantina dance (NO SOUND)
//    22 = Random Holo Movement On (All) - No other actions
//    23 = Holo Lights On (All)
//    24 = Holo Lights Off (All)
//    25 = Holo reset (motion off, lights off)
//    26 = Volume Up
//    27 = Volume Down
//    28 = Volume Max
//    29 = Volume Mid
//    30 = Open All Dome Panels
//    31 = Open Top Dome Panels
//    32 = Open Bottom Dome Panels
//    33 = Close All Dome Panels
//    34 = Open Dome Panel #1
//    35 = Close Dome Panel #1
//    36 = Open Dome Panel #2
//    37 = Close Dome Panel #2
//    38 = Open Dome Panel #3
//    39 = Close Dome Panel #3
//    40 = Open Dome Panel #4
//    41 = Close Dome Panel #4
//    42 = Open Dome Panel #5
//    43 = Close Dome Panel #5
//    44 = Open Dome Panel #6
//    45 = Close Dome Panel #6
//    46 = Open Dome Panel #7
//    47 = Close Dome Panel #7
//    48 = Open Dome Panel #8
//    49 = Close Dome Panel #8
//    50 = Open Dome Panel #9
//    51 = Close Dome Panel #9
//    52 = Open Dome Panel #10
//    53 = Close Dome Panel #10
//   *** BODY PANEL OPTIONS ASSUME SECOND MARCDUINO MASTER BOARD ON MEGA ADK SERIAL #3 ***
//    56 = Open Body Panel #1
//    57 = Close Body Panel #1
//    58 = Open Body Panel #2
//    59 = Close Body Panel #2
//    60 = Open Body Panel #3
//    61 = Close Body Panel #3
//    62 = Open Body Panel #4
//    63 = Close Body Panel #4
//    64 = Open Body Panel #5
//    65 = Close Body Panel #5
//    66 = Open Body Panel #6
//    67 = Close Body Panel #6
//    68 = Open Body Panel #7
//    69 = Close Body Panel #7
//    70 = Open Body Panel #8
//    71 = Close Body Panel #8
//    72 = Open Body Panel #9
//    73 = Close Body Panel #9
//    74 = Open Body Panel #10
//    75 = Close Body Panel #10
//   *** MAGIC PANEL LIGHTING COMMANDS
//    76 = Magic Panel ON
//    77 = Magic Panel OFF
//    78 = Magic Panel Flicker (10 seconds)
//   ***  Tim Ebel addons
//    79 = Eebel Sppok Wave Dome and body
//    80 = Eebel Wave Bye and WaveByeSound
//    81 = Eebel Utility Arms Open and then Close
//    82 = Eebel Open all Body Doors, raise arms, operate tools, lower arms close all doors
//    83 = Eebel Use Gripper
//    84 = Eebel Use INterface Tool
//    85 = Eebel Ping Pong Body Doors
//    86 = Eebel Star Wars Disco Dance
//    87 = Eebel Star Trek Disco Dance (Wrong franchise! I know, right?)
//    88 = Eebel Play Next Song
//    89 = Eebel Play Previous Song    
    switch (MD_func)
    {
      // Close All Panels
      case 1:   
        Serial1.print(":SE00\r");
        Serial3.print(":SE00\r");
        break;

      // Scream - all panels open
      case 2:
        Serial1.print(":SE01\r");
        break;

      // Wave, One Panel at a time
      case 3:
        //Dome and Body Wave
        Serial1.print(":SE02\r");
        Serial3.print(":SE02\r");
        break;

      // Fast (smirk) back and forth wave      
      case 4:
        Serial1.print(":SE03\r");
        break;
                
      case 5:
        Serial1.print(":SE04\r");
        break;
                
      case 6:
        Serial1.print(":SE05\r");
        break;
                
      case 7:
        //Faint
        Serial1.print(":SE06\r");
        Serial3.print(":SE06\r");
        break;
                
      case 8:
        Serial1.print(":SE07\r");
        break;
                
      case 9:
        Serial1.print(":SE08\r");
        break;
                
      case 10:
        Serial1.print(":SE09\r");
        break;
                
      case 11:
        Serial1.print(":SE10\r");
        break;
                
      case 12:
        Serial1.print(":SE11\r");
        break;
                
      case 13:
        Serial1.print(":SE13\r");
        break;
                
      case 14:
        Serial1.print(":SE14\r");
        break;
                
      case 15:
        Serial1.print(":SE51\r");
        break;
                
      case 16:
        Serial1.print(":SE52\r");
        break;
                
      case 17:
        Serial1.print(":SE53\r");
        break;
                
      case 18:
        Serial1.print(":SE54\r");
        break;
                
      case 19:
        Serial1.print(":SE55\r");
        break;
                
      case 20:
        Serial1.print(":SE56\r");
        break;
                
      case 21:
        Serial1.print(":SE57\r");
        break;
                
      case 22:
        Serial1.print("*RD00\r");
        break;
                
      case 23:
        //Serial1.print("*ON00\r");
        //Toggle Holo lights On/Off 
        if (HoloOn == false){
          Serial1.print("*ON00\r"); //Turn Holos On 
          HoloOn = true;
        } else {
          //Turn Holos Off
          Serial1.print("*OF00\r");
          HoloOn = false;
        }
        break;
                
      case 24:
        Serial1.print("*OF00\r");
        break;
                
      case 25:
        Serial1.print("*ST00\r");
        break;
                
      case 26:
        Serial1.print("$+\r");
        break;
                
      case 27:
        Serial1.print("$-\r");
        break;
                
      case 28:
        Serial1.print("$f\r");
        break;
                
      case 29:
        Serial1.print("$m\r");
        break;
                
      case 30:
        Serial1.print(":OP00\r");
        Serial3.print(":OP04\r"); //Left Body Door
        Serial3.print(":OP07\r"); //Right Body Door
        delay(550); //wait for Main Doors
        Serial3.print(":OP01\r"); //DPL
        Serial1.print(":ST00\r"); //Stop the buzz
        Serial3.print(":ST00\r"); //Stop the buzz       
        break;
                
      case 31:
        Serial1.print(":OP11\r");
        break;
                
      case 32:
        Serial1.print(":OP12\r");
        break;
                
      case 33:
        Serial1.print(":CL00\r");
        Serial3.print(":CL00\r");
        break;
                
      case 34:
        Serial1.print(":OP01\r");
        break;
                
      case 35:
        Serial1.print(":CL01\r");
        break;
                
      case 36:
        Serial1.print(":OP02\r");
        break;
                
      case 37:
        Serial1.print(":CL02\r");
        break;
                
      case 38:
        Serial1.print(":OP03\r");
        break;
                
      case 39:
        Serial1.print(":CL03\r");
        break;
                
      case 40:
        Serial1.print(":OP04\r");
        break;
                
      case 41:
        Serial1.print(":CL04\r");
        break;
                
      case 42:
        Serial1.print(":OP05\r");
        break;
                
      case 43:
        Serial1.print(":CL05\r");
        break;
                
      case 44:
        Serial1.print(":OP06\r");
        break;
                
      case 45:
        Serial1.print(":CL06\r");
        break;
                
      case 46:
        Serial1.print(":OP07\r");
        break;
                
      case 47:
        Serial1.print(":CL07\r");
        break;
                
      case 48:
        Serial1.print(":OP08\r");
        break;
                
      case 49:
        Serial1.print(":CL08\r");
        break;
                
      case 50:
        Serial1.print(":OP09\r");
        break;
                
      case 51:
        Serial1.print(":CL09\r");
        break;
                
      case 52:
        Serial1.print(":OP10\r");
        break;
                
      case 53:
        Serial1.print(":CL10\r");
        break;

      // Open All Body Panels
      case 54:
        Serial3.print(":OP00\r");
        break;

      // Close All Body Panels         
      case 55:
        Serial3.print(":CL00\r");
        break;
                
      case 56:
        //Toggle Body Panel Data Panel Door
        if (DPLOpen == false){
          Serial3.print(":OP01\r"); //Open the panel 
          delay(550); //give panel time to open
          Serial3.print(":ST01\r"); //Stop the buzz
          DPLOpen = true;
        } else {
          //Close Body Panel 1
          Serial3.print(":CL01\r");
          DPLOpen = false;
        }
        break;
                
      case 57:
        //Close Body Panel 1
        Serial3.print(":CL01\r");
        break;
                
      case 58:
      //Top Utility Arm Toggle
        if (TopUArmOpen == false){
          Serial3.print(":OP02\r"); //Open the panel 
          delay(550); //give panel time to open
          Serial3.print(":ST02\r"); //Stop the buzz
          TopUArmOpen = true;
        } else {
          //Close Utility Arm Panel 2
          Serial3.print(":CL02\r");
          TopUArmOpen = false;
        }
        break;
                
      case 59:
        Serial3.print(":CL02\r");
        break;
                
      case 60:
        //Bottom Utility Arm Toggle
        if (BotUArmOpen == false){
          Serial3.print(":OP03\r"); //Open the panel 
          delay(550); //give panel time to open
          Serial3.print(":ST03\r"); //Stop the buzz
          BotUArmOpen = true;
        } else {
          //Close Utility Arm Panel 2
          Serial3.print(":CL03\r");
          BotUArmOpen = false;
        }
        break;
                
      case 61:
        Serial3.print(":CL03\r");
        break;
                
      case 62:
        //Toggle Left Body Door Panel 4
        if (LeftDoorOpen == false){
          Serial3.print(":OP04\r"); //Open the panel 4
          delay(400); //give panel time to open
          Serial3.print(":ST04\r"); //Stop the buzz
          LeftDoorOpen = true;
        } else {
          //Close Left Door Panel 4
          Serial3.print(":CL04\r");
          LeftDoorOpen = false;
        }
        break;
                
      case 63:
        Serial3.print(":CL04\r");
        break;
                
      case 64:
        Serial3.print(":OP05\r");
        break;
                
      case 65:
        Serial3.print(":CL05\r");
        break;
                
      case 66:
        Serial3.print(":OP06\r");
        break;
                
      case 67:
        Serial3.print(":CL06\r");
        break;
                
      case 68:
        //Toggle Right Body Door Panel 7
        if (RightDoorOpen == false){
          Serial3.print(":OP07\r"); //Open the panel 7
          delay(400); //give panel time to open
          Serial3.print(":ST07\r"); //Stop the buzz
          RightDoorOpen = true;
        } else {
          //Close Right Door Panel 7
          Serial3.print(":CL07\r");
          RightDoorOpen = false;
        }
        break;
                
      case 69:
        Serial3.print(":CL07\r");
        break;
                
      case 70:
        Serial3.print(":OP08\r");
        break;
                
      case 71:
        Serial3.print(":CL08\r");
        break;
                
      case 72:
        Serial3.print(":OP09\r");
        break;
                
      case 73:
        Serial3.print(":CL09\r");
        break;
                
      case 74:
        Serial3.print(":OP10\r");
        break;

      case 75:
        Serial3.print(":CL10\r");
        break;

      case 76:
        Serial3.print("*MO99\r");
        break;

      case 77:
        Serial3.print("*MO00\r");
        break;

      case 78:
        Serial3.print("*MF10\r");
        break;
        //Eebel code start
      case 79:
        //Scream and Wiggle Dome and Body
        Serial1.print(":SE16\r");
        Serial3.print(":SE32\r");
        break;
      case 80:
        //WaveBye
        Serial1.print(":SE17\r");
        break;
      case 81:
        //Utility Arm Open and Close
        Serial3.print(":SE30\r");
        break;
      case 82:
        //Test all body panels/tools
        Serial3.print(":SE31\r");
        break;
      case 83:
        //Use Gripper Arm
        Serial3.print(":SE33\r");
        break;
      case 84:
        //Use Interface Tool
        Serial3.print(":SE34\r");
        break;
      case 85:
        //Use Ping Pong Big Body Doors 
        Serial3.print(":SE35\r");
        break;    
      case 86:
        //Star Wars Disco
        Serial1.print(":SE18\r");
        break;
      case 87:
        //Star Trek Disco
        Serial1.print(":SE19\r");
        break;  
      case 88:
        //Play Next Song
        CurrentSongNum = CurrentSongNum + 1; //First of 5 Custom Song MP3 Files default is 0 at startup
        if (CurrentSongNum > CustomSongMax){   
            CurrentSongNum = 0;
            Serial1.print(MakeSongCommand(1));//Reset to beginning Song and play it
        }  else {
            Serial1.print(MakeSongCommand(CurrentSongNum));//Play Newly selected song
        }
        break;
      case 89:
        //Play Previous Song
        CurrentSongNum = CurrentSongNum - 1; //Previous of 5 Custom Song MP3 Files default is 0 at startup
        
        if (CurrentSongNum < 1){   
            CurrentSongNum = CustomSongMax;
        }
            Serial1.print(MakeSongCommand(CurrentSongNum));//Reset to beginning Song and play it
//        }  else {
//            Serial1.print(MakeSongCommand(CurrentSongNum));//Play Newly selected song
//        }
        break;
    }
      //Eebel code end
  }  // End Std Marcduino Function Calls
   
  if (type == 2) // Custom Button Configuration
  {
   
      if (MP3_num > 181 && MP3_num < 203) // Valid Custom Sound Range Selected - Play Custom Sound Selection
      {
        
        switch (MP3_num)
        {
          
          case 182:
            // Star Wars Disco
             Serial1.print("$87\r");
             break;
             
          case 183:
            // Star Trek Disco
             Serial1.print("$88\r");
             break;
          
          case 184:
            //Meco Darth Vader
             Serial1.print("$809\r");
             break;

          case 185:
            //Here They Come
             Serial1.print("$810\r");
             break;
             
          case 186:
            //Return of the Jedi Finale
             Serial1.print("$811\r");
             break;
          
          case 187:
             Serial1.print("$812\r");
             break;
             
          case 188:
             Serial1.print("$813\r");
             break;
             
          case 189:
             Serial1.print("$814\r");
             break;
          
          case 190:
             Serial1.print("$815\r");
             break;
             
          case 191:
             Serial1.print("$816\r");
             break;
             
          case 192:
             Serial1.print("$817\r");
             break;
          
          case 193:
             Serial1.print("$818\r");
             break;
             
          case 194:
             Serial1.print("$819\r");
             break;
             
          case 195:
             Serial1.print("$820\r");
             break;
          
          case 196:
             Serial1.print("$821\r");
             break;
             
          case 197:
             Serial1.print("$822\r");
             break;
             
          case 198:
             Serial1.print("$823\r");
             break;
          
          case 199:
             Serial1.print("$824\r");
             break;

          case 200:
             Serial1.print("$825\r");
             break;
          case 201:
             //Star Wars Theme
             Serial1.print("$82\r");
             break;
          case 202:
             //Darth Vader Theme
             Serial1.print("$803\r");
             break;
        }     
        
      }
      
      if (panel_type > 0 && panel_type < 10) // Valid panel type selected - perform custom panel functions
      {
        
          // Reset the custom panel flags
          DP1_Status = 0;
          DP2_Status = 0;
          DP3_Status = 0;
          DP4_Status = 0;
          DP5_Status = 0;
          DP6_Status = 0;
          DP7_Status = 0;
          DP8_Status = 0;
          DP9_Status = 0;
          DP10_Status = 0;
        
          if (panel_type > 1)
          {
            Serial1.print(":CL00\r");  // close all the panels prior to next custom routine
            delay(50); // give panel close command time to process before starting next panel command 
          }
        
          switch (panel_type)
          {
            
             case 1:
                Serial1.print(":CL00\r");
                break;
                
             case 2:
                Serial1.print(":SE51\r");
                break;
                
             case 3:
                Serial1.print(":SE52\r");
                break;

             case 4:
                Serial1.print(":SE53\r");
                break;

             case 5:
                Serial1.print(":SE54\r");
                break;

             case 6:
                Serial1.print(":SE55\r");
                break;

             case 7:
                Serial1.print(":SE56\r");
                break;

             case 8:
                Serial1.print(":SE57\r");
                break;

             case 9: // This is the setup section for the custom panel routines
             
                runningCustRoutine = true;
                
                // Configure Dome Panel #1
                if (use_DP1)
                {
                  
                  DP1_Status = 1; 
                  DP1_start = millis();
                  
                  if (DP1_str_delay < 31)
                  {
                    
                       DP1_s_delay = DP1_str_delay; 
                       
                  } else
                  {
                       DP1_Status = 0; 
                  }
                  
                  if (DP1_open_time > 0 && DP1_open_time < 31)
                  {
                    
                       DP1_o_time = DP1_open_time; 
                       
                  } else
                  {
                       DP1_Status = 0; 
                  }
                      
                }
                
                // Configure Dome Panel #2
                if (use_DP2)
                {
                  
                  DP2_Status = 1; 
                  DP2_start = millis();
                  
                  if (DP2_str_delay < 31)
                  {
                    
                       DP2_s_delay = DP2_str_delay; 
                       
                  } else
                  {
                       DP2_Status = 0; 
                  }
                  
                  if (DP2_open_time > 0 && DP2_open_time < 31)
                  {
                    
                       DP2_o_time = DP2_open_time; 
                       
                  } else
                  {
                       DP2_Status = 0; 
                  } 
       
                }
                

                // Configure Dome Panel #3
                if (use_DP3)
                {
                  
                  DP3_Status = 1; 
                  DP3_start = millis();
                  
                  if (DP3_str_delay < 31)
                  {
                    
                       DP3_s_delay = DP3_str_delay; 
                       
                  } else
                  {
                       DP3_Status = 0; 
                  }
                  
                  if (DP3_open_time > 0 && DP3_open_time < 31)
                  {
                    
                       DP3_o_time = DP3_open_time; 
                       
                  } else
                  {
                       DP3_Status = 0; 
                  } 
       
                }
                
                // Configure Dome Panel #4
                if (use_DP4)
                {
                  
                  DP4_Status = 1; 
                  DP4_start = millis();
                  
                  if (DP4_str_delay < 31)
                  {
                    
                       DP4_s_delay = DP4_str_delay; 
                       
                  } else
                  {
                       DP4_Status = 0; 
                  }
                  
                  if (DP4_open_time > 0 && DP4_open_time < 31)
                  {
                    
                       DP4_o_time = DP4_open_time; 
                       
                  } else
                  {
                       DP4_Status = 0; 
                  } 
       
                }
                
                // Configure Dome Panel #5
                if (use_DP5)
                {
                  
                  DP5_Status = 1; 
                  DP5_start = millis();
                  
                  if (DP5_str_delay < 31)
                  {
                    
                       DP5_s_delay = DP5_str_delay; 
                       
                  } else
                  {
                       DP5_Status = 0; 
                  }
                  
                  if (DP5_open_time > 0 && DP5_open_time < 31)
                  {
                    
                       DP5_o_time = DP5_open_time; 
                       
                  } else
                  {
                       DP5_Status = 0; 
                  } 
       
                }
                
                // Configure Dome Panel #6
                if (use_DP6)
                {
                  
                  DP6_Status = 1; 
                  DP6_start = millis();
                  
                  if (DP6_str_delay < 31)
                  {
                    
                       DP6_s_delay = DP6_str_delay; 
                       
                  } else
                  {
                       DP6_Status = 0; 
                  }
                  
                  if (DP6_open_time > 0 && DP6_open_time < 31)
                  {
                    
                       DP6_o_time = DP6_open_time; 
                       
                  } else
                  {
                       DP6_Status = 0; 
                  } 
       
                }
                
                // Configure Dome Panel #7
                if (use_DP7)
                {
                  
                  DP7_Status = 1; 
                  DP7_start = millis();
                  
                  if (DP7_str_delay < 31)
                  {
                    
                       DP7_s_delay = DP7_str_delay; 
                       
                  } else
                  {
                       DP7_Status = 0; 
                  }
                  
                  if (DP7_open_time > 0 && DP7_open_time < 31)
                  {
                    
                       DP7_o_time = DP7_open_time; 
                       
                  } else
                  {
                       DP7_Status = 0; 
                  } 
       
                }
                
                // Configure Dome Panel #8
                if (use_DP8)
                {
                  
                  DP8_Status = 1; 
                  DP8_start = millis();
                  
                  if (DP8_str_delay < 31)
                  {
                    
                       DP8_s_delay = DP8_str_delay; 
                       
                  } else
                  {
                       DP8_Status = 0; 
                  }
                  
                  if (DP8_open_time > 0 && DP8_open_time < 31)
                  {
                    
                       DP8_o_time = DP8_open_time; 
                       
                  } else
                  {
                       DP8_Status = 0; 
                  } 
       
                }
                
                // Configure Dome Panel #9
                if (use_DP9)
                {
                  
                  DP9_Status = 1; 
                  DP9_start = millis();
                  
                  if (DP9_str_delay < 31)
                  {
                    
                       DP9_s_delay = DP9_str_delay; 
                       
                  } else
                  {
                       DP9_Status = 0; 
                  }
                  
                  if (DP9_open_time > 0 && DP9_open_time < 31)
                  {
                    
                       DP9_o_time = DP9_open_time; 
                       
                  } else
                  {
                       DP9_Status = 0; 
                  } 
       
                }
                
                // Configure Dome Panel #10
                if (use_DP10)
                {
                  
                  DP10_Status = 1; 
                  DP10_start = millis();
                  
                  if (DP10_str_delay < 31)
                  {
                    
                       DP10_s_delay = DP10_str_delay; 
                       
                  } else
                  {
                       DP10_Status = 0; 
                  }
                  
                  if (DP10_open_time > 0 && DP10_open_time < 31)
                  {
                    
                       DP10_o_time = DP10_open_time; 
                       
                  } else
                  {
                       DP10_Status = 0; 
                  } 
       
                }
                              
                // If every dome panel config failed to work - reset routine flag to false
                if (DP1_Status + DP2_Status + DP3_Status + DP4_Status + DP5_Status + DP6_Status + DP7_Status + DP8_Status + DP9_Status + DP10_Status == 0)
                {
                   
                   runningCustRoutine = false;

                }
                
                break;           
          }
      }
        
      
      if (LD_type > 0 && LD_type < 9) // Valid Logic Display Selected - Display Custom Logic Display
      {
        
          if (panel_type > 1 && panel_type < 10)  // If a custom panel movement was selected - need to briefly pause before changing light sequence to avoid conflict)
          {   
              delay(30);
          }
        
          switch (LD_type)
          {
            
            case 1:
              Serial1.print("@0T1\r");
              break;
              
            case 2:
              Serial1.print("@0T4\r");
              break;
              
            case 3:
              Serial1.print("@0T5\r");
              break;

            case 4:
              Serial1.print("@0T6\r");
              break;

            case 5:
              Serial1.print("@0T10\r");
              break;

            case 6:
              Serial1.print("@0T11\r");
              break;

            case 7:
              Serial1.print("@0T92\r");
              break;

            case 8:
              Serial1.print("@0T100\r");
              delay(50);
              String custString = "@0M";
              custString += LD_text;
              custString += "\r";
              Serial1.print(custString);
              break;
          }
      }
       
  } 
  
}

// ====================================================================================================================
// This function determines if MarcDuino buttons were selected and calls main processing function for FOOT controller
// ====================================================================================================================
void marcDuinoFoot()
{
   if (PS3NavFoot->PS3NavigationConnected && (PS3NavFoot->getButtonPress(UP) || PS3NavFoot->getButtonPress(DOWN) || PS3NavFoot->getButtonPress(LEFT) || PS3NavFoot->getButtonPress(RIGHT)))
   {
      
       if ((millis() - previousMarcDuinoMillis) > 1000)
       {
            marcDuinoButtonCounter = 0;
            previousMarcDuinoMillis = millis();
       } 
     
       marcDuinoButtonCounter += 1;
         
   } else
   {
       return;    
   }
   
   // Clear inbound buffer of any data sent form the MarcDuino board
   while (Serial1.available()) Serial1.read();

    //------------------------------------ 
    // Send triggers for the base buttons 
    //------------------------------------
    if (PS3NavFoot->getButtonPress(UP) && !PS3NavFoot->getButtonPress(CROSS) && !PS3NavFoot->getButtonPress(CIRCLE) && !PS3NavFoot->getButtonPress(L1) && !PS3NavFoot->getButtonPress(PS) && marcDuinoButtonCounter == 1)
    {

       if (PS3NavDome->PS3NavigationConnected && (PS3NavDome->getButtonPress(CROSS) || PS3NavDome->getButtonPress(CIRCLE) || PS3NavDome->getButtonPress(PS)))
       {
              // Skip this section
       } else
       {     
               marcDuinoButtonPush(btnUP_type, btnUP_MD_func, btnUP_cust_MP3_num, btnUP_cust_LD_type, btnUP_cust_LD_text, btnUP_cust_panel, 
                                 btnUP_use_DP1,
                                 btnUP_DP1_open_start_delay, 
                                 btnUP_DP1_stay_open_time,
                                 btnUP_use_DP2,
                                 btnUP_DP2_open_start_delay, 
                                 btnUP_DP2_stay_open_time,
                                 btnUP_use_DP3,
                                 btnUP_DP3_open_start_delay, 
                                 btnUP_DP3_stay_open_time,
                                 btnUP_use_DP4,
                                 btnUP_DP4_open_start_delay, 
                                 btnUP_DP4_stay_open_time,
                                 btnUP_use_DP5,
                                 btnUP_DP5_open_start_delay, 
                                 btnUP_DP5_stay_open_time,
                                 btnUP_use_DP6,
                                 btnUP_DP6_open_start_delay, 
                                 btnUP_DP6_stay_open_time,
                                 btnUP_use_DP7,
                                 btnUP_DP7_open_start_delay, 
                                 btnUP_DP7_stay_open_time,
                                 btnUP_use_DP8,
                                 btnUP_DP8_open_start_delay, 
                                 btnUP_DP8_stay_open_time,
                                 btnUP_use_DP9,
                                 btnUP_DP9_open_start_delay, 
                                 btnUP_DP9_stay_open_time,
                                 btnUP_use_DP10,
                                 btnUP_DP10_open_start_delay, 
                                 btnUP_DP10_stay_open_time);
                    
                #ifdef SHADOW_VERBOSE      
                     output += "FOOT: btnUP";
                #endif
               
                return;
        
         }
        
    }
    
    if (PS3NavFoot->getButtonPress(DOWN) && !PS3NavFoot->getButtonPress(CROSS) && !PS3NavFoot->getButtonPress(CIRCLE) && !PS3NavFoot->getButtonPress(L1) && !PS3NavFoot->getButtonPress(PS) && marcDuinoButtonCounter == 1)
    {
      
       if (PS3NavDome->PS3NavigationConnected && (PS3NavDome->getButtonPress(CROSS) || PS3NavDome->getButtonPress(CIRCLE) || PS3NavDome->getButtonPress(PS)))
       {
              // Skip this section
       } else
       {     
            marcDuinoButtonPush(btnDown_type, btnDown_MD_func, btnDown_cust_MP3_num, btnDown_cust_LD_type, btnDown_cust_LD_text, btnDown_cust_panel, 
                         btnDown_use_DP1,
                         btnDown_DP1_open_start_delay, 
                         btnDown_DP1_stay_open_time,
                         btnDown_use_DP2,
                         btnDown_DP2_open_start_delay, 
                         btnDown_DP2_stay_open_time,
                         btnDown_use_DP3,
                         btnDown_DP3_open_start_delay, 
                         btnDown_DP3_stay_open_time,
                         btnDown_use_DP4,
                         btnDown_DP4_open_start_delay, 
                         btnDown_DP4_stay_open_time,
                         btnDown_use_DP5,
                         btnDown_DP5_open_start_delay, 
                         btnDown_DP5_stay_open_time,
                         btnDown_use_DP6,
                         btnDown_DP6_open_start_delay, 
                         btnDown_DP6_stay_open_time,
                         btnDown_use_DP7,
                         btnDown_DP7_open_start_delay, 
                         btnDown_DP7_stay_open_time,
                         btnDown_use_DP8,
                         btnDown_DP8_open_start_delay, 
                         btnDown_DP8_stay_open_time,
                         btnDown_use_DP9,
                         btnDown_DP9_open_start_delay, 
                         btnDown_DP9_stay_open_time,
                         btnDown_use_DP10,
                         btnDown_DP10_open_start_delay, 
                         btnDown_DP10_stay_open_time);
                         
        #ifdef SHADOW_VERBOSE      
             output += "FOOT: btnDown";
        #endif
      
       
        return;
       }
    }
    
    if (PS3NavFoot->getButtonPress(LEFT) && !PS3NavFoot->getButtonPress(CROSS) && !PS3NavFoot->getButtonPress(CIRCLE) && !PS3NavFoot->getButtonPress(L1) && !PS3NavFoot->getButtonPress(PS) && marcDuinoButtonCounter == 1)
    {
       if (PS3NavDome->PS3NavigationConnected && (PS3NavDome->getButtonPress(CROSS) || PS3NavDome->getButtonPress(CIRCLE) || PS3NavDome->getButtonPress(PS)))
       {
              // Skip this section
       } else
       {           
            marcDuinoButtonPush(btnLeft_type, btnLeft_MD_func, btnLeft_cust_MP3_num, btnLeft_cust_LD_type, btnLeft_cust_LD_text, btnLeft_cust_panel, 
                         btnLeft_use_DP1,
                         btnLeft_DP1_open_start_delay, 
                         btnLeft_DP1_stay_open_time,
                         btnLeft_use_DP2,
                         btnLeft_DP2_open_start_delay, 
                         btnLeft_DP2_stay_open_time,
                         btnLeft_use_DP3,
                         btnLeft_DP3_open_start_delay, 
                         btnLeft_DP3_stay_open_time,
                         btnLeft_use_DP4,
                         btnLeft_DP4_open_start_delay, 
                         btnLeft_DP4_stay_open_time,
                         btnLeft_use_DP5,
                         btnLeft_DP5_open_start_delay, 
                         btnLeft_DP5_stay_open_time,
                         btnLeft_use_DP6,
                         btnLeft_DP6_open_start_delay, 
                         btnLeft_DP6_stay_open_time,
                         btnLeft_use_DP7,
                         btnLeft_DP7_open_start_delay, 
                         btnLeft_DP7_stay_open_time,
                         btnLeft_use_DP8,
                         btnLeft_DP8_open_start_delay, 
                         btnLeft_DP8_stay_open_time,
                         btnLeft_use_DP9,
                         btnLeft_DP9_open_start_delay, 
                         btnLeft_DP9_stay_open_time,
                         btnLeft_use_DP10,
                         btnLeft_DP10_open_start_delay, 
                         btnLeft_DP10_stay_open_time);
                         
        #ifdef SHADOW_VERBOSE      
             output += "FOOT: btnLeft";
        #endif
       
        return;
       }
        
     }

    if (PS3NavFoot->getButtonPress(RIGHT) && !PS3NavFoot->getButtonPress(CROSS) && !PS3NavFoot->getButtonPress(CIRCLE) && !PS3NavFoot->getButtonPress(L1) && !PS3NavFoot->getButtonPress(PS) && marcDuinoButtonCounter == 1)
    {
      
       if (PS3NavDome->PS3NavigationConnected && (PS3NavDome->getButtonPress(CROSS) || PS3NavDome->getButtonPress(CIRCLE) || PS3NavDome->getButtonPress(PS)))
       {
              // Skip this section
       } else
       {     
             marcDuinoButtonPush(btnRight_type, btnRight_MD_func, btnRight_cust_MP3_num, btnRight_cust_LD_type, btnRight_cust_LD_text, btnRight_cust_panel, 
                         btnRight_use_DP1,
                         btnRight_DP1_open_start_delay, 
                         btnRight_DP1_stay_open_time,
                         btnRight_use_DP2,
                         btnRight_DP2_open_start_delay, 
                         btnRight_DP2_stay_open_time,
                         btnRight_use_DP3,
                         btnRight_DP3_open_start_delay, 
                         btnRight_DP3_stay_open_time,
                         btnRight_use_DP4,
                         btnRight_DP4_open_start_delay, 
                         btnRight_DP4_stay_open_time,
                         btnRight_use_DP5,
                         btnRight_DP5_open_start_delay, 
                         btnRight_DP5_stay_open_time,
                         btnRight_use_DP6,
                         btnRight_DP6_open_start_delay, 
                         btnRight_DP6_stay_open_time,
                         btnRight_use_DP7,
                         btnRight_DP7_open_start_delay, 
                         btnRight_DP7_stay_open_time,
                         btnRight_use_DP8,
                         btnRight_DP8_open_start_delay, 
                         btnRight_DP8_stay_open_time,
                         btnRight_use_DP9,
                         btnRight_DP9_open_start_delay, 
                         btnRight_DP9_stay_open_time,
                         btnRight_use_DP10,
                         btnRight_DP10_open_start_delay, 
                         btnRight_DP10_stay_open_time);
                         
        #ifdef SHADOW_VERBOSE      
             output += "FOOT: btnRight";
        #endif
      
       
        return;
       }
        
    }
    
    //------------------------------------ 
    // Send triggers for the CROSS + base buttons 
    //------------------------------------
    if (((!PS3NavDome->PS3NavigationConnected && PS3NavFoot->getButtonPress(UP) && PS3NavFoot->getButtonPress(CROSS)) || (PS3NavDome->PS3NavigationConnected && PS3NavFoot->getButtonPress(UP) && PS3NavDome->getButtonPress(CROSS))) && marcDuinoButtonCounter == 1)
    {
      
       marcDuinoButtonPush(btnUP_CROSS_type, btnUP_CROSS_MD_func, btnUP_CROSS_cust_MP3_num, btnUP_CROSS_cust_LD_type, btnUP_CROSS_cust_LD_text, btnUP_CROSS_cust_panel, 
                         btnUP_CROSS_use_DP1,
                         btnUP_CROSS_DP1_open_start_delay, 
                         btnUP_CROSS_DP1_stay_open_time,
                         btnUP_CROSS_use_DP2,
                         btnUP_CROSS_DP2_open_start_delay, 
                         btnUP_CROSS_DP2_stay_open_time,
                         btnUP_CROSS_use_DP3,
                         btnUP_CROSS_DP3_open_start_delay, 
                         btnUP_CROSS_DP3_stay_open_time,
                         btnUP_CROSS_use_DP4,
                         btnUP_CROSS_DP4_open_start_delay, 
                         btnUP_CROSS_DP4_stay_open_time,
                         btnUP_CROSS_use_DP5,
                         btnUP_CROSS_DP5_open_start_delay, 
                         btnUP_CROSS_DP5_stay_open_time,
                         btnUP_CROSS_use_DP6,
                         btnUP_CROSS_DP6_open_start_delay, 
                         btnUP_CROSS_DP6_stay_open_time,
                         btnUP_CROSS_use_DP7,
                         btnUP_CROSS_DP7_open_start_delay, 
                         btnUP_CROSS_DP7_stay_open_time,
                         btnUP_CROSS_use_DP8,
                         btnUP_CROSS_DP8_open_start_delay, 
                         btnUP_CROSS_DP8_stay_open_time,
                         btnUP_CROSS_use_DP9,
                         btnUP_CROSS_DP9_open_start_delay, 
                         btnUP_CROSS_DP9_stay_open_time,
                         btnUP_CROSS_use_DP10,
                         btnUP_CROSS_DP10_open_start_delay, 
                         btnUP_CROSS_DP10_stay_open_time);
      
        #ifdef SHADOW_VERBOSE      
             output += "FOOT: btnUP_CROSS";
        #endif
      
       
        return;
        
    }
    
    if (((!PS3NavDome->PS3NavigationConnected && PS3NavFoot->getButtonPress(DOWN) && PS3NavFoot->getButtonPress(CROSS)) || (PS3NavDome->PS3NavigationConnected && PS3NavFoot->getButtonPress(DOWN) && PS3NavDome->getButtonPress(CROSS))) && marcDuinoButtonCounter == 1)
    {
      
       marcDuinoButtonPush(btnDown_CROSS_type, btnDown_CROSS_MD_func, btnDown_CROSS_cust_MP3_num, btnDown_CROSS_cust_LD_type, btnDown_CROSS_cust_LD_text, btnDown_CROSS_cust_panel, 
                         btnDown_CROSS_use_DP1,
                         btnDown_CROSS_DP1_open_start_delay, 
                         btnDown_CROSS_DP1_stay_open_time,
                         btnDown_CROSS_use_DP2,
                         btnDown_CROSS_DP2_open_start_delay, 
                         btnDown_CROSS_DP2_stay_open_time,
                         btnDown_CROSS_use_DP3,
                         btnDown_CROSS_DP3_open_start_delay, 
                         btnDown_CROSS_DP3_stay_open_time,
                         btnDown_CROSS_use_DP4,
                         btnDown_CROSS_DP4_open_start_delay, 
                         btnDown_CROSS_DP4_stay_open_time,
                         btnDown_CROSS_use_DP5,
                         btnDown_CROSS_DP5_open_start_delay, 
                         btnDown_CROSS_DP5_stay_open_time,
                         btnDown_CROSS_use_DP6,
                         btnDown_CROSS_DP6_open_start_delay, 
                         btnDown_CROSS_DP6_stay_open_time,
                         btnDown_CROSS_use_DP7,
                         btnDown_CROSS_DP7_open_start_delay, 
                         btnDown_CROSS_DP7_stay_open_time,
                         btnDown_CROSS_use_DP8,
                         btnDown_CROSS_DP8_open_start_delay, 
                         btnDown_CROSS_DP8_stay_open_time,
                         btnDown_CROSS_use_DP9,
                         btnDown_CROSS_DP9_open_start_delay, 
                         btnDown_CROSS_DP9_stay_open_time,
                         btnDown_CROSS_use_DP10,
                         btnDown_CROSS_DP10_open_start_delay, 
                         btnDown_CROSS_DP10_stay_open_time);
                    
        #ifdef SHADOW_VERBOSE      
             output += "FOOT: btnDown_CROSS";
        #endif
      
       
        return;
        
    }
    
    if (((!PS3NavDome->PS3NavigationConnected && PS3NavFoot->getButtonPress(LEFT) && PS3NavFoot->getButtonPress(CROSS)) || (PS3NavDome->PS3NavigationConnected && PS3NavFoot->getButtonPress(LEFT) && PS3NavDome->getButtonPress(CROSS))) && marcDuinoButtonCounter == 1)
    {
      
       marcDuinoButtonPush(btnLeft_CROSS_type, btnLeft_CROSS_MD_func, btnLeft_CROSS_cust_MP3_num, btnLeft_CROSS_cust_LD_type, btnLeft_CROSS_cust_LD_text, btnLeft_CROSS_cust_panel, 
                         btnLeft_CROSS_use_DP1,
                         btnLeft_CROSS_DP1_open_start_delay, 
                         btnLeft_CROSS_DP1_stay_open_time,
                         btnLeft_CROSS_use_DP2,
                         btnLeft_CROSS_DP2_open_start_delay, 
                         btnLeft_CROSS_DP2_stay_open_time,
                         btnLeft_CROSS_use_DP3,
                         btnLeft_CROSS_DP3_open_start_delay, 
                         btnLeft_CROSS_DP3_stay_open_time,
                         btnLeft_CROSS_use_DP4,
                         btnLeft_CROSS_DP4_open_start_delay, 
                         btnLeft_CROSS_DP4_stay_open_time,
                         btnLeft_CROSS_use_DP5,
                         btnLeft_CROSS_DP5_open_start_delay, 
                         btnLeft_CROSS_DP5_stay_open_time,
                         btnLeft_CROSS_use_DP6,
                         btnLeft_CROSS_DP6_open_start_delay, 
                         btnLeft_CROSS_DP6_stay_open_time,
                         btnLeft_CROSS_use_DP7,
                         btnLeft_CROSS_DP7_open_start_delay, 
                         btnLeft_CROSS_DP7_stay_open_time,
                         btnLeft_CROSS_use_DP8,
                         btnLeft_CROSS_DP8_open_start_delay, 
                         btnLeft_CROSS_DP8_stay_open_time,
                         btnLeft_CROSS_use_DP9,
                         btnLeft_CROSS_DP9_open_start_delay, 
                         btnLeft_CROSS_DP9_stay_open_time,
                         btnLeft_CROSS_use_DP10,
                         btnLeft_CROSS_DP10_open_start_delay, 
                         btnLeft_CROSS_DP10_stay_open_time);
            
        #ifdef SHADOW_VERBOSE      
             output += "FOOT: btnLeft_CROSS";
        #endif
      
       
        return;
        
    }

    if (((!PS3NavDome->PS3NavigationConnected && PS3NavFoot->getButtonPress(RIGHT) && PS3NavFoot->getButtonPress(CROSS)) || (PS3NavDome->PS3NavigationConnected && PS3NavFoot->getButtonPress(RIGHT) && PS3NavDome->getButtonPress(CROSS))) && marcDuinoButtonCounter == 1)
    {
      
       marcDuinoButtonPush(btnRight_CROSS_type, btnRight_CROSS_MD_func, btnRight_CROSS_cust_MP3_num, btnRight_CROSS_cust_LD_type, btnRight_CROSS_cust_LD_text, btnRight_CROSS_cust_panel, 
                         btnRight_CROSS_use_DP1,
                         btnRight_CROSS_DP1_open_start_delay, 
                         btnRight_CROSS_DP1_stay_open_time,
                         btnRight_CROSS_use_DP2,
                         btnRight_CROSS_DP2_open_start_delay, 
                         btnRight_CROSS_DP2_stay_open_time,
                         btnRight_CROSS_use_DP3,
                         btnRight_CROSS_DP3_open_start_delay, 
                         btnRight_CROSS_DP3_stay_open_time,
                         btnRight_CROSS_use_DP4,
                         btnRight_CROSS_DP4_open_start_delay, 
                         btnRight_CROSS_DP4_stay_open_time,
                         btnRight_CROSS_use_DP5,
                         btnRight_CROSS_DP5_open_start_delay, 
                         btnRight_CROSS_DP5_stay_open_time,
                         btnRight_CROSS_use_DP6,
                         btnRight_CROSS_DP6_open_start_delay, 
                         btnRight_CROSS_DP6_stay_open_time,
                         btnRight_CROSS_use_DP7,
                         btnRight_CROSS_DP7_open_start_delay, 
                         btnRight_CROSS_DP7_stay_open_time,
                         btnRight_CROSS_use_DP8,
                         btnRight_CROSS_DP8_open_start_delay, 
                         btnRight_CROSS_DP8_stay_open_time,
                         btnRight_CROSS_use_DP9,
                         btnRight_CROSS_DP9_open_start_delay, 
                         btnRight_CROSS_DP9_stay_open_time,
                         btnRight_CROSS_use_DP10,
                         btnRight_CROSS_DP10_open_start_delay, 
                         btnRight_CROSS_DP10_stay_open_time);
                    
        #ifdef SHADOW_VERBOSE      
             output += "FOOT: btnRight_CROSS";
        #endif
      
       
        return;
        
    }

    //------------------------------------ 
    // Send triggers for the CIRCLE + base buttons 
    //------------------------------------
    if (((!PS3NavDome->PS3NavigationConnected && PS3NavFoot->getButtonPress(UP) && PS3NavFoot->getButtonPress(CIRCLE)) || (PS3NavDome->PS3NavigationConnected && PS3NavFoot->getButtonPress(UP) && PS3NavDome->getButtonPress(CIRCLE))) && marcDuinoButtonCounter == 1)
    {
      
       marcDuinoButtonPush(btnUP_CIRCLE_type, btnUP_CIRCLE_MD_func, btnUP_CIRCLE_cust_MP3_num, btnUP_CIRCLE_cust_LD_type, btnUP_CIRCLE_cust_LD_text, btnUP_CIRCLE_cust_panel, 
                         btnUP_CIRCLE_use_DP1,
                         btnUP_CIRCLE_DP1_open_start_delay, 
                         btnUP_CIRCLE_DP1_stay_open_time,
                         btnUP_CIRCLE_use_DP2,
                         btnUP_CIRCLE_DP2_open_start_delay, 
                         btnUP_CIRCLE_DP2_stay_open_time,
                         btnUP_CIRCLE_use_DP3,
                         btnUP_CIRCLE_DP3_open_start_delay, 
                         btnUP_CIRCLE_DP3_stay_open_time,
                         btnUP_CIRCLE_use_DP4,
                         btnUP_CIRCLE_DP4_open_start_delay, 
                         btnUP_CIRCLE_DP4_stay_open_time,
                         btnUP_CIRCLE_use_DP5,
                         btnUP_CIRCLE_DP5_open_start_delay, 
                         btnUP_CIRCLE_DP5_stay_open_time,
                         btnUP_CIRCLE_use_DP6,
                         btnUP_CIRCLE_DP6_open_start_delay, 
                         btnUP_CIRCLE_DP6_stay_open_time,
                         btnUP_CIRCLE_use_DP7,
                         btnUP_CIRCLE_DP7_open_start_delay, 
                         btnUP_CIRCLE_DP7_stay_open_time,
                         btnUP_CIRCLE_use_DP8,
                         btnUP_CIRCLE_DP8_open_start_delay, 
                         btnUP_CIRCLE_DP8_stay_open_time,
                         btnUP_CIRCLE_use_DP9,
                         btnUP_CIRCLE_DP9_open_start_delay, 
                         btnUP_CIRCLE_DP9_stay_open_time,
                         btnUP_CIRCLE_use_DP10,
                         btnUP_CIRCLE_DP10_open_start_delay, 
                         btnUP_CIRCLE_DP10_stay_open_time);
                    
        #ifdef SHADOW_VERBOSE      
             output += "FOOT: btnUP_CIRCLE";
        #endif
      
       
        return;
        
    }
    
    if (((!PS3NavDome->PS3NavigationConnected && PS3NavFoot->getButtonPress(DOWN) && PS3NavFoot->getButtonPress(CIRCLE)) || (PS3NavDome->PS3NavigationConnected && PS3NavFoot->getButtonPress(DOWN) && PS3NavDome->getButtonPress(CIRCLE))) && marcDuinoButtonCounter == 1)
    {
      
       marcDuinoButtonPush(btnDown_CIRCLE_type, btnDown_CIRCLE_MD_func, btnDown_CIRCLE_cust_MP3_num, btnDown_CIRCLE_cust_LD_type, btnDown_CIRCLE_cust_LD_text, btnDown_CIRCLE_cust_panel, 
                         btnDown_CIRCLE_use_DP1,
                         btnDown_CIRCLE_DP1_open_start_delay, 
                         btnDown_CIRCLE_DP1_stay_open_time,
                         btnDown_CIRCLE_use_DP2,
                         btnDown_CIRCLE_DP2_open_start_delay, 
                         btnDown_CIRCLE_DP2_stay_open_time,
                         btnDown_CIRCLE_use_DP3,
                         btnDown_CIRCLE_DP3_open_start_delay, 
                         btnDown_CIRCLE_DP3_stay_open_time,
                         btnDown_CIRCLE_use_DP4,
                         btnDown_CIRCLE_DP4_open_start_delay, 
                         btnDown_CIRCLE_DP4_stay_open_time,
                         btnDown_CIRCLE_use_DP5,
                         btnDown_CIRCLE_DP5_open_start_delay, 
                         btnDown_CIRCLE_DP5_stay_open_time,
                         btnDown_CIRCLE_use_DP6,
                         btnDown_CIRCLE_DP6_open_start_delay, 
                         btnDown_CIRCLE_DP6_stay_open_time,
                         btnDown_CIRCLE_use_DP7,
                         btnDown_CIRCLE_DP7_open_start_delay, 
                         btnDown_CIRCLE_DP7_stay_open_time,
                         btnDown_CIRCLE_use_DP8,
                         btnDown_CIRCLE_DP8_open_start_delay, 
                         btnDown_CIRCLE_DP8_stay_open_time,
                         btnDown_CIRCLE_use_DP9,
                         btnDown_CIRCLE_DP9_open_start_delay, 
                         btnDown_CIRCLE_DP9_stay_open_time,
                         btnDown_CIRCLE_use_DP10,
                         btnDown_CIRCLE_DP10_open_start_delay, 
                         btnDown_CIRCLE_DP10_stay_open_time);
                    
        #ifdef SHADOW_VERBOSE      
             output += "FOOT: btnDown_CIRCLE";
        #endif
      
       
        return;
        
    }
    
    if (((!PS3NavDome->PS3NavigationConnected && PS3NavFoot->getButtonPress(LEFT) && PS3NavFoot->getButtonPress(CIRCLE)) || (PS3NavDome->PS3NavigationConnected && PS3NavFoot->getButtonPress(LEFT) && PS3NavDome->getButtonPress(CIRCLE))) && marcDuinoButtonCounter == 1)
    {
      
       marcDuinoButtonPush(btnLeft_CIRCLE_type, btnLeft_CIRCLE_MD_func, btnLeft_CIRCLE_cust_MP3_num, btnLeft_CIRCLE_cust_LD_type, btnLeft_CIRCLE_cust_LD_text, btnLeft_CIRCLE_cust_panel, 
                         btnLeft_CIRCLE_use_DP1,
                         btnLeft_CIRCLE_DP1_open_start_delay, 
                         btnLeft_CIRCLE_DP1_stay_open_time,
                         btnLeft_CIRCLE_use_DP2,
                         btnLeft_CIRCLE_DP2_open_start_delay, 
                         btnLeft_CIRCLE_DP2_stay_open_time,
                         btnLeft_CIRCLE_use_DP3,
                         btnLeft_CIRCLE_DP3_open_start_delay, 
                         btnLeft_CIRCLE_DP3_stay_open_time,
                         btnLeft_CIRCLE_use_DP4,
                         btnLeft_CIRCLE_DP4_open_start_delay, 
                         btnLeft_CIRCLE_DP4_stay_open_time,
                         btnLeft_CIRCLE_use_DP5,
                         btnLeft_CIRCLE_DP5_open_start_delay, 
                         btnLeft_CIRCLE_DP5_stay_open_time,
                         btnLeft_CIRCLE_use_DP6,
                         btnLeft_CIRCLE_DP6_open_start_delay, 
                         btnLeft_CIRCLE_DP6_stay_open_time,
                         btnLeft_CIRCLE_use_DP7,
                         btnLeft_CIRCLE_DP7_open_start_delay, 
                         btnLeft_CIRCLE_DP7_stay_open_time,
                         btnLeft_CIRCLE_use_DP8,
                         btnLeft_CIRCLE_DP8_open_start_delay, 
                         btnLeft_CIRCLE_DP8_stay_open_time,
                         btnLeft_CIRCLE_use_DP9,
                         btnLeft_CIRCLE_DP9_open_start_delay, 
                         btnLeft_CIRCLE_DP9_stay_open_time,
                         btnLeft_CIRCLE_use_DP10,
                         btnLeft_CIRCLE_DP10_open_start_delay, 
                         btnLeft_CIRCLE_DP10_stay_open_time);
                    
        #ifdef SHADOW_VERBOSE      
             output += "FOOT: btnLeft_CIRCLE";
        #endif
      
       
        return;
        
    }

    if (((!PS3NavDome->PS3NavigationConnected && PS3NavFoot->getButtonPress(RIGHT) && PS3NavFoot->getButtonPress(CIRCLE)) || (PS3NavDome->PS3NavigationConnected && PS3NavFoot->getButtonPress(RIGHT) && PS3NavDome->getButtonPress(CIRCLE))) && marcDuinoButtonCounter == 1)
    {
      
       marcDuinoButtonPush(btnRight_CIRCLE_type, btnRight_CIRCLE_MD_func, btnRight_CIRCLE_cust_MP3_num, btnRight_CIRCLE_cust_LD_type, btnRight_CIRCLE_cust_LD_text, btnRight_CIRCLE_cust_panel, 
                         btnRight_CIRCLE_use_DP1,
                         btnRight_CIRCLE_DP1_open_start_delay, 
                         btnRight_CIRCLE_DP1_stay_open_time,
                         btnRight_CIRCLE_use_DP2,
                         btnRight_CIRCLE_DP2_open_start_delay, 
                         btnRight_CIRCLE_DP2_stay_open_time,
                         btnRight_CIRCLE_use_DP3,
                         btnRight_CIRCLE_DP3_open_start_delay, 
                         btnRight_CIRCLE_DP3_stay_open_time,
                         btnRight_CIRCLE_use_DP4,
                         btnRight_CIRCLE_DP4_open_start_delay, 
                         btnRight_CIRCLE_DP4_stay_open_time,
                         btnRight_CIRCLE_use_DP5,
                         btnRight_CIRCLE_DP5_open_start_delay, 
                         btnRight_CIRCLE_DP5_stay_open_time,
                         btnRight_CIRCLE_use_DP6,
                         btnRight_CIRCLE_DP6_open_start_delay, 
                         btnRight_CIRCLE_DP6_stay_open_time,
                         btnRight_CIRCLE_use_DP7,
                         btnRight_CIRCLE_DP7_open_start_delay, 
                         btnRight_CIRCLE_DP7_stay_open_time,
                         btnRight_CIRCLE_use_DP8,
                         btnRight_CIRCLE_DP8_open_start_delay, 
                         btnRight_CIRCLE_DP8_stay_open_time,
                         btnRight_CIRCLE_use_DP9,
                         btnRight_CIRCLE_DP9_open_start_delay, 
                         btnRight_CIRCLE_DP9_stay_open_time,
                         btnRight_CIRCLE_use_DP10,
                         btnRight_CIRCLE_DP10_open_start_delay, 
                         btnRight_CIRCLE_DP10_stay_open_time);
            
        
        #ifdef SHADOW_VERBOSE      
             output += "FOOT: btnRight_CIRCLE";
        #endif
      
       
        return;
        
    }
    
    //------------------------------------ 
    // Send triggers for the L1 + base buttons 
    //------------------------------------
    if (PS3NavFoot->getButtonPress(UP) && PS3NavFoot->getButtonPress(L1) && marcDuinoButtonCounter == 1)
    {
      
       marcDuinoButtonPush(btnUP_L1_type, btnUP_L1_MD_func, btnUP_L1_cust_MP3_num, btnUP_L1_cust_LD_type, btnUP_L1_cust_LD_text, btnUP_L1_cust_panel, 
                         btnUP_L1_use_DP1,
                         btnUP_L1_DP1_open_start_delay, 
                         btnUP_L1_DP1_stay_open_time,
                         btnUP_L1_use_DP2,
                         btnUP_L1_DP2_open_start_delay, 
                         btnUP_L1_DP2_stay_open_time,
                         btnUP_L1_use_DP3,
                         btnUP_L1_DP3_open_start_delay, 
                         btnUP_L1_DP3_stay_open_time,
                         btnUP_L1_use_DP4,
                         btnUP_L1_DP4_open_start_delay, 
                         btnUP_L1_DP4_stay_open_time,
                         btnUP_L1_use_DP5,
                         btnUP_L1_DP5_open_start_delay, 
                         btnUP_L1_DP5_stay_open_time,
                         btnUP_L1_use_DP6,
                         btnUP_L1_DP6_open_start_delay, 
                         btnUP_L1_DP6_stay_open_time,
                         btnUP_L1_use_DP7,
                         btnUP_L1_DP7_open_start_delay, 
                         btnUP_L1_DP7_stay_open_time,
                         btnUP_L1_use_DP8,
                         btnUP_L1_DP8_open_start_delay, 
                         btnUP_L1_DP8_stay_open_time,
                         btnUP_L1_use_DP9,
                         btnUP_L1_DP9_open_start_delay, 
                         btnUP_L1_DP9_stay_open_time,
                         btnUP_L1_use_DP10,
                         btnUP_L1_DP10_open_start_delay, 
                         btnUP_L1_DP10_stay_open_time);
            
        #ifdef SHADOW_VERBOSE      
             output += "FOOT: btnUP_L1";
        #endif
      
       
        return;
        
    }
    
    if (PS3NavFoot->getButtonPress(DOWN) && PS3NavFoot->getButtonPress(L1) && marcDuinoButtonCounter == 1)
    {
      
       marcDuinoButtonPush(btnDown_L1_type, btnDown_L1_MD_func, btnDown_L1_cust_MP3_num, btnDown_L1_cust_LD_type, btnDown_L1_cust_LD_text, btnDown_L1_cust_panel, 
                         btnDown_L1_use_DP1,
                         btnDown_L1_DP1_open_start_delay, 
                         btnDown_L1_DP1_stay_open_time,
                         btnDown_L1_use_DP2,
                         btnDown_L1_DP2_open_start_delay, 
                         btnDown_L1_DP2_stay_open_time,
                         btnDown_L1_use_DP3,
                         btnDown_L1_DP3_open_start_delay, 
                         btnDown_L1_DP3_stay_open_time,
                         btnDown_L1_use_DP4,
                         btnDown_L1_DP4_open_start_delay, 
                         btnDown_L1_DP4_stay_open_time,
                         btnDown_L1_use_DP5,
                         btnDown_L1_DP5_open_start_delay, 
                         btnDown_L1_DP5_stay_open_time,
                         btnDown_L1_use_DP6,
                         btnDown_L1_DP6_open_start_delay, 
                         btnDown_L1_DP6_stay_open_time,
                         btnDown_L1_use_DP7,
                         btnDown_L1_DP7_open_start_delay, 
                         btnDown_L1_DP7_stay_open_time,
                         btnDown_L1_use_DP8,
                         btnDown_L1_DP8_open_start_delay, 
                         btnDown_L1_DP8_stay_open_time,
                         btnDown_L1_use_DP9,
                         btnDown_L1_DP9_open_start_delay, 
                         btnDown_L1_DP9_stay_open_time,
                         btnDown_L1_use_DP10,
                         btnDown_L1_DP10_open_start_delay, 
                         btnDown_L1_DP10_stay_open_time);
                    
        #ifdef SHADOW_VERBOSE      
             output += "FOOT: btnDown_L1";
        #endif
      
       
        return;
        
    }
    
    if (PS3NavFoot->getButtonPress(LEFT) && PS3NavFoot->getButtonPress(L1) && marcDuinoButtonCounter == 1)
    {
      
       marcDuinoButtonPush(btnLeft_L1_type, btnLeft_L1_MD_func, btnLeft_L1_cust_MP3_num, btnLeft_L1_cust_LD_type, btnLeft_L1_cust_LD_text, btnLeft_L1_cust_panel, 
                         btnLeft_L1_use_DP1,
                         btnLeft_L1_DP1_open_start_delay, 
                         btnLeft_L1_DP1_stay_open_time,
                         btnLeft_L1_use_DP2,
                         btnLeft_L1_DP2_open_start_delay, 
                         btnLeft_L1_DP2_stay_open_time,
                         btnLeft_L1_use_DP3,
                         btnLeft_L1_DP3_open_start_delay, 
                         btnLeft_L1_DP3_stay_open_time,
                         btnLeft_L1_use_DP4,
                         btnLeft_L1_DP4_open_start_delay, 
                         btnLeft_L1_DP4_stay_open_time,
                         btnLeft_L1_use_DP5,
                         btnLeft_L1_DP5_open_start_delay, 
                         btnLeft_L1_DP5_stay_open_time,
                         btnLeft_L1_use_DP6,
                         btnLeft_L1_DP6_open_start_delay, 
                         btnLeft_L1_DP6_stay_open_time,
                         btnLeft_L1_use_DP7,
                         btnLeft_L1_DP7_open_start_delay, 
                         btnLeft_L1_DP7_stay_open_time,
                         btnLeft_L1_use_DP8,
                         btnLeft_L1_DP8_open_start_delay, 
                         btnLeft_L1_DP8_stay_open_time,
                         btnLeft_L1_use_DP9,
                         btnLeft_L1_DP9_open_start_delay, 
                         btnLeft_L1_DP9_stay_open_time,
                         btnLeft_L1_use_DP10,
                         btnLeft_L1_DP10_open_start_delay, 
                         btnLeft_L1_DP10_stay_open_time);
                    
        #ifdef SHADOW_VERBOSE      
             output += "FOOT: btnLeft_L1";
        #endif
      
       
        return;
        
    }

    if (PS3NavFoot->getButtonPress(RIGHT) && PS3NavFoot->getButtonPress(L1) && marcDuinoButtonCounter == 1)
    {
      
       marcDuinoButtonPush(btnRight_L1_type, btnRight_L1_MD_func, btnRight_L1_cust_MP3_num, btnRight_L1_cust_LD_type, btnRight_L1_cust_LD_text, btnRight_L1_cust_panel, 
                         btnRight_L1_use_DP1,
                         btnRight_L1_DP1_open_start_delay, 
                         btnRight_L1_DP1_stay_open_time,
                         btnRight_L1_use_DP2,
                         btnRight_L1_DP2_open_start_delay, 
                         btnRight_L1_DP2_stay_open_time,
                         btnRight_L1_use_DP3,
                         btnRight_L1_DP3_open_start_delay, 
                         btnRight_L1_DP3_stay_open_time,
                         btnRight_L1_use_DP4,
                         btnRight_L1_DP4_open_start_delay, 
                         btnRight_L1_DP4_stay_open_time,
                         btnRight_L1_use_DP5,
                         btnRight_L1_DP5_open_start_delay, 
                         btnRight_L1_DP5_stay_open_time,
                         btnRight_L1_use_DP6,
                         btnRight_L1_DP6_open_start_delay, 
                         btnRight_L1_DP6_stay_open_time,
                         btnRight_L1_use_DP7,
                         btnRight_L1_DP7_open_start_delay, 
                         btnRight_L1_DP7_stay_open_time,
                         btnRight_L1_use_DP8,
                         btnRight_L1_DP8_open_start_delay, 
                         btnRight_L1_DP8_stay_open_time,
                         btnRight_L1_use_DP9,
                         btnRight_L1_DP9_open_start_delay, 
                         btnRight_L1_DP9_stay_open_time,
                         btnRight_L1_use_DP10,
                         btnRight_L1_DP10_open_start_delay, 
                         btnRight_L1_DP10_stay_open_time);
                   
        #ifdef SHADOW_VERBOSE      
             output += "FOOT: btnRight_L1";
        #endif
      
       
        return;
        
    }
    
    //------------------------------------ 
    // Send triggers for the PS + base buttons 
    //------------------------------------
    if (((!PS3NavDome->PS3NavigationConnected && PS3NavFoot->getButtonPress(UP) && PS3NavFoot->getButtonPress(PS)) || (PS3NavDome->PS3NavigationConnected && PS3NavFoot->getButtonPress(UP) && PS3NavDome->getButtonPress(PS))) && marcDuinoButtonCounter == 1)
    {
      
       marcDuinoButtonPush(btnUP_PS_type, btnUP_PS_MD_func, btnUP_PS_cust_MP3_num, btnUP_PS_cust_LD_type, btnUP_PS_cust_LD_text, btnUP_PS_cust_panel, 
                         btnUP_PS_use_DP1,
                         btnUP_PS_DP1_open_start_delay, 
                         btnUP_PS_DP1_stay_open_time,
                         btnUP_PS_use_DP2,
                         btnUP_PS_DP2_open_start_delay, 
                         btnUP_PS_DP2_stay_open_time,
                         btnUP_PS_use_DP3,
                         btnUP_PS_DP3_open_start_delay, 
                         btnUP_PS_DP3_stay_open_time,
                         btnUP_PS_use_DP4,
                         btnUP_PS_DP4_open_start_delay, 
                         btnUP_PS_DP4_stay_open_time,
                         btnUP_PS_use_DP5,
                         btnUP_PS_DP5_open_start_delay, 
                         btnUP_PS_DP5_stay_open_time,
                         btnUP_PS_use_DP6,
                         btnUP_PS_DP6_open_start_delay, 
                         btnUP_PS_DP6_stay_open_time,
                         btnUP_PS_use_DP7,
                         btnUP_PS_DP7_open_start_delay, 
                         btnUP_PS_DP7_stay_open_time,
                         btnUP_PS_use_DP8,
                         btnUP_PS_DP8_open_start_delay, 
                         btnUP_PS_DP8_stay_open_time,
                         btnUP_PS_use_DP9,
                         btnUP_PS_DP9_open_start_delay, 
                         btnUP_PS_DP9_stay_open_time,
                         btnUP_PS_use_DP10,
                         btnUP_PS_DP10_open_start_delay, 
                         btnUP_PS_DP10_stay_open_time);
            
        #ifdef SHADOW_VERBOSE      
             output += "FOOT: btnUP_PS";
        #endif
      
       
        return;
        
    }
    
    if (((!PS3NavDome->PS3NavigationConnected && PS3NavFoot->getButtonPress(DOWN) && PS3NavFoot->getButtonPress(PS)) || (PS3NavDome->PS3NavigationConnected && PS3NavFoot->getButtonPress(DOWN) && PS3NavDome->getButtonPress(PS))) && marcDuinoButtonCounter == 1)
    {
      
       marcDuinoButtonPush(btnDown_PS_type, btnDown_PS_MD_func, btnDown_PS_cust_MP3_num, btnDown_PS_cust_LD_type, btnDown_PS_cust_LD_text, btnDown_PS_cust_panel, 
                         btnDown_PS_use_DP1,
                         btnDown_PS_DP1_open_start_delay, 
                         btnDown_PS_DP1_stay_open_time,
                         btnDown_PS_use_DP2,
                         btnDown_PS_DP2_open_start_delay, 
                         btnDown_PS_DP2_stay_open_time,
                         btnDown_PS_use_DP3,
                         btnDown_PS_DP3_open_start_delay, 
                         btnDown_PS_DP3_stay_open_time,
                         btnDown_PS_use_DP4,
                         btnDown_PS_DP4_open_start_delay, 
                         btnDown_PS_DP4_stay_open_time,
                         btnDown_PS_use_DP5,
                         btnDown_PS_DP5_open_start_delay, 
                         btnDown_PS_DP5_stay_open_time,
                         btnDown_PS_use_DP6,
                         btnDown_PS_DP6_open_start_delay, 
                         btnDown_PS_DP6_stay_open_time,
                         btnDown_PS_use_DP7,
                         btnDown_PS_DP7_open_start_delay, 
                         btnDown_PS_DP7_stay_open_time,
                         btnDown_PS_use_DP8,
                         btnDown_PS_DP8_open_start_delay, 
                         btnDown_PS_DP8_stay_open_time,
                         btnDown_PS_use_DP9,
                         btnDown_PS_DP9_open_start_delay, 
                         btnDown_PS_DP9_stay_open_time,
                         btnDown_PS_use_DP10,
                         btnDown_PS_DP10_open_start_delay, 
                         btnDown_PS_DP10_stay_open_time);
                    
        #ifdef SHADOW_VERBOSE      
             output += "FOOT: btnDown_PS";
        #endif
      
       
        return;
        
    }
    
    if (((!PS3NavDome->PS3NavigationConnected && PS3NavFoot->getButtonPress(LEFT) && PS3NavFoot->getButtonPress(PS)) || (PS3NavDome->PS3NavigationConnected && PS3NavFoot->getButtonPress(LEFT) && PS3NavDome->getButtonPress(PS))) && marcDuinoButtonCounter == 1)
    {
      
       marcDuinoButtonPush(btnLeft_PS_type, btnLeft_PS_MD_func, btnLeft_PS_cust_MP3_num, btnLeft_PS_cust_LD_type, btnLeft_PS_cust_LD_text, btnLeft_PS_cust_panel, 
                         btnLeft_PS_use_DP1,
                         btnLeft_PS_DP1_open_start_delay, 
                         btnLeft_PS_DP1_stay_open_time,
                         btnLeft_PS_use_DP2,
                         btnLeft_PS_DP2_open_start_delay, 
                         btnLeft_PS_DP2_stay_open_time,
                         btnLeft_PS_use_DP3,
                         btnLeft_PS_DP3_open_start_delay, 
                         btnLeft_PS_DP3_stay_open_time,
                         btnLeft_PS_use_DP4,
                         btnLeft_PS_DP4_open_start_delay, 
                         btnLeft_PS_DP4_stay_open_time,
                         btnLeft_PS_use_DP5,
                         btnLeft_PS_DP5_open_start_delay, 
                         btnLeft_PS_DP5_stay_open_time,
                         btnLeft_PS_use_DP6,
                         btnLeft_PS_DP6_open_start_delay, 
                         btnLeft_PS_DP6_stay_open_time,
                         btnLeft_PS_use_DP7,
                         btnLeft_PS_DP7_open_start_delay, 
                         btnLeft_PS_DP7_stay_open_time,
                         btnLeft_PS_use_DP8,
                         btnLeft_PS_DP8_open_start_delay, 
                         btnLeft_PS_DP8_stay_open_time,
                         btnLeft_PS_use_DP9,
                         btnLeft_PS_DP9_open_start_delay, 
                         btnLeft_PS_DP9_stay_open_time,
                         btnLeft_PS_use_DP10,
                         btnLeft_PS_DP10_open_start_delay, 
                         btnLeft_PS_DP10_stay_open_time);
            
        #ifdef SHADOW_VERBOSE      
             output += "FOOT: btnLeft_PS";
        #endif
      
       
        return;
        
    }

    if (((!PS3NavDome->PS3NavigationConnected && PS3NavFoot->getButtonPress(RIGHT) && PS3NavFoot->getButtonPress(PS)) || (PS3NavDome->PS3NavigationConnected && PS3NavFoot->getButtonPress(RIGHT) && PS3NavDome->getButtonPress(PS))) && marcDuinoButtonCounter == 1)
    {
      
       marcDuinoButtonPush(btnRight_PS_type, btnRight_PS_MD_func, btnRight_PS_cust_MP3_num, btnRight_PS_cust_LD_type, btnRight_PS_cust_LD_text, btnRight_PS_cust_panel, 
                         btnRight_PS_use_DP1,
                         btnRight_PS_DP1_open_start_delay, 
                         btnRight_PS_DP1_stay_open_time,
                         btnRight_PS_use_DP2,
                         btnRight_PS_DP2_open_start_delay, 
                         btnRight_PS_DP2_stay_open_time,
                         btnRight_PS_use_DP3,
                         btnRight_PS_DP3_open_start_delay, 
                         btnRight_PS_DP3_stay_open_time,
                         btnRight_PS_use_DP4,
                         btnRight_PS_DP4_open_start_delay, 
                         btnRight_PS_DP4_stay_open_time,
                         btnRight_PS_use_DP5,
                         btnRight_PS_DP5_open_start_delay, 
                         btnRight_PS_DP5_stay_open_time,
                         btnRight_PS_use_DP6,
                         btnRight_PS_DP6_open_start_delay, 
                         btnRight_PS_DP6_stay_open_time,
                         btnRight_PS_use_DP7,
                         btnRight_PS_DP7_open_start_delay, 
                         btnRight_PS_DP7_stay_open_time,
                         btnRight_PS_use_DP8,
                         btnRight_PS_DP8_open_start_delay, 
                         btnRight_PS_DP8_stay_open_time,
                         btnRight_PS_use_DP9,
                         btnRight_PS_DP9_open_start_delay, 
                         btnRight_PS_DP9_stay_open_time,
                         btnRight_PS_use_DP10,
                         btnRight_PS_DP10_open_start_delay, 
                         btnRight_PS_DP10_stay_open_time);
                    
        #ifdef SHADOW_VERBOSE      
             output += "FOOT: btnRight_PS";
        #endif
      
       
        return;
        
    }

}

// ===================================================================================================================
// This function determines if MarcDuino buttons were selected and calls main processing function for DOME Controller
// ===================================================================================================================
void marcDuinoDome()
{
   if (PS3NavDome->PS3NavigationConnected && (PS3NavDome->getButtonPress(UP) || PS3NavDome->getButtonPress(DOWN) || PS3NavDome->getButtonPress(LEFT) || PS3NavDome->getButtonPress(RIGHT)))
   {
      
       if ((millis() - previousMarcDuinoMillis) > 1000)
       {
            marcDuinoButtonCounter = 0;
            previousMarcDuinoMillis = millis();
       } 
     
       marcDuinoButtonCounter += 1;
         
   } else
   {
       return;    
   }
   
   // Clear inbound buffer of any data sent form the MarcDuino board
   while (Serial1.available()) Serial1.read();

    //------------------------------------ 
    // Send triggers for the base buttons 
    //------------------------------------
    if (PS3NavDome->getButtonPress(UP) && !PS3NavDome->getButtonPress(CROSS) && !PS3NavDome->getButtonPress(CIRCLE) && !PS3NavDome->getButtonPress(L1) && !PS3NavDome->getButtonPress(PS) && !PS3NavFoot->getButtonPress(CROSS) && !PS3NavFoot->getButtonPress(CIRCLE) && !PS3NavFoot->getButtonPress(PS) && marcDuinoButtonCounter == 1)
    {
      
       marcDuinoButtonPush(1, FTbtnUP_MD_func, btnUP_cust_MP3_num, btnUP_cust_LD_type, btnUP_cust_LD_text, btnUP_cust_panel, 
                         btnUP_use_DP1,
                         btnUP_DP1_open_start_delay, 
                         btnUP_DP1_stay_open_time,
                         btnUP_use_DP2,
                         btnUP_DP2_open_start_delay, 
                         btnUP_DP2_stay_open_time,
                         btnUP_use_DP3,
                         btnUP_DP3_open_start_delay, 
                         btnUP_DP3_stay_open_time,
                         btnUP_use_DP4,
                         btnUP_DP4_open_start_delay, 
                         btnUP_DP4_stay_open_time,
                         btnUP_use_DP5,
                         btnUP_DP5_open_start_delay, 
                         btnUP_DP5_stay_open_time,
                         btnUP_use_DP6,
                         btnUP_DP6_open_start_delay, 
                         btnUP_DP6_stay_open_time,
                         btnUP_use_DP7,
                         btnUP_DP7_open_start_delay, 
                         btnUP_DP7_stay_open_time,
                         btnUP_use_DP8,
                         btnUP_DP8_open_start_delay, 
                         btnUP_DP8_stay_open_time,
                         btnUP_use_DP9,
                         btnUP_DP9_open_start_delay, 
                         btnUP_DP9_stay_open_time,
                         btnUP_use_DP10,
                         btnUP_DP10_open_start_delay, 
                         btnUP_DP10_stay_open_time);
            
        #ifdef SHADOW_VERBOSE      
             output += "DOME: btnUP";
        #endif
      
        return;
        
    }
    
    if (PS3NavDome->getButtonPress(DOWN) && !PS3NavDome->getButtonPress(CROSS) && !PS3NavDome->getButtonPress(CIRCLE) && !PS3NavDome->getButtonPress(L1) && !PS3NavDome->getButtonPress(PS) && !PS3NavFoot->getButtonPress(CROSS) && !PS3NavFoot->getButtonPress(CIRCLE) && !PS3NavFoot->getButtonPress(PS) && marcDuinoButtonCounter == 1)
    {
      
       marcDuinoButtonPush(1, FTbtnDown_MD_func, btnDown_cust_MP3_num, btnDown_cust_LD_type, btnDown_cust_LD_text, btnDown_cust_panel, 
                         btnDown_use_DP1,
                         btnDown_DP1_open_start_delay, 
                         btnDown_DP1_stay_open_time,
                         btnDown_use_DP2,
                         btnDown_DP2_open_start_delay, 
                         btnDown_DP2_stay_open_time,
                         btnDown_use_DP3,
                         btnDown_DP3_open_start_delay, 
                         btnDown_DP3_stay_open_time,
                         btnDown_use_DP4,
                         btnDown_DP4_open_start_delay, 
                         btnDown_DP4_stay_open_time,
                         btnDown_use_DP5,
                         btnDown_DP5_open_start_delay, 
                         btnDown_DP5_stay_open_time,
                         btnDown_use_DP6,
                         btnDown_DP6_open_start_delay, 
                         btnDown_DP6_stay_open_time,
                         btnDown_use_DP7,
                         btnDown_DP7_open_start_delay, 
                         btnDown_DP7_stay_open_time,
                         btnDown_use_DP8,
                         btnDown_DP8_open_start_delay, 
                         btnDown_DP8_stay_open_time,
                         btnDown_use_DP9,
                         btnDown_DP9_open_start_delay, 
                         btnDown_DP9_stay_open_time,
                         btnDown_use_DP10,
                         btnDown_DP10_open_start_delay, 
                         btnDown_DP10_stay_open_time);
                         
        #ifdef SHADOW_VERBOSE      
             output += "DOME: btnDown";
        #endif
      
        return;      
    }
    
    if (PS3NavDome->getButtonPress(LEFT) && !PS3NavDome->getButtonPress(CROSS) && !PS3NavDome->getButtonPress(CIRCLE) && !PS3NavDome->getButtonPress(L1) && !PS3NavDome->getButtonPress(PS) && !PS3NavFoot->getButtonPress(CROSS) && !PS3NavFoot->getButtonPress(CIRCLE) && !PS3NavFoot->getButtonPress(PS) && marcDuinoButtonCounter == 1)
    {
      
       marcDuinoButtonPush(1, FTbtnLeft_MD_func, btnLeft_cust_MP3_num, btnLeft_cust_LD_type, btnLeft_cust_LD_text, btnLeft_cust_panel, 
                         btnLeft_use_DP1,
                         btnLeft_DP1_open_start_delay, 
                         btnLeft_DP1_stay_open_time,
                         btnLeft_use_DP2,
                         btnLeft_DP2_open_start_delay, 
                         btnLeft_DP2_stay_open_time,
                         btnLeft_use_DP3,
                         btnLeft_DP3_open_start_delay, 
                         btnLeft_DP3_stay_open_time,
                         btnLeft_use_DP4,
                         btnLeft_DP4_open_start_delay, 
                         btnLeft_DP4_stay_open_time,
                         btnLeft_use_DP5,
                         btnLeft_DP5_open_start_delay, 
                         btnLeft_DP5_stay_open_time,
                         btnLeft_use_DP6,
                         btnLeft_DP6_open_start_delay, 
                         btnLeft_DP6_stay_open_time,
                         btnLeft_use_DP7,
                         btnLeft_DP7_open_start_delay, 
                         btnLeft_DP7_stay_open_time,
                         btnLeft_use_DP8,
                         btnLeft_DP8_open_start_delay, 
                         btnLeft_DP8_stay_open_time,
                         btnLeft_use_DP9,
                         btnLeft_DP9_open_start_delay, 
                         btnLeft_DP9_stay_open_time,
                         btnLeft_use_DP10,
                         btnLeft_DP10_open_start_delay, 
                         btnLeft_DP10_stay_open_time);
                         
        #ifdef SHADOW_VERBOSE      
             output += "DOME: btnLeft";
        #endif
       
        return;
        
    }

    if (PS3NavDome->getButtonPress(RIGHT) && !PS3NavDome->getButtonPress(CROSS) && !PS3NavDome->getButtonPress(CIRCLE) && !PS3NavDome->getButtonPress(L1) && !PS3NavDome->getButtonPress(PS) && !PS3NavFoot->getButtonPress(CROSS) && !PS3NavFoot->getButtonPress(CIRCLE) && !PS3NavFoot->getButtonPress(PS) && marcDuinoButtonCounter == 1)
    {
      
       marcDuinoButtonPush(1, FTbtnRight_MD_func, btnRight_cust_MP3_num, btnRight_cust_LD_type, btnRight_cust_LD_text, btnRight_cust_panel, 
                         btnRight_use_DP1,
                         btnRight_DP1_open_start_delay, 
                         btnRight_DP1_stay_open_time,
                         btnRight_use_DP2,
                         btnRight_DP2_open_start_delay, 
                         btnRight_DP2_stay_open_time,
                         btnRight_use_DP3,
                         btnRight_DP3_open_start_delay, 
                         btnRight_DP3_stay_open_time,
                         btnRight_use_DP4,
                         btnRight_DP4_open_start_delay, 
                         btnRight_DP4_stay_open_time,
                         btnRight_use_DP5,
                         btnRight_DP5_open_start_delay, 
                         btnRight_DP5_stay_open_time,
                         btnRight_use_DP6,
                         btnRight_DP6_open_start_delay, 
                         btnRight_DP6_stay_open_time,
                         btnRight_use_DP7,
                         btnRight_DP7_open_start_delay, 
                         btnRight_DP7_stay_open_time,
                         btnRight_use_DP8,
                         btnRight_DP8_open_start_delay, 
                         btnRight_DP8_stay_open_time,
                         btnRight_use_DP9,
                         btnRight_DP9_open_start_delay, 
                         btnRight_DP9_stay_open_time,
                         btnRight_use_DP10,
                         btnRight_DP10_open_start_delay, 
                         btnRight_DP10_stay_open_time);
                         
        #ifdef SHADOW_VERBOSE      
             output += "DOME: btnRight";
        #endif
      
      
        return;
        
    }
    
    //------------------------------------ 
    // Send triggers for the CROSS + base buttons 
    //------------------------------------
    if (PS3NavDome->getButtonPress(UP) && PS3NavFoot->getButtonPress(CROSS) && marcDuinoButtonCounter == 1)
    {
      
       marcDuinoButtonPush(1, FTbtnUP_CROSS_MD_func, btnUP_CROSS_cust_MP3_num, btnUP_CROSS_cust_LD_type, btnUP_CROSS_cust_LD_text, btnUP_CROSS_cust_panel, 
                         btnUP_CROSS_use_DP1,
                         btnUP_CROSS_DP1_open_start_delay, 
                         btnUP_CROSS_DP1_stay_open_time,
                         btnUP_CROSS_use_DP2,
                         btnUP_CROSS_DP2_open_start_delay, 
                         btnUP_CROSS_DP2_stay_open_time,
                         btnUP_CROSS_use_DP3,
                         btnUP_CROSS_DP3_open_start_delay, 
                         btnUP_CROSS_DP3_stay_open_time,
                         btnUP_CROSS_use_DP4,
                         btnUP_CROSS_DP4_open_start_delay, 
                         btnUP_CROSS_DP4_stay_open_time,
                         btnUP_CROSS_use_DP5,
                         btnUP_CROSS_DP5_open_start_delay, 
                         btnUP_CROSS_DP5_stay_open_time,
                         btnUP_CROSS_use_DP6,
                         btnUP_CROSS_DP6_open_start_delay, 
                         btnUP_CROSS_DP6_stay_open_time,
                         btnUP_CROSS_use_DP7,
                         btnUP_CROSS_DP7_open_start_delay, 
                         btnUP_CROSS_DP7_stay_open_time,
                         btnUP_CROSS_use_DP8,
                         btnUP_CROSS_DP8_open_start_delay, 
                         btnUP_CROSS_DP8_stay_open_time,
                         btnUP_CROSS_use_DP9,
                         btnUP_CROSS_DP9_open_start_delay, 
                         btnUP_CROSS_DP9_stay_open_time,
                         btnUP_CROSS_use_DP10,
                         btnUP_CROSS_DP10_open_start_delay, 
                         btnUP_CROSS_DP10_stay_open_time);
      
        #ifdef SHADOW_VERBOSE      
             output += "DOME: btnUP_CROSS";
        #endif
      
      
        return;
        
    }
    
    if (PS3NavDome->getButtonPress(DOWN) && PS3NavFoot->getButtonPress(CROSS) && marcDuinoButtonCounter == 1)
    {
      
       marcDuinoButtonPush(1, FTbtnDown_CROSS_MD_func, btnDown_CROSS_cust_MP3_num, btnDown_CROSS_cust_LD_type, btnDown_CROSS_cust_LD_text, btnDown_CROSS_cust_panel, 
                         btnDown_CROSS_use_DP1,
                         btnDown_CROSS_DP1_open_start_delay, 
                         btnDown_CROSS_DP1_stay_open_time,
                         btnDown_CROSS_use_DP2,
                         btnDown_CROSS_DP2_open_start_delay, 
                         btnDown_CROSS_DP2_stay_open_time,
                         btnDown_CROSS_use_DP3,
                         btnDown_CROSS_DP3_open_start_delay, 
                         btnDown_CROSS_DP3_stay_open_time,
                         btnDown_CROSS_use_DP4,
                         btnDown_CROSS_DP4_open_start_delay, 
                         btnDown_CROSS_DP4_stay_open_time,
                         btnDown_CROSS_use_DP5,
                         btnDown_CROSS_DP5_open_start_delay, 
                         btnDown_CROSS_DP5_stay_open_time,
                         btnDown_CROSS_use_DP6,
                         btnDown_CROSS_DP6_open_start_delay, 
                         btnDown_CROSS_DP6_stay_open_time,
                         btnDown_CROSS_use_DP7,
                         btnDown_CROSS_DP7_open_start_delay, 
                         btnDown_CROSS_DP7_stay_open_time,
                         btnDown_CROSS_use_DP8,
                         btnDown_CROSS_DP8_open_start_delay, 
                         btnDown_CROSS_DP8_stay_open_time,
                         btnDown_CROSS_use_DP9,
                         btnDown_CROSS_DP9_open_start_delay, 
                         btnDown_CROSS_DP9_stay_open_time,
                         btnDown_CROSS_use_DP10,
                         btnDown_CROSS_DP10_open_start_delay, 
                         btnDown_CROSS_DP10_stay_open_time);
                    
        #ifdef SHADOW_VERBOSE      
             output += "DOME: btnDown_CROSS";
        #endif
      
      
        return;
        
    }
    
    if (PS3NavDome->getButtonPress(LEFT) && PS3NavFoot->getButtonPress(CROSS) && marcDuinoButtonCounter == 1)
    {
      
       marcDuinoButtonPush(1, FTbtnLeft_CROSS_MD_func, btnLeft_CROSS_cust_MP3_num, btnLeft_CROSS_cust_LD_type, btnLeft_CROSS_cust_LD_text, btnLeft_CROSS_cust_panel, 
                         btnLeft_CROSS_use_DP1,
                         btnLeft_CROSS_DP1_open_start_delay, 
                         btnLeft_CROSS_DP1_stay_open_time,
                         btnLeft_CROSS_use_DP2,
                         btnLeft_CROSS_DP2_open_start_delay, 
                         btnLeft_CROSS_DP2_stay_open_time,
                         btnLeft_CROSS_use_DP3,
                         btnLeft_CROSS_DP3_open_start_delay, 
                         btnLeft_CROSS_DP3_stay_open_time,
                         btnLeft_CROSS_use_DP4,
                         btnLeft_CROSS_DP4_open_start_delay, 
                         btnLeft_CROSS_DP4_stay_open_time,
                         btnLeft_CROSS_use_DP5,
                         btnLeft_CROSS_DP5_open_start_delay, 
                         btnLeft_CROSS_DP5_stay_open_time,
                         btnLeft_CROSS_use_DP6,
                         btnLeft_CROSS_DP6_open_start_delay, 
                         btnLeft_CROSS_DP6_stay_open_time,
                         btnLeft_CROSS_use_DP7,
                         btnLeft_CROSS_DP7_open_start_delay, 
                         btnLeft_CROSS_DP7_stay_open_time,
                         btnLeft_CROSS_use_DP8,
                         btnLeft_CROSS_DP8_open_start_delay, 
                         btnLeft_CROSS_DP8_stay_open_time,
                         btnLeft_CROSS_use_DP9,
                         btnLeft_CROSS_DP9_open_start_delay, 
                         btnLeft_CROSS_DP9_stay_open_time,
                         btnLeft_CROSS_use_DP10,
                         btnLeft_CROSS_DP10_open_start_delay, 
                         btnLeft_CROSS_DP10_stay_open_time);
            
        #ifdef SHADOW_VERBOSE      
             output += "DOME: btnLeft_CROSS";
        #endif
      
      
        return;
        
    }

    if (PS3NavDome->getButtonPress(RIGHT) && PS3NavFoot->getButtonPress(CROSS) && marcDuinoButtonCounter == 1)
    {
      
       marcDuinoButtonPush(1, FTbtnRight_CROSS_MD_func, btnRight_CROSS_cust_MP3_num, btnRight_CROSS_cust_LD_type, btnRight_CROSS_cust_LD_text, btnRight_CROSS_cust_panel, 
                         btnRight_CROSS_use_DP1,
                         btnRight_CROSS_DP1_open_start_delay, 
                         btnRight_CROSS_DP1_stay_open_time,
                         btnRight_CROSS_use_DP2,
                         btnRight_CROSS_DP2_open_start_delay, 
                         btnRight_CROSS_DP2_stay_open_time,
                         btnRight_CROSS_use_DP3,
                         btnRight_CROSS_DP3_open_start_delay, 
                         btnRight_CROSS_DP3_stay_open_time,
                         btnRight_CROSS_use_DP4,
                         btnRight_CROSS_DP4_open_start_delay, 
                         btnRight_CROSS_DP4_stay_open_time,
                         btnRight_CROSS_use_DP5,
                         btnRight_CROSS_DP5_open_start_delay, 
                         btnRight_CROSS_DP5_stay_open_time,
                         btnRight_CROSS_use_DP6,
                         btnRight_CROSS_DP6_open_start_delay, 
                         btnRight_CROSS_DP6_stay_open_time,
                         btnRight_CROSS_use_DP7,
                         btnRight_CROSS_DP7_open_start_delay, 
                         btnRight_CROSS_DP7_stay_open_time,
                         btnRight_CROSS_use_DP8,
                         btnRight_CROSS_DP8_open_start_delay, 
                         btnRight_CROSS_DP8_stay_open_time,
                         btnRight_CROSS_use_DP9,
                         btnRight_CROSS_DP9_open_start_delay, 
                         btnRight_CROSS_DP9_stay_open_time,
                         btnRight_CROSS_use_DP10,
                         btnRight_CROSS_DP10_open_start_delay, 
                         btnRight_CROSS_DP10_stay_open_time);
                    
        #ifdef SHADOW_VERBOSE      
             output += "DOME: btnRight_CROSS";
        #endif
      
      
        return;
        
    }

    //------------------------------------ 
    // Send triggers for the CIRCLE + base buttons 
    //------------------------------------
    if (PS3NavDome->getButtonPress(UP) && PS3NavFoot->getButtonPress(CIRCLE) && marcDuinoButtonCounter == 1)
    {
      
       marcDuinoButtonPush(1, FTbtnUP_CIRCLE_MD_func, btnUP_CIRCLE_cust_MP3_num, btnUP_CIRCLE_cust_LD_type, btnUP_CIRCLE_cust_LD_text, btnUP_CIRCLE_cust_panel, 
                         btnUP_CIRCLE_use_DP1,
                         btnUP_CIRCLE_DP1_open_start_delay, 
                         btnUP_CIRCLE_DP1_stay_open_time,
                         btnUP_CIRCLE_use_DP2,
                         btnUP_CIRCLE_DP2_open_start_delay, 
                         btnUP_CIRCLE_DP2_stay_open_time,
                         btnUP_CIRCLE_use_DP3,
                         btnUP_CIRCLE_DP3_open_start_delay, 
                         btnUP_CIRCLE_DP3_stay_open_time,
                         btnUP_CIRCLE_use_DP4,
                         btnUP_CIRCLE_DP4_open_start_delay, 
                         btnUP_CIRCLE_DP4_stay_open_time,
                         btnUP_CIRCLE_use_DP5,
                         btnUP_CIRCLE_DP5_open_start_delay, 
                         btnUP_CIRCLE_DP5_stay_open_time,
                         btnUP_CIRCLE_use_DP6,
                         btnUP_CIRCLE_DP6_open_start_delay, 
                         btnUP_CIRCLE_DP6_stay_open_time,
                         btnUP_CIRCLE_use_DP7,
                         btnUP_CIRCLE_DP7_open_start_delay, 
                         btnUP_CIRCLE_DP7_stay_open_time,
                         btnUP_CIRCLE_use_DP8,
                         btnUP_CIRCLE_DP8_open_start_delay, 
                         btnUP_CIRCLE_DP8_stay_open_time,
                         btnUP_CIRCLE_use_DP9,
                         btnUP_CIRCLE_DP9_open_start_delay, 
                         btnUP_CIRCLE_DP9_stay_open_time,
                         btnUP_CIRCLE_use_DP10,
                         btnUP_CIRCLE_DP10_open_start_delay, 
                         btnUP_CIRCLE_DP10_stay_open_time);
                    
        #ifdef SHADOW_VERBOSE      
             output += "DOME: btnUP_CIRCLE";
        #endif
      
      
        return;
        
    }
    
    if (PS3NavDome->getButtonPress(DOWN) && PS3NavFoot->getButtonPress(CIRCLE) && marcDuinoButtonCounter == 1)
    {
      
       marcDuinoButtonPush(1, FTbtnDown_CIRCLE_MD_func, btnDown_CIRCLE_cust_MP3_num, btnDown_CIRCLE_cust_LD_type, btnDown_CIRCLE_cust_LD_text, btnDown_CIRCLE_cust_panel, 
                         btnDown_CIRCLE_use_DP1,
                         btnDown_CIRCLE_DP1_open_start_delay, 
                         btnDown_CIRCLE_DP1_stay_open_time,
                         btnDown_CIRCLE_use_DP2,
                         btnDown_CIRCLE_DP2_open_start_delay, 
                         btnDown_CIRCLE_DP2_stay_open_time,
                         btnDown_CIRCLE_use_DP3,
                         btnDown_CIRCLE_DP3_open_start_delay, 
                         btnDown_CIRCLE_DP3_stay_open_time,
                         btnDown_CIRCLE_use_DP4,
                         btnDown_CIRCLE_DP4_open_start_delay, 
                         btnDown_CIRCLE_DP4_stay_open_time,
                         btnDown_CIRCLE_use_DP5,
                         btnDown_CIRCLE_DP5_open_start_delay, 
                         btnDown_CIRCLE_DP5_stay_open_time,
                         btnDown_CIRCLE_use_DP6,
                         btnDown_CIRCLE_DP6_open_start_delay, 
                         btnDown_CIRCLE_DP6_stay_open_time,
                         btnDown_CIRCLE_use_DP7,
                         btnDown_CIRCLE_DP7_open_start_delay, 
                         btnDown_CIRCLE_DP7_stay_open_time,
                         btnDown_CIRCLE_use_DP8,
                         btnDown_CIRCLE_DP8_open_start_delay, 
                         btnDown_CIRCLE_DP8_stay_open_time,
                         btnDown_CIRCLE_use_DP9,
                         btnDown_CIRCLE_DP9_open_start_delay, 
                         btnDown_CIRCLE_DP9_stay_open_time,
                         btnDown_CIRCLE_use_DP10,
                         btnDown_CIRCLE_DP10_open_start_delay, 
                         btnDown_CIRCLE_DP10_stay_open_time);
                    
        #ifdef SHADOW_VERBOSE      
             output += "DOME: btnDown_CIRCLE";
        #endif
      
      
        return;
        
    }
    
    if (PS3NavDome->getButtonPress(LEFT) && PS3NavFoot->getButtonPress(CIRCLE) && marcDuinoButtonCounter == 1)
    {
      
       marcDuinoButtonPush(1, FTbtnLeft_CIRCLE_MD_func, btnLeft_CIRCLE_cust_MP3_num, btnLeft_CIRCLE_cust_LD_type, btnLeft_CIRCLE_cust_LD_text, btnLeft_CIRCLE_cust_panel, 
                         btnLeft_CIRCLE_use_DP1,
                         btnLeft_CIRCLE_DP1_open_start_delay, 
                         btnLeft_CIRCLE_DP1_stay_open_time,
                         btnLeft_CIRCLE_use_DP2,
                         btnLeft_CIRCLE_DP2_open_start_delay, 
                         btnLeft_CIRCLE_DP2_stay_open_time,
                         btnLeft_CIRCLE_use_DP3,
                         btnLeft_CIRCLE_DP3_open_start_delay, 
                         btnLeft_CIRCLE_DP3_stay_open_time,
                         btnLeft_CIRCLE_use_DP4,
                         btnLeft_CIRCLE_DP4_open_start_delay, 
                         btnLeft_CIRCLE_DP4_stay_open_time,
                         btnLeft_CIRCLE_use_DP5,
                         btnLeft_CIRCLE_DP5_open_start_delay, 
                         btnLeft_CIRCLE_DP5_stay_open_time,
                         btnLeft_CIRCLE_use_DP6,
                         btnLeft_CIRCLE_DP6_open_start_delay, 
                         btnLeft_CIRCLE_DP6_stay_open_time,
                         btnLeft_CIRCLE_use_DP7,
                         btnLeft_CIRCLE_DP7_open_start_delay, 
                         btnLeft_CIRCLE_DP7_stay_open_time,
                         btnLeft_CIRCLE_use_DP8,
                         btnLeft_CIRCLE_DP8_open_start_delay, 
                         btnLeft_CIRCLE_DP8_stay_open_time,
                         btnLeft_CIRCLE_use_DP9,
                         btnLeft_CIRCLE_DP9_open_start_delay, 
                         btnLeft_CIRCLE_DP9_stay_open_time,
                         btnLeft_CIRCLE_use_DP10,
                         btnLeft_CIRCLE_DP10_open_start_delay, 
                         btnLeft_CIRCLE_DP10_stay_open_time);
                    
        #ifdef SHADOW_VERBOSE      
             output += "DOME: btnLeft_CIRCLE";
        #endif
      
      
        return;
        
    }

    if (PS3NavDome->getButtonPress(RIGHT) && PS3NavFoot->getButtonPress(CIRCLE) && marcDuinoButtonCounter == 1)
    {
      
       marcDuinoButtonPush(1, FTbtnRight_CIRCLE_MD_func, btnRight_CIRCLE_cust_MP3_num, btnRight_CIRCLE_cust_LD_type, btnRight_CIRCLE_cust_LD_text, btnRight_CIRCLE_cust_panel, 
                         btnRight_CIRCLE_use_DP1,
                         btnRight_CIRCLE_DP1_open_start_delay, 
                         btnRight_CIRCLE_DP1_stay_open_time,
                         btnRight_CIRCLE_use_DP2,
                         btnRight_CIRCLE_DP2_open_start_delay, 
                         btnRight_CIRCLE_DP2_stay_open_time,
                         btnRight_CIRCLE_use_DP3,
                         btnRight_CIRCLE_DP3_open_start_delay, 
                         btnRight_CIRCLE_DP3_stay_open_time,
                         btnRight_CIRCLE_use_DP4,
                         btnRight_CIRCLE_DP4_open_start_delay, 
                         btnRight_CIRCLE_DP4_stay_open_time,
                         btnRight_CIRCLE_use_DP5,
                         btnRight_CIRCLE_DP5_open_start_delay, 
                         btnRight_CIRCLE_DP5_stay_open_time,
                         btnRight_CIRCLE_use_DP6,
                         btnRight_CIRCLE_DP6_open_start_delay, 
                         btnRight_CIRCLE_DP6_stay_open_time,
                         btnRight_CIRCLE_use_DP7,
                         btnRight_CIRCLE_DP7_open_start_delay, 
                         btnRight_CIRCLE_DP7_stay_open_time,
                         btnRight_CIRCLE_use_DP8,
                         btnRight_CIRCLE_DP8_open_start_delay, 
                         btnRight_CIRCLE_DP8_stay_open_time,
                         btnRight_CIRCLE_use_DP9,
                         btnRight_CIRCLE_DP9_open_start_delay, 
                         btnRight_CIRCLE_DP9_stay_open_time,
                         btnRight_CIRCLE_use_DP10,
                         btnRight_CIRCLE_DP10_open_start_delay, 
                         btnRight_CIRCLE_DP10_stay_open_time);
            
        
        #ifdef SHADOW_VERBOSE      
             output += "DOME: btnRight_CIRCLE";
        #endif
      
      
        return;
        
    }
    
    //------------------------------------ 
    // Send triggers for the L1 + base buttons 
    //------------------------------------
    if (PS3NavDome->getButtonPress(UP) && PS3NavDome->getButtonPress(L1) && marcDuinoButtonCounter == 1)
    {
      
       marcDuinoButtonPush(1, FTbtnUP_L1_MD_func, btnUP_L1_cust_MP3_num, btnUP_L1_cust_LD_type, btnUP_L1_cust_LD_text, btnUP_L1_cust_panel, 
                         btnUP_L1_use_DP1,
                         btnUP_L1_DP1_open_start_delay, 
                         btnUP_L1_DP1_stay_open_time,
                         btnUP_L1_use_DP2,
                         btnUP_L1_DP2_open_start_delay, 
                         btnUP_L1_DP2_stay_open_time,
                         btnUP_L1_use_DP3,
                         btnUP_L1_DP3_open_start_delay, 
                         btnUP_L1_DP3_stay_open_time,
                         btnUP_L1_use_DP4,
                         btnUP_L1_DP4_open_start_delay, 
                         btnUP_L1_DP4_stay_open_time,
                         btnUP_L1_use_DP5,
                         btnUP_L1_DP5_open_start_delay, 
                         btnUP_L1_DP5_stay_open_time,
                         btnUP_L1_use_DP6,
                         btnUP_L1_DP6_open_start_delay, 
                         btnUP_L1_DP6_stay_open_time,
                         btnUP_L1_use_DP7,
                         btnUP_L1_DP7_open_start_delay, 
                         btnUP_L1_DP7_stay_open_time,
                         btnUP_L1_use_DP8,
                         btnUP_L1_DP8_open_start_delay, 
                         btnUP_L1_DP8_stay_open_time,
                         btnUP_L1_use_DP9,
                         btnUP_L1_DP9_open_start_delay, 
                         btnUP_L1_DP9_stay_open_time,
                         btnUP_L1_use_DP10,
                         btnUP_L1_DP10_open_start_delay, 
                         btnUP_L1_DP10_stay_open_time);
            
        #ifdef SHADOW_VERBOSE      
             output += "DOME: btnUP_L1";
        #endif
      
      
        return;
        
    }
    
    if (PS3NavDome->getButtonPress(DOWN) && PS3NavDome->getButtonPress(L1) && marcDuinoButtonCounter == 1)
    {
      
       marcDuinoButtonPush(1, FTbtnDown_L1_MD_func, btnDown_L1_cust_MP3_num, btnDown_L1_cust_LD_type, btnDown_L1_cust_LD_text, btnDown_L1_cust_panel, 
                         btnDown_L1_use_DP1,
                         btnDown_L1_DP1_open_start_delay, 
                         btnDown_L1_DP1_stay_open_time,
                         btnDown_L1_use_DP2,
                         btnDown_L1_DP2_open_start_delay, 
                         btnDown_L1_DP2_stay_open_time,
                         btnDown_L1_use_DP3,
                         btnDown_L1_DP3_open_start_delay, 
                         btnDown_L1_DP3_stay_open_time,
                         btnDown_L1_use_DP4,
                         btnDown_L1_DP4_open_start_delay, 
                         btnDown_L1_DP4_stay_open_time,
                         btnDown_L1_use_DP5,
                         btnDown_L1_DP5_open_start_delay, 
                         btnDown_L1_DP5_stay_open_time,
                         btnDown_L1_use_DP6,
                         btnDown_L1_DP6_open_start_delay, 
                         btnDown_L1_DP6_stay_open_time,
                         btnDown_L1_use_DP7,
                         btnDown_L1_DP7_open_start_delay, 
                         btnDown_L1_DP7_stay_open_time,
                         btnDown_L1_use_DP8,
                         btnDown_L1_DP8_open_start_delay, 
                         btnDown_L1_DP8_stay_open_time,
                         btnDown_L1_use_DP9,
                         btnDown_L1_DP9_open_start_delay, 
                         btnDown_L1_DP9_stay_open_time,
                         btnDown_L1_use_DP10,
                         btnDown_L1_DP10_open_start_delay, 
                         btnDown_L1_DP10_stay_open_time);
                    
        #ifdef SHADOW_VERBOSE      
             output += "DOME: btnDown_L1";
        #endif
      
      
        return;
        
    }
    
    if (PS3NavDome->getButtonPress(LEFT) && PS3NavDome->getButtonPress(L1) && marcDuinoButtonCounter == 1)
    {
      
       marcDuinoButtonPush(1, FTbtnLeft_L1_MD_func, btnLeft_L1_cust_MP3_num, btnLeft_L1_cust_LD_type, btnLeft_L1_cust_LD_text, btnLeft_L1_cust_panel, 
                         btnLeft_L1_use_DP1,
                         btnLeft_L1_DP1_open_start_delay, 
                         btnLeft_L1_DP1_stay_open_time,
                         btnLeft_L1_use_DP2,
                         btnLeft_L1_DP2_open_start_delay, 
                         btnLeft_L1_DP2_stay_open_time,
                         btnLeft_L1_use_DP3,
                         btnLeft_L1_DP3_open_start_delay, 
                         btnLeft_L1_DP3_stay_open_time,
                         btnLeft_L1_use_DP4,
                         btnLeft_L1_DP4_open_start_delay, 
                         btnLeft_L1_DP4_stay_open_time,
                         btnLeft_L1_use_DP5,
                         btnLeft_L1_DP5_open_start_delay, 
                         btnLeft_L1_DP5_stay_open_time,
                         btnLeft_L1_use_DP6,
                         btnLeft_L1_DP6_open_start_delay, 
                         btnLeft_L1_DP6_stay_open_time,
                         btnLeft_L1_use_DP7,
                         btnLeft_L1_DP7_open_start_delay, 
                         btnLeft_L1_DP7_stay_open_time,
                         btnLeft_L1_use_DP8,
                         btnLeft_L1_DP8_open_start_delay, 
                         btnLeft_L1_DP8_stay_open_time,
                         btnLeft_L1_use_DP9,
                         btnLeft_L1_DP9_open_start_delay, 
                         btnLeft_L1_DP9_stay_open_time,
                         btnLeft_L1_use_DP10,
                         btnLeft_L1_DP10_open_start_delay, 
                         btnLeft_L1_DP10_stay_open_time);
                    
        #ifdef SHADOW_VERBOSE      
             output += "DOME: btnLeft_L1";
        #endif
      
      
        return;
        
    }

    if (PS3NavDome->getButtonPress(RIGHT) && PS3NavDome->getButtonPress(L1) && marcDuinoButtonCounter == 1)
    {
      
       marcDuinoButtonPush(1, FTbtnRight_L1_MD_func, btnRight_L1_cust_MP3_num, btnRight_L1_cust_LD_type, btnRight_L1_cust_LD_text, btnRight_L1_cust_panel, 
                         btnRight_L1_use_DP1,
                         btnRight_L1_DP1_open_start_delay, 
                         btnRight_L1_DP1_stay_open_time,
                         btnRight_L1_use_DP2,
                         btnRight_L1_DP2_open_start_delay, 
                         btnRight_L1_DP2_stay_open_time,
                         btnRight_L1_use_DP3,
                         btnRight_L1_DP3_open_start_delay, 
                         btnRight_L1_DP3_stay_open_time,
                         btnRight_L1_use_DP4,
                         btnRight_L1_DP4_open_start_delay, 
                         btnRight_L1_DP4_stay_open_time,
                         btnRight_L1_use_DP5,
                         btnRight_L1_DP5_open_start_delay, 
                         btnRight_L1_DP5_stay_open_time,
                         btnRight_L1_use_DP6,
                         btnRight_L1_DP6_open_start_delay, 
                         btnRight_L1_DP6_stay_open_time,
                         btnRight_L1_use_DP7,
                         btnRight_L1_DP7_open_start_delay, 
                         btnRight_L1_DP7_stay_open_time,
                         btnRight_L1_use_DP8,
                         btnRight_L1_DP8_open_start_delay, 
                         btnRight_L1_DP8_stay_open_time,
                         btnRight_L1_use_DP9,
                         btnRight_L1_DP9_open_start_delay, 
                         btnRight_L1_DP9_stay_open_time,
                         btnRight_L1_use_DP10,
                         btnRight_L1_DP10_open_start_delay, 
                         btnRight_L1_DP10_stay_open_time);
                   
        #ifdef SHADOW_VERBOSE      
             output += "DOME: btnRight_L1";
        #endif
      
      
        return;
        
    }
    
    //------------------------------------ 
    // Send triggers for the PS + base buttons 
    //------------------------------------
    if (PS3NavDome->getButtonPress(UP) && PS3NavFoot->getButtonPress(PS) && marcDuinoButtonCounter == 1)
    {
      
       marcDuinoButtonPush(1, FTbtnUP_PS_MD_func, btnUP_PS_cust_MP3_num, btnUP_PS_cust_LD_type, btnUP_PS_cust_LD_text, btnUP_PS_cust_panel, 
                         btnUP_PS_use_DP1,
                         btnUP_PS_DP1_open_start_delay, 
                         btnUP_PS_DP1_stay_open_time,
                         btnUP_PS_use_DP2,
                         btnUP_PS_DP2_open_start_delay, 
                         btnUP_PS_DP2_stay_open_time,
                         btnUP_PS_use_DP3,
                         btnUP_PS_DP3_open_start_delay, 
                         btnUP_PS_DP3_stay_open_time,
                         btnUP_PS_use_DP4,
                         btnUP_PS_DP4_open_start_delay, 
                         btnUP_PS_DP4_stay_open_time,
                         btnUP_PS_use_DP5,
                         btnUP_PS_DP5_open_start_delay, 
                         btnUP_PS_DP5_stay_open_time,
                         btnUP_PS_use_DP6,
                         btnUP_PS_DP6_open_start_delay, 
                         btnUP_PS_DP6_stay_open_time,
                         btnUP_PS_use_DP7,
                         btnUP_PS_DP7_open_start_delay, 
                         btnUP_PS_DP7_stay_open_time,
                         btnUP_PS_use_DP8,
                         btnUP_PS_DP8_open_start_delay, 
                         btnUP_PS_DP8_stay_open_time,
                         btnUP_PS_use_DP9,
                         btnUP_PS_DP9_open_start_delay, 
                         btnUP_PS_DP9_stay_open_time,
                         btnUP_PS_use_DP10,
                         btnUP_PS_DP10_open_start_delay, 
                         btnUP_PS_DP10_stay_open_time);
            
        #ifdef SHADOW_VERBOSE      
             output += "DOME: btnUP_PS";
        #endif
       
        return;
        
    }
    
    if (PS3NavDome->getButtonPress(DOWN) && PS3NavFoot->getButtonPress(PS) && marcDuinoButtonCounter == 1)
    {
      
       marcDuinoButtonPush(1, FTbtnDown_PS_MD_func, btnDown_PS_cust_MP3_num, btnDown_PS_cust_LD_type, btnDown_PS_cust_LD_text, btnDown_PS_cust_panel, 
                         btnDown_PS_use_DP1,
                         btnDown_PS_DP1_open_start_delay, 
                         btnDown_PS_DP1_stay_open_time,
                         btnDown_PS_use_DP2,
                         btnDown_PS_DP2_open_start_delay, 
                         btnDown_PS_DP2_stay_open_time,
                         btnDown_PS_use_DP3,
                         btnDown_PS_DP3_open_start_delay, 
                         btnDown_PS_DP3_stay_open_time,
                         btnDown_PS_use_DP4,
                         btnDown_PS_DP4_open_start_delay, 
                         btnDown_PS_DP4_stay_open_time,
                         btnDown_PS_use_DP5,
                         btnDown_PS_DP5_open_start_delay, 
                         btnDown_PS_DP5_stay_open_time,
                         btnDown_PS_use_DP6,
                         btnDown_PS_DP6_open_start_delay, 
                         btnDown_PS_DP6_stay_open_time,
                         btnDown_PS_use_DP7,
                         btnDown_PS_DP7_open_start_delay, 
                         btnDown_PS_DP7_stay_open_time,
                         btnDown_PS_use_DP8,
                         btnDown_PS_DP8_open_start_delay, 
                         btnDown_PS_DP8_stay_open_time,
                         btnDown_PS_use_DP9,
                         btnDown_PS_DP9_open_start_delay, 
                         btnDown_PS_DP9_stay_open_time,
                         btnDown_PS_use_DP10,
                         btnDown_PS_DP10_open_start_delay, 
                         btnDown_PS_DP10_stay_open_time);
                    
        #ifdef SHADOW_VERBOSE      
             output += "DOME: btnDown_PS";
        #endif
      
      
        return;
        
    }
    
    if (PS3NavDome->getButtonPress(LEFT) && PS3NavFoot->getButtonPress(PS) && marcDuinoButtonCounter == 1)
    {
      
       marcDuinoButtonPush(1, FTbtnLeft_PS_MD_func, btnLeft_PS_cust_MP3_num, btnLeft_PS_cust_LD_type, btnLeft_PS_cust_LD_text, btnLeft_PS_cust_panel, 
                         btnLeft_PS_use_DP1,
                         btnLeft_PS_DP1_open_start_delay, 
                         btnLeft_PS_DP1_stay_open_time,
                         btnLeft_PS_use_DP2,
                         btnLeft_PS_DP2_open_start_delay, 
                         btnLeft_PS_DP2_stay_open_time,
                         btnLeft_PS_use_DP3,
                         btnLeft_PS_DP3_open_start_delay, 
                         btnLeft_PS_DP3_stay_open_time,
                         btnLeft_PS_use_DP4,
                         btnLeft_PS_DP4_open_start_delay, 
                         btnLeft_PS_DP4_stay_open_time,
                         btnLeft_PS_use_DP5,
                         btnLeft_PS_DP5_open_start_delay, 
                         btnLeft_PS_DP5_stay_open_time,
                         btnLeft_PS_use_DP6,
                         btnLeft_PS_DP6_open_start_delay, 
                         btnLeft_PS_DP6_stay_open_time,
                         btnLeft_PS_use_DP7,
                         btnLeft_PS_DP7_open_start_delay, 
                         btnLeft_PS_DP7_stay_open_time,
                         btnLeft_PS_use_DP8,
                         btnLeft_PS_DP8_open_start_delay, 
                         btnLeft_PS_DP8_stay_open_time,
                         btnLeft_PS_use_DP9,
                         btnLeft_PS_DP9_open_start_delay, 
                         btnLeft_PS_DP9_stay_open_time,
                         btnLeft_PS_use_DP10,
                         btnLeft_PS_DP10_open_start_delay, 
                         btnLeft_PS_DP10_stay_open_time);
            
        #ifdef SHADOW_VERBOSE      
             output += "DOME: btnLeft_PS";
        #endif
      
      
        return;
        
    }

    if (PS3NavDome->getButtonPress(RIGHT) && PS3NavFoot->getButtonPress(PS) && marcDuinoButtonCounter == 1)
    {
      
       marcDuinoButtonPush(1, FTbtnRight_PS_MD_func, btnRight_PS_cust_MP3_num, btnRight_PS_cust_LD_type, btnRight_PS_cust_LD_text, btnRight_PS_cust_panel, 
                         btnRight_PS_use_DP1,
                         btnRight_PS_DP1_open_start_delay, 
                         btnRight_PS_DP1_stay_open_time,
                         btnRight_PS_use_DP2,
                         btnRight_PS_DP2_open_start_delay, 
                         btnRight_PS_DP2_stay_open_time,
                         btnRight_PS_use_DP3,
                         btnRight_PS_DP3_open_start_delay, 
                         btnRight_PS_DP3_stay_open_time,
                         btnRight_PS_use_DP4,
                         btnRight_PS_DP4_open_start_delay, 
                         btnRight_PS_DP4_stay_open_time,
                         btnRight_PS_use_DP5,
                         btnRight_PS_DP5_open_start_delay, 
                         btnRight_PS_DP5_stay_open_time,
                         btnRight_PS_use_DP6,
                         btnRight_PS_DP6_open_start_delay, 
                         btnRight_PS_DP6_stay_open_time,
                         btnRight_PS_use_DP7,
                         btnRight_PS_DP7_open_start_delay, 
                         btnRight_PS_DP7_stay_open_time,
                         btnRight_PS_use_DP8,
                         btnRight_PS_DP8_open_start_delay, 
                         btnRight_PS_DP8_stay_open_time,
                         btnRight_PS_use_DP9,
                         btnRight_PS_DP9_open_start_delay, 
                         btnRight_PS_DP9_stay_open_time,
                         btnRight_PS_use_DP10,
                         btnRight_PS_DP10_open_start_delay, 
                         btnRight_PS_DP10_stay_open_time);
                    
        #ifdef SHADOW_VERBOSE      
             output += "DOME: btnRight_PS";
        #endif
      
      
        return;
        
    }

}


// =======================================================================================
// This function handles the processing of custom MarcDuino panel routines
// =======================================================================================
void custMarcDuinoPanel()
{
  
      // Open & Close Logic: Dome Panel #1
      if (DP1_Status == 1)
      {
        
         if ((DP1_start + (DP1_s_delay * 1000)) < millis())
         {
           
             Serial1.print(":OP01\r");
             DP1_Status = 2;
         }
        
      }
      
      if (DP1_Status == 2)
      {
        
         if ((DP1_start + ((DP1_s_delay + DP1_o_time) * 1000)) < millis())
         {
           
             Serial1.print(":CL01\r");
             DP1_Status = 0;
         }        
        
      }
      
      // Open & Close Logic: Dome Panel #2
      if (DP2_Status == 1)
      {
        
         if ((DP2_start + (DP2_s_delay * 1000)) < millis())
         {
           
             Serial1.print(":OP02\r");
             DP2_Status = 2;
         }
        
      }
      
      if (DP2_Status == 2)
      {
        
         if ((DP2_start + ((DP2_s_delay + DP2_o_time) * 1000)) < millis())
         {
           
             Serial1.print(":CL02\r");
             DP2_Status = 0;
         }        
        
      } 
 
      // Open & Close Logic: Dome Panel #3
      if (DP3_Status == 1)
      {
        
         if ((DP3_start + (DP3_s_delay * 1000)) < millis())
         {
           
             Serial1.print(":OP03\r");
             DP3_Status = 2;
         }
        
      }
      
      if (DP3_Status == 2)
      {
        
         if ((DP3_start + ((DP3_s_delay + DP3_o_time) * 1000)) < millis())
         {
           
             Serial1.print(":CL03\r");
             DP3_Status = 0;
         }        
        
      } 
      
      // Open & Close Logic: Dome Panel #4
      if (DP4_Status == 1)
      {
        
         if ((DP4_start + (DP4_s_delay * 1000)) < millis())
         {
           
             Serial1.print(":OP04\r");
             DP4_Status = 2;
         }
        
      }
      
      if (DP4_Status == 2)
      {
        
         if ((DP4_start + ((DP4_s_delay + DP4_o_time) * 1000)) < millis())
         {
           
             Serial1.print(":CL04\r");
             DP4_Status = 0;
         }        
        
      }
      
      // Open & Close Logic: Dome Panel #5
      if (DP5_Status == 1)
      {
        
         if ((DP5_start + (DP5_s_delay * 1000)) < millis())
         {
           
             Serial1.print(":OP05\r");
             DP5_Status = 2;
         }
        
      }
      
      if (DP5_Status == 2)
      {
        
         if ((DP5_start + ((DP5_s_delay + DP5_o_time) * 1000)) < millis())
         {
           
             Serial1.print(":CL05\r");
             DP5_Status = 0;
         }        
        
      }
      
      // Open & Close Logic: Dome Panel #6
      if (DP6_Status == 1)
      {
        
         if ((DP6_start + (DP6_s_delay * 1000)) < millis())
         {
           
             Serial1.print(":OP06\r");
             DP6_Status = 2;
         }
        
      }
      
      if (DP6_Status == 2)
      {
        
         if ((DP6_start + ((DP6_s_delay + DP6_o_time) * 1000)) < millis())
         {
           
             Serial1.print(":CL06\r");
             DP6_Status = 0;
         }        
        
      }
      
      // Open & Close Logic: Dome Panel #7
      if (DP7_Status == 1)
      {
        
         if ((DP7_start + (DP7_s_delay * 1000)) < millis())
         {
           
             Serial1.print(":OP07\r");
             DP7_Status = 2;
         }
        
      }
      
      if (DP7_Status == 2)
      {
        
         if ((DP7_start + ((DP7_s_delay + DP7_o_time) * 1000)) < millis())
         {
           
             Serial1.print(":CL07\r");
             DP7_Status = 0;
         }        
        
      }

      // Open & Close Logic: Dome Panel #8
      if (DP8_Status == 1)
      {
        
         if ((DP8_start + (DP8_s_delay * 1000)) < millis())
         {
           
             Serial1.print(":OP08\r");
             DP8_Status = 2;
         }
        
      }
      
      if (DP8_Status == 2)
      {
        
         if ((DP8_start + ((DP8_s_delay + DP8_o_time) * 1000)) < millis())
         {
           
             Serial1.print(":CL08\r");
             DP8_Status = 0;
         }        
        
      }
      
      // Open & Close Logic: Dome Panel #9
      if (DP9_Status == 1)
      {
        
         if ((DP9_start + (DP9_s_delay * 1000)) < millis())
         {
           
             Serial1.print(":OP09\r");
             DP9_Status = 2;
         }
        
      }
      
      if (DP9_Status == 2)
      {
        
         if ((DP9_start + ((DP9_s_delay + DP9_o_time) * 1000)) < millis())
         {
           
             Serial1.print(":CL09\r");
             DP9_Status = 0;
         }        
        
      }
      
      // Open & Close Logic: Dome Panel #10
      if (DP10_Status == 1)
      {
        
         if ((DP10_start + (DP10_s_delay * 1000)) < millis())
         {
           
             Serial1.print(":OP10\r");
             DP10_Status = 2;
         }
        
      }
      
      if (DP10_Status == 2)
      {
        
         if ((DP10_start + ((DP10_s_delay + DP10_o_time) * 1000)) < millis())
         {
           
             Serial1.print(":CL10\r");
             DP10_Status = 0;
         }        
        
      }
      
      // If all the panels have now closed - close out the custom routine
      if (DP1_Status + DP2_Status + DP3_Status + DP4_Status + DP5_Status + DP6_Status + DP7_Status + DP8_Status + DP9_Status + DP10_Status == 0)
      {
        
          runningCustRoutine = false;
        
      }
}

// =======================================================================================
//                             Dome Automation Function
//
//    Features toggles 'on' via L2 + CIRCLE.  'off' via L2 + CROSS.  Default is 'off'.
//
//    This routines randomly turns the dome motor in both directions.  It assumes the 
//    dome is in the 'home' position when the auto dome feature is toggled on.  From
//    there it turns the dome in a random direction.  Stops for a random length of 
//    of time.  Then returns the dome to the home position.  This randomly repeats.
//
//    It is driven off the user variable - time360DomeTurn.  This records how long
//    it takes the dome to do a 360 degree turn at the given auto dome speed.  Tweaking
//    this parameter to be close provides the best results.
//
//    Activating the dome controller manually immediately cancels the auto dome feature
//    or you can toggle the feature off by pressing L2 + CROSS.
// =======================================================================================
void autoDome()
{
    long rndNum;
    int domeSpeed;
    
    if (domeStatus == 0)  // Dome is currently stopped - prepare for a future turn
    {
      
        if (domeTargetPosition == 0)  // Dome is currently in the home position - prepare to turn away
        {
          
            domeStartTurnTime = millis() + (random(3, 10) * 1000);
            
            rndNum = random(5,354);
            
            domeTargetPosition = rndNum;  // set the target position to a random degree of a 360 circle - shaving off the first and last 5 degrees
            
            if (domeTargetPosition < 180)  // Turn the dome in the positive direction
            {
              
                domeTurnDirection = 1;
                
                domeStopTurnTime = domeStartTurnTime + ((domeTargetPosition / 360) * time360DomeTurn);
              
            } else  // Turn the dome in the negative direction
            {
                    
                domeTurnDirection = -1;
                
                domeStopTurnTime = domeStartTurnTime + (((360 - domeTargetPosition) / 360) * time360DomeTurn);
              
            }
          
        } else  // Dome is not in the home position - send it back to home
        {
          
            domeStartTurnTime = millis() + (random(3, 10) * 1000);
            
            if (domeTargetPosition < 180)
            {
              
                domeTurnDirection = -1;
                
                domeStopTurnTime = domeStartTurnTime + ((domeTargetPosition / 360) * time360DomeTurn);
              
            } else
            {
                    
                domeTurnDirection = 1;
                
                domeStopTurnTime = domeStartTurnTime + (((360 - domeTargetPosition) / 360) * time360DomeTurn);
              
            }
            
            domeTargetPosition = 0;
          
        }
      
        domeStatus = 1;  // Set dome status to preparing for a future turn
               
        #ifdef SHADOW_DEBUG
          output += "Dome Automation: Initial Turn Set\r\n";
          output +=  "Current Time: ";
          output +=  millis();
          output += "\r\n Next Start Time: ";
          output += domeStartTurnTime;
          output += "\r\n";
          output += "Next Stop Time: ";
          output += domeStopTurnTime;
          output += "\r\n";          
          output += "Dome Target Position: ";
          output += domeTargetPosition;
          output += "\r\n";          
        #endif

    }
    
    
    if (domeStatus == 1)  // Dome is prepared for a future move - start the turn when ready
    {
      
        if (domeStartTurnTime < millis())
        {
          
             domeStatus = 2; 
             
             #ifdef SHADOW_DEBUG
                output += "Dome Automation: Ready To Start Turn\r\n";
             #endif
          
        }
    }
    
    if (domeStatus == 2) // Dome is now actively turning until it reaches its stop time
    {
      
        if (domeStopTurnTime > millis())
        {
          
              domeSpeed = domeAutoSpeed * domeTurnDirection;
          
              SyR->motor(domeSpeed);

             #ifdef SHADOW_DEBUG
                output += "Turning Now!!\r\n";
             #endif
          
          
        } else  // turn completed - stop the motor
        {
              domeStatus = 0;
              SyR->stop();

              #ifdef SHADOW_DEBUG
                 output += "STOP TURN!!\r\n";
              #endif
        }
      
    }
  
}

// =======================================================================================
//           Program Utility Functions - Called from various locations
// =======================================================================================
//Eebel Start
const char* MakeSongCommand(int SongNumber){
    //Takes the song number and makes a command to send to the Marcduino
    //Valid songs are 804- 811 right now input is 1-8
    static char songCommand[8];
    SongNumber = SongNumber + 3;  //Adjust for numbering convention of Marcduino Song Files
    snprintf(songCommand, sizeof(songCommand), "$8%d\r", SongNumber);
    output += songCommand;//For debugging

    return songCommand;   
}

//Eebel End
// =======================================================================================
//           PPS3 Controller Device Mgt Functions
// =======================================================================================

void handlePairingConnection(const char* btAddress, PS3BT* controller, boolean isDome)
{
    byte mac[6];
    parseMacString(btAddress, mac);
    writeMacToEEPROM(pairingSlot, mac);

    char nameBuf[16];
    strcpy_P(nameBuf, (char*)pgm_read_ptr(&(slotNames[pairingSlot])));

    Serial.print(F("\r\n>> Paired ["));
    Serial.print(nameBuf);
    Serial.print(F("]: "));
    Serial.println(btAddress);

    controller->disconnect();
    if (isDome)
        isSecondaryPS3NavigatonInitialized = false;
    else
        isPS3NavigatonInitialized = false;

    pairingSlot++;
    if (pairingSlot >= EEPROM_NUM_SLOTS)
    {
        pairingMode = false;
        Serial.println(F("\r\nAll 4 slots paired! Exiting pairing mode."));
        loadMacsFromEEPROM();
        cmdStatus();
    }
    else
    {
        char nextNameBuf[16];
        strcpy_P(nextNameBuf, (char*)pgm_read_ptr(&(slotNames[pairingSlot])));
        Serial.print(F("Waiting for "));
        Serial.print(nextNameBuf);
        Serial.println(F(" controller..."));
    }
}

void onInitPS3NavFoot()
{
    Serial.print(F("\r\n[FOOT onInit] enter"));
    Serial.flush();
    char btAddress[MAC_STRING_LEN];
    getLastConnectedBtMAC(btAddress);
    Serial.print(F(" MAC="));
    Serial.print(btAddress);
    Serial.flush();
    // LED will be set from loop() to avoid USB OUT transfer from inside USB callback chain
    pendingFootLed = true;
    isPS3NavigatonInitialized = true;
    badPS3Data = 0;

    Serial.print(F(" pairingMode="));
    Serial.println(pairingMode);
    Serial.flush();

    // --- PAIRING MODE: capture this controller for the current slot ---
    if (pairingMode)
    {
        handlePairingConnection(btAddress, PS3NavFoot, false);
        return;
    }

    // --- NORMAL MODE: validate MAC against stored values ---
    if (strcmp(btAddress, PS3ControllerFootMac) == 0
        || strcmp(btAddress, PS3ControllerBackupFootMac) == 0
        || isMacTextUnset(PS3ControllerFootMac))
    {
          #ifdef SHADOW_DEBUG
             output += "\r\nWe have our FOOT controller connected.\r\n";
          #endif

          mainControllerConnected = true;
          WaitingforReconnect = true;

    } else
    {
        #ifdef SHADOW_DEBUG
              output += "\r\nWe have an invalid controller trying to connect as the FOOT controller, it will be dropped.\r\n";
        #endif

        stopFeet();
        SyR->stop();
        isFootMotorStopped = true;
        footDriveSpeed = 0;
        // Don't send HID commands from inside USB callback - just disconnect
        PS3NavFoot->disconnect();
        printOutput();

        pendingFootLed = false;
        isPS3NavigatonInitialized = false;
        mainControllerConnected = false;
    }
}

void onInitPS3NavDome()
{
    Serial.print(F("\r\n[DOME onInit] enter"));
    Serial.flush();
    char btAddress[MAC_STRING_LEN];
    getLastConnectedBtMAC(btAddress);
    Serial.print(F(" MAC="));
    Serial.print(btAddress);
    Serial.flush();
    // LED will be set from loop() to avoid USB OUT transfer from inside USB callback chain
    pendingDomeLed = true;
    isSecondaryPS3NavigatonInitialized = true;
    badPS3Data = 0;

    Serial.print(F(" pairingMode="));
    Serial.println(pairingMode);
    Serial.flush();

    // --- PAIRING MODE: capture this controller for the current slot ---
    if (pairingMode)
    {
        handlePairingConnection(btAddress, PS3NavDome, true);
        return;
    }

    // --- NORMAL MODE: validate MAC against stored values ---
    if (strcmp(btAddress, PS3ControllerDomeMAC) == 0
        || strcmp(btAddress, PS3ControllerBackupDomeMAC) == 0
        || isMacTextUnset(PS3ControllerDomeMAC))
    {
          #ifdef SHADOW_DEBUG
             output += "\r\nWe have our DOME controller connected.\r\n";
          #endif

          domeControllerConnected = true;
          WaitingforReconnectDome = true;

    } else
    {
        #ifdef SHADOW_DEBUG
              output += "\r\nWe have an invalid controller trying to connect as the DOME controller, it will be dropped.\r\n";
        #endif

        stopFeet();
        SyR->stop();
        isFootMotorStopped = true;
        footDriveSpeed = 0;
        // Don't send HID commands from inside USB callback - just disconnect
        PS3NavDome->disconnect();
        printOutput();

        pendingDomeLed = false;
        isSecondaryPS3NavigatonInitialized = false;
        domeControllerConnected = false;
    }
}

void getLastConnectedBtMAC(char* btAddress)
{
    macBytesToString(Btd.disc_bdaddr, btAddress);
}

boolean criticalFaultDetect()
{
    if (PS3NavFoot->PS3NavigationConnected || PS3NavFoot->PS3Connected)
    {
        
        currentTime = millis();
        lastMsgTime = PS3NavFoot->getLastMessageTime();
        msgLagTime = currentTime - lastMsgTime;            
        
        if (WaitingforReconnect)
        {
            
            if (msgLagTime < 200)
            {
             
                WaitingforReconnect = false; 
            
            }
            
            lastMsgTime = currentTime;
            
        } 
        
        if ( currentTime >= lastMsgTime)
        {
              msgLagTime = currentTime - lastMsgTime;
              
        } else
        {

             msgLagTime = 0;
        }
        
        if (msgLagTime > 300 && !isFootMotorStopped)
        {
            #ifdef SHADOW_DEBUG
              output += "It has been 300ms since we heard from the PS3 Foot Controller\r\n";
              output += "Shut downing motors, and watching for a new PS3 Foot message\r\n";
            #endif
            stopFeet();
            isFootMotorStopped = true;
            footDriveSpeed = 0;
        }
        
        if ( msgLagTime > 10000 )
        {
            #ifdef SHADOW_DEBUG
              output += "It has been 10s since we heard from the PS3 Foot Controller\r\n";
              output += "msgLagTime:";
              output += msgLagTime;
              output += "  lastMsgTime:";
              output += lastMsgTime;
              output += "  millis:";
              output += millis();            
              output += "\r\nDisconnecting the Foot controller.\r\n";
            #endif
            stopFeet();
            isFootMotorStopped = true;
            footDriveSpeed = 0;
            PS3NavFoot->disconnect();
            WaitingforReconnect = true;
            return true;
        }

        //Check PS3 Signal Data
        if(!PS3NavFoot->getStatus(Plugged) && !PS3NavFoot->getStatus(Unplugged))
        {
          Serial.println("\r\nSignal Check");
            //We don't have good data from the controller.
            //Wait 15ms if no second controller - 100ms if some controller connected, Update USB, and try again
            if (PS3NavDome->PS3NavigationConnected)
            {
                  delay(100);     
            } else
            {
                  delay(15);
            }
            
            Usb.Task();   
            lastMsgTime = PS3NavFoot->getLastMessageTime();
            
            if(!PS3NavFoot->getStatus(Plugged) && !PS3NavFoot->getStatus(Unplugged))
            {
                badPS3Data++;
                #ifdef SHADOW_DEBUG
                    output += "\r\n**Invalid data from PS3 FOOT Controller. - Resetting Data**\r\n";
                #endif
                return true;
            }
        }
        else if (badPS3Data > 0)
        {

            badPS3Data = 0;
        }
        
        if ( badPS3Data > 10 )
        {
            #ifdef SHADOW_DEBUG
                output += "Too much bad data coming from the PS3 FOOT Controller\r\n";
                output += "Disconnecting the controller and stop motors.\r\n";
            #endif
            stopFeet();
            isFootMotorStopped = true;
            footDriveSpeed = 0;
            PS3NavFoot->disconnect();
            WaitingforReconnect = true;
            return true;
        }
    }
    else if (!isFootMotorStopped)
    {
        #ifdef SHADOW_DEBUG      
            output += "No foot controller was found\r\n";
            output += "Shuting down motors and watching for a new PS3 foot message\r\n";
        #endif
        stopFeet();
        isFootMotorStopped = true;
        footDriveSpeed = 0;
        WaitingforReconnect = true;
        return true;
    }
    
    return false;
}

boolean criticalFaultDetectDome()
{
    if (PS3NavDome->PS3NavigationConnected || PS3NavDome->PS3Connected)
    {

        currentTime = millis();
        lastMsgTime = PS3NavDome->getLastMessageTime();
        msgLagTime = currentTime - lastMsgTime;            
        
        if (WaitingforReconnectDome)
        {
            if (msgLagTime < 200)
            {
             
                WaitingforReconnectDome = false; 
            
            }
            
            lastMsgTime = currentTime;
            
        }
        
        if ( currentTime >= lastMsgTime)
        {
             msgLagTime = currentTime - lastMsgTime;
              
        } else
        {
             msgLagTime = 0;
        }
        
        if ( msgLagTime > 10000 )
        {
            #ifdef SHADOW_DEBUG
              output += "It has been 10s since we heard from the PS3 Dome Controller\r\n";
              output += "msgLagTime:";
              output += msgLagTime;
              output += "  lastMsgTime:";
              output += lastMsgTime;
              output += "  millis:";
              output += millis();            
              output += "\r\nDisconnecting the Dome controller.\r\n";
            #endif
            
            SyR->stop();
            PS3NavDome->disconnect();
            WaitingforReconnectDome = true;
            return true;
        }

        //Check PS3 Signal Data
        if(!PS3NavDome->getStatus(Plugged) && !PS3NavDome->getStatus(Unplugged))
        {

            // We don't have good data from the controller.
            //Wait 100ms, Update USB, and try again
            delay(100);
            
            Usb.Task();
            lastMsgTime = PS3NavDome->getLastMessageTime();
            
            if(!PS3NavDome->getStatus(Plugged) && !PS3NavDome->getStatus(Unplugged))
            {
                badPS3DataDome++;
                #ifdef SHADOW_DEBUG
                    output += "\r\n**Invalid data from PS3 Dome Controller. - Resetting Data**\r\n";
                #endif
                return true;
            }
        } else if (badPS3DataDome > 0)
        {
             badPS3DataDome = 0;
        }
        
        if ( badPS3DataDome > 10 )
        {
            #ifdef SHADOW_DEBUG
                output += "Too much bad data coming from the PS3 DOME Controller\r\n";
                output += "Disconnecting the controller and stop motors.\r\n";
            #endif
            SyR->stop();
            PS3NavDome->disconnect();
            WaitingforReconnectDome = true;
            return true;
        }
    } 
    
    return false;
}

// =======================================================================================
//           USB Read Function - Supports Main Program Loop
// =======================================================================================

boolean readUSB()
{
  
     Usb.Task();
     
    //The more devices we have connected to the USB or BlueTooth, the more often Usb.Task need to be called to eliminate latency.
    if (PS3NavFoot->PS3NavigationConnected) 
    {
        if (criticalFaultDetect())
        {
            //We have a fault condition that we want to ensure that we do NOT process any controller data!!!
            printOutput();
            return false;
        }
        
    } else if (!isFootMotorStopped)
    {
        #ifdef SHADOW_DEBUG      
            output += "No foot controller was found\r\n";
            output += "Shuting down motors, and watching for a new PS3 foot message\r\n";
        #endif
        stopFeet();
        isFootMotorStopped = true;
        footDriveSpeed = 0;
        WaitingforReconnect = true;
    }
    
    if (PS3NavDome->PS3NavigationConnected) 
    {

        if (criticalFaultDetectDome())
        {
           //We have a fault condition that we want to ensure that we do NOT process any controller data!!!
           printOutput();
           return false;
        }
    }
    
    return true;
}

// =======================================================================================
//          Print Output Function
// =======================================================================================

void printOutput()
{
    if (output.length())
    {
        if (Serial) Serial.println(output);
        output.remove(0); // Reset while keeping reserved capacity
    }
}
