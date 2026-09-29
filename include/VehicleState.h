#ifndef VEHICLESTATE_H
#define VEHICLESTATE_H

#include <vector>
#include <mutex>

#include "ISubject.h"
#include "IObserver.h"
#include "DrivingMode.h"
#include "Tyre.h"

class VehicleState : public ISubject
{
private:

    
     //Engine
    
    bool engineRunning;

    
    // Doors
    
    bool doorsLocked;

    
    // Battery
    
    int batteryLevel;
    bool charging;

    
    // Fuel
    
    int fuelLevel;

    
    // Driving
    
    int speed;
    float distanceTravelled;
    int estimatedRange;
    int tripTimeSeconds;

    
    // Vehicle
    
    int vehicleHealth;
    DrivingMode drivingMode;

    
    // Tyres
    
    Tyre frontLeft;
    Tyre frontRight;
    Tyre rearLeft;
    Tyre rearRight;

    
    // Observer Pattern
    
    std::vector<IObserver*> observers;
    mutable std::mutex stateMutex;

public:

    VehicleState();

    
    // Engine
    

    void startEngine();
    void stopEngine();
    bool isEngineRunning() const;

    
    // Doors
    

    void lockDoors();
    void unlockDoors();
    bool areDoorsLocked() const;

    
    // Battery
    

    void setBatteryLevel(int level);
    int getBatteryLevel() const;

    void setCharging(bool value);
    bool isCharging() const;

    
    // Fuel
    

    void setFuelLevel(int level);
    int getFuelLevel() const;

    
    // Speed
    

    void setSpeed(int value);
    int getSpeed() const;

    
    // Distance


    void setDistanceTravelled(float distance);
    float getDistanceTravelled() const;

    
    // Estimated Range
    

    void setEstimatedRange(int range);
    int getEstimatedRange() const;

    
    // Trip Time
    

    void setTripTime(int seconds);
    int getTripTime() const;

    
    // Driving Mode
    

    void setDrivingMode(DrivingMode mode);
    DrivingMode getDrivingMode() const;

    
    // Vehicle Health
    

    void setVehicleHealth(int health);
    int getVehicleHealth() const;

    
    // Tyres


    const Tyre& getFrontLeftTyre() const;
const Tyre& getFrontRightTyre() const;
const Tyre& getRearLeftTyre() const;
const Tyre& getRearRightTyre() const;
    
    // Observer Pattern
    

    void attach(IObserver* observer) override;
    void detach(IObserver* observer) override;
    void notify() override;
};

#endif