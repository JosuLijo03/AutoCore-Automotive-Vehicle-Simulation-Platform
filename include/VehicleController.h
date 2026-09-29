#ifndef VEHICLECONTROLLER_H
#define VEHICLECONTROLLER_H

#include "VehicleState.h"
#include "EngineService.h"
#include "DoorService.h"
#include "BatteryService.h"
#include "ClimateService.h"

class VehicleController
{
private:
    VehicleState* vehicle;

    EngineService* engineService;
    DoorService* doorService;
    BatteryService* batteryService;
    ClimateService* climateService;

public:
    VehicleController(
        VehicleState* state,
        EngineService* engine,
        DoorService* door,
        BatteryService* battery,
        ClimateService* climate);

    // Engine
    void startEngine();
    void stopEngine();

    // Doors
    void lockDoors();
    void unlockDoors();

    // Battery
    void chargeBattery(int amount);

    // Access Vehicle State
    VehicleState& getVehicleState();
};

#endif