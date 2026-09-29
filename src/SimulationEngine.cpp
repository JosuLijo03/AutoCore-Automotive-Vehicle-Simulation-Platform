#include "SimulationEngine.h"

#include <cstdlib>
#include <ctime>

SimulationEngine::SimulationEngine(VehicleState* state)
    : QObject(nullptr),
      vehicle(state)
{
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    connect(&timer,
            &QTimer::timeout,
            this,
            &SimulationEngine::updateVehicle);
}

void SimulationEngine::startSimulation()
{
    if (!timer.isActive())
        timer.start(1000);
}

void SimulationEngine::stopSimulation()
{
    timer.stop();
}

void SimulationEngine::updateVehicle()
{
   
    // Charging Mode
   

    if(vehicle->isCharging())
    {
        int battery = vehicle->getBatteryLevel();

        if(battery < 100)
        {
            battery++;
            vehicle->setBatteryLevel(battery);
            vehicle->setEstimatedRange(battery * 4);
        }
        else
        {
            vehicle->setCharging(false);
            vehicle->setDrivingMode(DrivingMode::Parked);
        }

        return;
    }

   
    // Vehicle OFF
   

    if(!vehicle->isEngineRunning())
        return;

  
    // Trip Time
    

    vehicle->setTripTime(
        vehicle->getTripTime() + 1);

   
    // Speed
    

    int speed;

    if(vehicle->getDrivingMode() == DrivingMode::Manual)
    {
        speed = 30 + (std::rand() % 40);
    }
    else if(vehicle->getDrivingMode() == DrivingMode::AutoDrive)
    {
        speed = 40 + (std::rand() % 30);
    }
    else
    {
        speed = 0;
    }

    vehicle->setSpeed(speed);

   
    // Battery Consumption
  
    int battery = vehicle->getBatteryLevel();

    if(speed < 20)
        battery -= 1;
    else if(speed < 60)
        battery -= 2;
    else
        battery -= 3;

    if(battery < 0)
        battery = 0;

    vehicle->setBatteryLevel(battery);

    
    // Battery Empty
   

    if(battery == 0)
    {
        vehicle->setSpeed(0);

        vehicle->stopEngine();

        vehicle->setDrivingMode(DrivingMode::Parked);

        stopSimulation();

        return;
    }

    
    // Distance
    
    float distance =
        vehicle->getDistanceTravelled();

    distance += static_cast<float>(speed) / 3600.0f;

    vehicle->setDistanceTravelled(distance);

    
    // Estimated Range
    
    vehicle->setEstimatedRange(
        battery * 4);
}