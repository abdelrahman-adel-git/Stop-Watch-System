<h1 align="center">
⏱️ Stop Watch System ⏱️
</h1>

This project implements a stopwatch system using an ATmega32 microcontroller. It features precise timekeeping and user-friendly controls.

## 🛠️ Project Overview

The system is built around an ATmega32 microcontroller (1MHz) and includes:

- **Timer1** configured in CTC (Clear Timer on Compare Match) mode for accurate timekeeping.
- **Multiplexed 7-segment displays** with a 7447 decoder to show the elapsed time.
- **External interrupts** for user control functions: resume, stop, and reset.

### 🌟 Features

- **Accurate Timekeeping**: Uses Timer1 in CTC mode for reliable stopwatch functionality.
- **User Interface**: Multiplexed 7-segment displays for time output.
- **Control Functions**:
  - **Resume**: Continues the stopwatch from where it was paused.
  - **Stop**: Halts the stopwatch.
  - **Reset**: Resets the stopwatch to zero.

### 🔧 Components and Drivers

- **Microcontroller**: ATmega32 (1MHz)
- **Components**:
  - Timer1 (CTC mode)
  - Multiplexed 7-segment displays
  - 7447 BCD to 7-segment decoder
- **Interrupts**:
  - External interrupts for control functions (resume, stop, reset)

## 🏗️ System Architecture

The system is designed to handle real-time timekeeping and user interaction efficiently:

1. **Timer1**:
   - Configured in CTC mode for time counting.
   - Generates interrupts at fixed intervals for updating the display.

2. **7-Segment Displays**:
   - Display the elapsed time using a multiplexed approach.
   - Controlled by the 7447 decoder.

3. **External Interrupts**:
   - **Resume**: Continues the stopwatch from the paused state.
   - **Stop**: Halts the timekeeping process.
   - **Reset**: Resets the stopwatch to zero.

## 💻 Simulation of the Stopwatch System

![Simulation of the Stopwatch System](https://github.com/user-attachments/assets/113a31c3-b0f8-45e3-abef-4e297c04203a)
