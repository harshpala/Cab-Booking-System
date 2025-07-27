#pragma once
#include "../model/Location.hpp"
#include "../model/enums/VehicleType.hpp"

// Abstraction & Polymorphism: Defines a contract for all pricing strategies.
class PricingStrategy {
public:
    virtual ~PricingStrategy() = default;
    virtual double calculateFare(const Location& from, const Location& to, VehicleType vehicleType) const = 0;
};