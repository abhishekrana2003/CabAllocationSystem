#include "Cab.h"
#include <iostream>

Cab::Cab(int id, const Location &currentLoc) 
    : currentLocation(currentLoc), cabId(id) {}

Cab::Cab(int id, const Location &currentLoc, const std::string &driver) 
    : currentLocation(currentLoc), cabId(id), driverName(driver) {}

const Location &Cab::getCurrentLocation() const
{
    return currentLocation;
}

void Cab::setCurrentLocation(const Location &location)
{
    currentLocation = location;
}

int Cab::getCabId() const
{
    return cabId;
}

bool Cab::isCabFree() const
{
    return isFree;
}

void Cab::bookCab()
{
    isFree = false;
}

void Cab::unbookCab()
{
    isFree = true;
}

const std::string &Cab::getDriverName() const
{
    return driverName;  
}

void Cab::setDriverName(const std::string &name)
{
    driverName = name;  
}

void Cab::updateLocation(const Location &newLocation)
{
    std::cout << "Cab " << cabId << " is now at " << newLocation.getLatitude() << ", " << newLocation.getLongitude() << std::endl;
    currentLocation = newLocation;
    std::cout << "Cab " << cabId << " is now at " << currentLocation.getLatitude() << ", " << currentLocation.getLongitude() << std::endl;
}
