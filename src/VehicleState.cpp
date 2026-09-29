#include "VehicleState.h"

#include <algorithm>


// Constructor


VehicleState::VehicleState()
{
    // Engine
    engineRunning = false;

    // Doors
    doorsLocked = false;

    // Battery
    batteryLevel = 100;
    charging = false;

    // Driving
    speed = 0;
    distanceTravelled = 0.0f;
    estimatedRange = 400;
    tripTimeSeconds = 0;

    // Vehicle
    vehicleHealth = 100;
    drivingMode = DrivingMode::Parked;
}


// Observer Pattern

void VehicleState::attach(IObserver* observer)
{
    std::lock_guard<std::mutex> lock(stateMutex);
    observers.push_back(observer);
}

void VehicleState::detach(IObserver* observer)
{
    std::lock_guard<std::mutex> lock(stateMutex);

    observers.erase(
        std::remove(observers.begin(), observers.end(), observer),
        observers.end());
}

void VehicleState::notify()
{
    for (IObserver* observer : observers)
    {
        observer->update();
    }
}


// Engine

void VehicleState::startEngine()
{
    std::lock_guard<std::mutex> lock(stateMutex);

    engineRunning = true;

    notify();
}

void VehicleState::stopEngine()
{
    std::lock_guard<std::mutex> lock(stateMutex);

    engineRunning = false;
    speed = 0;

    notify();
}

bool VehicleState::isEngineRunning() const
{
    std::lock_guard<std::mutex> lock(stateMutex);

    return engineRunning;
}


// Doors

void VehicleState::lockDoors()
{
    std::lock_guard<std::mutex> lock(stateMutex);

    doorsLocked = true;

    notify();
}

void VehicleState::unlockDoors()
{
    std::lock_guard<std::mutex> lock(stateMutex);

    doorsLocked = false;

    notify();
}

bool VehicleState::areDoorsLocked() const
{
    std::lock_guard<std::mutex> lock(stateMutex);

    return doorsLocked;
}


// Battery


void VehicleState::setBatteryLevel(int level)
{
    std::lock_guard<std::mutex> lock(stateMutex);

    if(level < 0)
        level = 0;

    if(level > 100)
        level = 100;

    batteryLevel = level;

    notify();
}

int VehicleState::getBatteryLevel() const
{
    std::lock_guard<std::mutex> lock(stateMutex);

    return batteryLevel;
}

void VehicleState::setCharging(bool value)
{
    std::lock_guard<std::mutex> lock(stateMutex);

    charging = value;

    notify();
}

bool VehicleState::isCharging() const
{
    std::lock_guard<std::mutex> lock(stateMutex);

    return charging;
}


// Speed
//-------------------------------------------------

void VehicleState::setSpeed(int value)
{
    std::lock_guard<std::mutex> lock(stateMutex);

    speed = value;

    notify();
}

int VehicleState::getSpeed() const
{
    std::lock_guard<std::mutex> lock(stateMutex);

    return speed;
}


// Distance


void VehicleState::setDistanceTravelled(float distance)
{
    std::lock_guard<std::mutex> lock(stateMutex);

    distanceTravelled = distance;

    notify();
}

float VehicleState::getDistanceTravelled() const
{
    std::lock_guard<std::mutex> lock(stateMutex);

    return distanceTravelled;
}


// Estimated Range


void VehicleState::setEstimatedRange(int range)
{
    std::lock_guard<std::mutex> lock(stateMutex);

    estimatedRange = range;

    notify();
}

int VehicleState::getEstimatedRange() const
{
    std::lock_guard<std::mutex> lock(stateMutex);

    return estimatedRange;
}


// Trip Time


void VehicleState::setTripTime(int seconds)
{
    std::lock_guard<std::mutex> lock(stateMutex);

    tripTimeSeconds = seconds;

    notify();
}

int VehicleState::getTripTime() const
{
    std::lock_guard<std::mutex> lock(stateMutex);

    return tripTimeSeconds;
}


// Driving Mode

void VehicleState::setDrivingMode(DrivingMode mode)
{
    std::lock_guard<std::mutex> lock(stateMutex);

    drivingMode = mode;

    notify();
}

DrivingMode VehicleState::getDrivingMode() const
{
    std::lock_guard<std::mutex> lock(stateMutex);

    return drivingMode;
}


// Vehicle Health


void VehicleState::setVehicleHealth(int health)
{
    std::lock_guard<std::mutex> lock(stateMutex);

    if(health < 0)
        health = 0;

    if(health > 100)
        health = 100;

    vehicleHealth = health;

    notify();
}

int VehicleState::getVehicleHealth() const
{
    std::lock_guard<std::mutex> lock(stateMutex);

    return vehicleHealth;
}


// Tyres

const Tyre& VehicleState::getFrontLeftTyre() const
{
    return frontLeft;
}

const Tyre& VehicleState::getFrontRightTyre() const
{
    return frontRight;
}

const Tyre& VehicleState::getRearLeftTyre() const
{
    return rearLeft;
}

const Tyre& VehicleState::getRearRightTyre() const
{
    return rearRight;
}