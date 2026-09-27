#ifndef NODE_HPP
#define NODE_HPP

#include "../hal/SoilGatewayHAL.hpp"

#include <chrono>
#include <mutex>

enum class NodeState
{
    OFFLINE,
    ONLINE,
    ALERT
};

class Node
{
public:
    explicit Node(int id);

    void update(const SoilNode& data);

    int getId() const;

    SoilNode getData() const;

    NodeState getState() const;

    bool isMoistureLow() const;

private:
    int id;

    SoilNode data;

    NodeState state;

    mutable std::mutex mutex;

    static constexpr int MOISTURE_THRESHOLD = 35;
};

#endif
