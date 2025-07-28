#pragma once
#include "PricingStrategy.hpp"

// Inheritance & Polymorphism
class VehicleTypePricingStrategy : public PricingStrategy {
public:
    double calculateFare(const Location& from, const Location& to, VehicleType vehicleType) const override {
        double baseRatePerKm;
        switch (vehicleType) {
            case HATCHBACK: baseRatePerKm = 8.0; break;
            case SEDAN:     baseRatePerKm = 10.0; break;
            case SUV:       baseRatePerKm = 12.5; break;
            default:        baseRatePerKm = 10.0; break;
        }
        double distance = from.distanceTo(to);
        return baseRatePerKm * distance;
    }
};