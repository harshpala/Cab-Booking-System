#pragma once
#include <string>

enum VehicleType {
    HATCHBACK,
    SEDAN,
    SUV
};

// Helper function to convert enum to string for printing
inline std::string vehicleTypeToString(VehicleType type) {
    switch (type) {
        case HATCHBACK: return "HATCHBACK";
        case SEDAN:     return "SEDAN";
        case SUV:       return "SUV";
        default:        return "UNKNOWN";
    }
}