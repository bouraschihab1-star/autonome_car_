# Autonomous Robotics Project

## Overview

This project implements an autonomous robotic system developed in **C++** with a **Qt-based interface** for real-time supervision. It focuses on sensor acquisition, data filtering, and proportional control to enable stable and responsive navigation.

## Features

* **Real-time sensor acquisition** (distance measurements)
* **Filtered data processing** for improved stability
* **Proportional controller (P-control)** for navigation and steering decisions
* **Qt interface** for:

  * Live monitoring of sensor values, setpoints, and control signals
  * Dynamic adjustment of parameters (KP, thresholds, filtering options)
* **Testing and validation tools** ensuring reproducible robot behavior

## Technologies

* **C++17**
* **Qt (Widgets / Signals & Slots)**
* **Microcontroller-based sensor system** (distance sensors)

## Objectives

* Achieve stable autonomous navigation
* Establish a modular and testable base for future improvements

## Repository Structure

* `/src` — Core C++ logic
* `/ui` — Qt interface files
* `/tests` — Validation and debugging tools
* `/docs` — Technical notes and explanations

## Future Improvements

* Add PID controller option
* Implement advanced filtering (moving average, Kalman)
* Improve visualization in the Qt interface

## Author
Created and maintained by Chihabedinne Bouras.
