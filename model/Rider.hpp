#pragma once
#include <string>
#include "Location.hpp"

using namespace std;


// Encapsulation
class Rider {
private:
    string id;
    string name;
    Location currentLocation;

public:
    Rider(const string& id = "", const string& name = "") : id(id), name(name) {}

    void updateLocation(const Location& location) {
        this->currentLocation = location;
    }

    Location getCurrentLocation() const { return currentLocation; }
    string getName() const { return name; }
    string getId() const { return id; }
};