#include "SoilGatewayHAL.hpp"

#include <iostream>

int main()
{
    SoilGatewayHAL gateway;

    if (!gateway.openDevice())
    {
        std::cerr << "Failed to open soil gateway.\n";
        return 1;
    }

    std::vector<SoilNode> nodes = gateway.readNodes();

    if (nodes.empty())
    {
        std::cerr << "No node data received.\n";
        return 1;
    }

    std::cout << "=== Soil Moisture Gateway ===\n";
    std::cout << "Nodes received: " << nodes.size() << "\n\n";

    for (const auto& node : nodes)
    {
        std::cout
            << "Node " << node.nodeId
            << " | Moisture: " << node.moisture << "%"
            << " | Temperature: " << node.temperature << "C"
            << " | Battery: " << node.battery << "%\n";
    }

    gateway.closeDevice();

    return 0;
}
