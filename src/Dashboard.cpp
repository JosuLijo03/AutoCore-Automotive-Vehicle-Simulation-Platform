#include "Dashboard.h"

#include <iostream>

using namespace std;


// Constructor


Dashboard::Dashboard(VehicleState* state)
{
    vehicle = state;
}


// Observer Update


void Dashboard::update()
{
    // Qt GUI updates automatically.
}


// Display Dashboard


void Dashboard::display(const VehicleState& vehicle)
{
    cout << "\n=============================================\n";
    cout << "           AUTOCORE EV DASHBOARD\n";
    cout << "=============================================\n";

    cout << "Vehicle Health : "
         << analyzer.calculateHealth(vehicle)
         << "/100\n\n";

   
    // Engine
    

    cout << "Vehicle        : "
         << (vehicle.isEngineRunning() ? "READY" : "OFF")
         << endl;

    
    // Doors
    

    cout << "Doors          : "
         << (vehicle.areDoorsLocked() ? "LOCKED" : "UNLOCKED")
         << endl;

    
    // Battery
    

    cout << "Battery        : "
         << vehicle.getBatteryLevel()
         << "%\n";

    
    // Charging
    

    cout << "Charging       : "
         << (vehicle.isCharging() ? "YES" : "NO")
         << endl;

    
    // Driving Mode
   

    cout << "Driving Mode   : ";

    switch(vehicle.getDrivingMode())
    {
        case DrivingMode::Parked:
            cout << "Parked";
            break;

        case DrivingMode::Manual:
            cout << "Manual";
            break;

        case DrivingMode::AutoDrive:
            cout << "Auto Drive";
            break;

        case DrivingMode::Charging:
            cout << "Charging";
            break;

        case DrivingMode::Service:
            cout << "Service";
            break;
    }

    cout << endl;

  
    // Speed
    

    cout << "Speed          : "
         << vehicle.getSpeed()
         << " km/h\n";

    
    // Distance
    

    cout << "Distance       : "
         << vehicle.getDistanceTravelled()
         << " km\n";

    
    // Range
    

    cout << "Range Left     : "
         << vehicle.getEstimatedRange()
         << " km\n";

   
    // Faults
    

    cout << "\nFaults\n";
    cout << "---------------------------------------------\n";

    auto faults = faultManager.analyze(vehicle);

    if(faults.empty())
    {
        cout << "No Faults Detected\n";
    }
    else
    {
        for(const auto& fault : faults)
        {
            cout << "- " << fault.message << endl;
        }
    }

    cout << "=============================================\n";
}