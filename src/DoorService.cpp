#include "DoorService.h"
#include "Logger.h"

DoorService::DoorService(VehicleState* state)
{
    vehicle = state;
}

std::string DoorService::getName() const
{
    return "Door Service";
}

void DoorService::start()
{
    Logger::info("Door Service Started");
}

void DoorService::stop()
{
    Logger::info("Door Service Stopped");
}

void DoorService::lockDoors()
{
    if(vehicle->areDoorsLocked())
    {
        Logger::warning("Doors are already locked.");
        return;
    }

    vehicle->lockDoors();
    Logger::info("Doors Locked");
}

void DoorService::unlockDoors()
{
    if(!vehicle->areDoorsLocked())
    {
        Logger::warning("Doors are already unlocked.");
        return;
    }

    vehicle->unlockDoors();
    Logger::info("Doors Unlocked");
}