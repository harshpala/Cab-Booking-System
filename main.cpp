#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <thread>
#include <chrono>

#include "service/RiderService.hpp"
#include "service/DriverService.hpp"
#include "service/CabService.hpp"
#include "service/BookingService.hpp"
#include "pricing/SurgePricingStrategy.hpp"

using namespace std;

int main() {
    RiderService riderService;
    DriverService driverService;
    CabService cabService;
    
    // For demo, set demand = 5 to trigger surge
    SurgePricingStrategy pricingStrategy(5);
    BookingService bookingService(cabService, pricingStrategy);

    // Register rider
    Rider* rider = riderService.registerRider("r1", "Alice");
    rider->updateLocation(Location(10, 10));
    Location destination(20, 20);

    // Register drivers & cabs
    driverService.registerDriver("d1", "DriverOne");
    cabService.registerCab("c1", "DriverOne", Location(12, 10), VehicleType::SEDAN, "TS09AB1234");
    driverService.registerDriver("d2", "DriverTwo");
    cabService.registerCab("c2", "DriverTwo", Location(11, 11), VehicleType::HATCHBACK, "TS08XY5678");

    // Step 1: Show fare estimates
    cout << "\n📋 Fare Estimates:" << endl;
    auto estimates = bookingService.showAvailableVehicleTypes(rider->getCurrentLocation(), destination);
    for (const auto& e : estimates) {
        cout << " - " << e << endl;
    }

    // Step 2: Simulate rider selecting a vehicle type
    VehicleType chosenType = VehicleType::SEDAN;
    Booking booking;
    try {
        booking = bookingService.bookCab(rider, chosenType, destination);
    } catch (const runtime_error& e) {
        cerr << "❌ Booking failed: " << e.what() << endl;
        return 1;
    }

    // Step 3: Show OTP to user
    cout << "\n🔐 Share this OTP with driver to start the ride: " << booking.getOtp() << endl;

    // Step 4: Driver enters OTP with max 3 attempts
    int maxAttempts = 3;
    bool rideStarted = false;
    string enteredOtp;
    for (int i = 1; i <= maxAttempts; ++i) {
        cout << "🚘 Driver: Please enter OTP to start ride (Attempt " << i << " of " << maxAttempts << "): ";
        cin >> enteredOtp;
        bookingService.driverStartRide(booking, enteredOtp);
        if (booking.getStatus() == BookingStatus::STARTED) {
            rideStarted = true;
            break;
        }
    }

    if (!rideStarted) {
        cout << "❌ Too many failed attempts. Ride cannot be started." << endl;
        return 1;
    }

    // Step 5: Simulate ride in progress
    cout << "🚕 Ride is in progress..." << endl;
    for (int i = 1; i <= 5; ++i) {
        cout << "⏳ Traveling";
        for (int j = 0; j < i; ++j) cout << ".";
        cout << " (" << i << " sec)" << endl;
        this_thread::sleep_for(chrono::seconds(1));
    }

    // Step 6: Driver ends ride
    bookingService.driverEndRide(booking);

    // Step 7: Summary
    cout << "\n🧾 Final Ride Summary:" << endl;
    booking.printSummary();
    
    return 0;
}