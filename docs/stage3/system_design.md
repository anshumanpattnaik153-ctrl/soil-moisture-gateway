# Stage 3 – System Design & Architecture

## 1. Project Title

Smart Agricultural Soil-Moisture Multi-Node Gateway

## 2. System Overview

The Smart Agricultural Soil-Moisture Multi-Node Gateway is a Linux-based
simulation and processing system designed to collect, process, monitor and
store data from multiple agricultural sensor nodes.

The system represents multiple soil sensor nodes and processes parameters
such as soil moisture, temperature and battery level.

The gateway classifies soil conditions and generates irrigation
recommendations based on sensor data.

The project is designed to demonstrate Linux, C++, system programming,
device-driver concepts, hardware/software interaction and multi-node
sensor processing.

## 3. High-Level Architecture

The system is divided into the following major components:

Sensor Nodes
     |
     v
Hardware Abstraction Layer (HAL)
     |
     v
Linux Device Driver
     |
     v
Sensor Gateway / Daemon
     |
     v
C++ Sensor Processor
     |
     +------------------+
     |                  |
     v                  v
Backend / Database   Monitoring
     |
     v
Reports / Analytics

## 4. Major Components

### 4.1 Sensor Nodes

The sensor nodes represent agricultural field sensing devices.

Each node provides:

- Node ID
- Soil moisture
- Temperature
- Battery percentage
- Timestamp
- Sensor/device information

The prototype currently represents multiple virtual sensor nodes.

### 4.2 Hardware Abstraction Layer

The Hardware Abstraction Layer provides a common interface between
higher-level software and sensor/device implementations.

Responsibilities:

- Abstract hardware-specific operations
- Provide sensor data to the gateway
- Reduce dependency on hardware implementation
- Support future real sensor integration

### 4.3 Linux Device Driver

The Linux device-driver component represents the low-level interface
between the operating system and the sensor device.

Responsibilities:

- Provide a Linux device interface
- Receive/read sensor information
- Expose sensor data to user-space software
- Demonstrate kernel/user-space interaction

### 4.4 Sensor Gateway / Daemon

The gateway daemon acts as the central processing service.

Responsibilities:

- Receive sensor data
- Manage multiple sensor nodes
- Forward data to the C++ processor
- Maintain continuous monitoring
- Coordinate communication between system components

### 4.5 C++ Sensor Processor

The C++ processor performs sensor-data processing.

Responsibilities:

- Process sensor readings
- Determine soil status
- Generate irrigation recommendations
- Validate sensor values
- Display processed information
- Generate sensor logs

### 4.6 Backend and Database

The backend stores processed sensor information.

Responsibilities:

- Store sensor records
- Retrieve historical data
- Provide monitoring information
- Support future API integration
- Support analytics

## 5. Data Structure

The primary sensor data structure is:

SensorNode

Fields:

- node_id
- moisture
- temperature
- battery
- status
- recommendation
- timestamp

Example conceptual structure:

SensorNode
 |
 +-- node_id
 +-- moisture
 +-- temperature
 +-- battery
 +-- status
 +-- recommendation
 +-- timestamp

## 6. Soil Status Logic

The initial soil classification is:

Moisture < 40%
    -> DRY
    -> IRRIGATION RECOMMENDED

Moisture 40% to 60%
    -> NORMAL
    -> NO ACTION

Moisture > 60%
    -> WET
    -> NO ACTION

This threshold-based logic can be improved in future versions using
weather information, crop type and historical sensor data.

## 7. System Data Flow

1. Sensor nodes generate sensor readings.
2. The hardware abstraction layer represents the sensor interface.
3. The Linux device-driver layer provides the operating-system interface.
4. The gateway daemon receives sensor information.
5. The C++ processor validates and processes the data.
6. Soil status is calculated.
7. Irrigation recommendations are generated.
8. Processed data is logged.
9. Backend/database components store the information.
10. Monitoring and analytics components use the processed data.

## 8. Class Diagram

The planned class structure is:

SensorNode
 |
 +-- nodeId
 +-- moisture
 +-- temperature
 +-- battery
 +-- status
 +-- recommendation
 +-- timestamp

SensorProcessor
 |
 +-- processSensorData()
 +-- getStatus()
 +-- getRecommendation()
 +-- validateData()

Gateway
 |
 +-- receiveSensorData()
 +-- manageNodes()
 +-- forwardData()

DataLogger
 |
 +-- saveData()
 +-- readData()

The exact class structure may be refined during implementation.

## 9. Sequence Diagram

The planned processing sequence is:

Sensor Node
    |
    | Sensor data
    v
HAL
    |
    | Device data
    v
Linux Device Driver
    |
    | Read data
    v
Gateway Daemon
    |
    | Sensor record
    v
C++ Sensor Processor
    |
    | Process data
    v
Status / Recommendation
    |
    +---------> Logger
    |
    +---------> Database
    |
    +---------> Monitoring

## 10. State Machine

A sensor node can follow these states:

START
  |
  v
INITIALIZE
  |
  v
READ SENSOR
  |
  v
VALIDATE DATA
  |
  +---- Invalid ----> ERROR
  |                    |
  |                    v
  |                 RECOVER
  |                    |
  +--------------------+
  |
  v
PROCESS DATA
  |
  +---- Moisture < 40% ----> DRY
  |
  +---- Moisture 40-60% ---> NORMAL
  |
  +---- Moisture > 60% ----> WET
  |
  v
LOG DATA
  |
  v
MONITOR
  |
  v
READ SENSOR

## 11. System Interfaces

The planned interfaces are:

### Driver Interface

Provides communication between the Linux kernel/device-driver layer
and user-space applications.

### Gateway Interface

Transfers sensor information from the gateway daemon to the processing
layer.

### Processor Interface

Provides processed sensor status and irrigation recommendations.

### Database Interface

Stores and retrieves sensor information.

## 12. Development Environment

The project development environment includes:

- Ubuntu Linux 26.04 virtual machine
- Oracle VirtualBox
- GNU/Linux terminal
- GNU C++ compiler (g++)
- C++17
- GNU Nano
- Git
- Git repository
- Linux system programming tools

## 13. Repository Structure

The planned repository structure is:

soil-moisture-gateway/
|
+-- backend/
+-- cpp/
+-- daemon/
+-- driver/
+-- hal/
+-- docs/
|   +-- stage1/
|   +-- stage2/
|   +-- stage3/
+-- .gitignore

## 14. Git Branching Strategy

The project uses Git for version control.

Main branches:

master
    |
    +-- stage3-design
    |
    +-- future implementation branches

The master branch represents the stable project history.

Feature or stage-specific branches are used for development before
changes are integrated into the stable branch.

## 15. Implementation Plan

Stage 3:
- Complete system architecture
- Complete UML/design documentation
- Define interfaces
- Define data structures

Stage 4:
- Implement core C++ modules
- Implement gateway components
- Develop initial driver prototype
- Integrate components
- Demonstrate working prototype

Stage 5:
- Perform unit testing
- Perform integration testing
- Debug the system
- Improve reliability and performance
- Update documentation

Stage 6:
- Complete final implementation
- Demonstrate complete system
- Prepare final report
- Prepare UML and architecture diagrams
- Demonstrate Git history
- Present achievements, limitations and future improvements

## 16. Design Considerations

The system is designed to be:

- Modular
- Maintainable
- Scalable
- Testable
- Extensible
- Suitable for Linux-based development

The multi-node architecture allows additional sensor nodes to be
added without changing the complete system architecture.

## 17. Stage 3 Deliverables

The following deliverables are planned for Stage 3:

- System architecture
- Component descriptions
- Data structures
- Class diagram
- Sequence diagram
- State machine diagram
- Development environment
- Repository structure
- Git branching strategy
- Implementation plan
- Stage 3 documentation

## 18. Stage 3 Success Criteria

Stage 3 will be considered complete when:

- The system architecture is documented.
- Major components and responsibilities are defined.
- Data structures are documented.
- Class, sequence and state-machine designs are prepared.
- Development tools are identified.
- Git branching strategy is documented.
- Implementation roadmap is defined.
- The design is consistent with the project requirements.
- Stage 3 documentation is committed to Git.

## 19. Stage 3 Conclusion

Stage 3 defines the architecture and design of the Smart Agricultural
Soil-Moisture Multi-Node Gateway.

The design provides a structured path from sensor data acquisition through
Linux/device-driver interaction, gateway processing, C++ processing,
logging, database storage and monitoring.

The design will guide the implementation and integration work in Stage 4.
