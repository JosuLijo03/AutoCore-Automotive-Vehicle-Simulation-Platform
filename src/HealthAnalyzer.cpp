#include "HealthAnalyzer.h"

int HealthAnalyzer::calculateHealth(const VehicleState& vehicle) const
{
    int score = 100;

   
    // Battery
    

    int battery = vehicle.getBatteryLevel();

    if (battery < 80)
        score -= (80 - battery) / 2;

    if (battery < 20)
        score -= 15;

  
    // Doors
   

    if (!vehicle.areDoorsLocked())
        score -= 5;

    
    // Speed
    

    if (vehicle.getSpeed() > 120)
        score -= 5;

   
    // Tyres
   

    if (!vehicle.getFrontLeftTyre().healthy)
        score -= 5;

    if (!vehicle.getFrontRightTyre().healthy)
        score -= 5;

    if (!vehicle.getRearLeftTyre().healthy)
        score -= 5;

    if (!vehicle.getRearRightTyre().healthy)
        score -= 5;

    
    // Clamp
    

    if (score < 0)
        score = 0;

    if (score > 100)
        score = 100;

    return score;
}

bool HealthAnalyzer::isSafeToDrive(const VehicleState& vehicle) const
{
    return calculateHealth(vehicle) >= 70;
}