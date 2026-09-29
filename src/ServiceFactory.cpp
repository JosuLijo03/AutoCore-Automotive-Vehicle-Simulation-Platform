#include "ServiceFactory.h"

std::shared_ptr<EngineService>
ServiceFactory::createEngineService(VehicleState* vehicle)
{
    return std::make_shared<EngineService>(vehicle);
}

std::shared_ptr<DoorService>
ServiceFactory::createDoorService(VehicleState* vehicle)
{
    return std::make_shared<DoorService>(vehicle);
}

std::shared_ptr<BatteryService>
ServiceFactory::createBatteryService(VehicleState* vehicle)
{
    return std::make_shared<BatteryService>(vehicle);
}

std::shared_ptr<ClimateService>
ServiceFactory::createClimateService()
{
    return std::make_shared<ClimateService>();
}