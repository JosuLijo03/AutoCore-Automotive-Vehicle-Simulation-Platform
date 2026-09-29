#ifndef DASHBOARD_H
#define DASHBOARD_H

#include "VehicleState.h"
#include "HealthAnalyzer.h"
#include "FaultManager.h"
#include "IObserver.h"

class Dashboard : public IObserver
{
private:
    VehicleState* vehicle;

    HealthAnalyzer analyzer;
    FaultManager faultManager;

public:
    explicit Dashboard(VehicleState* state);

    void display(const VehicleState& vehicle);

    void update() override;
};

#endif