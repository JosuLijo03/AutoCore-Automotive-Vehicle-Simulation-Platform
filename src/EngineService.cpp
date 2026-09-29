#include "EngineService.h"
#include "Logger.h"

EngineService::EngineService(VehicleState* state)
{
    vehicle = state;
}

std::string EngineService::getName() const
{
    return "Engine Service";
}

void EngineService::start()
{
    Logger::info("Engine Service Started");
}

void EngineService::stop()
{
    Logger::info("Engine Service Stopped");
}

void EngineService::startEngine()
{
    if(vehicle->isEngineRunning())
    {
        Logger::warning("Engine is already running.");
        return;
    }

    vehicle->startEngine();
    Logger::info("Engine Started");
}

void EngineService::stopEngine()
{
    if(!vehicle->isEngineRunning())
    {
        Logger::warning("Engine is already stopped.");
        return;
    }

    vehicle->stopEngine();
    Logger::info("Engine Stopped");
}