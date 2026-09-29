#ifndef BATTERYSERVICE_H
#define BATTERYSERVICE_H

#include "IService.h"
#include "VehicleState.h"
#include <string>

class BatteryService : public IService
{
private:
    VehicleState* vehicle;

public:
    explicit BatteryService(VehicleState* state);

    std::string getName() const override;

    void start() override;
    void stop() override;

    void charge(int amount);
    void discharge(int amount);
};

#endif