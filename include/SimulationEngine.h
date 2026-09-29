#ifndef SIMULATIONENGINE_H
#define SIMULATIONENGINE_H

#include <QObject>
#include <QTimer>

#include "VehicleState.h"

class SimulationEngine : public QObject
{
    Q_OBJECT

private:

    VehicleState* vehicle;

    QTimer timer;

public:

    explicit SimulationEngine(VehicleState* state);

    void startSimulation();

    void stopSimulation();

private slots:

    void updateVehicle();
};

#endif