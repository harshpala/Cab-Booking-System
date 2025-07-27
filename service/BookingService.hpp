#pragma once
#include <vector>
#include <stdexcept>
#include <cmath>
#include "CabService.hpp"
#include "../pricing/PricingStrategy.hpp"
#include "../model/Booking.hpp"
#include "../utils/VehicleFareEstimate.hpp"

using namespace std;


// Encapsulation
class BookingService {
private:
    CabService& cabService;
    const PricingStrategy& pricingStrategy;

public:
    BookingService(CabService& cabSvc, const PricingStrategy& pricing)
        : cabService(cabSvc), pricingStrategy(pricing) {}

    vector<VehicleFareEstimate> showAvailableVehicleTypes(const Location& from, const Location& to) {
        vector<VehicleFareEstimate> estimates;
        vector<VehicleType> allTypes = {VehicleType::HATCHBACK, VehicleType::SEDAN, VehicleType::SUV};
        for (VehicleType type : allTypes) {
            double fare = pricingStrategy.calculateFare(from, to, type);
            estimates.emplace_back(type, round(fare * 100.0) / 100.0);
        }
        return estimates;
    }

    Booking bookCab(Rider* rider, VehicleType vehicleType, const Location& destination) {
        if (!rider) throw runtime_error("Rider cannot be null.");
        Cab* cab = cabService.findNearestAvailableCab(rider->getCurrentLocation(), vehicleType);
        if (!cab) throw runtime_error("No available cab of type: " + vehicleTypeToString(vehicleType));
        cab->assignToRide();
        return Booking(rider, cab, destination, pricingStrategy);
    }

    void driverStartRide(Booking& booking, const string& enteredOtp) {
        if (booking.getOtp() != enteredOtp) {
            cout << "❌ Invalid OTP! Ride cannot start." << endl;
            return;
        }
        booking.setStatus(BookingStatus::STARTED);
        booking.setStartTime(chrono::system_clock::now());
        cout << "✅ OTP verified. Ride started." << endl;
    }

    void driverEndRide(Booking& booking) {
        Cab* cab = booking.getCab();
        if (!cab || booking.getStatus() != BookingStatus::STARTED) {
            cout << "❌ Cannot end ride. Ride hasn't started or is invalid." << endl;
            return;
        }
        booking.setStatus(BookingStatus::ENDED);
        booking.setEndTime(chrono::system_clock::now());
        double finalFare = pricingStrategy.calculateFare(
            booking.getPickupLocation(), booking.getDestination(), cab->getVehicleType());
        booking.setFare(round(finalFare * 100.0) / 100.0);
        cab->markAvailable();
        cout << "🏁 Ride ended by driver." << endl;
    }
};