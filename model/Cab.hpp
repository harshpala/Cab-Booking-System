#pragma once
#include <string>
#include "Location.hpp"
#include "enums/VehicleType.hpp"

using namespace std;


// Encapsulation
class Cab {
private:
    string id;
    string driverName;
    Location location;
    VehicleType vehicleType;
    string carNumber;
    bool available;

public:
    Cab(const string& id, const string& driverName, const Location& loc, VehicleType vType, const string& cNum)
        : id(id), driverName(driverName), location(loc), vehicleType(vType), carNumber(cNum), available(true) {}

    bool isAvailable() const { return available; }
    void assignToRide() { this->available = false; }
    void markAvailable() { this->available = true; }

    Location getLocation() const { return location; }
    string getDriverName() const { return driverName; }
    VehicleType getVehicleType() const { return vehicleType; }
    string getCarNumber() const { return carNumber; }
    string getId() const { return id; }
};