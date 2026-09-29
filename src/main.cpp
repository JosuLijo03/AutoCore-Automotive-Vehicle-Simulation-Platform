#include <iostream>
#include <memory>
#include <limits>

#include "ServiceManager.h"

#include "EngineService.h"
#include "DoorService.h"
#include "BatteryService.h"
#include "ClimateService.h"

#include "VehicleState.h"
#include "Dashboard.h"
#include "SensorManager.h"

#include "ServiceFactory.h"
#include "DatabaseManager.h"

using namespace std;

int main()
{
    VehicleState vehicle;

    DatabaseManager database;

    if (!database.connect("autocore.db"))
        return 1;

    database.createTables();

    ServiceManager manager;

    auto engine = ServiceFactory::createEngineService(&vehicle);
    auto door = ServiceFactory::createDoorService(&vehicle);
    auto battery = ServiceFactory::createBatteryService(&vehicle);
    auto climate = ServiceFactory::createClimateService();

    manager.registerService(engine);
    manager.registerService(door);
    manager.registerService(battery);
    manager.registerService(climate);

    Dashboard dashboard(&vehicle);
    vehicle.attach(&dashboard);

    SensorManager sensors(&vehicle);
    sensors.start();

    int choice;

    while (true)
    {
        system("cls");

        dashboard.display(vehicle);

        cout << "\n";
cout << "1. Start Engine\n";
cout << "2. Stop Engine\n";
cout << "3. Lock Doors\n";
cout << "4. Unlock Doors\n";
cout << "5. Charge Battery\n";
cout << "6. Show Vehicle History\n";
cout << "7. Exit\n";

        

        cout << "\nChoice : ";
       if (!(cin >> choice))
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "\nPlease enter a valid number!\n";
    system("pause");
    continue;
}



switch (choice)
{
case 1:
{
    if (vehicle.isEngineRunning())
    {
        cout << "\nEngine is already running!\n";
    }
    else
    {
        engine->startEngine();
        cout << "\nEngine Started Successfully!\n";
    }

    cout << "Engine State : "
         << (vehicle.isEngineRunning() ? "ON" : "OFF") << endl;
    break;
}

case 2:
{
    if (!vehicle.isEngineRunning())
    {
        cout << "\nEngine is already stopped!\n";
    }
    else
    {
        engine->stopEngine();
        cout << "\nEngine Stopped Successfully!\n";
    }

    cout << "Engine State : "
         << (vehicle.isEngineRunning() ? "ON" : "OFF") << endl;
    break;
}

case 3:
{
    if (vehicle.areDoorsLocked())
    {
        cout << "\nDoors are already locked!\n";
    }
    else
    {
        door->lockDoors();
        cout << "\nDoors Locked Successfully!\n";
    }

    cout << "Door State : "
         << (vehicle.areDoorsLocked() ? "LOCKED" : "UNLOCKED") << endl;
    break;
}

case 4:
{
    if (!vehicle.areDoorsLocked())
    {
        cout << "\nDoors are already unlocked!\n";
    }
    else
    {
        door->unlockDoors();
        cout << "\nDoors Unlocked Successfully!\n";
    }

    cout << "Door State : "
         << (vehicle.areDoorsLocked() ? "LOCKED" : "UNLOCKED") << endl;
    break;
}

case 5:
{
    if (vehicle.getBatteryLevel() >= 100)
    {
        cout << "\nBattery is already fully charged!\n";
    }
    else
    {
        battery->charge(10);
        cout << "\nBattery Charged Successfully!\n";
    }

    cout << "Battery Level : "
         << vehicle.getBatteryLevel() << "%" << endl;
    break;
}

case 6:
{
    database.showVehicleHistory();
    break;
}

    case 7:
    {
        sensors.stop();

        database.saveVehicleState(vehicle);
        database.close();

        cout << "\nVehicle state saved successfully.\n";
        cout << "Exiting AutoCore...\n";

        return 0;
    }

    default:
    {
        cout << "\nInvalid Choice!\n";
        break;
    }
}

cout << "\nPress Enter to continue...";
cin.ignore(numeric_limits<streamsize>::max(), '\n');
cin.get();

}   // while(true)

return 0;
}