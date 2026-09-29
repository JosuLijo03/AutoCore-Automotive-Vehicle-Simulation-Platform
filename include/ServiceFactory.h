#ifndef SERVICEFACTORY_H
#define SERVICEFACTORY_H

#include <memory>

#include "EngineService.h"
#include "DoorService.h"
#include "BatteryService.h"
#include "ClimateService.h"

class ServiceFactory
{
public:
    static std::shared_ptr<EngineService> createEngineService(VehicleState* vehicle);

    static std::shared_ptr<DoorService> createDoorService(VehicleState* vehicle);

    static std::shared_ptr<BatteryService> createBatteryService(VehicleState* vehicle);

    static std::shared_ptr<ClimateService> createClimateService();
};

#endif