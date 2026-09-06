# ACIRA

ACIRA is a gift box with a date lock and an attitude. You set how many days until it is
allowed to open. Until then, if you pick it up it tells you no, and if you press the
button anyway it argues with you out loud in the JARVIS voice.

When the day comes it plays a song, congratulates you on the screen and opens its own
lid.

The name is a backronym I built to fit: Autonomous, Cube-shaped, Interactive, Robotic,
Automatically-opening-box. It is pronounced Ah-Kih-Ruh.

I built it over the 2024 to 2025 school year for TSA Microcontroller Design. It took 2nd
at States and 2nd at Nationals in 2025, and 159 logged hours.

The full build guide, with the parts list, the wiring and the printed files, is at
[noahpuckett.me/box.html](https://noahpuckett.me/box.html). This repo is just the code.

## What is in here

Two sketches. `Main` is the box. `LED_Ring` is a small standalone sketch I used to work
out the ring animation on its own.

```
Main/
  Main.ino        All the logic. Reads the button and the knob, asks the
                  accelerometer whether the box has been handled, calls the rest.
  OLED.cpp/.h     Reads the knob and prints the countdown or the congratulations.
  Audio.cpp/.h    Drives the DFPlayer Mini and keeps track of which line comes next.
  Accel.cpp/.h    Talks to the MPU6050 and decides whether the box was picked up.
  MyServo.cpp/.h  Moves the lid between home and open.

LED_Ring/
  LED_Ring.ino    Spins a hue around the NeoPixel ring.
  hsv.h           HSV to RGB, integer only, no floats.
```

Every device is in its own pair of files, so the main loop reads like a description of
what the box does instead of a wall of setup.

## How it decides what to do

The knob decides everything. It is a potentiometer on pin 13, read as 0 to 4095 and
scaled to 0 to 31 days. There is no clock in the box, which surprises people. The date
lock is really just a number you dial in, and the screen shows it.

Above zero days the box is locked. Every input gets a line:

- The accelerometer sees you pick it up or shake it, and it plays from folder 1.
- You press the open button too early, and it plays from folder 2.

At zero days the screen says open now and the button actually works. Pressing it plays
folder 4, which is the celebration song, and then drives the servo to 120 degrees to
push the lid up.

Being picked up is two thresholds, not one. The accelerometer has to have moved more
than 2 m/s/s away from where it last was, **and** the gyro has to read more than
0.8 rad/s at the same time. One alone was not enough. Acceleration by itself fires when
the table gets bumped, and rotation by itself fires when you nudge the box turning it
around to look at it. Wanting both means it only complains when it has actually been
lifted.

The last acceleration reading only updates when a comment fired. That way the box
compares against where it was sitting rather than against where it was a fiftieth of a
second ago, so slowly tilting it is still noticed.

## The voice lines are in rotation, not random

Each folder keeps its own counter. You get line 1, then 2, then 3, then 4, then back to
1. I tried random picking first and it was worse, because random means you hear the same
insult twice in a row and that ruins the joke.

The lines are mine and I generated them on an AI voice site in the JARVIS voice. The
celebration song is from the Breath of the Wild soundtrack, so the audio is not in this
repo. Put your own MP3s on the SD card in folders `01`, `02` and `04`. Four tracks in
folder 1, four in folder 2, one in folder 4. If you use a different number, change
`track1max` and `track2max` at the top of `Audio.cpp`.

## Building it

Board is **DOIT ESP32 DEVKIT V1** in the Arduino IDE, serial monitor at 9600.

Libraries you need: `Adafruit_PWMServoDriver`, `Adafruit_SSD1306`, `Adafruit_GFX`,
`Adafruit_NeoPixel`, `DFRobotDFPlayerMini`, and an MPU6050 library plus
`Adafruit_Sensor`. `Wire` ships with the ESP32 board package.

Pins that are set in the code rather than on a diagram:

| What | Pin |
| --- | --- |
| Open button | 15, input pullup, so it reads inverted |
| Date knob | 13, analog |
| DFPlayer serial | 16 and 17, on Serial1 |
| DFPlayer busy | 35 |
| OLED | I2C at address 0x3C |
| Servo | Channel 0 on a PCA9685 at 0x40 |
| LED ring | 6, in the LED_Ring sketch |

The header is called `MyServo.h` and not `Servo.h` on purpose. The Arduino IDE ships a
built in library called Servo, and if you name yours the same thing the compiler
sometimes finds the wrong one.

The lid moves with `moveServoSlow`, which steps to the target in 100 increments with a
10 ms pause each instead of jumping. A servo told to go straight from 0 to 120 slams,
and the lid is heavier than an MG90s wants it to be.

## One thing to know

The ring is not wired into the main sketch in this version. `Main.ino` never includes
the LED code, so the box runs fine without it and the ring animation lives in its own
sketch. That is the next thing I would fix.
