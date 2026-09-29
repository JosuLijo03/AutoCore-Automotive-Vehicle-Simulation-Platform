#include "SensorManager.h"

#include <chrono>
#include <thread>

SensorManager::SensorManager(VehicleState* state)
{
    vehicle = state;
    running = false;
}

SensorManager::~SensorManager()
{
    stop();
}

void SensorManager::start()
{
    if (running)
        return;

    running = true;

    sensorThread = std::thread(&SensorManager::updateLoop, this);
}

void SensorManager::stop()
{
    running = false;

    if (sensorThread.joinable())
        sensorThread.join();
}

void SensorManager::updateLoop()
{
    while (running)
    {
        if (vehicle->isEngineRunning())
        {
           
            // Speed
           

            int speed = vehicle->getSpeed();

            if (speed < 80)
                speed += 5;

            vehicle->setSpeed(speed);

           
            // Battery
         
            int battery = vehicle->getBatteryLevel();

            if (battery > 0)
                battery--;

            vehicle->setBatteryLevel(battery);

          
            // Battery Empty
           

            if (battery == 0)
            {
                vehicle->stopEngine();
                vehicle->setSpeed(0);
            }

            
            // Distance
            

            float distance =
                vehicle->getDistanceTravelled();

            distance += speed / 3600.0f;

            vehicle->setDistanceTravelled(distance);

          
            // Estimated Range
            

            vehicle->setEstimatedRange(battery * 4);
        }
        else
        {
            vehicle->setSpeed(0);
        }

        std::this_thread::sleep_for(
            std::chrono::seconds(1));
    }
}