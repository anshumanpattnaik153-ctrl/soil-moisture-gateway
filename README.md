# Smart Agricultural Soil-Moisture Monitoring Gateway

## Project Overview

The Smart Agricultural Soil-Moisture Monitoring Gateway is a Linux-based prototype for monitoring multiple agricultural sensor nodes.

The project demonstrates Linux device-driver development, system programming, C++, hardware abstraction, backend development, database storage and web-based monitoring.

## Architecture

```text
Simulated Sensor Nodes
        ↓
Hardware Abstraction Layer
        ↓
Linux Device Driver
        ↓
Gateway Daemon
        ↓
C++ Sensor Processing
        ↓
Flask Backend
        ↓
SQLite Database
        ↓
Monitoring Dashboard
