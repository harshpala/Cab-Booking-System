#pragma once
#include <string>
#include <chrono>
#include <random>
#include <iomanip>
#include <ctime>
#include "Rider.hpp"
#include "Cab.hpp"
#include "enums/BookingStatus.hpp"
#include "../pricing/PricingStrategy.hpp"

using namespace std;


// Encapsulation
class Booking {
private:
    Rider* rider;
    Cab* cab;
    Location pickupLocation;
    Location destination;
    BookingStatus status;
    chrono::system_clock::time_point startTime;
    chrono::system_clock::time_point endTime;
    double fare;
    string otp;

    string generateOtp() {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> distrib(1000, 9999);
        return to_string(distrib(gen));
    }

public:
    Booking(Rider* r, Cab* c, const Location& dest, const PricingStrategy& strategy)
        : rider(r), cab(c), destination(dest), status(BookingStatus::CREATED) {
        if (rider) this->pickupLocation = rider->getCurrentLocation();
        if (cab) this->fare = strategy.calculateFare(pickupLocation, destination, cab->getVehicleType());
        this->otp = generateOtp();
    }
    
    Booking() : rider(nullptr), cab(nullptr), status(BookingStatus::CREATED) {}

    void setStatus(BookingStatus newStatus) { this->status = newStatus; }
    void setStartTime(const chrono::system_clock::time_point& time) { this->startTime = time; }
    void setEndTime(const chrono::system_clock::time_point& time) { this->endTime = time; }
    void setFare(double newFare) { this->fare = newFare; }

    Rider* getRider() const { return rider; }
    Cab* getCab() const { return cab; }
    Location getPickupLocation() const { return pickupLocation; }
    Location getDestination() const { return destination; }
    BookingStatus getStatus() const { return status; }
    string getOtp() const { return otp; }

    void printSummary() const {
        if (!rider || !cab) return;
        auto to_time_t = [](const auto& tp) { return chrono::system_clock::to_time_t(tp); };
        time_t start_c_time = to_time_t(startTime);
        time_t end_c_time = to_time_t(endTime);
        
        cout << "Rider: " << rider->getName() << endl;
        cout << "Driver: " << cab->getDriverName() << endl;
        cout << "Car: " << cab->getCarNumber() << " (" << vehicleTypeToString(cab->getVehicleType()) << ")" << endl;
        cout << "Pickup: " << pickupLocation << " -> Drop: " << destination << endl;
        cout << "Fare: Rs " << fixed << setprecision(2) << fare << endl;
        cout << "Start Time: " << put_time(localtime(&start_c_time), "%F %T") << endl;
        cout << "End Time: " << put_time(localtime(&end_c_time), "%F %T") << endl;
    }
};