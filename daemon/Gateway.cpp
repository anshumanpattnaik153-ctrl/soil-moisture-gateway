#include "Gateway.hpp"

#include <chrono>
#include <iostream>

Gateway::Gateway()
    : hal("/dev/soil_gateway"),
      running(false)
{
    for (int i = 1; i <= NODE_COUNT; ++i)
    {
        nodes.push_back(std::make_unique<Node>(i));
    }
}

Gateway::~Gateway()
{
    stop();
}

bool Gateway::start()
{
    if (running)
        return true;

    if (!hal.openDevice())
    {
        std::cerr << "[Gateway] Failed to open HAL device\n";
        return false;
    }

    running = true;

    monitoringThread = std::thread(
        &Gateway::monitoringLoop,
        this
    );

    std::cout << "[Gateway] Started successfully\n";

    return true;
}

void Gateway::stop()
{
    if (!running)
        return;

    running = false;

    if (monitoringThread.joinable())
    {
        monitoringThread.join();
    }

    hal.closeDevice();

    std::cout << "[Gateway] Stopped\n";
}

void Gateway::monitoringLoop()
{
    while (running)
    {
        std::vector<SoilNode> data = hal.readNodes();

        if (!data.empty())
        {
            processNodes(data);
        }
        else
        {
            std::cerr << "[Gateway] No sensor data received\n";
        }

        std::this_thread::sleep_for(
            std::chrono::seconds(2)
        );
    }
}

void Gateway::processNodes(
    const std::vector<SoilNode>& data)
{
    std::lock_guard<std::mutex> lock(gatewayMutex);

    for (const auto& sensorData : data)
    {
        if (sensorData.nodeId < 1 ||
            sensorData.nodeId > NODE_COUNT)
        {
            continue;
        }

        Node& node = *nodes[sensorData.nodeId - 1];

        node.update(sensorData);

        NodeState state = node.getState();
        // Sensor analytics
if (sensorData.moisture < 30)
{
    std::cout << "[STATUS: DRY] ";
    std::cout << "[ACTION: WATERING RECOMMENDED] ";
}
else if (sensorData.moisture <= 60)
{
    std::cout << "[STATUS: NORMAL] ";
}
else
{
    std::cout << "[STATUS: WET] ";
}

if (sensorData.battery < 20)
{
    std::cout << "[WARNING: LOW BATTERY] ";
}

if (sensorData.temperature > 35)
{
    std::cout << "[WARNING: HIGH TEMPERATURE] ";
}

        std::cout
            << "[Node " << sensorData.nodeId << "] "
            << "Moisture=" << sensorData.moisture << "% "
            << "Temperature=" << sensorData.temperature << "C "
            << "Battery=" << sensorData.battery << "% ";

        if (state == NodeState::ONLINE)
        {
            std::cout << "[ONLINE]";
        }
        else if (state == NodeState::ALERT)
        {
            std::cout << "[ALERT: LOW MOISTURE]";
        }
        else
        {
            std::cout << "[OFFLINE]";
        }

        std::cout << '\n';
    }

    std::cout << "----------------------------------------\n";
}
