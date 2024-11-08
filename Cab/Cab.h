#ifndef CAB_H
#define CAB_H

#include "./../Location/Location.h"
#include <vector>
#include <string> 
class Cab
{
private:
    int cabId;
    Location currentLocation;
    bool isFree = true;      
    std::string driverName;  

public:
    Cab(int id, const Location &currentLoc);
    Cab(int id, const Location &currentLoc, const std::string &driver);

    int getCabId() const;
    bool isCabFree() const;
    const std::string &getDriverName() const;
    void setDriverName(const std::string &name);
    void bookCab();     
    void unbookCab();  

    const Location &getCurrentLocation() const;
    void setCurrentLocation(const Location &loc);

    void updateLocation(const Location &newLocation);
};

#endif
