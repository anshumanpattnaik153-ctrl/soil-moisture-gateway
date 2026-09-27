# Stage 5 – Testing, Integration & Improvement
## Test Results and Verification Report

## 1. Introduction

Stage 5 focuses on testing, integration, debugging and improvement of the Smart Agricultural Soil-Moisture Monitoring Gateway.

Testing was performed on the Linux/Ubuntu development environment using simulated multi-node sensor data.

The testing covered the C++ processing module, Hardware Abstraction Layer (HAL), Linux device driver, gateway daemon, Flask backend, database/API services and monitoring dashboard.

---

## 2. Test Environment

- Operating System: Ubuntu Linux 26.04
- Programming Languages: C, C++, Python
- C++ Compiler: G++
- Linux Kernel: Ubuntu Linux kernel
- Backend Framework: Flask
- Database: SQLite
- API Testing: curl
- Version Control: Git
- Sensor Input: Simulated sensor nodes
- Number of Sensor Nodes: 8

---

## 3. Test Results

| Test ID | Component | Test | Result |
|---------|-----------|------|--------|
| TC-01 | C++ Processor | Compile sensor processor | PASS |
| TC-02 | C++ Processor | Process simulated sensor readings | PASS |
| TC-03 | C++ Processor | Verify moisture status classification | PASS |
| TC-04 | HAL | Access device and receive sensor data | PASS* |
| TC-05 | Linux Driver | Load kernel module | PASS |
| TC-06 | Linux Driver | Verify `/dev/soil_gateway` | PASS |
| TC-07 | Gateway | Start gateway daemon | PASS |
| TC-08 | Gateway | Detect/process sensor nodes | PASS |
| TC-09 | Gateway | Generate low-moisture alert | PASS |
| TC-10 | Backend | Start Flask application | PASS |
| TC-11 | API | Test `/api/nodes` | PASS |
| TC-12 | Database/API | Test `/api/history` | PASS |
| TC-13 | Dashboard | Display sensor monitoring data | PASS |
| TC-14 | Analytics | Test `/api/analytics` | PASS |
| TC-15 | Integration | Run gateway and process sensor data | PASS |

\* HAL access requires elevated privileges because `/dev/soil_gateway` currently has root-only permissions.

---

## 4. C++ Processor Testing

The C++ sensor processor was compiled and executed successfully.

The processor successfully processed 8 simulated sensor nodes and displayed:

- Node ID
- Soil moisture
- Temperature
- Battery level
- Moisture status
- Irrigation recommendation

The processor correctly classified sensor conditions into:

- DRY
- NORMAL
- WET

A dry sensor node generated an irrigation recommendation.

**Result: PASS**

---

## 5. HAL Testing

The Hardware Abstraction Layer was tested using the Linux device interface.

Initially, running the HAL as a normal user produced:

```text
Permission denied
