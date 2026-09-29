#ifndef VEHICLESTATUSANALYZER_H
#define VEHICLESTATUSANALYZER_H

#include <string>
#include <vector>

#include "VehicleState.h"

class VehicleStatusAnalyzer
{
private:

    VehicleState* vehicle;

public:

    explicit VehicleStatusAnalyzer(VehicleState* state);

    
    // Vehicle Readiness
    

    bool isVehicleReady();

    
    // Status
    

    std::string getOverallHealth();

    std::string getBatteryStatus();

    std::string getChargingStatus();

    std::string getDrivingModeStatus();

    std::string getDoorStatus();

    std::string getTyreStatus();

    
    // Warnings
    

    std::vector<std::string> getWarnings();

    
    // Report
    

    std::string generateStatusReport();
};

#endif