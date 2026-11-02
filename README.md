# SWARM-Lite 2.0

**SWARM-Lite 2.0** is an embedded systems project featuring two mobile robots that communicate wirelessly and coordinate their movement through a master–child architecture. The master robot assigns commands or tasks, while the child robot executes them using its own onboard sensing and motor control.

The project focuses on reliable robot-to-robot communication, simple autonomous navigation, and integrating embedded software with a working physical platform.

## System Overview

Each robot uses a two-wheel differential-drive configuration with a passive caster for support. Navigation takes place on a predefined track marked with tape: a reflectance sensor array detects the line, and the controller adjusts the left and right wheel speeds to follow it.

The robots use **ESP-NOW** to exchange commands, acknowledgments, and status updates directly between their ESP32 microcontrollers. The master manages task-level decisions; each robot handles its own low-level movement and safety responses.

The design deliberately avoids SLAM and general-purpose path planning. Routes can instead be represented as sequences of decisions at known intersections on the track.

## Planned Capabilities

- **Master–child coordination:** The master sends tasks and movement instructions to the child.
- **Wireless communication:** ESP-NOW messaging with sequence numbers, acknowledgments, and communication-loss handling.
- **Line-following navigation:** Reflectance sensor feedback and differential motor control.
- **Route execution:** Predefined routes and junction-based decisions.
- **Obstacle detection:** A forward-facing distance sensor for stopping or responding to a blocked route.
- **Status reporting:** Clear robot states and serial logs for testing and debugging.

These are development goals; they are not claims of completed or verified functionality.

## Hardware

The planned hardware for **each robot** includes:

| Component | Purpose |
| --- | --- |
| ESP32 development board | Embedded control and wireless communication |
| Two DC gearmotors and drive wheels | Differential-drive locomotion |
| Passive caster | Third point of support |
| Dual-channel motor driver | Independent motor speed and direction control |
| QTR-8RC reflectance sensor array | Track and line detection |
| HC-SR04 ultrasonic sensor | Forward obstacle detection |
| Rechargeable battery and power regulation | Onboard power |
| LEDs and buzzer | Status indication |
| Custom chassis and mounting brackets | Mechanical integration |

Final component models and electrical ratings will be confirmed during hardware selection and testing.

## Software

The firmware is being developed in **C using ESP-IDF**. Its main responsibilities are separated into:

- **Communication:** Peer setup, message transmission and reception, acknowledgments, and timeouts.
- **Coordination:** Task assignments, route selection, and master–child state management.
- **Navigation:** Line sensing, motor control, intersection detection, and local safety stops.
- **Diagnostics:** Status indicators and serial output for validation.

A shared message format connects the communication and navigation modules, allowing the two robots to use a common firmware foundation with different roles.

## Development Plan

1. Establish the firmware project, module interfaces, and ESP-NOW communication.
2. Implement navigation, task handling, and coordination logic.
3. Build the robots and prepare the marked-track test arena.
4. Integrate and tune both robots on hardware.
5. Run communication, navigation, and end-to-end demonstration tests.

## Current Status

**Early development — Week 1.** The initial focus is the firmware structure and communication between two ESP32 boards. Hardware integration and on-track performance testing will follow.

## Team

Developed as a two-member Embedded Systems course project.