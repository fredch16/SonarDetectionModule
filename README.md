# Sonar Detection Module

A real-time ultrasonic scanning system built using an ESP32, an HC-SR04 ultrasonic sensor, and a servo motor.

This project explores how low-cost sensors can be combined with embedded control systems to generate a simple spatial representation of the surrounding environment through automated scanning and real-time visualization.

<p align="center">
  <img src="./media/demo.gif" alt="Sonar scanning demonstration" width="700"/>
</p>

---

## Motivation

I built this project to explore how sensing systems interact with physical space, and how environmental data can be collected, processed, and visualized in real time using low-cost embedded hardware.

The project combines:
- sensor integration,
- servo control,
- spatial scanning,
- telemetry,
- and real-time visualization

into a single interactive system.

Rather than focusing on precision mapping, the goal was to better understand the fundamentals behind active sensing systems commonly used in robotics and autonomous systems.

---

## System Architecture

```text
HC-SR04 Ultrasonic Sensor
                ↓
        ESP32 Data Acquisition
                ↓
         Distance Processing
                ↓
         Servo Angle Control
                ↓
         Serial Telemetry
                ↓
      Real-Time Visualization
```

---

## Features

- Real-time distance measurement
- Servo-mounted sensor scanning
- Automatic sweep mode
- Manual joystick control
- Live visualization pipeline
- Adjustable scanning range

---

## Technical Challenges

Some of the more interesting parts of the project included:
- stabilizing noisy ultrasonic readings,
- synchronizing scan angle with sensor measurements,
- handling inconsistent reflections,
- smoothing visualization updates,
- and balancing scan speed with measurement reliability.

These challenges made the project a valuable introduction to real-world sensing limitations and embedded control systems.

---

## Project Walkthrough

A full build walkthrough and demonstration can be found here:

[https://www.youtube.com/watch?v=oYuoHVy-8jg]

---

## Future Improvements

- Higher resolution scanning
- Wireless telemetry
- Occupancy grid mapping
- Multiple sensor integration
- SLAM experimentation
- Improved filtering and smoothing
- Autonomous tracking modes

---

## License

MIT License
