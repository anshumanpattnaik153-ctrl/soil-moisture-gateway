#include "SoilGatewayHAL.hpp"

#include <fcntl.h>
#include <unistd.h>

#include <cerrno>
#include <cstring>
#include <iostream>
#include <sstream>

SoilGatewayHAL::SoilGatewayHAL(const std::string& devicePath)
    : devicePath(devicePath),
      fileDescriptor(-1)
{
}

SoilGatewayHAL::~SoilGatewayHAL()
{
    closeDevice();
}

bool SoilGatewayHAL::openDevice()
{
    if (isOpen())
        return true;

    fileDescriptor = open(devicePath.c_str(), O_RDONLY);

    if (fileDescriptor < 0)
    {
        std::cerr << "HAL: Failed to open "
                  << devicePath
                  << ": "
                  << std::strerror(errno)
                  << '\n';

        return false;
    }

    return true;
}

void SoilGatewayHAL::closeDevice()
{
    if (fileDescriptor >= 0)
    {
        close(fileDescriptor);
        fileDescriptor = -1;
    }
}

bool SoilGatewayHAL::isOpen() const
{
    return fileDescriptor >= 0;
}

std::vector<SoilNode> SoilGatewayHAL::readNodes()
{
    std::vector<SoilNode> nodes;

    if (!isOpen())
    {
        std::cerr << "HAL: Device is not open\n";
        return nodes;
    }

    char buffer[1024];

    ssize_t bytesRead = read(
        fileDescriptor,
        buffer,
        sizeof(buffer) - 1
    );

    if (bytesRead < 0)
    {
        std::cerr << "HAL: Read failed: "
                  << std::strerror(errno)
                  << '\n';

        return nodes;
    }

    buffer[bytesRead] = '\0';

    std::istringstream input(buffer);

    std::string line;

    while (std::getline(input, line))
    {
        SoilNode node;

        if (std::sscanf(
                line.c_str(),
                "Node %d: Moisture=%d%% Temperature=%dC Battery=%d%%",
                &node.nodeId,
                &node.moisture,
                &node.temperature,
                &node.battery) == 4)
        {
            nodes.push_back(node);
        }
    }

    return nodes;
}
