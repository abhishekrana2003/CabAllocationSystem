#include "CabSearch.h"
#include <cmath>
#include <queue>
#include <vector>

EmployeeCabSearch::EmployeeCabSearch(const Location &empLoc, CabAllocationSystem &cabAllocSys)
    : employeeLocation(empLoc), cabAllocationSystem(cabAllocSys) {}


double EmployeeCabSearch::calculateDistance(const Location &loc1, const Location &loc2) const
{
    double lat1 = loc1.getLatitude();
    double lon1 = loc1.getLongitude();
    double lat2 = loc2.getLatitude();
    double lon2 = loc2.getLongitude();

  
    return std::sqrt((lat2 - lat1) * (lat2 - lat1) + (lon2 - lon1) * (lon2 - lon1));
}


std::vector<Cab>& EmployeeCabSearch::getAllCabs()
{
    return cabAllocationSystem.getAllCabs();
}

std::vector<Cab> EmployeeCabSearch::suggestNearbyCabs()
{
    std::vector<Cab> nearbyCabs;
   
    std::priority_queue<std::pair<double, Cab>, std::vector<std::pair<double, Cab>>, std::greater<>> cabQueue;


    const double thresholdDistance = 100.0;

    for (const auto &cab : getAllCabs())
    {
       
        if (!cab.isCabFree()) {
            continue;
        }

        double distance = calculateDistance(employeeLocation, cab.getCurrentLocation());

        if (distance < thresholdDistance) {
            cabQueue.push({distance, cab});
        }
    }

    
    while (!cabQueue.empty())
    {
        nearbyCabs.push_back(cabQueue.top().second);
        cabQueue.pop();
    }

    return nearbyCabs;
}