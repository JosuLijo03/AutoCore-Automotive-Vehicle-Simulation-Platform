#ifndef SENSORMANAGER_H
#define SENSORMANAGER_H

#include "VehicleState.h"

#include <thread>
#include <atomic>

class SensorManager
{
private:
    VehicleState* vehicle;

    std::thread sensorThread;

    std::atomic<bool> running;

    void updateLoop();

public:
    explicit SensorManager(VehicleState* state);

    ~SensorManager();

    void start();

    void stop();
};

#endif