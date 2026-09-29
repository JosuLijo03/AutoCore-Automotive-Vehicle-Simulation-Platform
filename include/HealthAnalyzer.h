#ifndef HEALTHANALYZER_H
#define HEALTHANALYZER_H

#include "VehicleState.h"

class HealthAnalyzer
{
public:
    int calculateHealth(const VehicleState& vehicle) const;

    bool isSafeToDrive(const VehicleState& vehicle) const;
};

#endif