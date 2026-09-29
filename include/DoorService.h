#ifndef DOORSERVICE_H
#define DOORSERVICE_H

#include "IService.h"
#include "VehicleState.h"
#include <string>

class DoorService : public IService
{
private:
    VehicleState* vehicle;

public:
    explicit DoorService(VehicleState* state);

    std::string getName() const override;

    void start() override;
    void stop() override;

    void lockDoors();
    void unlockDoors();
};

#endif