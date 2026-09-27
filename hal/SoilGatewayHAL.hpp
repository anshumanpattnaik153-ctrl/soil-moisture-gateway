#ifndef SOIL_GATEWAY_HAL_HPP
#define SOIL_GATEWAY_HAL_HPP

#include <string>
#include <vector>

struct SoilNode
{
    int nodeId;
    int moisture;
    int temperature;
    int battery;
};

class SoilGatewayHAL
{
public:
    explicit SoilGatewayHAL(const std::string& devicePath = "/dev/soil_gateway");
    ~SoilGatewayHAL();

    SoilGatewayHAL(const SoilGatewayHAL&) = delete;
    SoilGatewayHAL& operator=(const SoilGatewayHAL&) = delete;

    bool openDevice();
    void closeDevice();

    std::vector<SoilNode> readNodes();

    bool isOpen() const;

private:
    std::string devicePath;
    int fileDescriptor;
};

#endif
