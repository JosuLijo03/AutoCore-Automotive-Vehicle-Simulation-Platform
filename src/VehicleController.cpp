#include "VehicleController.h"

VehicleController::VehicleController(
    VehicleState* state,
    EngineService* engine,
    DoorService* door,
    BatteryService* battery,
    ClimateService* climate)
{
    vehicle = state;
    engineService = engine;
    doorService = door;
    batteryService = battery;
    climateService = climate;
}

void VehicleController::startEngine()
{
    engineService->startEngine();
}

void VehicleController::stopEngine()
{
    engineService->stopEngine();
}

void VehicleController::lockDoors()
{
    doorService->lockDoors();
}

void VehicleController::unlockDoors()
{
    doorService->unlockDoors();
}

void VehicleController::chargeBattery(int amount)
{
    batteryService->charge(amount);
}

VehicleState& VehicleController::getVehicleState()
{
    return *vehicle;
}