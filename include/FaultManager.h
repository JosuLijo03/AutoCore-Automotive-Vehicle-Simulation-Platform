#ifndef FAULTMANAGER_H
#define FAULTMANAGER_H

#include <string>
#include <vector>
#include "VehicleState.h"

enum class FaultSeverity
{
    LOW,
    MEDIUM,
    HIGH,
    CRITICAL
};

struct Fault
{
    std::string message;
    FaultSeverity severity;
};

class FaultManager
{
public:
    std::vector<Fault> analyze(const VehicleState& vehicle) const;
};

#endif