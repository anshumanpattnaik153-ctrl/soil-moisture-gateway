#ifndef GATEWAY_HPP
#define GATEWAY_HPP

#include "Node.hpp"
#include "../hal/SoilGatewayHAL.hpp"

#include <atomic>
#include <memory>
#include <mutex>
#include <thread>
#include <vector>

class Gateway
{
public:
    Gateway();
    ~Gateway();

    Gateway(const Gateway&) = delete;
    Gateway& operator=(const Gateway&) = delete;

    bool start();
    void stop();

private:
    void monitoringLoop();
    void processNodes(const std::vector<SoilNode>& data);

    SoilGatewayHAL hal;

    std::vector<std::unique_ptr<Node>> nodes;

    std::thread monitoringThread;

    std::atomic<bool> running;

    mutable std::mutex gatewayMutex;

    static constexpr int NODE_COUNT = 8;
};

#endif
