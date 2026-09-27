#include "Node.hpp"

Node::Node(int id)
    : id(id),
      data{},
      state(NodeState::OFFLINE)
{
    data.nodeId = id;
}

void Node::update(const SoilNode& newData)
{
    std::lock_guard<std::mutex> lock(mutex);

    data = newData;

    if (data.moisture < MOISTURE_THRESHOLD)
    {
        state = NodeState::ALERT;
    }
    else
    {
        state = NodeState::ONLINE;
    }
}

int Node::getId() const
{
    std::lock_guard<std::mutex> lock(mutex);

    return id;
}

SoilNode Node::getData() const
{
    std::lock_guard<std::mutex> lock(mutex);

    return data;
}

NodeState Node::getState() const
{
    std::lock_guard<std::mutex> lock(mutex);

    return state;
}

bool Node::isMoistureLow() const
{
    std::lock_guard<std::mutex> lock(mutex);

    return data.moisture < MOISTURE_THRESHOLD;
}
