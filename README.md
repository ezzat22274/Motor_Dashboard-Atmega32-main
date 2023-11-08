# Motor Dashboard for ATmega32

This is a simple motor dashboard program for the ATmega32 microcontroller.

## Table of Contents
- [Features](#features)
- [Drivers Used](#drivers-used)
- [Components Used](#components-used)
- [Usage](#usage)

## Features

- Secure password entry to access dashboard functions.
- Control LEDs and a stepper motor using a keypad.
- Three incorrect password attempts will result in closing the dashboard.


## Drivers Used

This project makes use of the following drivers:

- **DIO (Digital Input/Output Driver)**: This driver is responsible for configuring and controlling the digital input/output pins.

- **GIE (General Interrupt Enable Driver)**: It enables or disables global interrupt functionality.

- **EXTI (External Interrupt Driver)**: Used for external interrupt handling.

- **LCD (Liquid Crystal Display Driver)**: To display information on an LCD screen.

- **KPD (Keypad Driver)**: For keypad input handling.

## Usage

- Press a number key to enter a digit of the password (four digits in total).
- Press '=' to submit the password.
- If the correct password is entered, you will have access to the dashboard functions.
- Use the keypad to control LEDs (on/off) and the direction of the stepper motor.
