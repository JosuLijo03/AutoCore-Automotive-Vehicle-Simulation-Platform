#ifndef ENGINESERVICE_H
#define ENGINESERVICE_H

#include "IService.h"
#include "VehicleState.h"
#include <string>

class EngineService : public IService
{
private:
    VehicleState* vehicle;

public:
    explicit EngineService(VehicleState* state);

    std::string getName() const override;

    void start() override;
    void stop() override;

    void startEngine();
    void stopEngine();
};

#endif