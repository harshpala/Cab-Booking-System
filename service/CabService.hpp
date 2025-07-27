#pragma once
#include <list>
#include <limits>
#include "../model/Cab.hpp"

using namespace std;


// Encapsulation
class CabService {
private:
    list<Cab> cabs;
public:
    void registerCab(const string& id, const string& driverName, const Location& loc, VehicleType vType, const string& cNum) {
        cabs.emplace_back(id, driverName, loc, vType, cNum);
    }

    Cab* findNearestAvailableCab(const Location& riderLocation, VehicleType vehicleType) {
        Cab* nearestCab = nullptr;
        double minDistance = numeric_limits<double>::max();
        for (auto it = cabs.begin(); it != cabs.end(); ++it) {
            if (it->isAvailable() && it->getVehicleType() == vehicleType) {
                double distance = it->getLocation().distanceTo(riderLocation);
                if (distance < minDistance) {
                    minDistance = distance;
                    nearestCab = &(*it);
                }
            }
        }
        return nearestCab;
    }
};