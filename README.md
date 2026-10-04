# Smart Agricultural Soil-Moisture Monitoring Gateway

## Project Overview

The **Smart Agricultural Soil-Moisture Monitoring Gateway** is a Linux-based prototype designed to monitor and process soil-moisture and environmental information from multiple agricultural sensor nodes.

The project demonstrates Linux Device Driver concepts, Hardware Abstraction Layer (HAL), Linux system programming, C/C++ programming, gateway processing, a C++ HTTP backend, SQLite database storage, and a web-based monitoring dashboard.

The current prototype uses simulated sensor nodes to demonstrate the complete software architecture and data flow. Physical agricultural sensors can be integrated in future development.

## Problem Statement

Agricultural fields require continuous monitoring of soil conditions to support efficient irrigation decisions.

Manual monitoring can be time-consuming and may result in over-irrigation, under-irrigation, unnecessary water consumption, and delayed detection of dry soil conditions.

This project provides a Linux-based gateway that collects sensor information, processes the data, identifies soil conditions, generates irrigation recommendations, and presents the information through a web dashboard.

## Objectives

- Develop a Linux-based agricultural monitoring gateway.
- Demonstrate Linux Device Driver concepts.
- Implement a Hardware Abstraction Layer.
- Process multiple agricultural sensor nodes.
- Use C/C++ for system-level and application-level development.
- Classify soil conditions using soil-moisture values.
- Detect low-moisture conditions.
- Generate irrigation recommendations.
- Store and retrieve sensor information using SQLite.
- Develop a C++ HTTP backend.
- Provide a web-based monitoring dashboard.
- Demonstrate complete system integration.

## System Architecture

```text
Simulated Sensor Nodes
          |
          v
Hardware Abstraction Layer (HAL)
          |
          v
Linux Device Driver
          |
          v
Gateway Daemon
          |
          v
C++ Sensor Processing
          |
          v
C++ HTTP Backend
          |
          v
SQLite Database
          |
          v
Monitoring Dashboard

## Technologies Used

| Technology | Purpose |
|---|---|
| Linux | Operating system and development platform |
| C | Linux Device Driver development |
| C++17 | Gateway, sensor processing and backend |
| Linux Kernel Module | Device-driver implementation |
| POSIX/Linux APIs | System-level programming |
| SQLite3 | Database storage |
| HTTP | Backend communication |
| HTML/CSS/JavaScript | Monitoring dashboard |
| Git | Version control |
| GitHub | Project hosting |
| Graphviz | Architecture diagrams |

## Major Components

### 1. Simulated Sensor Nodes

The prototype uses simulated agricultural sensor nodes.

Each sensor node contains:

- Node ID
- Soil moisture
- Temperature
- Battery level
- Soil condition

The prototype demonstrates monitoring of multiple sensor nodes simultaneously.

### 2. Hardware Abstraction Layer

The Hardware Abstraction Layer (HAL) provides an interface between the gateway software and the underlying device interface.

The HAL separates device-specific operations from higher-level application logic and provides a foundation for future physical sensor integration.

### 3. Linux Device Driver

The project implements a Linux character-device-driver interface.

The device is exposed through:

```text
/dev/soil_gateway


## C++ HTTP Backend

The project uses a C++ HTTP backend to provide sensor information to the dashboard.

Backend source:

backend_cpp/server.cpp

The backend runs at:

http://127.0.0.1:5000

The backend provides HTTP endpoints for sensor history, sensor nodes, individual node information, analytics, and dashboard access.

## SQLite Database

SQLite is used as the local database layer.

The database provides storage and retrieval of sensor-related information required by the backend and dashboard.

SQLite was selected because it is lightweight, does not require a separate database server, and integrates easily with C++.

Runtime database files are excluded from Git tracking through .gitignore.

## Monitoring Dashboard

The project includes a web-based monitoring dashboard served by the C++ HTTP backend.

Open:

http://127.0.0.1:5000/

The dashboard displays:

- Total number of nodes
- Soil-moisture values
- Temperature
- Battery level
- Soil condition
- Dry-node alerts
- Historical information
- System analytics

## API Endpoints

### Sensor History

GET /api/history

### All Sensor Nodes

GET /api/nodes

### Individual Sensor Node

GET /api/nodes/<node_id>

### Analytics

GET /api/analytics

Example:

curl http://127.0.0.1:5000/api/nodes
curl http://127.0.0.1:5000/api/analytics

## Example Analytics

The prototype successfully generated:

Total Nodes         : 8
Average Moisture    : 49.125
Average Temperature : 27.25
Average Battery     : 89.5
Dry Nodes            : 2
Normal Nodes         : 4
Wet Nodes            : 2

## Prerequisites

- Linux operating system
- GCC/G++
- C++17 compiler
- Make
- Linux kernel development tools
- SQLite3
- SQLite3 development library
- Git

## Installation

Clone the repository:

git clone https://github.com/anshumanpattnaik153-ctrl/soil-moisture-gateway.git

Enter the project directory:

cd soil-moisture-gateway

## Build Instructions

### Linux Device Driver

make -C driver

### C++ Sensor Processor

g++ cpp/sensor_processor.cpp -o cpp/sensor_processor

### C++ HTTP Backend

g++ -std=c++17 backend_cpp/server.cpp -o backend_cpp/soil_backend -lsqlite3


## Running the Project

### Step 1: Load the Device Driver

sudo insmod driver/soil_gateway.ko

Verify the driver:

lsmod | grep soil_gateway

Verify the device:

ls -l /dev/soil_gateway

### Step 2: Start the Gateway

sudo ./daemon/soil_gateway_debug

The gateway processes sensor information and generates alerts for dry nodes.

Press Ctrl+C to stop the gateway.

### Step 3: Start the C++ Backend

Open another terminal:

./backend_cpp/soil_backend

The backend starts at:

http://127.0.0.1:5000

### Step 4: Open the Dashboard

Open a web browser and visit:

http://127.0.0.1:5000/

## Testing and Results

The project was tested at component and integration levels.

| Test | Result |
|---|---|
| C++ compilation | PASS |
| Sensor processing | PASS |
| Moisture classification | PASS |
| Hardware Abstraction Layer | PASS |
| Linux Device Driver loading | PASS |
| Device node creation | PASS |
| Gateway daemon execution | PASS |
| Multiple-node processing | PASS |
| Low-moisture alert | PASS |
| C++ backend startup | PASS |
| `/api/nodes` API | PASS |
| `/api/history` API | PASS |
| `/api/analytics` API | PASS |
| Dashboard operation | PASS |
| End-to-end integration | PASS |

## Project Structure

```text
soil-moisture-gateway/
│
├── backend_cpp/
│   ├── server.cpp
│   └── index.html
│
├── cpp/
│   └── sensor_processor.cpp
│
├── daemon/
│   └── Gateway source files
│
├── driver/
│   ├── Device Driver source
│   └── Makefile
│
├── hal/
│   ├── HAL source
│   └── HAL test program
│
├── docs/
│   ├── stage1/
│   ├── stage2/
│   ├── stage3/
│   ├── stage4/
│   ├── stage5/
│   ├── stage6/
│   └── final/
│
├── .gitignore
└── README.md


## Documentation

The `docs/` directory contains:

- Project introduction
- Project requirements
- System design
- Implementation plan
- Testing plan
- Testing results
- Final implementation documentation
- Architecture diagram
- Class diagram
- Sequence diagram
- State diagram
- Final project report
- Project presentation

## Development Stages

### Stage 1 — Project Introduction

Defined the project idea, scope, and agricultural monitoring problem.

### Stage 2 — Requirements

Defined functional and technical requirements.

### Stage 3 — System Design

Designed the system architecture and major components.

### Stage 4 — Implementation Planning

Defined the implementation approach for the driver, HAL, gateway, and processing components.

### Stage 5 — Testing

Performed component-level and integration testing.

### Stage 6 — Final Implementation

Integrated the Linux Device Driver, gateway, C++ processing, C++ HTTP backend, SQLite database, and monitoring dashboard.

## Limitations

- Physical soil-moisture sensors are not connected.
- Sensor data is currently simulated.
- The system is designed primarily for local Linux execution.
- Automatic irrigation hardware is not implemented.
- Cloud deployment is not included.
- Authentication and authorization are not implemented.
- HTTPS is not configured for the prototype.
- The system is an academic prototype rather than a production deployment.

## Future Scope

- Physical soil-moisture sensor integration
- ESP32 or Raspberry Pi sensor nodes
- Wireless sensor communication
- Wi-Fi, LoRa, or Zigbee connectivity
- Automatic irrigation control
- Water pump and relay integration
- Cloud-based monitoring
- Mobile application
- User authentication
- HTTPS support
- Advanced agricultural analytics
- Weather integration
- Predictive irrigation
- Machine-learning-based recommendations

## Project Requirements Compliance

### Programming Languages

C  
C++17

### Operating System

Linux

### Linux Device Driver

A Linux Device Driver and `/dev/soil_gateway` device interface are implemented.

### System Programming

The project demonstrates Linux system-level programming and device interaction.

### Software Architecture

```text
Sensor Nodes
     ↓
HAL
     ↓
Linux Device Driver
     ↓
Gateway
     ↓
C++ Sensor Processing
     ↓
C++ HTTP Backend
     ↓
SQLite Database
     ↓
Monitoring Dashboard


## Conclusion

The **Smart Agricultural Soil-Moisture Monitoring Gateway** demonstrates a complete Linux-based software architecture for agricultural sensor monitoring.

The prototype successfully integrates simulated sensor nodes, Hardware Abstraction Layer, Linux Device Driver, gateway daemon, C++ sensor processing, C++ HTTP backend, SQLite database, and web-based monitoring dashboard.

The system successfully processes multiple sensor nodes, classifies soil-moisture conditions, detects dry nodes, generates irrigation recommendations, provides monitoring data through HTTP APIs, and presents the information through a web dashboard.

Although the current implementation uses simulated sensor nodes, the architecture provides a strong foundation for future integration with physical agricultural sensors, wireless communication, automatic irrigation, cloud monitoring, and advanced agricultural analytics.

## Author

**B.Tech – Computer Science and Engineering**

**Project:** Smart Agricultural Soil-Moisture Monitoring Gateway

**Academic Project**

## GitHub Repository

https://github.com/anshumanpattnaik153-ctrl/soil-moisture-gateway
