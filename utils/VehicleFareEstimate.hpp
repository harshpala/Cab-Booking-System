#pragma once
#include <iostream>
#include <iomanip>
#include "../model/enums/VehicleType.hpp"

using namespace std;


// Encapsulation
class VehicleFareEstimate {
private:
    VehicleType vehicleType;
    double estimatedFare;

public:
    VehicleFareEstimate(VehicleType vType, double fare) : vehicleType(vType), estimatedFare(fare) {}

    friend ostream& operator<<(ostream& os, const VehicleFareEstimate& estimate) {
        os << vehicleTypeToString(estimate.vehicleType) << " -> Rs " << fixed << setprecision(2) << estimate.estimatedFare;
        return os;
    }
};