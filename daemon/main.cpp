#include "Gateway.hpp"

#include <csignal>
#include <iostream>
#include <thread>
#include <chrono>

static volatile std::sig_atomic_t stopRequested = 0;

void signalHandler(int)
{
    stopRequested = 1;
}

int main()
{
    std::signal(SIGINT, signalHandler);
    std::signal(SIGTERM, signalHandler);

    std::cout << "========================================\n";
    std::cout << "     Soil Moisture Gateway Daemon\n";
    std::cout << "========================================\n";

    Gateway gateway;

    if (!gateway.start())
    {
        std::cerr << "Failed to start gateway\n";
        return 1;
    }

    std::cout << "Gateway daemon running...\n";
    std::cout << "Press Ctrl+C to stop.\n\n";

    while (!stopRequested)
    {
        std::this_thread::sleep_for(
            std::chrono::milliseconds(500)
        );
    }

    std::cout << "\nStopping gateway...\n";

    gateway.stop();

    std::cout << "Gateway daemon stopped.\n";

    return 0;
}
