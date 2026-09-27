# Stage 2 – Project Requirements Document (PRD)

## Project Title

Smart Agricultural Soil-Moisture Multi-Node Gateway

## 1. Project Overview

The Smart Agricultural Soil-Moisture Multi-Node Gateway is a Linux-based software system designed to simulate, process, store, and monitor soil-moisture information from multiple agricultural sensor nodes.

The system will demonstrate concepts related to Linux, C++, system programming, device-driver concepts, hardware/software interaction, data processing, networking, and backend services.

The project will initially use simulated sensor data and software-based sensor nodes. The architecture will allow future integration with real sensor hardware.

## 2. Problem Statement

Agricultural irrigation requires information about soil conditions at different locations.

A single sensor may not provide sufficient information for a larger agricultural area. A multi-node system can collect information from several locations and process the data centrally.

The project aims to develop a Linux-based gateway capable of receiving and processing data from multiple sensor nodes, determining soil conditions, storing sensor information, and providing monitoring information to the user.

## 3. Objectives

The main objectives are:

1. Develop a Linux-based agricultural sensor gateway.
2. Simulate multiple soil-moisture sensor nodes.
3. Process sensor information using C++.
4. Use Linux system-programming concepts.
5. Develop a hardware-abstraction/device-driver interface.
6. Transfer sensor information between system components.
7. Store sensor data using a database.
8. Provide a backend interface for monitoring sensor information.
9. Detect dry, normal, and wet soil conditions.
10. Generate irrigation recommendations.
11. Maintain logs and historical sensor information.
12. Test and document the complete system.

## 4. Project Scope

### In Scope

- Linux development environment
- C++ sensor-processing module
- Multiple virtual sensor nodes
- Soil-moisture processing
- Temperature and battery information
- Sensor status classification
- Irrigation recommendation generation
- Linux system-programming concepts
- Hardware abstraction layer
- Linux device-driver implementation/concept
- Inter-process communication where required
- Data logging
- SQLite/database storage
- Python/Flask backend
- REST API
- Monitoring interface
- Unit testing
- Integration testing
- System testing
- Git version control
- Technical documentation

### Out of Scope

- Commercial agricultural deployment
- Direct control of real irrigation pumps
- Production-grade wireless hardware
- Safety-critical agricultural control
- Large-scale cloud deployment

Real hardware integration may be considered as a future improvement.

## 5. Functional Requirements

### FR-01: Sensor Node Management

The system shall support multiple sensor nodes.

Each node shall contain:

- Node ID
- Soil moisture
- Temperature
- Battery level
- Sensor status
- Recommendation

### FR-02: Sensor Data Processing

The system shall process sensor information and classify soil conditions.

The initial classification shall be:

- Moisture below 40%: DRY
- Moisture from 40% to 60%: NORMAL
- Moisture above 60%: WET

### FR-03: Irrigation Recommendation

The system shall generate an irrigation recommendation based on soil moisture.

Dry nodes shall generate:

IRRIGATION RECOMMENDED

Normal and wet nodes shall generate:

NO ACTION

### FR-04: Data Storage

The system shall store processed sensor information in a database.

The database shall maintain information such as:

- Timestamp
- Node ID
- Moisture
- Temperature
- Battery
- Status
- Recommendation

### FR-05: Backend API

The backend shall provide APIs for accessing:

- Current sensor nodes
- Individual node information
- Historical sensor data
- System analytics

### FR-06: Monitoring

The system shall provide a monitoring mechanism for viewing sensor information and system status.

### FR-07: Logging

The system shall maintain logs of sensor-processing and gateway activities.

### FR-08: Device Interface

The project shall provide a Linux-oriented device interface or driver component to demonstrate communication between user-space software and a lower-level system component.

## 6. Non-Functional Requirements

### NFR-01: Reliability

The system should process valid sensor information consistently.

### NFR-02: Performance

Sensor data processing should be lightweight and suitable for a Linux-based gateway.

### NFR-03: Maintainability

The software shall be divided into independent modules with clear responsibilities.

### NFR-04: Portability

The software should be capable of running in a Linux environment such as Ubuntu.

### NFR-05: Security

The system should avoid storing sensitive information unnecessarily and should validate input data.

### NFR-06: Scalability

The architecture should allow additional sensor nodes to be added without major changes to the core processing logic.

### NFR-07: Documentation

Source code, architecture, requirements, testing results, Git history, and project progress shall be documented throughout development.

## 7. Major System Modules

The project will contain the following major modules:

### 7.1 C++ Sensor Processor

Responsible for:

- Sensor-node representation
- Sensor data processing
- Soil-status classification
- Irrigation recommendation
- C++ data structures
- File-based output/logging

### 7.2 Linux Device Driver / Device Interface

Responsible for demonstrating:

- Linux kernel/device-driver concepts
- Device registration
- Device access
- Communication between user space and kernel/device layer

### 7.3 Hardware Abstraction Layer

Responsible for providing an abstraction between sensor/device interfaces and higher-level application software.

### 7.4 Daemon / System Service

Responsible for:

- Background execution
- Periodic sensor processing
- Logging
- Gateway operation

### 7.5 Backend Gateway

Responsible for:

- Receiving sensor information
- Providing APIs
- Connecting processing components
- Providing monitoring functionality

### 7.6 Database

Responsible for:

- Sensor history
- Node information
- Timestamped measurements
- System analytics

### 7.7 Monitoring Interface

Responsible for displaying:

- Node status
- Moisture
- Temperature
- Battery
- Recommendations
- Historical information
- Analytics

## 8. Expected Inputs

The system may receive:

- Node ID
- Soil moisture percentage
- Temperature
- Battery percentage
- Timestamp
- Sensor/device information

## 9. Expected Outputs

The system shall produce:

- Soil status
- Irrigation recommendation
- Processed sensor data
- Sensor logs
- Database records
- API responses
- Monitoring information
- System analytics

## 10. Initial Data Model

Each sensor node shall use a structure similar to:

```text
SensorNode
|
+-- node_id
+-- moisture
+-- temperature
+-- battery
+-- status
+-- recommendation
+-- timestamp
