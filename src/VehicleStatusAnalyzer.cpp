#include "VehicleStatusAnalyzer.h"

#include <sstream>

VehicleStatusAnalyzer::VehicleStatusAnalyzer(VehicleState* state)
{
    vehicle = state;
}


// Vehicle Ready


bool VehicleStatusAnalyzer::isVehicleReady()
{
    return vehicle->getBatteryLevel() > 20;
}


// Battery


std::string VehicleStatusAnalyzer::getBatteryStatus()
{
    int battery = vehicle->getBatteryLevel();

    if (battery >= 70)
        return "Healthy";

    if (battery >= 30)
        return "Low";

    return "Critical";
}


// Charging


std::string VehicleStatusAnalyzer::getChargingStatus()
{
    return vehicle->isCharging() ? "Charging" : "Not Charging";
}


// Driving Mode


std::string VehicleStatusAnalyzer::getDrivingModeStatus()
{
    switch(vehicle->getDrivingMode())
    {
        case DrivingMode::Parked:
            return "Parked";

        case DrivingMode::Manual:
            return "Manual";

        case DrivingMode::AutoDrive:
            return "Auto Drive";

        case DrivingMode::Charging:
            return "Charging";

        case DrivingMode::Service:
            return "Service";
    }

    return "Unknown";
}


// Doors


std::string VehicleStatusAnalyzer::getDoorStatus()
{
    return vehicle->areDoorsLocked() ? "Locked" : "Unlocked";
}


// Tyres


std::string VehicleStatusAnalyzer::getTyreStatus()
{
    if (!vehicle->getFrontLeftTyre().healthy)
        return "Front Left Fault";

    if (!vehicle->getFrontRightTyre().healthy)
        return "Front Right Fault";

    if (!vehicle->getRearLeftTyre().healthy)
        return "Rear Left Fault";

    if (!vehicle->getRearRightTyre().healthy)
        return "Rear Right Fault";

    return "Healthy";
}


// Overall Health


std::string VehicleStatusAnalyzer::getOverallHealth()
{
    if (vehicle->getBatteryLevel() < 20)
        return "WARNING";

    if (getTyreStatus() != "Healthy")
        return "WARNING";

    return "GOOD";
}


// Warnings


std::vector<std::string> VehicleStatusAnalyzer::getWarnings()
{
    std::vector<std::string> warnings;

    if (vehicle->getBatteryLevel() < 20)
        warnings.push_back("Battery Critical");

    if (!vehicle->areDoorsLocked())
        warnings.push_back("Doors Unlocked");

    if (getTyreStatus() != "Healthy")
        warnings.push_back(getTyreStatus());

    return warnings;
}


// Status Report


std::string VehicleStatusAnalyzer::generateStatusReport()
{
    std::stringstream report;

    report << "========== CURRENT VEHICLE STATUS ==========\n\n";

    report << "Vehicle Health : "
           << getOverallHealth()
           << "\n";

    report << "Vehicle : "
           << (vehicle->isEngineRunning() ? "READY" : "OFF")
           << "\n";

    report << "Driving Mode : "
           << getDrivingModeStatus()
           << "\n";

    report << "Battery : "
           << vehicle->getBatteryLevel()
           << "% ("
           << getBatteryStatus()
           << ")\n";

    report << "Charging : "
           << getChargingStatus()
           << "\n";

    report << "Estimated Range : "
           << vehicle->getEstimatedRange()
           << " km\n";

    report << "Speed : "
           << vehicle->getSpeed()
           << " km/h\n";

    report << "Distance : "
           << vehicle->getDistanceTravelled()
           << " km\n";

    report << "Doors : "
           << getDoorStatus()
           << "\n";

    report << "Tyres : "
           << getTyreStatus()
           << "\n";

    report << "\nWarnings\n";

    auto warnings = getWarnings();

    if (warnings.empty())
    {
        report << "None\n";
    }
    else
    {
        for (const auto& warning : warnings)
        {
            report << "- " << warning << "\n";
        }
    }

    return report.str();
}