#include "FaultManager.h"

std::vector<Fault> FaultManager::analyze(const VehicleState& vehicle) const
{
    std::vector<Fault> faults;

    // Battery
  

    if (vehicle.getBatteryLevel() <= 10)
    {
        faults.push_back(
        {
            "Battery critically low",
            FaultSeverity::CRITICAL
        });
    }
    else if (vehicle.getBatteryLevel() <= 20)
    {
        faults.push_back(
        {
            "Battery low",
            FaultSeverity::HIGH
        });
    }

  
    // Overspeed
   

    if (vehicle.getSpeed() > 140)
    {
        faults.push_back(
        {
            "Overspeed detected",
            FaultSeverity::MEDIUM
        });
    }

  
    // Doors
   
    if (!vehicle.areDoorsLocked())
    {
        faults.push_back(
        {
            "Doors are unlocked",
            FaultSeverity::LOW
        });
    }

    
    // Tyres
    

    if (!vehicle.getFrontLeftTyre().healthy)
    {
        faults.push_back(
        {
            "Front Left Tyre Fault",
            FaultSeverity::HIGH
        });
    }

    if (!vehicle.getFrontRightTyre().healthy)
    {
        faults.push_back(
        {
            "Front Right Tyre Fault",
            FaultSeverity::HIGH
        });
    }

    if (!vehicle.getRearLeftTyre().healthy)
    {
        faults.push_back(
        {
            "Rear Left Tyre Fault",
            FaultSeverity::HIGH
        });
    }

    if (!vehicle.getRearRightTyre().healthy)
    {
        faults.push_back(
        {
            "Rear Right Tyre Fault",
            FaultSeverity::HIGH
        });
    }

   
    // Charging
    
    if (vehicle.isCharging() &&
        vehicle.isEngineRunning())
    {
        faults.push_back(
        {
            "Vehicle cannot drive while charging",
            FaultSeverity::CRITICAL
        });
    }

    return faults;
}