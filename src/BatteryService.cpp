#include "BatteryService.h"
#include "Logger.h"

BatteryService::BatteryService(VehicleState* state)
{
    vehicle = state;
}

std::string BatteryService::getName() const
{
    return "Battery Service";
}

void BatteryService::start()
{
    Logger::info("Battery Service Started");
}

void BatteryService::stop()
{
    Logger::info("Battery Service Stopped");
}

void BatteryService::charge(int amount)
{
    if(vehicle->getBatteryLevel() >= 100)
    {
        Logger::warning("Battery is already fully charged.");
        return;
    }

    int battery = vehicle->getBatteryLevel();

    battery += amount;

    if(battery > 100)
        battery = 100;

    vehicle->setBatteryLevel(battery);

    Logger::info("Battery Charged");
}

void BatteryService::discharge(int amount)
{
    int battery = vehicle->getBatteryLevel();

    battery -= amount;

    if(battery < 0)
        battery = 0;

    vehicle->setBatteryLevel(battery);

    Logger::info("Battery Discharged");
}